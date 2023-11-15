#pragma once
//版本1
template<class InputIterator, class OutputIterator>
OutputIterator partial_sum(InputIterator first, InputIterator last, OutputIterator result) {
	if (first == last) return result;
	*result = *first;
	return __partial_sum(first, last, result, value_type(first));
}

template<class InputIterator, class OutputIterator, class T>
OutputIterator __partial_sum(InputIterator first, InputIterator last, OutputIterator result, T*) {
	T value = *first;
	while (++first != last) {
		value = value + *first;
		*++result = value;
	}
	return  ++result;
}

//版本2
template<class InputIterator, class OutputItrerator, class BinaryOperation>
OutputItrerator partial_sum(InputIterator first, InputIterator last,
	OutputItrerator result, BinaryOperation binary_op) {
	if (first == last) return result;
	*result = *first;
	return __partial_sum(first, last, result, value_type(first), binary_op);
}

template<class InputIterator, class OutputIterator, class BinaryOperation>
OutputIterator partial_sum(InputIterator first, InputIterator last, OutputIterator result, BinaryOperation binary_op) {
	T value = *first;
	while (++firs != last) {
		value = binary_op(value, *first);
		*++result = value;
	}
	return ++result;
}