#include<vector>
#include<iostream>
#include<algorithm>

int main()
{
	int i;
	std::vector<int> iv(2, 9);
	std::cout << "size=" << iv.size() << std::endl;
	std::cout << "capacity=" << iv.capacity() << std::endl;
	std::cout << "=================================================================" << std::endl;

	iv.push_back(1);
	std::cout << "size=" << iv.size() << std::endl;
	std::cout << "capacity=" << iv.capacity() << std::endl;
	std::cout << "=================================================================" << std::endl;

	iv.push_back(2);
	std::cout << "size=" << iv.size() << std::endl;
	std::cout << "capacity=" << iv.capacity() << std::endl;
	std::cout << "=================================================================" << std::endl;

	iv.push_back(3);
	std::cout << "size=" << iv.size() << std::endl;
	std::cout << "capacity=" << iv.capacity() << std::endl;
	std::cout << "=================================================================" << std::endl;

	iv.push_back(4);
	std::cout << "size=" << iv.size() << std::endl;
	std::cout << "capacity=" << iv.capacity() << std::endl;
	std::cout << "=================================================================" << std::endl;

	for (i = 0; i < iv.size(); ++i) {
		std::cout << iv[i] << ' ';
	}
	std::cout<<std::endl;
	std::cout << "=================================================================" << std::endl;

	iv.push_back(5);
	std::cout << "size=" << iv.size() << std::endl;
	std::cout << "capacity=" << iv.capacity() << std::endl;
	for (i = 0; i < iv.size(); ++i) {
		std::cout << iv[i] << ' ';
	}
	std::cout << std::endl;
	std::cout << "=================================================================" << std::endl;

	iv.pop_back();
	iv.pop_back();
	std::cout << "size=" << iv.size() << std::endl;
	std::cout << "capacity=" << iv.capacity() << std::endl;
	std::cout << "=================================================================" << std::endl;

	iv.pop_back();
	std::cout << "size=" << iv.size() << std::endl;
	std::cout << "capacity=" << iv.capacity() << std::endl;
	std::cout << "=================================================================" << std::endl;

	std::vector<int>::iterator ivite = find(iv.begin(), iv.end(), 1);
	//find实现细节，简易版本
	/*=========================================================================================
template <class InputIterator, class T>
InputIterator find(InputIterator first, InputIterator last, const T& value) {
    while (first != last) {
        if (*first == value) {
            return first;  // 找到匹配的值，返回迭代器
        }
        ++first;
    }
    return last;  // 未找到匹配的值，返回范围的结束迭代器
}
============================================================================================================*/
	if (ivite != iv.end()) iv.erase(ivite);
	std::cout << "size=" << iv.size() << std::endl;
	std::cout << "capacity=" << iv.capacity() << std::endl;
	for (i = 0; i < iv.size(); ++i) {
		std::cout << iv[i] << ' ';
	}
	std::cout << std::endl;
	std::cout << "=================================================================" << std::endl;

	auto ite = find(iv.begin(), iv.end(), 2);
	if (ite != iv.end()) iv.insert(ite, 3, 7);
	std::cout << "size=" << iv.size() << std::endl;
	std::cout << "capacity=" << iv.capacity() << std::endl;
	for (i = 0; i < iv.size(); ++i) {
		std::cout << iv[i] << ' ';
	}
	std::cout << std::endl;
	std::cout << "=================================================================" << std::endl;

	iv.clear();
	std::cout << "size=" << iv.size() << std::endl;
	std::cout << "capacity=" << iv.capacity() << std::endl;
	std::cout << "=================================================================" << std::endl;

	return 0;

}
