#pragma once
#include<iostream>


template <typename T>
class ListItem;

template <typename T>
class List
{
public:
	void insert_front(T value);
	void insert_end(T value);
	void display(std::ostream& os = std::cout) const
	{
		auto start = _front;
		for (start; start != _end; start++) {
			std::cout << *_end << std::endl;
		}
	}
	//..
private:
	ListItem<T>* _end;
	ListItem<T>* _front;
	long _size;
};


template <typename T>
class ListItem
{
public:
	T value() const { return _value; }
	ListItem* next() const { return _next; }

private:
	T _value;
	ListItem* _next;    //单向列表
};