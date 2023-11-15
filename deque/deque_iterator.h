

//deque迭代器
//首先，它必须能够指出连续分段空间，其次它必须能哦按段自己是否已经处于其所在缓冲区的边缘
//如果是，一旦前进或后退时就必须跳跃至下一个或上一个缓冲区，为了能够正确跳跃
//deque必须随时常掌握管控中心（map）
//以下为具体实现

template<class T, class Ref, class Ptr, size_t BufSiz>
struct __deque_iterator {  //未继承std::iterator
	typedef __deque_iterator<T, T&, T*, BufSiz>   iterator;
	typedef __deque_iterator<T, const T&, const T*, BufSiz> const_iterator;
	static size_t buffer_size() { return __deque_buf_size(BufSiz, sizeof(T)); }


	//未继承std::iterator 所以必须自行撰写五个必要的得带起相应型别
	typedef random_access_iterator_tag iterator_category;
	typedef T value_type;
	typedef Ptr pointer;
	typedef Ref reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef T** map_pointer;

	typedef __deque_iterator self;

	//保持与容器的联结 
	T* cur;      //此迭代器所指之缓冲区的现行（current）元素
	T* first;    //此迭代器所指之缓冲区的头
	T* last;     //此迭代器所指之缓冲区的尾（含备用空间）
	map_pointer bode;    //指向管控中心



	//deque的迭代器利用set_node跳一个缓冲区
	void set_node(map_pointer new_node) {
		node = new_node;
		first = *new_node;
		last = first + difference_type(buffer_size());
	}


	//以下各个重载运算子是__deque_iterator<>成功运作的关键
	reference operator*() const { return *cur; }
	//这意味着对于参数列表传入的对象，其成员变量是只读的，不会被修改。
	// 这个const关键字的存在可以保证在常成员函数内部，不会对对象的状态做出任何改变，从而确保对象的状态不会被意外地修改。
	pointer operator->() const { return &(operator*()); }
	difference_type operator-(const self& x) const {
		return difference_type(buffer_size()) * (node - x.node - 1) + (cur - first) + (x.last - x.cur);
	}

	self& operator++() {
		++cur;
		if (cur == last) {
			set_node(node + 1);
			cur = first;
		}
		return *this;
	}

	self& operator--() {    //前置递减
		if (cur == first) {
			set_node(node - 1);
			cur = last;
		}
		--cur;
		return *this;
	}
	self operator--(int) {    //后置式，标准写法
		self tap = *this;
		--*this;
		return tmp;
	}

	//以下实现随机存取，迭代器可以直接跳跃n个距离
	self& operator+=(differenxe_type n) {
		difference_type offset = n + (cur - first);
		if (offset >= 0 && offset < difference_type(buffer_size()))
			//目标在同一缓冲区
			cur += n;
		else
		{//目标的位置不在同一缓冲区内
			difference_type node_offset =
				offset > 0 ? offset / difference_type(buffer_size())
				: -difference_type((-offset - 1) / buffer_size()) - 1;
			//切换至正确的节点（亦即缓冲区）
			set_node(node + node_offset);
			//切换至正确的元素
			cur = first + (offset - node_offset * difference_type(buffer_size());
		}
		return *this;
	}

	self& operator+(difference_type n) const {
		self tmp = *this;
		return tmp += n;
	}

	self& operator-+(difference_type n) { return *this += (-n); }

	self& operator-=(difference_type n) const {
		self tmp = *this;
		return tmp -= n;
	}


	//以下实现随机存取
	reference operator[](difference_type n) const { return *(*this + n); }


	bool operator==(const self& x) const { return cur == x.cur; }
	bool operator!=(const self& x) const { return !(*this == x); }
	bool operator<(const self& x) const {
		return (node == x.node) ? (cur < x.cur) : (node < x.node);
	}


	//以下是push_back()函数内容

public:
	void push_back(const value_type& t) {
		if (finish.cur != finish.last - 1) {
			//最后缓冲区尚有一个以上的备用空间
			construct(finish.cur, t);  //直接在备用空间上构造元素
			++finish.cur;    //调整最后缓冲区的使用状态
		}
		else    //最后缓冲回去已没了
			push)back_aux(t);
	}


	//只有当finish.cur==finish.last-1时才会调用push_back_aux()
	//也就是说，只有当最后一个缓冲区只剩下一个备用元素空间时才会被调用
	template<class T, class Alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::push_back_aux(const value_type& t) {
		value_type t_copy = t;
		reserve_map_at_back();
		*(finish.node + 1) = allocate_node();
		__STL_TRY{
			construct(finish.cur, t_copy);
		finish.set_node(finish.node + 1);
		finish.cur = finish.first;
		}
		__STL_UNWIND(deallocate_node(*(finish.node + 1)));
	}

public:
	void push_front(const value_type& t) {
		if (start.cur!- start.first) {
			construct(start.cur - 1, t);
			--start.cur;
		}
		else
			push_front_aux(t);
	}

