#pragma once
//STL仿函数应该有能力被函数配接器修饰，彼此像积木一样地串接
//为了拥有配接能力，每一个仿函数必须定义自己的相应型别，就像迭代器如果要融入整个STL大家庭，也必须依照规定定义自己的五个相应型别一样
//这些型别是为了让配接器能够取出，获得仿函数的某些信息，相应型别都只是一些typedef，所有必要操作在编译期就全部完成了，对程序的执行效率没有任何影响


//仿函数的相应型别主要用来表现函数参数型别和传回值型别

//unary_function   (unary  一元的)
//unary_function用来呈现一元函数的参数型别和返回值类型
//stl规定，每一个Adaptable Unary Function都应该继承此类别
template<class Arg, class Result>
struct unary_function {
	typedef Arg argument_type;
	typedef Result result_type;
};
//一旦某个仿函数继承了unary_function，其用户便可以这样取得仿函数的参数型别，并以相同的手法取得其回返值型别
template<class T>
struct negate :public unary_function<T, T> {
	T operator()(const T& x) const { return -x; }
};

//以下配接器（adapter）用来表示某个仿函数的逻辑负值
template<class Predicate>
class unary_negate
{
	//...
public:
	bool operator()(const typename Predicate::Argument_type& x) const {
		//...
	}
};