#pragma once
typedef bool __rb_tree_color_type;
const __rb_tree_color_type __rb_tree_red = false;     //红色为0
const __rb_tree_color_type __rb_tree_black = true;   //黑色为1

struct __rb_tree_node_base
{
	typedef __rb_tree_color_type color_type;
	typedef __rb_tree_node_base* base_ptr;

	color_type color;
	base_ptr parent;
	base_ptr left;
	base_ptr right;

	static base_ptr minimum(base_ptr x)
	{
		while (x->left != 0) x = x->left;
		return x;
	}

	static base_ptr maximum(base_ptr x)
	{
		while (x->right != 0)x = x -> right;
		return x;
	}

};

template<class Value>
struct __rb_tree_node :public __rb_tree_node_base
{
	typedef __rb_tree_node<Value>* linc_type;
	Value value_field;   //节点值
};

//基层迭代器
struct __rb_tree_base_iterator
{
	typedef __rb_tree_node_base::base_ptr base_ptr;
	typedef bidirectional_iterator_tag iterator_category;

	typedef ptrdiff_t difference_type;

	base_ptr node;    //用来和容器产生连结关系
	//以下其实可实现于operator++内，
	void increment()
	{
		if (node->right != 0) {
			node = node->right;
			while (node->left != 0)
				node = node->left;
		}
		else {
			base_ptr y = node->parent;
			while (node == y->right) {
				node = y;
				y = y->parent;
			}
			if (node->right != y)
				node = y;
		}
	}

	//以下其实可实现于operator--内，
	void decrement()
	{
		if (node->color == __rb_tree_red && node->parent->parent == node)
			node = node->right;
	//以上情况发生于node为header时（亦即node为end（）时）
		//注意，header之右子节点即most right，指向整棵树的max节点
		else if (node->left != 0) {
			base_ptr y = node->left;
			while (y->right != 0)
				y = y->right;
			node = y;
		}
		else {
			base_ptr y = node->parent;
			while (node == y->left) {
				node = y;
				y = y->parent;
			}
			node = y;
		}
	
	}

};


//R-B的正规迭代器
template<class Value, class Ref, class Ptr>
struct __rb_tree_iterator :public __rb_tree_base_iterator
{
	typedef Value value_type;
	typedef Ref reference;
	typedef Ptr pointer;
	typedef __rb_tree_iterator<Value, Value&, Value*> iterator;
	typedef __rb_tree_iterator<Value, const Value&, const Value*> const_iterator;
	typedef __rb_tree_iterator<Value, Ref, Ptr> self;
	typedef __rb_tree_node<Value>* link_type;

	__rb_tree_iterator(){ }
	__rb_tree_iterator(link_type x) { node = x; }
	__rb_tree_iterator(const iterator& it) { node = it.node; }

	reference operator*() const { return link_type(node)->value_field; }
#ifndef __SGI_STL_NO_ARROW_OPERATOR
	pointer operator->()const { return &(operator*()); }
#endif
	self& operator++() { increment(); return *this; }
	self& operator++(int) {
		self tmp = *this;
		increment();
		return tmp;
	}

	self& operator--() { decrement(); return *this; }
	self& operator--() {
		self tmp = *this;
		decrement();
		return tmp;
	}


};


//下面是rb_tree的定义，你可以看到其中定义有专属的空间配置器，每次用来配置一个节点大小，也可以看到各种型别定义，用来维护整棵RB-tree的三笔数据
//（其中有个仿函数，functor，用来表现节点的大小比较方式）， 以及一些member functions的定义或声明
template<class Key, class Value, class KeyOfValue, class Compare, class Alloc = alloc>
class rb_tree
{
	typedef void* void_pointer;
	typedef __rb_tree_node_base* base_ptr;
	typedef __rb_tree_node<Value> rb_tree_node;
	typedef simple_alloc<rb_tree_node, Alloc> rb_tree_node_allocator;
	typedef __rb_tree_color_type color_type;
public:
	//没有定义iterator（定义在后面）
	typedef Key key_type;
	typedef Value value_type;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef rb_tree_node* link_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
protected:
	link_type get_node() { return rb_tree_node_allocator::allocate(); }
	void put_node(link_type p) { rb_tree_node_allocator::deallocate(p); }

	link_type create_node(const value_type& x) {
		link_type tmp = get_node();  //配置空间
		__STL_TRY{
			construct(&tmp->value_field, x);   //构造内容
		}
		__STL_UNWIND(put_node(tmp));
		return tmp;
	}

	link_type clone_node(link_type x) {  //复制一个节点（的值和色）
		link_type tmp = create_node(x->value_field);
		tmp->color = x->color;
		tmp->left = 0;
		tmp->right = 0;
		return tmp;
	}

	void destroy_node(link_type p) {
		destroy(&p->value_field);  //析构内容
		put_node(p);              //释放内存
	}
protected:
	//RB-tree只以三笔数据表现
	size_type node_count;     //追踪记录树的大小
	link_type header;        //这是实现上的一个技巧
	Compare key_compare;   //节点间键值大小比较准则，应该会是个function object


	//以下三个函数用来方便取得header的成员
	link_type& root() const { return (link_type&)header->parent; }
	link_type& leftmost()const { return(link_type&)header->left; }
	link_type& rightmost() const { return (link_type&)header->right; }
	//    关键数据通常是容器中存储的具体元素值，如整数、对象等。
	//链接信息包括指向父节点、左子节点和右子节点的指针，以维护容器的结构。