	//由于目前状态下，第一缓冲区并无备用空间，所以调用push_front_aux()


	//只有当start.cur ==start.first时才会被调用
	template<class T, class Alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::push_front_aux(const value_type& t)
	{
		value_type t_copy = t;
		reserve_map_at_front();     //若符合某种条件则必须重新换一个map
		__STL_TRY{
			start.set_note(start.node - 1);    //配置一个新节点
		start.cur = start.last - 1;
		construct(start.cur, t_copy);
		}
			catch () {
			start.set_node(start.node + 1);
			stat.cur = start.first;
			deallocate_node(*(start.node - 1));
			throw;
		}
	}


	//什么时候map需要重新整治？
	//这个问题的判断由reserve_map_at_back()和reserve_map_at_front()进行，实际操作则由reallocate_map()执行

	void reserve_map_at_back(size_type nodes_to_add = 1) {
		if (nodes_to_add + 1 > map_size - (finish.node - map))
			//如果map尾端的节点备用空间不足
			//符合以上条件则必须冲换一个map（配置更大的，拷贝原来的，释放现在的）
			reallocate_map(nodes_to_add, false);
	}

	void reserve_map_at_front(size_type nodes_to_add = 1) {
		if (nodes_to_add > start.node - map)
			//如果map前端的节点备用空间不足
			//符合以上条件则必须重换一个map、
			reallocate_map(nodes_to_add, true);
	}

	template<class T, class Alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::reallocate_map(size_type nodes_to_add, bool add_at_front) {
		size_type old_num_nodes = finish.node - start.node + 1;
		size_type new_num_nodes = old_num_nodes + nodes_to_add;

		map_pinter new_nstart;
		if (map_size > 2 * new_num_nodes) {
			new_nstart = map + (map_size - new_num_nodes) / 2 + (add_at_front ? nodes_to_add : 0);
			if (new_nstart < start.node)
				copy(start.node, finish.node + 1, new_nstart);
			//因为finish.node代表的是map中最后一个元素，
			// 但是由于copy这个函数输入的作用域是[)前闭后开的，所以，必须使用finish.node+1作为开区间的参数输入才能得到完整的map区间
			else
				copy_backward(start.node, finish.node + 1, new_start + old_num_nodes);

		}
		else {
			map_pointer new_map_size = map_size + max(map_size, nodes_to_add) + 2;
			//这里的 +2 是为了确保在新的 map 中预留两个额外的节点空间，以便在将来可能的扩展中有足够的缓冲区空间可用。
			// 这两个额外的节点是为了容纳新元素，以及在可能的重新分配期间允许扩展缓冲区而保留的
			
			//配置一块空间，准备给新map用
			map_pointer new_map = map_allocator::allocate(new_map_size);
			new_nstart = new_map + (new_map_size - new_num_nodes) / 2 + (add_at_front ? nodes_to_add : 0);

			//把原map内容拷贝过来
			copy(start.node, finish.node + 1, new_start);
			//释放原map
			map_allocator::deallocate(map, map_size);
			//设定新map的起始地址与大小
			map = new_map;
			map_size = new_map_size;
		}
		//重新设定迭代器start和finish
		start.set_node(new_nstart);
		finish.set_node(new_nstart + old_num_nodes - 1);
	}




	//=======================================================================================
	//deque的元素操作
	//无论从deque的最前端或最尾端取元素，都需要考虑在某种条件下，将缓冲区释放掉
	void pop_back() {
		if (finish.cur != finish.first) {
			//最后缓冲区有一个（或更多）元素
			--finish.cur;
			destroy(finish.cur);   //将最后元素析构
		}
		else {
			//最后缓冲区没有任何元素
			pop_back_aux();    //这里将进行缓冲区的释放工作
		}
	}

	//只有当finish.cur ==finish.first时才会被调用
	template<class T, class Alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::pop_back_aux() {
		deallocate_node(finish.first);
		finish.set_node(finish.node - 1);
		destroy(finish.cur);
	}

	void pop_fornt() {
		if (start.cur != start.last - 1) {
			destroy(start, cur);
			++start.cur;
		}
		else
		{
			pop_front_aux();
		}
	}

	//只有当start.cur==start.last-1时才会调用
	template<class T, class Alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::pop_front_aux() {
		destroy(start.cur);
		deallocate_node(start.first);
		start.set_node(start.node + 1);
		start.cur = start.first;
	}


