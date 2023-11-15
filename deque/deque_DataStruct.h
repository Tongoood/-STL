#pragma once
template<class T, class Alloc = alloc, size_t Bufsize = 0>
class deque {
public:
	typedef T value_type;
	typedef value_type* pointer;
	typedef size_t size_type;

public:
	typedef __deque_iterator<T, T&, T*, BufSiz> iterator;

protected:
	//元素的指针的指针
	typedef pointer* map_pointer;
protected:
	iterator start;    //第一个节点（第一个缓冲区的第一个元素）
	iterator finish;    //最后一个节点 （最后一个缓冲区的最后一个元素的下一个位置）

	map_pointer map;    //指向map，map是块连续空间
	                    //其每个元素都是个指针，指向一个节点（缓冲区）
	size_type map_size;   //map中有多少个指针

	//deque自行定义了两个专属的空间配置器
protected:
	//专属之空间配置器，每次配置一个元素大小
	typedef simple_alloc<value_type, Alloc> data_allocator;
	//专属之空间配置器,每次配置一个指针大小
	typedef simple_alloc<pointer, Alloc>map_allocator;

	//并提供一个constructor如下：
	deque(int n, const value_type& value)
		:start(), finish(), map(0), map_size(0)
	{
		fill_initialize(n, value);
	}

	//其内所调用的fill_initialize()负责产生并安排好deque的结构， 并将元素的初值设定妥当
	template<class T, class Alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::fill_initialize(size_type& value)
	{
		create_map_and_nodes(n);
		map_pointer cur;
		__STL_TRY{
			//为每个阶段的缓冲区设定初值
			for (cur = start.node; cur < finish.node; ++cur) {
				uninitialized_fill(*cur, *cur + buffer_size(), value);
				//最后一个节点的设定稍有不同（因为尾端可能有备用空间，不必设初值）
				uninitialized_fill(finish.first, finish.cur, value);
			}
		}
			catch () {

		}
	}


	//其中create_map_and_nodes()负责产生并安排好deque的结构
	template<class T, class ALLOC, size_t BufSize>
	void deque<T, Alloc, BufSize>::create_map_and_nodes(size_type num_elements)
	{
		//需要节点数 = （元素个数/每个缓冲区可容纳的元素个数）+1
		//如果刚好整除，会多配一个节点
		size_type num_nodes = num_elements / buffer_size() + 1;

		//一个map要管理几个节点。最少8个，最多是“所需节点数加2”
		//前后各预备一个，扩充时使用
		map_size = max(initial_map_size(), num_nodes + 2);
		map = map_allocator::allocate(map_size);

		//以上配置出一个 “具有mao_size个节点”的map

		//以下令nstart和nfinish指向map所拥有的全部节点的最中央区段
		//保持在最中央，可使头尾两端的扩充能量一样大，每个节点可对应一个缓冲区
		map_pointer nstart = map + (map_size - num_nodes);
		map_pointer nfinish = nstart + num_nodes - 1;

		map_pointer cur;
		__STL_TRY{
			//为map内的每个现用节点配置缓冲区，所有缓冲区加起来就是deque的
			//可用空间（最后一个缓冲区可能留有一些剩余）
			for (cur = nstart; cur <= nfinish; ++cur)
			{
				*cur = allocate_node();
			}
		}
			catch () {

		}

		//为deque内的两个迭代器start和end设定正确内容
		start.set_node(nstart);
		finish.set__node(nfinish);
		start.cur = start.first;
		finish.cur = finish.first + num_elements % buffer_size();
	}
};

//有了上述结构，下述机能便可以完成
public:
	iterator begin() { return start; }
	iterator end() { return finish; }

	reference operator[](size_type n) {
		return start[difference_type(n)];   //调用__Deque_itertaor<>::operator[]
	}
	reference front() { return *start; }
	reference back() {
		iterator tmp = finish;
		--tmp;
		return *tmp;
	}

	size_type size() const { return finish - start; }

	size_type max_size() const { return size_type(-1); }
	//当你使用 -1 来初始化无符号整数时，由于无符号整数没有负数的概念，编译器会将 -1 解释为最大可能的无符号整数值，即将所有比特都置为1
	//所以，使用 -1 来初始化无符号整数是一种常见的方式来表示无符号整数的最大值
	bool empty()const { return finish == start; }