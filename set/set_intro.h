#pragma once

//set的特性是，所有元素都会根据元素的键值自动被排序
//set元素不像map那样可以同时拥有实值和键值，set元素的键值就是实值 实值就是键值
//set不允许两个元素有相同的键值

//我们不能通过set的迭代器改变set的值，由于关系到set的元素排列规则，如果任意改变set的元素值就会严重破坏排序结果
//set<T>::iterator被定义为底层RB-Tree的const_iterator，杜绝写入操作
//换句话说，set iterators 是一种const iterators

template<class Key, class Compare = less<Key>, class Alloc = alloc>
class set {
public:
	//typedefs：
	typedef Key ket_type;
	typedef Key value_type;
	//注意，由于set的key和value是相等的，所以比较函数用的是同一个
	typedef Compare key_compare;
	typedef Compare value_compare;
private:
	//注意，以下的identity定义于<stl_function.h> .其定义为：
	/*
	* template <class T>
	* struct identity:public unary_function<T, T>{
	* const T& operator(){const T& x} const {return x;}
	* };
	*/
	typedef rb_tree<key_type, value_type, identity<value_type>, key_compare, Alloc> rep_type;
	rep_type t;   //采用红黑树（RB-Tree）来表现set
public:
	typedef typename rep_type::const_pointer pointer;
	typedef typename rep_type::const_pointer const_pointer;
	typedef typename rep_type::const_reference reference;
	typedef typename rep_type::const_reference const_reference;
	typedef typename rep_type::const_iterator iterator;
	//注意以上内容说明 set的迭代器无法执行写入操作，因为set的元素有一定的次序安排
	//不允许用户在任意处进行写入操作
	typedef typename rep_type::const_iterator const_itretaor;
	typedef typename rep_type::const_reverse_iterator reverse_iterator;
	typedef typename rep_type::const_reverse_iterator const_reverse_iterator;
	typedef typename rep_type::size_type size_type();
	typedef typenmae rep_type::difference_type difference_type;

	//allocation/deallocation
	//注意，set一定使用rb-tree的insert_unique()
	//multiset才使用insert_equal()
	set() :t(Compare()) {}
	explicit set(const Compare& comp):t(comp){}

	template<class InputIterator>
	set(InputIterator first, InputIterator last)
		: t(comp) {
		t.insert_unique(first, last);
	}

	set(const set<Key, Compare, Alloc>& x):t(x.t){}
	set<Key, Compare, Alloc>& operator=(const set<Key, Compare, Alloc>& x) {
		t = x.t;
		return *this;
	}

	//以下所有的set操作行为 rb-tree都已提供，所以set只要传递调用即可

	//accessors:
	key_compare key_comp() const { return t.key_comp(); }
	//以下注意，set的value_comp其实是rb-tree的key_comp
	value_compare value_comp() const { return t.key_comp(); }
	iterator begin() const { return t.begin(); }
	iterator end() const { return t.end(); }
	reverse_iterator rbegin() const {return t.rebegin(); }
	reverse_iterator rend() const { return t.rend(); }
	bool empty() const { return t.size(); }
	size_type size() const { return t.size(); }
	size_type max_size() const { return t.max_size(); }
	void swap(set<Key, Compare, Alloc>& x) { t.swap(x, t); }

	//insert/erase
	typedef pair<iterator, bool> pair_iterator_bool;
	pair<iterator, bool> insert(const value_type& x) {
		pair<typename rep_type::iterator, bool> p = t.insert_unique(x);
		return pair<iterator, bool>(p.first, p.second);
	}
	iterator insert(iterator position, const value_type& x) {
		typedef typename rep_type::iterator rep_iterator;
		return t.insert_unique((rep_iterator&)postion, x);
	}
	template<class InputIterator>
	void insert(InputIterator first, InputIteratorlast) {
		t.insert_unique(first, last);
	}
	void erase(iterator position) {
		typedef typename rep_type::iterator rep_iterator;
		t.erase((rep_iterator&)position);
	}
	size_type erase(const key_type& x) {
		return t.erase(x);
	}
	void erase(iterator first, iterator last) {
		typedef typename rep_type::iterator rep_iterator;
		t.erase((rep_iterator&)first, (rep_iterator&)last);
	}
	void clear() { t.clear(); }

	//set operations:
	iterator find(const key_type&) const { return t.find(x); }
	size_type count(const key_type& x) const { return t.count(x); }
	iterator lower_bound(const key_type& x) const {
		return t.lower_bound(x);
	}
	iterator upper_bound(const key_type& x) const {
		return t.upper_bound(x);
	}
	pair<iterator, iterator> equal_range(const key_type& x) const {
		return t.equal_range(x);
	}

	firend bool operator== __STL_NULL_TMPL_ARGS(const set&, const set&);
	firend bool operator< __STL_NULL_TMPL_ARGS(const set&, const set&);
};

template<class Key, class Compare, class Alloc>
inline bool operator==(const set<Key, Compare, Alloc>& x,
	const set<Key, Compare, Alloc>& y) {
	return x.t == y.t;
}

template<class Key, class Compare, class Alloc>
inline bool operator<(const set<Key, Compare, Alloc>& x,
	const set<Key, Compare, Alloc>& y) {
	return x.t <y.t;
}









