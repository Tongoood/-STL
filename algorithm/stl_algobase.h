#pragma once


//equal
//如果我们希望保证两个序列完全相等，必须先判断其元素个数是否相同

//if(vec1.size()==vec2.size()&& equal(vec1.begin(),vec1.end(),vec2.begin);
template<class InputIterator1, class InputIterator2>
inline bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
	//以下，如果序列1的元素个数多于序列2的元素个数，就糟糕了
	for (; first1 != last1; ++first1, ++first2)
		if (*first1 != *first2)
			return false;
	return true;
}

template<class InputIterator1, class InputIterator2, class BinaryPredicate>
inline bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate binary_pred) {
	for(;first1!=last1;++first1,++first2)
		if(!binary_pred(*first1, *first2)
			return false;
		return true;
}

//fill
//将【first， last）内的所有元素该填新值
template<class ForwardIterator, class T>
void fill(ForwardIterator first, ForwardIterator last, const T& value) {
	for(;first!=last;++first)
		*first = value;
}

//fill_n
//将【first，last）内前n个元素改填新值，返回的迭代器指向被填入的最后一个元素的下一个位置
template<class OutputIterator, class Size, class T>
OutputIterator fill_n(OutputIterator first, Size n, const T& value) {
	for (; n > 0; --n, ++first) {
		*first = value;
	}
	return first;
}


//iter_Swap
//将两个forwarditerators所指的对象对调
template<class ForwardIterator1, class ForwardIterator2>
inline void iter_swap(ForwardIterator1 a, ForwardIterator2 b) {
	__iter_swap(a, b, value_type(a));   //注意第三参数型别
}

template<class ForwardIterator1, class ForwardIterator2, class T>
inline void __iter_swap(ForwardIterator1 a, ForwardIterator2 b, T*) {
	T tmp = *a;
	*a = *b;
	*b = tmp;
}

//其实可以不写双层结构，可以直接这么写
template<class ForwardIterator1, class ForwardIterator2>
inline void iter_swap(ForwardIterator1 a, ForwardIterator2 b) {
	typename iterator_traits<ForwardIterator1>::value_type tmp = *a;
	*a = *b;
	*b = tmp;
}

//lexicographical_compare
//以字典排列方式对两个序列【first1，last1）【first2，last2）进行比较
//如果第一序列元素较小 返回true，否则false
//如果到达last1而未到达last2，返回true
//如果到达last2而未到达last1，返回false
//如果同时到达last1，last2，返回false

template<class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator2 last1,
	InputIterator2 first2, InputIterator2 last2) {
	//以下，任何一个序列到达尾端，就结束，否则两序列就相应元素一一进行对比
	for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
		if (*first1 < *first2)
			return true;
		if (*first2 < *first1)
			return false;
	}
	//到此处，如果第一序列到达尾端，第二序列尚有余额，那么第一序列小于第二序列
	//否则 则大于 返回false
	return first1 == last1 && first2 != last2;
}

template<class InputIterator1, class InputIterator2,class Compare>
bool lexicographical_compare(InputIterator1 first1, InputIterator2 last1,
	InputIterator2 first2, InputIterator2 last2,
	Compare comp) {
	//以下，任何一个序列到达尾端，就结束，否则两序列就相应元素一一进行对比
	for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
		if (comp(*first1,*first2))
			return true;
		if (comp(*first1, *first2))
			return false;
	}
	//到此处，如果第一序列到达尾端，第二序列尚有余额，那么第一序列小于第二序列
	//否则 则大于 返回false
	return first1 == last1 && first2 != last2;
}

//为了提高效率，特化版本
inline bool lexicographical_compare(const unsigned char* first1,
	const unsigned char* last1,
	const unsigned char* first2,
	const unsigned char* last2)
{
	const size_t len1 = last1 - first1;
	const size_t len2 = last2 - first2;
	//先比较相同长度的一段，使用memcmp()速度很快
	const int result = memcmp(first1, first2, min(len1, len2));
	//如果不相上下，则长度较长者被视为比较大
	return result!=0?result<0:len1<len2;

}

//max

//版本1
template<class T>
inline const T& max(const T& a, const T& b) {
	return a < b ? b : a;
}
//版本2
template<class T, class Compare>
inline const T& max(const T& a, const T& b, Compare comp) {
	return comp(a,b) ? b : a;   //由comp决定大小比较标准
}

//min
//版本1
template<class T>
inline const T& min(const T& a, const T& b) {
	return b < a ? b : a;
}
//版本2
template<class T,class Compare>
inline const T& min(const T& a, const T& b,Compare comp) {
	return comp(b,a) ? b : a;
}

//mismatch
//用来平行比较两个序列，指出两者之间的第一个不匹配点，返回一对迭代器，分别指向两序列中的不匹配点
//如果都匹配，返回两序列各自的last迭代器
//如果第二序列比第一序列多，多出的内容可以忽略不计
//如果第一序列比第二序列多， 那么会出现不可知结果
template<class InputIterator1,class InputIterator2>
pair<InputIterator1, InputIterator2> mismatch(
	InputIterator1 first1,
	InputIterator1 last1,
	InputIterator2 first2) {
	//序列一元素个数必须多过序列二元素个数
	while (first1 != last1 && *first1 == *first2) {
		++first1;
		++first2;
	}
	return pair<InputIterator1, InputIterator2>(first1, first2);
}

//版本2
template<class InputIterator1, class InputIterator2, class BinaryPredicate>
pair<InputIterator1, InputIterator2> mismatch(
	InputIterator1 first1,
	InputIterator1 last1,
	InputIterator2 first2,
	BinaryPredicate binary_pred) {
	while (first1 != last1 && binary_pred(*first1, *first2)) {
		++first1;
		++first2;
	}
	return pair<InputIterator1, InputIterator2>(first1, first2);
}

//swap
template<class T>
inline void swap(T& a, T& b) {
	T tmp = a;
	a = b;
	b = tmp;
}

































+