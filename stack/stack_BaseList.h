#pragma once
//test.cpp

#include<stack>
#include<list>
#include<iostream>
#include<algorithm>

int main()
{
	std::stack<int, std::list<int>> istack;
	istack.push(1);
	istack.push(3);
	istack.push(5);
	istack.push(7);

	std::cout << istack.size() << std::endl;
	std::cout << istack.top() << std::endl;


	istack.pop();
	std::cout << istack.top() << std::endl;


	istack.pop();
	std::cout << istack.top() << std::endl;

	istack.pop();
	std::cout << istack.top() << std::endl;

	std::cout << istack.size() << std::endl;



	return 0;

}