		//将节点的关键数据和链接信息分开，使得容器的实现可以更加通用

	//以下六个函数用来方便取得节点x的成员
	static link_type& left(link_type x)
	{
		return (link_type&)(x->left);
	}
	static link_type& right(link_type x)
	{
		return (link_type&)(x->right);
	}
	static link_type& parent(link_type x)
	{
		return (link_type&)(x->parent);
	}
	static reference value(link_type x)
	{
		return x->value_field;
	}
	static const Key& key(link_type x)
	{
		return KeyOfValue()(value(x));
	}
	static color_type& color(link_type x)
	{
		return (color_tyee&)(x->color);
	}

	//以下六个函数用来方便去的节点x的成员
	static link_type& left(base_ptr x)
	{
		return (link_type&)(x->left);
	}
	static link_type& right(base_ptr x)
	{
		return (link_type&)(x->right);
	}
	static link_type& parent(base_ptr x)
	{
		return (link_type&)(x->parent);
	}
	static link_type& value(base_ptr x)
	{
		return ((link_type)x)->value_field;
	}
	static const Key& key(base_ptr x)
	{
		return KeyOfValue()(value(link_type(x)));
	}
	static color_type& color(base_ptr x)
	{
		return (color_type&)(link_type(x)->color);
	}

	//求取极大值和极小值，node class 有实现此功能，交给他们即可完成
	static link_type minimum(link_type x) {
		return (link_type)__rb_tree_node::minimum(x);
	}
	static link_type maximum(link_type x) {
		return (link_type)__rb_tree_node::maximum(x);
	}

public:
	typedef __rb_tree_iterator<Value_type, reference, pointer> iterator;
private:
	iterator __insert(base_ptr x, base_ptr y, const value_type& v);
	link_type __copy(link_type x, link_type p);
	void __erase(link_type x);
	void init() {
		header = get_node();   //产生一个节点空间，令header指向它
		color(header) = __rb_tree_red;  //令header为红色，用来区分header和root
		                                //在iterator，operator之中
		root() = 0;
		leftmost() = header;         //令header的左子节点为自己
		rightmost() = header;        //令header的右子节点为自己
	}
public:
	//allocation/deallocation
	rb_tree(const Compare& comp = Compare()):node_count(0), key_compare(comp)
	{
		init();
	}

	~rb_tree() {
		clear();
		put_node(header);
	}
	rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& operator=(const rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& x);
public:
	//accessors
	Compare key_comp() const { return key_compare; }
	iterator begin() { return leftmost(); }   //RB树的起头为最左节点
	iterator end() {return header;  }          //rb树的中带你为header的所指处
	bool empty() const { return node_count == 0; }
	size_type size() const { return node_count; }
	size_type max_sie() const { return size_type(-1); }

public:
	//将x插入到rb-tree中（保持节点独一无二）
	pair<iterator, bool> insert_unique(const value_type& x);
	//将x插入到rb-tree中，允许节点值重复
	iterator insert_equal(const value_type& x);
};

//元素插入操作 insert_equal()
//插入新值，节点值允许重复
//注意，返回值是一个rb-tree迭代器，指向新增节点
template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator 
rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_equal(const Value& v)
{
	link_type y = header;
	link_type x = root();
	while (x != 0) {
		y = x;
		x = key_compare(KeyOfValue()(v), key(x)) ? left(x) : right(x);
		//以上，遇大则往左， 遇小于等于则往右
	}
	return __insert(x, y, v);
	//以上，下为新值插入点，y为插入点的父节点， v为新值
}

//元素插入操作 insert_unique()
//插入新值，节点键值不允许重复，若重复则插入无效
//注意， 返回值是以个pair，第一个元素是RB-tree迭代器，指向新增点
//第二元素表示插入成功与否
template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
pair<typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator, bool>
typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_unique(const Value& v)
{
	link_type y = header;
	link_type x = root();
	bool comp = true;
	while (x！ = 0) {
		y = x;
		comp = key_compare(KeyOfValue()(V), key(x));  
		x = comp ? left(x) : right(x);
	}

	//离开while循环之后，y所指即插入点之父节点

	iterator j = iterator(y);
	if (comp)
		if (j == begin())
			return pair<iterator, bool>(__insert(x, y, v), true);
		else
			--j;
	if (key_compare(key(j.node), KeyOfValue()(v)))
		return pair<iterator, bool>(__insert(x, y, v), true);

	return pair<iterator, bool>(j, false);
}


//真正的插入执行程序  __insert()
template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::
__insert(base_ptr x_, base_ptr y_, const Value& v) {
	//参数x_为新值插入点， 参数y_为插入点之父节点，参数v为新值
	link_type x = (link_type)x_;
	link_type y = (link_type)y_;
	link_type z;

	//key_compare是键值大小比较准则，应该会是个function object
	if (y == header || x != 0 || key_compare(KeyOfValue()(v), key(y)) {
		z = create_node(v);
		left(y) =  z;
			if (y == header) {
				root() = z;
				rightmost() = z;

		}
			else if(y ==leftmost())
				leftmost() = z;
	}
	else {
		z = create_node(v);
		right(y) = z;
		if (y == rightmost())
			rightmost() = z;
	}
	parent(z) = y;
	left(z) = 0;
	right(z) = 0;

	__rb_tree_rebalance(z, header->parent);
	++node_count;
	return itertaor(z);
}