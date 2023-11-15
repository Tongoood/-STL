#pragma once
template<class InputIterator, class OutputIterator>
OutputIterator adjacent_difference(InputIterator first, InputIterator last,
	OutputIterator result) {
	if (first == last) return result;
	*result = *first;   //首先记录第一个元素
	return __adjacent_difference(first, last, result, value_type(first));
}

template<class InputIterator, class OutputIterator, class T>
OutputIterator __adjacent_difference(InputIterator first, InputIterator last,
	OutputIterator result, T*) {
	T value = *first;
	while (++first != last) {
		T tmp = *first;
		*++result = tmp - value;
		value = tmp;
	}
	return ++result;
}

//版本2
template<class InputIterator, class OutputIterator, class BinaryOperation>
OutputIterator adjacent_difference(InputIterator first, InputIterator last, OutputIterator result,
	BinaryOperation binary_op) {
	if (first == last) return result;
	*result = *first;
	return __adjacent_difference(first, last, result, value_type(first), binary_op);
}
template<class InputIterator, class OutputIterator, class T, class BinaryOperation>
OutputIterator __adjacent_difference(InputIterator first, InputIterator last, OutputIterator result, T*,
	BinaryOperation binary_op) {
	T value = *first;
	while (++first != last) {
		T tmp = *first;
		*++result = binary_op(tmp, value);
		value = tmp;
	}
	return ++result;
}