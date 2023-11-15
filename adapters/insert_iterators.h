#pragma once

//insert iterators的主要观念是，每一个insert iterators内部都维护一个容器（必须由用户指定）
//容器有自己的迭代器，于是，客户端对insert iterators做赋值操作时，就在insert iterators中被转为对该容器的迭代器做插入操作
//也就是说inserrt iterators的operator=操作符中调用底层容器的push_front() push_back() insert()操作函数

//以下是迭代器配接器iterator adapter 用来将某个迭代器的赋值操作改为插入操作
//从容器尾端插入进去，back_insert
template<class Container>
class back_insert_iterator {
protected:
	Container* container;   //底层容器
public:
	typedef output_iterator_tag  iterator_category;   //注意类型
	typedef void   value_type;
	typedef void difference_type;
	typedef void pointer;
	typedef void reference;

	//下面这个ctor使back_insert_iterator与容器绑定起来
	explicit back_insert_iterator(Container& x):container(&x) {}
	back_insert_iterator<Container>& operator=(const typename Container::value_type& value) {
		container->push_back(value);               //这是关键，转而调用push_back()
		return *this;
	}

	//以下三个操作符对back_insert_iterator不起作用（关闭功能）
	back_insert_iterator<Container>& operator*() { return *this; }
	back_insert_iterator<Container>& operator++() { return *this; }
	back_insert_iterator<Container>& operator++(int) { return *this; }   //iterator++
};

//下面是一个辅助函数，帮助我们方便使用back_insert_iterator
template<class Container>
inline back_insert_iterator<Container> back_inserter(Container& x) {
	return back_insert_iterator<Container>(x);
}

//以下是iterator adapter将赋值操作改为前插
//前插不适用vector，因为vector没有提供push_front函数
template<class Container>
class front_insert_iterator {
protected:
	Container* container;   //底层容器
public:
	typedef output_iterator_tag  iterator_category;   //注意类型
	typedef void   value_type;
	typedef void difference_type;
	typedef void pointer;
	typedef void reference;

	//下面这个ctor使back_insert_iterator与容器绑定起来
	explicit front_insert_iterator(Container& x) :container(&x) {}
	back_insert_iterator<Container>& operator=(const typename Container::value_type& value) {
		container->push_front(value);               //这是关键，转而调用push_back()
		return *this;
	}

	//以下三个操作符对back_insert_iterator不起作用（关闭功能）
	front_insert_iterator<Container>& operator*() { return *this; }
	front_insert_iterator<Container>& operator++() { return *this; }
	front_insert_iterator<Container>& operator++(int) { return *this; }   //iterator++
};

//下面是一个辅助函数，帮助我们方便使用back_insert_iterator
template<class Container>
inline front_insert_iterator<Container> front_inserter(Container& x) {
	return front_insert_iterator<Container>(x);
}


//以下是iterator adapter将赋值操作改为插入操作
template<class Container>
class insert_iterator {
protected:
	Container* container;   //底层容器
	typename Container::iterator iter;
public:
	typedef output_iterator_tag  iterator_category;   //注意类型
	typedef void   value_type;
	typedef void difference_type;
	typedef void pointer;
	typedef void reference;

	//下面这个ctor使back_insert_iterator与容器绑定起来
	explicit front_insert_iterator(Container& x， typename Container::iterator i) :container(&x),iter(i) {}
	insert_iterator<Container>& operator=(const typename Container::value_type& value) {
		iter = container->insert(iter,value);               //这是关键，转而调用push_back()
		++iter;
		return *this;
	}

	//以下三个操作符对back_insert_iterator不起作用（关闭功能）
	insert_iterator<Container>& operator*() { return *this; }
	insert_iterator<Container>& operator++() { return *this; }
	insert_iterator<Container>& operator++(int) { return *this; }   //iterator++
};

//下面是一个辅助函数，帮助我们方便使用back_insert_iterator
template<class Container>
inline insert_iterator<Container> inserter(Container& x) {
	return insert_iterator<Container>(x);
}