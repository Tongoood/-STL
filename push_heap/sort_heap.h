#pragma once

//sort_heap的实质是  由于每次使用pop_heap可以获得heap的最大值，那么多次使用
//每次将pop_heap的范围减少一个元素,最后就会得到一个有序的递增序列

//注意排序后的heap就不再是一个合法的max_heap或者min_heap了

template<class RandomAccessIterator>
void sort_heap(RandomAccessIterator first, RandomAccessIterator last) {
	//以下，每执行一次pop_heap()，极值（在STL heap中为极大值）就会被放在尾端
	//扣除尾端再进行一次pop_heap()，依次循环，最后即得到排序结果

	while (last - first > 1) {
		pop_heap(first, last--);
	}
}