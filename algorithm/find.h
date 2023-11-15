#pragma once
template<class T>
T* find(T* begin, T* end, const T& value)
{
	while (begin != end && *begin() != value)
		++begin;
	return begin;
}