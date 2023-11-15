#pragma once

template<class T, class Alloc = alloc>
class vector {
public:
	//vector 的嵌套型别定义
	typedef T         value_type;
	typedef value_type* pointer;
	typedef value_type* iterator;
	typedef value_type& reference;
	typedef size_t size_type;
	typedef ptrdiff_t  difference_type;

protected:
	typedef simple_alloc<value_type, Alloc> data_allocator;
	iterator start;    //表示目前空间的头
	iterator finish;   //表示目前空间的尾
	iterator end_of_storage;   //表示目前可用空间的尾

	void insert_aux(iterator position, const T& x);
	void deallocate() {
		if (start)
			data_allocator::deallocate(start, end_of_storage - start);
	}
	void fill_initialize(size_type n, const T& value) {
		start = alloate_and_fill(n, value);
		finish = start + n;
		end_of_storage = finish;
	}
public:
	iterator begin() { return start; }
	iterator end() { return finish; }
	size_type size() const { return size_type(end() - begin()); }
	size_type capacity() const { return end_of_storage - begin(); }
	bool empty() const { return begin() == end(); }
	reference operator[] (siize_type n) { return *(begin() + n); }

	vector() :start(0), finish(0), end_of_storage(0) {}
	vector(size_type n, const T& value) { fill_initialize(n, value); }
	vector(int n, const T& value) { fill_initialize(n, value); }
	vector(long n, const T& value) { fill_initialize(n, value); }
	explicit vector(size_type n) { fill_initialize(n, T()); }

	~vector() {
		destroy(start, finish);
		deallocate();
	}
	reference front() { return *begin(); }   //第一个元素
	reference back() { return *(end() - 1); }   //最后一个元素
	void push_back(const T& x) {
		//construct 函数用于在已分配的内存空间中构造对象。在你的代码片段中，它被用于在 finish 指针指向的位置构造一个类型为 T 的对象，
		// //然后将 finish 后移，以便在 vector 中添加一个元素。
		//这种方式确实实现了在 vector 尾部添加元素的操作，即将元素构造在已分配的内存中，然后递增 finish 指针以指向新添加的元素的位置。
		if (finish != end_of_storage) {
			construct(finish, x);
			++finish;
		}
		else
			insert_aux(end(), x);
	}

	void pop_back() {
		--finish;
		destroy(finish);
	}

	iterator erase(iterator position) {     //清除某位置元素
		if (position + 1 != end())
			copy(position + 1, finish, position);   //后续元素往前移动
		--finish;
		destroy(finish);
		return position;
	}

	//copy函数具体实现细节
	/*===========================================================================================================
	template<class InputIterator, class OutputIterator>
	OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result) {
		while (first != last) {
			*result = *first;
			++result;
			++first;
		}
		return result;
	}
	==============================================================================================================*/

	void resize(size_type new_size, const T& x) {
		if (new_size < size())
			rease(begin() + new_size, end());
		else
			insert(end(), new_size - size(), x);
	}

	void resize(size_type new_size) { resize(new_size, T()); }
	void clear() { rease(begin(), end()); }

protected:
	//配置空间并填满内容
	iterator allocats_and_fill(size_type n, const T& x) {
		iterator result = data_allocator::allocate(n);
		uninitialized_fill_n(result, n, x);
		return result;
	}
};


//vector提供的是Random Access Iterators
template<class T, class Alloc = alloc>
class vector {
public:
	typedef T           value_type;
	typedef value_type* iterator;
	//...
};

//根据上面的定义，那么如下：
vector<int>::iterator ivite;
vector<Shape>::iterator svite;
//ivite的型别就是 int*, svite的型别就是Shape*

//为了降低空间配置时的时间成本，vector实际配置的大小可能比客户端需求量更大一些，以备将来可能的扩充，



//将尾端元素拿掉，并调整大小
void pop_back() {
	--finish;
	destroy(finish);
}

//清除（first， last）中的所有元素
iterator erase(iterator first, iterator last) {
	iterator i = copy(last, finish, first);
	destroy(i, finish);
	finish = finish - (last - first);
	return first;
}

//清除某个位置上的元素
iterator erase(iterator position) {
	if (position + 1 != end())
		copy(position + 1, finish, position);
	--finish;
	destroy(finish);
	//在--finish之后，finish指向的就是原来的最后一个元素，这样destroy finish之后，就会将原来的最后一个元素销毁掉
	return position;
}

void clear() { erase(begin(), end()); }


//下面是vector::insert()实现内容
//从position位置开始，插入n个元素，元素初值为x
template<class T, class Alloc>
void vector<T, Alloc>::insert(iterator position, size_type n, const T& x)
{
	if (n != 0) {    //当插入元素的数量不为0时，再执行操作
		if (size_type(end_of_storage - finish) >= 0) {
			//备用空间大于等于新增元素个数
			T x_copy = x;
			//一下计算插入点之后的现有元素个数
			const size_type elem_after = finish - position;
			iterator old_finish = finish;
			if (elems_after > n) {
				//插入点之后的现有元素个数大于新增元素个数
				uninitialized_copy(finish - n, finish, finish);
				finish += n;    //将尾端后移
				copy_backward(position; old_finish - n; old_finish);
				fill(position, position + n, copy_x);
			}
			else {
				//如果插入点之后的现有元素个数“小于等于”新增元素个数
				uninitialized_fill_n(finish, n - elems_after, x_copy);
				finish += n - elems_after;
				uninitialized_copy(position, old_finish, finish);
				finish += elems_after;
				fill(position, old_finish, x_copy);
			}
		}
		else {
			//备用空间小于“新增元素个数”（那就必须配置额外的内存）
			//首先决定新长度：旧长度的两倍，或旧长度+新增元素个数
			const size_type old_size = size();
			const size_type len = old_size + max(old_size, n);
			//以下配置新的vector空间
			iterator new_start = data_allocator::allocate(len);
			iterator new_finish = new_start;
			__STL_TRY{
				//以下先将vector的插入点之前的元素复制到新空间
				new_finish = uninitialized_copy(start, position, new_start);
				//以下再将新增元素（初值皆为x）
				new_finish = uninitialized_fill_n(new_finish, n, x);
				//以下再将旧vector中插入点之后的元素复制到新空间
				new_finish = uninitialized_copy(position, finish, new_finish);
				//uninitialized_copy 函数用于将一个范围内的元素从一个位置复制到另一个位置，并返回一个指向复制完结尾的迭代器
			}
#ifdef  __STL_USE_EXCEPTIONS
				catch () {
				//如果有异常发生， 实现“commit or rollback”semantics
				destroy(new_start, new_finish);
				data_allocator::deallocate(new_start, len);
				throw;
			}
#endif/*  __STL_USE_EXCEPTIONS */
			//以下清除并释放旧的vector
			destroy(start, finish);
			deallocate();
			//以下调整标记位置
			start = new_start;
			finish = new_finish;
			end_of_storage = new_start + len;
		}

	}
}