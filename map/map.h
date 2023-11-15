#pragma once

//我们不能通过map的迭代器改变map元素的键值  但是可以修改实值
//因此， map iterators既不是一种constant iterator也不是一种mutable iterator

template<class Key, class T, class Compare = less<Key>  //缺省采用递增排序
, class Alloc = alloc>
class map {
public:

	//typedefs
	typedef Key key_type;     //键值型别
	typedef T data_type;       //数据（实值）型别
	typedef T mapped_type;
	typedef pair<const Key, T> value_type;   //元素型别（键值/实值）
	typedef Compare key_compare;   //元素比较函数


	//以下定义一个functor，其作用就是调用“元素比较函数”
	class value_compare
		:public binary_function<value_type, value_type, bool> {
		friend class map<Key, Compare, Alloc>;
	protected:
		Compare comp;
		value_compare(Compare c):comp(c){}
	public:
		bool operator()(const value_type& x, const value_type& y) const {
			return comp(x.first, y.first);
		}
	};

private:
	//以下定义表述型别(representation type), 以map元素型别（一个pair）
	//的第一型别，作为RB-Tree节点的键值型别
	typedef rb_tree<Key_type, value_type, selectlst<value_type>, key_compare, Alloc> rep_type;
	rep_type t;
public:
	typedef typename rep_type::pointer pointer;
	typedef typename rep_type::const_pointer const_pointer;
	typedef typename rep_type::reference reference;
	typedef typename rep_type::const_reference const_reference;
	typedef typename rep_type::iterator iterator;
	//注意，map不像set一样将iterator定义为RB-Tree的const_iterator，因为它允许用户通过迭代器修改元素的实值
	typedef typename rep_type::const_iterator consyt_iterator;
	typedef typename rep_type::reverse_iterator reverse_iterator;
	typedef typename rep_type::const_reverse_iterator const_reverse_iterator;
	typedef typename rep_type::size_type size_type;
	typedef typename rep_type::difference_type difference_type;

	//allocation/deallocation
	//注意，map一定使用底层RB-Tree的insert_unique（）而非insert_equal()
	//multimap才使用insert_equal()
	//因为map不允许相同键值存在，multimap才允许相同键值存在

	map():t(Compare()){}
	explicit map(const Compare& comp):t(comp){}

	template<class InputIterator>
	map(InputIterator first, InputIterator last)
		: t(Compare()) {
		t.insert_unique(first, last);
	}

	template<class InputIterator>
	map(InputIterator first, InputIterator last, const Compare& comp)
		: t(comp) {
		t.insert_unique(first, lats);
	}

	map(const map<Key, T, Compare, Alloc>&x):t(x.t){}
	map<Key, T, Compare, Alloc>& operator=(const map<Key, T, Compare, Alloc>& x) {
		t = x.operator=;
		return *this;
	}

	//accessors:
	//以下所有的map操作行为， rb-tree都已提供，map只需要转调用即可

	key_compare key_comp() const { return t.key_comp(); }
	value_compare value_comp() const { return value_compare(t.key_comp()); }
	iterator begin() { return t.begin(); }
	const_iterator begin() { return t.begin(); }
	iterator end() { return t.end(); }
	const_iterator end() { return t.end(); }
	reverse_iterator rbegin() { return t.rbegin(); }
	const_reverse_iterator rbegin() const { return t.rbegin(); }
	reverse_iterator rend() { return t.rend(); }
	const_reverse_iterator rend() const { return t.rend(); }
	bool empty()const { return t.empty(); }
	size_type size()const { return t.size(); }
	size_type max_size()const { return t.max_size(); }
	//注意以下 下表（subscript）操作符
	T& operator[](const key_type& k) {
		return (*((insert(value_type(k, T()))).first)).second;
	}
	void swap(map<Key, T, Compare, Alloc>& x) { t.swap(x.t); }

	//insert/erase

	//注意以下insert操作返回的类型
	pair<iterator, bool>insert(const value_type& x) {
		return t.insert_unique(x);
	}
	iterator insert(iterator position, const value_type& x) {
		return t.insert_unique(position, x);
	}
	template<class InputeIterator>
	void insert(InputIterator first, InputIterator last) {
		t.insert_unique(first, last);
	}
	void erase(iterator position) { t.erase(position); }
	size_type erase(const key_type& x) { return t.erase(x); }
	void erase(iterator first, iterator last) { t.erase(first, last); }
	void clear() { t.clear(); }

	//map operations:

	iterator find(const key_type& x) { return t.find(x); }
	const_iterator find(const key_type& x)const { return t.find(x); }
	size_type count(const key_type& x) const { return t.count(x); }
	iterator lower_bound(const key_type& x) { return t.lower_bound(x); }
	const_iterator lower_bound(const key_type& x) const {
		return t.lower_bound(x);
	}
	iterator uppwer_bound(const key_type& x) { return t.upper_bound(x); }
	const_iterator upper_bound(const key_type& x)const {
		return t.upper_bound(x);
	}

	pair<iterator, iterator> equal_range(const key_type& x) {
		return t.equal_range(x);
	}
	pair<const_iterator, const_iterator> equal_range(const key_type& x) const {
		return t.equal_range(x);
	}
	friend bool operator== __STL_NULL_TMPL_ARGS(const map&, const map&);
	friend bool operator< __STL_NULL_TMPL_ARGS(const map&, const map&);
};
template<class Key, class T, class Compare, class Alloc>
inline bool operator==(const map<Key, T, Compare, Alloc>& x, const map<Key, T, Compare, Alloc>& y) {
	return x.t == y.t;
}
template<class Key, class T, class Compare, class Alloc>
inline bool operator<(const map<Key, T, Compare, Alloc>& x, const map<Key, T, Compare, Alloc>& y) {
	return x.t < y.t;
}