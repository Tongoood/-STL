//sgl list不仅是一个双向链表，而且还是一个环状双向链表，所欲它只需要一个指针，便可以完成表现整个链表
template<class t, class alloc=alloc>
class list {
protected:
	typedef __list_node<t> list_node;
public:
	typedef list_node* link_type;

protected:
	link_type node;  //只要一个指针，便可以表示整个环状双向链表
};

//如果指针node指向刻意置于尾端的一个空白节点
iterator begin() { return(link_type)((*node).next); }
iterator end() { return node; }

bool empty() const { return node->next == node; }
size_type size() const {
	size_type result = 0;
	distance(begin(), end(0, result);
	return result;
}

reference front() { return *begin(); }
reference back() { return *(--end()); }