	//下面是clear(),用来清除整个deque，deque的最初状态保有一个缓冲区，因此，clear完成之后回复初始状态，也一样要保留一个缓冲区
	template<class T, class Alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::clear() {
		//以下针对头尾意外的每一个缓冲区
		for (map_pointer node = start.node + 1; node < finish.node; ++node) {
			//将缓冲区的所有元素析构，注意，调用的是destroy（）
			destroy(*node, *node + buffer_size());
		}

		if (start.node != finish.node) {
			//start 和 finish 分别指向 deque 的起始位置和结束位置，
			// 它们的 cur 成员默认分别指向当前缓冲区的第一个元素和最后一个元素的下一个位置
			destroy(start.cur, start.last);    //将头缓冲区的元素全部析构
			destroy(finish.first, finish.cur);   //将尾缓冲区的目前的所有元素析构
			//以下释放尾缓冲区，头缓冲区保留
			data_allocator::deallocate(finish.first, buffer_size());
		}
		else   //只有一个缓冲区
			destroy(start.cur, start.last);

		finish = start;  //调整状态
	}


	iterator erase(iterator pos) {
		iterator next = pos;
		++next;
		difference_type index = pos - start;
		if (index < (size()) >> 1) {    //清楚点之前的元素个数
			copy_backward(start, pos, next);
			pop_front();
		}
		else {
			copy(next, finish, pos);
			pop_back();
		}
		return start + index;
	}


	//下面的erase用来清除[first, last)中的元素
	template<class T, class Alloc, size_t BufSize>
	deque<T, Alloc, BufSize>::iterator   //返回值
		deque<T, Alloc, BufSize>::erase(iterator first, iterator last) {
		if (first == start && last == finish) {
			//如果清除区间就是整个deque  直接调用clear
			clear();
			return finish;
		}
		else {
			difference_type n = last - first;                  //清除区间的长度
			difference_type elems_before = first - start;     //清楚区间前方的元素个数
			if (elems_before < (size() - n) / 2) {        //如果前方的元素比较少
				copy_backward(start, first, last);      //向后移动前方元素（覆盖清除区间）
				iterator new_start = start + n;         //标记deque的新起点
				destroy(start, new_start);              //移动完毕，将冗余的元素析构
				//以下将冗余的缓冲区释放
				for (map_pointer cur = start.node; cur < new_start.node; ++cur)
					data_allocator::deallocate(*cur, buffer_size());
				start = new_start;    //设定deque的新起点
			}
			else {       //如果清除区间后方的元素比较少
				copy(last, finish, first);
				iterator new_finish = finish - n;
				destroy(new_finish, finish);
				//以下将冗余的缓冲区释放
				for (map_pointer cur = new_finish.node + 1; cur <= finish.node; ++cur)
					data_allocator::deallocate(*cur, buffer_size());
				finish = new_finish;    //设定deque的新尾点
			}
			return start + elems_before;
		}
	}

	//在position处插入一个元素，其值为x
	iterator insert(iterator position, const value_type& x) {
		if (position.cur == start.cur) {   //如果插入点是deque的最前端
			push_front(x);
			return start;
		}
		else if (position.cur == finish.cur) {    //如果插入点是deque的最尾端
			push_back(x);
			itertaor tmp = finish;
			--tmp;
			return tmp;
		}
		else {
			return insert_aux(position, x);     //如果不是最前或者最后，那么就交给insert_aux去做
		}
	}

	template<class T, class Alloc, Size_t BufSize>
	typename deque<T, Alloc, BufSize>::iterator
		deque<T, Alloc, BufSize>::insert_aux(iterator pos, const value_type& x) {
		difference_type index = pos - start;   //插入点之前的元素个数
		value_type x_copy = x;
		if (index < size() / 2)          //如果插入点之前的元素个数比较少
		{
			push_front(front());//在最前端加入与第一个元素同值的元素
			iterator front1 = start;
			++front1;
			iterator front2 = front1;
			++front2;
			pos = start + index;
			iterator pos1 = pos;
			++pos1;
			copy(front2, pos1, front1);     //元素移动
		}
		else {       //插入点之后的元素个数比较少
			push_back(back());
			iterator back1 = finish;
			--back1;
			iterator back2 = back1;
			--back2;
			pos = start + index;
			copy_backward(pos, back2, back1);         //元素移动
		}
		*pos = x_copy;   //在插入点上设定新值
		return pos;

	}

};

//其中用来决定缓冲区大小的函数buffer_size(),调用__deque_buf_size(),后者是一个全局函数
//定义如下

//如果n不为0，传回n，表示buffer size由用户自定义
//如果n为0，表示buffer size使用默认值，那么
//如果sz（元素大小，sizeof（value_type）小于512，传回512/sz  ）
//如果sz不小于512，传回1

inline size_t __deque_buf_size(size_t n, size_t sz)
{
	return n != 0 ? n : (sz < 512 ? size_t(512 / sz) : size_t(1));
}

