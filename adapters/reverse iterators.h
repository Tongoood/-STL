#pragma once

//所谓reverse iterators，就是将迭代器的移动行为倒转。

//将所有元素逆转拷贝到ite所指位置上
//rbegin()和rend()与reverse_iterator有关
	//copy(id.rbegin(),id.rend(),ite)

//以下先介绍rbegin、rend
template<class T, class Alloc = alloc>
class vector {
	typedef T value_type;
	typedef value_type* iterator;
	typedef reverse_iterator<iterator> reverse_iterator;
	reverse_iterator rbegin() { return reverse_iterator(end()); }
	reverse_iterator rend() { return reverse_iterator(begin()); }
};

template<class T, class Alloc = alloc>
class list {
	typedef __list_iterator<T, T&, T*> iterator;
	typedef reverse_iterator<iterator> reverse_iterator;
	reverse_iterator rbegin() { return reverse_iterator(end()); }
	reverse_iterator rend() { return reverse_iterator(begin()); }
};

template<class T, class Alloc = alloc, size_t BufSiz = 0>
class deque {
	typedef __deque_iterator<T, T&, T*, BufSiz> iterator;
	typedef reverse_iterator<iterator> reverse_iterator;
	iterator begin() { return start; }
	iterator end() { return finish; }
	reverse_iterator rbegin() { return reverse_iterator(finish); }
	reverse_iterator rend() { return reverse_iterator(start); }
};



//reverse_iterator的源代码
//使某个迭代器逆反前进方向，使前进为后退，后退为前进
template<class Iterator>
class reverse_iterator
{
protected:
	Iterator current;
public:
	//逆向迭代器的五种相应型别都和其对应的正向迭代器相同
	typedef typename iterator_traits<Iterator>::iterator_category
		iterator_category;
	typedef typename iterator_traits<Iterator>::difference_type
		difference_type;
	typedef typename iterator_traits<Iterator>::pointer
		pointer;
	typedef typename iterator_traits<Iterator>::reference
		reference;
	typedef typename iterator_traits<Iterator>::value_type
		value_type;

	typedef Iterator iterator_type;            //代表前向迭代器
	typedef reverse_iterator<Iterator> self;   //代表逆向迭代器
	
public:
	reverse_iterator() {}
	//下面这个ctor将reverse_iterator与某个迭代器系起来
	explicit reverse_iterator(iterator_type x):current(x){}
	reverse_iterator(const self& x):currentr(x.current){}

	iterator_type base() const { return current; }
	reference operator*() const {
		Iterator tmp = current;
		return *--tmp;
		//以上为关键所在，对逆向迭代器取值,就是将对应之正向迭代器后退一格而后取值
	}
	pointer operator->() const { return &(operator*()); }

	//前进变为后退
	self& operator++() {
		--current;
		return *this;
	}

	self& operator++(int) {
		self tmp = *this;
		--current;
		return tmp;
	}

	//后退变成前进
	self& operator--() {
		++current;
		return *this;
	}

	self& operator--(int) {
		self tmp = current;
		++current;
		return tmp;
	}
	//前进和后退方向完全逆转
	self operator+(difference_type n) const {
		return self(current - n);
	}
	self& operator+=(difference_type n) {
		current -= n;
		return *this;
	}
	self operator-(difference_type n) const {
		return self(current + n);
	}
	self& operator-=(difference_type n) {
		current += n;
		return *this;
	}

	reference operator[] (difference_type n) const { return *(*this + n); }

};