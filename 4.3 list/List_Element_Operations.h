﻿
//插入一个节点作为头节点
void push_front(const T& x x) { insert(begin(), x); }
//插入一个节点，作为尾节点
void push_back(const T& x) { insert(end(), x); }

//移除迭代器position所指节点
iterator erase(iterator position) {
	link_type next_node = link_type(position.node->next);
	link_type prev_node = link_type(position.node->prev);
	prev_node->next = next_node;
	next_node->prev = prev_node;
	destroy_node(position.node);
	return iterator(next_node);
}

//移除头节点
void pop_front() { erase(begin()); }
//移除尾节点
void pop_back() {
	iterator tmp = end();
	erase(--tmp);
}

//清除所有节点（整个链表）
template<class T, class Alloc>
void list<T, Alloc>::clear()
{
	link_type cur = (link_type)node->next;    //begin()
	while (cur != node) {  //遍历每一个节点
		link_type tmp = cur;
		cur = (link_type)cur->next;
		destroy_node(tmp);    //销毁（析构并释放）一个节点
	}
	//恢复node原始状态
	node->next = node;
	node->prev = node;     //此时为空链表
}

//将数值为value的所有元素移除
template<class T, class Alloc>
void list<T, Alloc>::remove(const T& value) {
	iterator first = begin();
	iterator end = end();
	while (first != last) {
		iterator next = first;
		++next;
		if (*first == value) erase(first);
		first = next;
	}
}

//移除数值相同的连续元素，注意，只有连续而相同的元素，才会被移除剩一个
template<class T, class Alloc>
void list<T, Alloc>::unique() {
	iterator first = begin();
	iterator last = end();
	if (first == last) return;     //如果是空链表什么都不做
	iterator next = first;
	while (++next != last) {
		if (*first == *next)
			erase(first);
		else
			first = next;
		next = first;    //修正区段范围
	}
}


//list内部提供一个所谓的迁移操作（transfer），将某个连续范围的元素迁移到某个特定位置之前，这个操作为其它的复杂操作
//splice， sort， merge等奠定了良好的基础
//下面是transfer的源代码：

protected:
	//将[first, last)内的所有元素移动到position之前
	void transfer(iterator position, iterator last, iterator last) {
		if (position != last) {
			(*(link_type((*last.node).prev))).next = position.node;
			(*(link_type((*first.node).prev))).next = last.node;
			(*(link_type((*position.node).prev))).next = first.node;

			link_type tmp = link_type((*position.node).prev);
			(*position.node).prev = (*last.node).prev;
			(*last.node).prev = (*first.node).prev;
			(*first.node).prev = tmp;
		}
	}

	//上述的transfer并非公考接口，list公开提供的是所谓的接合操作（splice）：将某连续范围的元素从一个list移动到另一个list的
	//定点（之前），

	//为了提供各种接口弹性，list<T>::splice有许多版本
public:
	//将x接合于position所指位置，x必须不同于*this
	void splice(iterator position, list& x) {
		if (!x.empty())
			transfer(position, x.begin(), x.end());
	}

	//将i所指的元素接合于position所指位置之前、
	void splice(iterator position, list&, iterator i) {
		iterator j = i;
		++j;
		if (position == i || position == j)return;
		transfer(position, i, j);

	}

	//将[first, last)内的所有元素接合于position所指位置之前
	//position和[first,last)可能指向同一个list
	//但position不能位于first，last之间
	void splice(iterator position, list&, iterator first, iterator last) {
		if (first != last)
			transfer(position, first, last);
	}


//merge()
template<class T, class Alloc>
void list<T, Alloc>::merge(list<T, Alloc>& x) {
	iterator first1 = begin();
	iterator last1 = end();
	iterator first2 = x.bengin();
	iterator end2 = x.end();

	//请注意，以下操作的前提是两个lists都已经经过递增排序
	while (first1 != last1 && first2 != end2) {
		if (*first2 < *first1) {
			iterator next = first2;
			transfer(first1, first2, ++next);
			first2 = next;
		}
		else ++first1;
	}
	if (first2 != last2) transfer(last1, first2, last2);
}


//reverse将*this的内容逆向重置
template<class T, class Alloc>
void list<T, Alloc>::reverse() {
	//以下判断，如果是空链表，或仅有一个元素，则不进行任何操作
	//使用size()==0||size()==1来判断，虽然也可以，但是比较慢
	if (node->next == node || link_type(node->next)->next == node)
		return;
	iterator first = begin();
	++first;
	while (first != end()) {
		iterator old = first;
		++first;
		transfer(begin(), old, first);
	}
}

//list不能使用stl的sort（），必须使用自己的sort（）  成员函数
//因为stl的sort（）算法只接受RadomaAcessIterator
//本函数采用quick sort
template<class T, class Alloc>
void list<T, Alloc>::sort() {
	//	//以下判断，如果是空链表，或仅有一个元素，则不进行任何操作
	if (node->next == node || (node->next)->next == node)
		return;
	//一些新的lists，作为中介数据存放区
	list<T, Alloc> carry;
	list<T, Alloc>counter[64];
	int fill = 0;
	while (!empty()) {   
		carry.splice(carry.begin(), *this, begin());
		//在每次循环迭代中，它会将原链表的第一个元素（使用 begin() 函数获得）移动到 carry 中，这样做是为了准备将这个元素与其他元素进行合并。
		int i = 0;
		while (i < fill && !counter[i].empty()) {
			counter[i].merge(carry);
			carry.swap(counter[i++]);
		}
		carry.swap(counter[i]);
		if (i == fill) ++fill;
	}

	for (int i = 1; i < fill; ++i)
		counter[i].merge[counter[i - 1]];
	swap(counter[fill - 1]);
}