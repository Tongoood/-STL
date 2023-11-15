#pragma once

//multiset的特性和用法和set完全相同
//唯一的差别在于允许它键值重复，因此它的插入操作采用的是底层机制RB-Tree的insert_equal()而非insert_unique()
template<class Key, class Compare = less<Key>, class Alloc = alloc>
class multiset {
public:
	//typedefs:
	//(与set相同)
	//allocation/deallocation
	//注意，multiset一定使用insert_equal()而不使用insert_unique()
	//set才使用inert_unique()

	template<class InputIterator>
	multiset(InputIterator first, InputIterator last)
		:t(Compare()) {
		t.insert_equal(first, last);
	}
	multiset(InputIterator first, InputIterator last, const Compare comp)
		:t(comp) {
		t.insert_equal(first, last);
	}

	//insert/erase
	iterator insert(const value_type& x) {
		return t.insert_euqal(x);
	}
	iterator insert(iterator position, const value_type& x) {
		typedef typename rep_type::iterator rep_iterator;
		return t.insert_equal((rep_iterator&)position, x);
	}

	template<class InputIterator>
	void insert(InputIterator first, InputIterator last) {
		t.insert_equal(first, last);
	}

	//...其他与set相同

};