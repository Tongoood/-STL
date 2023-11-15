#include<iostream>
#include<deque>
#include<algorithm>


int main()
{
	//std::deque<int> Mydeque;
	//Mydeque.push_back(10);
	//Mydeque.push_back(20);
	//auto first = Mydeque.begin();
	//auto last = Mydeque.end();
	//std::cout << *first << std::endl;
	//std::cout << *(--last) << std::endl;   //20   证明deque的last也是指向最后一个空间的下一个空间，[)前闭后开区间

	std::deque<int> ideq(20, 9);
	std::cout << "size=" << ideq.size() << std::endl;
	std::cout << "============================================================" << std::endl;

	for (int i = 0; i < ideq.size(); ++i) {
		ideq[i] = i;
	}

	for (auto e : ideq) {
		std::cout << e << " ";
	}
	std::cout << std::endl;
	std::cout << "============================================================" << std::endl;

	for (int i = 0; i < 3; i++) {
		ideq.push_back(i);
	}

	for (auto e : ideq) {
		std::cout << e << " ";
	}
	std::cout << std::endl;
	std::cout << "size=" << ideq.size() << std::endl;
	std::cout << "============================================================" << std::endl;


	ideq.push_back(3);
	for (auto e : ideq) {
		std::cout << e << " ";
	}
	std::cout << std::endl;
	std::cout << "size=" << ideq.size() << std::endl;
	std::cout << "============================================================" << std::endl;

	ideq.push_front(99);
	for (auto e : ideq) {
		std::cout << e << " ";
	}
	std::cout << std::endl;
	std::cout << "size=" << ideq.size() << std::endl;
	std::cout << "============================================================" << std::endl;

	ideq.push_front(98);
	ideq.push_front(97);
	for (auto e : ideq) {
		std::cout << e << " ";
	}
	std::cout << std::endl;
	std::cout << "size=" << ideq.size() << std::endl;
	std::cout << "============================================================" << std::endl;


	std::deque<int>::iterator itr;
	itr = find(ideq.begin(), ideq.end(), 99);
	std::cout << *itr << std::endl;

	ideq.pop_back();

}