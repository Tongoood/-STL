#pragma once
/*等于 equal_to<T>
不等于 not_equal_to<T>
大于 greater<T>
大于或等于 greater_equal<T>
小于 less<T>
小于或等于less_equal<T>*/
template<class T>
struct equal_to :public binary_function<T, T, bool> {
	bool operator()(const T& x, const T& y) const { return x == y; }
};
template<class T>
struct not_equal_to :public binary_function<T, T, bool> {
	bool operator()(const T& x, const T& y) const { return x != y; }
};
template<class T>
struct greater :public binary_function<T, T, bool> {
	bool operator()(const T& x, const T& y) const { return x > y; }
};
template<class T>
struct less :public binary_function<T, T, bool> {
	bool operator()(const T& x, const T& y) const { return x < y; }
};
template<class T>
struct greater_equal :public binary_function<T, T, bool> {
	bool operator()(const T& x, const T& y) const { return x >= y; }
};
template<class T>
struct less_equal :public binary_function<T, T, bool> {
	bool operator()(const T& x, const T& y) const { return x <= y; }
};


//逻辑运算类仿函数

//And
//Or
//Not
//And 和Or是二元运算
//Not 是一元运算

template<class T>
struct logical_and :public binary_function<T, T, bool> {
	bool operator() (const T& x, const T& y) const { return x && y; }
};
template<class T>
struct logical_or :public binary_function<T, T, bool> {
	bool operator() (const T& x, const T& y) const { return x || y; }
};
template<class T>
struct logical_not :public binary_function<T, bool> {
	bool operator() (const T& x) const { return !x; }
};

//证同（identity）、选择（select）、投射（project）
//证同函数，任何数值通过此函数后，不会有任何改变
template<class T>
struct identity :public unary_function<T, T> {
	const T& operator() (const T& x) const { return x; }
};

//选择函数，接受一个pair，传回其第一个元素
template<class Pair>
struct select1st : public unary_function<Pair, typename Pair::first_type>
{
	const typename Pair::first_type& operator() (const Pair& x) const
	{
		return x.first;
	}
};

//选择函数，接受一个pair，传回其第二个元素
template<class Pair>
struct select2st : public unary_function<Pair, typename Pair::first_type>
{
	const typename Pair::first_type& operator() (const Pair& x) const
	{
		return x.second;
	}
};

//投射函数，传回第一参数，忽略第二参数
template<class Arg1, class Arg2>
struct project1st :public binary_function<Arg1, Arg2, Arg1> {
	Arg1 operator() (const Arg1& x, const Arg2&) const { return x; }
};
template<class Arg1, class Arg2>
struct project1st :public binary_function<Arg1, Arg2, Arg1> {
	Arg1 operator() (const Arg1& , const Arg2& y) const { return y; }
};