#pragma once
//由于list是双向链表
//所以使用bidirectional iterators
//list有一个重要性质，插入操作和结合操作都不会造成原有的list迭代器失效，这在vector中是不成立的
//list的元素删除操作，也只有指向被删除元素的那个迭代器失效，其它迭代器不受影响

//以下是list迭代器的设计
template<class T, class Ref, class Ptr>
struct __list_iterator {
	typedef __list_iterator<T, T&, T*>     iterator;
	typedef __list_iterator<T, Ref, Ptr>   self;

	typedef bidirectional_iterator_tag iterator_category;
	typedef T value_type;
	typedef Ptr pointer;
	typedef Ref reference;
	typedef __list_node<T>* (link_type));
	typedef size_t size_type;
	typedef ptrfidd_t difference_type;

	link_type node; //迭代器内部要有一个普通指针，指向list节点

	//constructor
	__list_iterator(link_type x) : node(x){ }
	__list_iterator () { }
	__list_iterator(const iterator& x):node(x.node){ }

	bool operator==(const self& x) const { return node == x.node; }
	bool operator!=(const self& x) const { return node != x.node; }

	//以下是对迭代器取值，取的是节点的数据值
	reference operator*() const { return (*node).data; }
	//返回引用，便于读写和修改数据

	//以下是迭代器的成员存取运算子的标准做法
	pointer operator->()const { return &(operator*()); }
	//&(operator*()) 中，& 是取地址运算符，用于获取 operator*() 返回的引用的地址

	//对迭代器+1，就是前进一个节点
	self& operator++() {
		node = (link_type)((*node).next);
		return *this;
	}
	self operator++(int) {
		self tmp = *this;
		++*this;
		return tmp;
	}

	//对迭代器减1，然后后退一个节点
	self& operator--() {
		node = (link_type)((*node).prev);
		return *this;
	}
	self operator--(int) {
		self tmp = *this;
		--*this;
		return tmp;
	}

};