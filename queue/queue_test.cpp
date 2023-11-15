#include<queue>
#include<list>
#include<iostream>
#include<algorithm>

int main()
{
	std::queue<int, std::list<int>> iqueue;
	iqueue.push(1);
	iqueue.push(3);
	iqueue.push(5);
	iqueue.push(7);

	std::cout << iqueue.size() << std::endl;
	std::cout << iqueue.front() << std::endl;

	iqueue.pop(); std::cout << iqueue.front() << std::endl;
	iqueue.pop(); std::cout << iqueue.front() << std::endl;
	iqueue.pop(); std::cout << iqueue.front() << std::endl;


	std::cout << iqueue.size() << std::endl;

	return 0;

}