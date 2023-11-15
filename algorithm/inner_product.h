#pragma once

//版本1
template<class InputIterator1, class InputIterator2, class T>
T inner_product(InputIterator1 first1, InputIterator1 last,
	InputIterator2 first2, T init) {
	//以第一序列之元素个数为依据， 将两个学列都走一遍
	for (; first1 != last; ++first1, ++first2)
		init = init + (*first1 * *first2);
	return init;
}

//版本2
template<class InputIterator1, class InputiIterator2,class T, class BinaryOperation1, class BinaryOperation2>
T inner_product(InputIterator1 first1, InputIterator1 last1,
	InputiIterator2 first2, T init, BinaryOperation1 binary_op1, BinaryOperation2 binary_op2) {
	//以第一序列之元素个数为依据， 将两个学列都走一遍
	for (; first1 != last1; ++first1, ++first2)
		//以外界提供的仿函数来取代第一版本中的operator*和operator+
		init = binary_op1(init, binary_op2(*first1, *first2));
	return init;
}