#pragma once
//push_heap算法细节
//以max_heap即大顶堆为例

template<class RandomAccessIterator>
inline void push_heap(RandomAccessIterator first, RandomAccessIterator last) {
	//注意，此函数被调用时，新元素已置于底部容器的最尾端
	__push_heap_aux(first, last, distance_type(first), value_type(first));
}

template<class RandonAccessIterator, class Distance, class T>
inline void __push_heap_aux(RandonAccessIterator first, RandonAccessIterator last, Distance*, T*) {
	__push_heap(first, Distance((last - first) - 1), Distance(0), T(*(last - 1)));
	//以上系根据implicit representation heap的结构特性；新值必置于底部
	//容器的最尾端，此即第一个洞号：（last - first） - 1
}

//以下这组push_back()不允许指定“大小比较标准”
template<class RandomAccessIterator, class Distance, class T>
void __push_heap(RandomAccessIterator first, Distance holeIndex, Distance topIndex, T value) {
	Disrance parent = (holeIndex - 1) / 2;   //找出父节点
	while (holeIndex > topIndex && *(first + parent) < value) {  //父节点的值小于新值，
		                                                          //若此处的比较变为使用函数对象comp的方式实现
																  //应该默认comp为less
																  // 即 父节点 less value 此时，新值向上传递
																  // 最后产生大顶堆
																  // 若comp 为 more
																  // 产生小顶堆
		//当商未达到顶端，且父节点小于新值（于是不符合heap的次序特性）
		//由于以上使用operator<, 可知STL heap是一种max——heap
		*(first + holeIndex) = *(first + parent);  //令洞值为其父值
		holeIndex = parent;   //调整洞号
		parent = (holeIndex - 1) / 2;   //新洞的父节点
	}   //一直循环，持续到顶端 或 满足heap的次序特性为止
	*(first + holeIndex) = value;    //将value填入洞内    完成插入操作
}