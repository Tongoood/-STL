#pragma once
template<class InputIterator , class T>
T accumulate(InputIterator first, InputIterator last, T init) {
	for (; first != last; ++first)
		init = init + *first;
	return init;
}

//版本2
template<class InputIterator, class T, class BinaryOperation>
T accumulate(InputIterator first, InputIterator last, T init, BinaryOperation binary_op) {
	for (; first != last; ++first) {
		init = binary_op(init, *first);
		return init;
	}
}
//算法用来计算init和【first， last）内的元素的综合，注意一定要提供一个初始值init
//确保当【first， last）为空的时候，仍然能够得到一个明确定义的值
//如果只需要计算【first，last）中的值，将init设置为0即可                                                                                                    