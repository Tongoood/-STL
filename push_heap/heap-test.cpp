
#include<vector>
#include<iostream>
#include<algorithm>

int main()
{
	{
		//底层以vector完成
		int ia[9] = { 0,1,2,3,4,8,9,3,5 };
		std::vector<int> ivec(ia, ia + 9);
		std::cout << "test based vector" << std::endl;
		std::cout << "===============================================" << std::endl;

		make_heap(ivec.begin(), ivec.end());
		for (auto e : ivec)
			std::cout << e << ' ';
		std::cout << std::endl;
		std::cout << "===============================================" << std::endl;

		ivec.push_back(7);
		push_heap(ivec.begin(), ivec.end());
		for (auto e : ivec)
			std::cout << e << ' ';
		std::cout << std::endl;
		std::cout << "===============================================" << std::endl;

		pop_heap(ivec.begin(), ivec.end());
		std::cout << ivec.back() << std::endl;
		std::cout << "===============================================" << std::endl;

		for (auto e : ivec)
			std::cout << e << ' ';
		std::cout << std::endl;
		std::cout << "===============================================" << std::endl;
		ivec.pop_back();
		for (auto e : ivec)
			std::cout << e << ' ';
		std::cout << std::endl;
		std::cout << "===============================================" << std::endl;

		sort_heap(ivec.begin(), ivec.end());
		for (auto e : ivec)
			std::cout << e << ' ';
		std::cout << std::endl;
		std::cout << "===============================================" << std::endl;
	}

	{
		//底层以array完成
		int ia[9] = { 0,1,2,3,4,8,9,3,5 };
		std::make_heap(ia, ia + 9);
		std::cout << "test based array" << std::endl;
		std::cout << "===============================================" << std::endl;
		for (auto e : ia)
			std::cout << e << ' ';
		std::cout << std::endl;
		std::cout << "===============================================" << std::endl;

		std::sort_heap(ia, ia + 9);
		for (auto e : ia)
			std::cout << e << ' ';
		std::cout << std::endl;
		std::cout << "===============================================" << std::endl;

		std::make_heap(ia, ia + 9);
		std::pop_heap(ia, ia + 9);
		std::cout << ia[8] << std::endl;

	}
}