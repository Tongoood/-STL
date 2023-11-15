#include<map>
#include<iostream>
#include<string>

int main()
{
	std::map<std::string, int>simap;
	simap[std::string("jjhou")] = 1;
	simap[std::string("jerry")] = 2;
	simap[std::string("jason")] = 3;
	simap[std::string("jimmy")] = 4;

	std::map<std::string, int>::iterator simap_iter = simap.begin();
	for (; simap_iter != simap.end(); ++simap_iter)
		std::cout << simap_iter->first << ' '
		<< simap_iter->second << std::endl;
	std::cout << "========================================================================" << std::endl;
	std::pair<std::string, int> value(std::string("davaid"), 5);
	simap.insert(value);

	std::map<std::string, int>::iterator simap_iter2 = simap.begin();
	for (; simap_iter2 != simap.end(); ++simap_iter2)
		std::cout << simap_iter2->first << ' '
		<< simap_iter2->second << std::endl;
	std::cout << "========================================================================" << std::endl;

	int number = simap[std::string("jjhou")];
	std::cout << number << std::endl;
	std::cout << "========================================================================" << std::endl;

	std::map<std::string, int>::iterator itel;

	//面对关联式容器，应该使用其所提供的find函数来搜索元素，会比stl算法find（）更有效率，因为stl算法的find是循序搜索
	itel = simap.find(std::string("mchen"));
	if (itel == simap.end())
		std::cout << "mchen not found" << std::endl;

	itel = simap.find(std::string("jerry"));
	if (itel != simap.end())
		std::cout << "jerry found" << std::endl;
	itel->second = 9;
	int number2 = simap[std::string("jerry")];
	std::cout << number2 << std::endl;
}

//[](subscript)操作符，用法有两种
//作为左值（内容可被修改）    作为右值(内容不可以被修改)
/*
map<std::string ,int> simap;
simap[std::string("jjhou")] =1;    左值，可以被修改
...
int number = simap[std::string("jjhou")];   右值  不可被修改



*/

/*

当你使用 insert 向 std::map 中插入元素，如果插入的键已经存在，
insert 会返回一个 std::pair，
其中的第一个元素是一个迭代器，指向 std::map 中已经存在的元素，第二个元素是一个布尔值，表示插入是否成功。

*/
