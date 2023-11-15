#pragma once
//vector是单向开口的连续线性空间
//deque则是一种双向开口的连续线性空间，
//所谓双向开口，意思是可以在头尾两端分别做元素的插入和删除操作
//vector也可以在头尾两端进行操作，但是vector头部操作效率很差，无法被接受

//deque与vector的最大差异，在于deque允许常数时间内对头端进行元素的插入或移除操作
//二在于deque没有所谓容量观念
//deque是动态地以分段空间组合而成，随时可以增加一段新的空间并链接起来

//虽然deque也提供了random access iterator，但它的迭代器不是普通指针
//因此，应该尽可能用vector而不是deque
//对deque进行排序操作，可以将deque完整复制到一个vector身上，而将vector排序后，再复制回deque
