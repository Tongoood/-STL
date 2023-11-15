#pragma once

/*加法plus
减法minux
乘法multiplies
除法divides
模取modulus
否定negate（一元，其余都是二元）*/

//以下为仿函数
template<class T>
struct plus : public binary_function<T, T, T> {
	T operator()(const T& x, const T& y) const { return x + y; }
};
template<class T>
struct minus : public binary_function<T, T, T> {
	T operator()(const T& x, const T& y) const { return x - y; }
};
template<class T>
struct multiplies : public binary_function<T, T, T> {
	T operator()(const T& x, const T& y) const { return x * y; }
};
template<class T>
struct divides : public binary_function<T, T, T> {
	T operator()(const T& x, const T& y) const { return x / y; }
};
template<class T>
struct modulus : public binary_function<T, T, T> {
	T operator()(const T& x, const T& y) const { return x % y; }
};

template<class T>
struct megate :public unary_function<T, T> {
	T operator()(const T& x) const { return -x; }
};

//证同元素
//所谓“运算op的证同元素”，意思是数值A若与该元素做op运算，会得到A自己
template<class T>
inline T identity_element(plus<T>)
{
	return T(0);
}

template<class T>
inline T identity_element(multiplies<T>)
{
	return T(1);
}