#include<iostream>

struct B { };
struct D1 :public B{ };
struct D2 : public D1 { };

template<class I>
void func(I& p, B)
{
	std::cout << "B version" << std::endl;
}

template<class I>
void func(I& p, D2)
{
	std::cout << "D2 version" << std::endl;
}

int main()
{
	int* p;
	func(p, B());
	func(p, D1());  /*如果子类没有重写（覆盖）某个函数，而您将子类的对象传递给接受父类对象的函数，
		编译器会将子类对象自动转换为父类对象，然后调用父类中的对应函数。这是因为子类对象可以视为父类对象的一种特殊情况。*/
	func(p, D2());

	return 0;
}

