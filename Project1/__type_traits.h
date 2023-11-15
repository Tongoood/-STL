#pragma once


//SGI STL ---      __type_traits
//双底线前缀的意思是指这是SGI STL内部所用的东西，不在STL标准规范内
//iterator_traits负责萃取迭代器的特性，__type_traits则负责萃取型别（type）的特性
//__type_traits，提供了一种机制，允许针对不同的型别属性，在编译时期完成函数派送决定，这对于
//撰写template很有帮助，
//例如，当我们准备对一个“元素型别未知”的数组执行copy操作时，如果我们能事先知道其元素型别是否有一个
//trivial copy constructor,便能帮助我们决定是否使用快速的memcpy()或memmove()

//对SGI STL中感兴趣内容的展示

//如果不是POD型别
template<class ForwardIterator, class Size, class T>
ForwardIterator
__uninitialzed_fill_n_aux(ForwardIterator first, Size n, const T& x, __false_type) {
	ForwardIterator cur = first;
	for (; n > 0; --n.++cur) {
		construct(&*cur, x);
		
	}
	return cur;
}

//如果是POD型别的
template<class ForwardIterator, class Size, class T>
inline ForwardIterator
__uninitialed_fill_n_aux(ForwardIterator first, Size n, const T& x, __true_type) {
	return fill_n(first, n, x);
}

//一下是fill_n的实现
template<class OutputIterator, class Size, class T>
OutputIterator fill_n(OutputIterator first, Size n, const T& value) {
	for (; n > 0; --n, ++first)
		*first = value;
	return first;
}