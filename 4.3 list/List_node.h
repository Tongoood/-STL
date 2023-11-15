#pragma once


template<class T>
struct __list_node {
	typedef void* void_pointor;
	void_pointor prev;    //型别为void*，其实可以设为__list_node<T>*    
	//使用 void* 类型的节点指针是为了处理任意类型的数据，包括用户自定义的数据类型
	void_pointer next;
	T data;

};

//显然是一个双向链表

//__list_node<T>* 表示指向 __list_node<T> 结构体的指针
// 而 T* 表示指向 T 类型的数据的指针。这两种指针类型的用途和作用对象是不同的，
// 前者通常用于管理链表节点结构，后者用于指向链表节点中存储的数据