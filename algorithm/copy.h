

//完全泛化版本
template<class InputIterator, class OutputIterator>
inline OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result)
{
	return __copy_dispatch<InputIterator, OutputIterator>()
		(first, last, result);
}

//下面是两个多载函数，针对原生指针（可视为一种特殊的迭代器）const char*和const wchar_t*,进行内存之间拷贝操作
//特殊版本1
inline char* copy(const char* first, const char* last, char* result) {
	memmove(result, first, last - first);
	return result + (last - first);
}
//特殊版本2
inline wchar* copy(const wchar* first, const wchar* last, wchar* result) {
	memmove(result, first, sizeof(wchar_t)*(last - first));
	return result + (last - first);
}

//copy()函数的泛化版本中调用了一个__copy_display()函数，此函数有一个完全泛化版本和两个偏特化版本
//完全泛化版本
template<class InputIterator, class OutputIterator>
struct __copy_dispatch
{
	OutputIterator operator()(InputIterator first, InputIterator last, OutputIterator result) {
		return __copy(first, last, result, iterator_category(first));
	}
};

//偏特化版本1，两个参数都是T*指针形式
template<class T>
struct __copy_dispatch<T*, T*>
{
	T operator()(T* first, T* last, T* result) {
		typedef typename __type_traits<T>::has_trivial_assignment_operator t;
		return __copy_t(first, last, result,t());
	}
};

//偏特化版本2，第一个参数为const T*指针形式，第二个参数为T*指针形式
template<class T>
struct __copy_dispatch<const T*, T*>
{
	T operator()(const T* first, const T* last, T* result) {
		typedef typename __type_traits<T>::has_trivial_assignment_operator t;
		return __copy_t(first, last, result, t());
	}
};


//__copy_dispatch()的完全泛化版根据迭代器种类的不同，调用了不同的__copy()，为的是不同种类的迭代器所使用的循环条件不同，有快慢之别
//InputIterator版本
template<class InputIterator, class OutputIterator>
inline OutputIterator __copy(InputIterator first, InputIterator last,
	OutputIterator result, input_iterator_tag)
{
	//以迭代器等同与否，决定循环是否继续，速度慢
	for (; first != last; ++result, ++first)
		*result = *first;
	return result;
}
//RandomAccessIterator版本
template<class RandomAccessIterator, class OutputIterator>
inline OutputIterator
__copy(RandomAccessIterator first, RandomAccessIterator last, OutputIterator result, random_access_iterator_tag)
{
	//又划分一个函数，为的是其他地点也可能用到
	return __copy_d(first, last, resylt, distance_type(first));
}

template<class RandomAccessIterator, class OutputIterator, class Distance>
inline OutputIterator
__copy_d(RandomAccessIterator first, RandomAccessIterator last, OutputIterator result, Distance*)
{
	//以n决定循环的执行次数，速度块
	for (Distance n = last - first; n > 0; --n, ++result, ++first)
		*result = *first;
	return result;
}

//以下版本适用于“指针所指之对象具备trivial assignment operator”
template<class T>
inline T* __copy_t(const T* first, const T* last, T* result, __true_type) {
	memmove(result, first, sizeof(T) * (last - first));
	return result + (last - first);
}

//以下版本适用于“指针所指之对象具备non-trivial assignment operator”
template<class T>
inline T* __copy_t(const T* first, const T* last, T* result, __false_type) {
	//原生指针是一种RandomAccessIterator ，所以交给__copy_d（）完成
	return __copy_d(first, last, result, (ptrdiff_t) * 0);
}

/*    Trivial Assignment Operator:
        "trivial assignment operator" 通常用于描述拷贝操作是非常简单、直接的情况。
        它对于内置数据类型（如整数、浮点数等）或者POD类型（Plain Old Data，类似C语言的结构体）来说是"trivial"的。
        对于这些类型，简单的内存复制操作（如 memcpy 或 memmove）通常足以执行拷贝。
        这些操作符执行的是按位拷贝，不需要特殊处理。

    Non-Trivial Assignment Operator:
        "non-trivial assignment operator" 描述了拷贝操作比较复杂或者不适合按位拷贝的情况。
        这通常涉及到自定义类型，其中拷贝操作可能涉及更多的资源管理、构造函数或析构函数的调用，或者其他定制行为。
        对于这些类型，通常需要调用对象的拷贝构造函数或赋值操作符函数，而不是简单的内存复制。
		*/


//vector的迭代器其实是原生指针，所以当vector容器使用copy()操作时，就往T*的方向走