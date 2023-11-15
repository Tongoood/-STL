#include<list>
#include<iostream>
#include<algorithm>

int main()
{
	int i;
	std::list<int> ilist;
	std::cout << "size=" << ilist.size() << std::endl;
	std::cout << "=======================================================================" << std::endl;

	ilist.push_back(0);
	ilist.push_back(1);
	ilist.push_back(2);
	ilist.push_back(3);
	ilist.push_back(4);
	std::cout << "size=" << ilist.size() << std::endl;
	std::cout << "=======================================================================" << std::endl;

	std::list<int>::iterator ite;
	for (ite = ilist.begin(); ite != ilist.end(); ++ite) {
		std::cout << *ite << " ";
	}
	std::cout << std::endl;
	std::cout << "=======================================================================" << std::endl;

	ite = find(ilist.begin(), ilist.end(), 3);
	if (ite != ilist.end()) {
		ilist.insert(ite, 99);
	}
	std::cout << "size=" << ilist.size() << std::endl;
	std::cout << *ite << std::endl;
	for (ite = ilist.begin(); ite != ilist.end(); ++ite) {
		std::cout << *ite << " ";
	}
	std::cout << std::endl;
	std::cout << "=======================================================================" << std::endl;

	ite = find(ilist.begin(), ilist.end(), 1);
	if (ite != ilist.end()) {
		std::cout << *(ilist.erase(ite)) << std::endl;
		//下面是erase函数的源码，可以看出erase返回的是下一个迭代器

//		iterator erase(const const_iterator _Where) noexcept /* strengthened */ {
//#if _ITERATOR_DEBUG_LEVEL == 2
//			_STL_VERIFY(_Where._Getcont() == _STD addressof(_Mypair._Myval2), "list erase iterator outside range");
//#endif // _ITERATOR_DEBUG_LEVEL == 2
//			const auto _Result = _Where._Ptr->_Next;
//			_Node::_Freenode(_Getal(), _Mypair._Myval2._Unlinknode(_Where._Ptr));
//			return _Make_iter(_Result);  
	for (ite = ilist.begin(); ite != ilist.end(); ++ite) {
		std::cout << *ite << " ";
	}
	std::cout << std::endl;
	std::cout << "=======================================================================" << std::endl;

	ilist.sort();

	return 0;


}