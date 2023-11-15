#pragma once

template<class RandomAccessIterator>
inline void pop_heap(RandomAccessIterator first, RandomAccessIterator last) {
	__pop_heap_aux(first, last, value_type(first));
}

template<class RandomAccessIterator, class T>
inline void __pop_heap_aux(RandomAccessIterator first, RandomAccessIterator last, T*) {
	__pop_heap(first, last - 1, last - 1, T(*(last - 1)), distance_type(first));
	//以上，根据implicit representation heap的次序特性， pop操作的结果
	//应为底部容器的第一个元素，因此，首先设定欲调整值为尾值，然后将首值调至
	//尾节点，然后重整【first， last-1）
	//使之重新成为一个合格的heap
}

template<class RandomAccessIterator, class T, class Distance>
inline void __pop_heap(RandomAccessIterator first, RandomAccessIterator last, RandomAccessIterator result, T value, Distance*) {
	*result = *first;//设定尾值为首值，于是尾值即为欲求结果
	__adjust_heap(first, Distance(0), Distance(last - first), value);
}

template<class RandomAccessIterator, class Distance, class T>
void __adjust_heap(RandomAccessIterator first, Distance holeIndex, Distance len, T value) {
	Distance topIndex = holeIndex;
	Disatnce secondChild = 2 * holeIndex + 2;
	while (secondChild < len) {
		//比较洞节点之左右两个子值，然后以secondChild代表较大子节点
		if (*(first + secondChild) < *(first + (secondChild - 1)))
			secondChild--;
		*(first + holeIndex) = *(first + secondChild);   //令较大子值为洞值，再令洞号下移至较大字节处
		holeIndex = secondChild;
		//找出新洞节点的右子节点
		secondChild = 2 * (secondChild + 1);
	}
	if (secondChild == len) {
		//没有右节点了，只有左节点
		//令左节点为洞值，再令洞号下移至左子节点处
		*(first + holeIndex) = *(first + (secondChild - 1));
		holeIndex = secondChild - 1;
	}

	__push_heap(first, holeIndex, topIndex, value);      //这里的value 是原来大顶堆的末尾值，由于取出根节点，导致末尾值需要填充到
	                                                      //按照大顶堆排序原则标准的洞处，即此处的holeIndex
}

//注意， pop_heap之后，最大元素只是被放置于底部容器的最尾端， 尚未被取走
//如果要取值，可用底部容器（vector）所提供的back（）操作
//如果要移除，可使用底部容器（vector）所提供的pop_back()操作