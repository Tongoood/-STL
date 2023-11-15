#include<iterator>
#include<deque>
#include<algorithm>
#include<iostream>

int main()
{
	//将outite绑定到cout，每次对outite指派一个元素，就后接一个” “
	std::ostream_iterator<int> outite(std::cout, " ");

	int ia[] = { 0,1,2,3,4,5 };
	std::deque<int> id{ ia,ia + 6 };

	//将所有元素拷贝到outite（那么也是拷贝到cout）
	copy(id.begin(), id.end(), outite);
	std::cout << std::endl;
	std::cout << "********************************" << std::endl;

	//将ia[]的部分元素拷贝到id内，使用front_insert_iterator
	//注意front_insert_iterator会将assign操作改为push_front操作
	//vector不支持push_front()
	copy(ia + 1, ia + 2, std::front_inserter(id));
	copy(id.begin(), id.end(), outite);
	std::cout << std::endl;
	std::cout << "********************************" << std::endl;

	//将ia[]的部分元素拷贝到id内，使用back_insert_iterator
//注意back_insert_iterator会将assign操作改为push_front操作
	copy(ia + 3, ia + 4, std::back_inserter(id));
	copy(id.begin(), id.end(), outite);
	std::cout << std::endl;
	std::cout << "********************************" << std::endl;


	//搜寻元素5所在位置
	std::deque<int>::iterator ite = find(id.begin(), id.end(), 5);
	//将ia[]的部分元素拷贝到id内，使用insert_iterator
	copy(ia + 0, ia + 3, inserter(id, ite));
	copy(id.begin(), id.end(), outite);
	std::cout << std::endl;
	std::cout << "********************************" << std::endl;

	//将所有元素逆向拷贝到outite
	//rbegin()和rend()与reverse_iterator有关
	copy(id.rbegin(), id.rend(), outite);
	copy(id.begin(), id.end(), outite);
	std::cout << std::endl;
	std::cout << "********************************" << std::endl;


	//将inite绑定到cin，将元素拷贝到inite，知道eos出现
	std::istream_iterator<int> inite(std::cin), eos;  //eos  : end-of-stream
	copy(inite, eos, inserter(id, id.begin()));
	copy(id.begin(), id.end(), outite);
}