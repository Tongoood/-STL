#pragma once
template<class T, class Alloc =alloc, size_t BufSiz = 0>
class deque {
public:
	typedef T value_type;
	typedef value_type* pointer;

protected:
	//元素的指针的指针
	typedef pointer* map_pointer;
protected:
	map_pointer map;   //指向map，map是块连续空间，其内的每个元素都是一个指针
	                   //（称为节点），指向一块缓冲区
	size_type map_size;   //map内可容纳多少指针
};