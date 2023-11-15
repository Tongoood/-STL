#pragma once

//这个算法用来将一段现有的数据转化为一个heap（STL中是max_heap），其主要依据是完全二叉树（complete binary tree）的隐式表达（implicit representation）

//将[first, last)排列为一个heap
template<class RandomAccessIterator>
inline void make_heap(RandomAccessIterator first, RandomAccessIterator last) {
	__make_heap(first, last, value_type(first), distance_type(first));
}

template<class RandomAccessIterator, class T, class Distance>
void __make_heap(RandomAccessIterator first, RandomAccessIterator last, T*, Distance*) {
	if (last - first < 2) return;   //如果长度为0 1 那么不用排列了
	Distance len = last - first;
	//找出第一个需要重新排的子树头部，以parent标示出，由于任何叶节点都不需要执行perlocate down
	//所以有以下计算， parent命名不佳，名为holeIndex更好
	Distance parent = (len - 2) / 2;
	//由于完全二叉树的性质，那么parent = (len - 2) / 2，这个parent节点一定是非叶节点，这样才能保证下面循环的进行

	while (true) {
		//重新排以parent为首的子树，len 是为了让__adjust_heap()判断操作范围
		//将每一个非叶节点都重新拍，那么就得到了全部经过重新调整的堆，结果显然是一个大顶堆
		__adjust_heap(first, parent, len, T(*(first + parent)));
		if (parent == 0)return;   //走完根节点，就结束
		parent--;         //（即将重新排的子树的）头部向前一个节点
	}
}

