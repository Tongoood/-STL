#pragma once
#include"mylist.h"

template<class Item>
struct ListIter
{
	Item* ptr;

	ListIter(Item* p = 0) :ptr(p) {}

	Item& operator*() const { return *ptr; }
	Item* operator->() const { return ptr; }

	//(1) pre-increment operator
	ListIter& operator++()
	{
		ptr = ptr->next(); 
		return *this;
	}

	//(2) post-increament operator
	ListIter operator++(int)
	{
		ListIter tmp = *this;
		++*this;
		return tmp;
	}

	bool operator==(const ListIter& i) const
	{
		return ptr == i.ptr;
	}

	bool operator!=(const ListIter& i) const
	{
		return ptr != i.ptr;
	}
};