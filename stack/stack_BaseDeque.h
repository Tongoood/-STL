#pragma once


//STLstack往往不被归类为container，而被归类为container adapter
//
template<class T, class Sequence = deque<T>>
class stack {
	friend bool operator== __STL_NULL_TMPL_ARGX(const stack&, const stack&);
	friend bool operator< __STL_NULL_TMPL_ARGS(const stack&, const stack&);
public:
	typedef typename Sequence::value_type value_type;
	typedef typename Sequence::size_type size_type;
	typedef typename Sequence::reference reference;
	typedef typename Sequence::const_reference const_reference;
protected:
	Sequence  c;   //底层容器
public:
	//以下完全利用Sequence c 的操作，完成stack的操作
	bool empty() const { return c.empty(); }
	size_type size() const { return c.size(); }
	reference top() { return c.back(); }
	const_referebce top() const { return c.back(); }
	void push(const value_type& x) { c.push_back(x); }
	void pop() { c.pop_back(); }
};

template<class T, class Sequence>
bool operator==(const stack<T, Sequence>& x, const stack<T, Sequence>& y) {
	return x.c == y.c;
}


template<class T, class Sequence>
bool operator<(const stack<T, Sequence>& x, const stack<T, Sequence>& y) {
	return x.c < y.c;
}