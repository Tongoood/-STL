#pragma once
//单向链表的节点结构
struct __slist_node_base
{
	__slist_node_base* next;
};

//单向链表的节点结构
template<class T>
struct __slist_node :public __slist_node_base
{
	T data;
};

//因为链表节点的指向下一个节点的指针类型是通用的，而节点存放的数据类型是特定的，所以需要将通用部分（指针类型）
// 和特定部分（数据类型）分开写，以实现链表的灵活性和重用性。这个设计允许你在同一个链表中存储不同数据类型的节点，同时共享通用的节点结构


//全局函数：已知某一节点，插入新节点于其后
inline __slist_node_base* __slist_make_link(
	__silist_node_base* prev_node,
	__slist_node_base* new_node
)
{
	new_node->next = prev_node->next;
	prev_node->next = new_node;
	return new_node;
}

//全局函数，单向链表的大小
inline size_t __slist_size(__slist_node_base* node)
{
	size_t result = 0;
	for (; node != 0; node = node->next)
		++result;
	return result;
}