#pragma once
template<class Predicate>
class binary_negate :public binary_function<typename Predicate::first_argument_type,
	typename Predicate::second_argument_type, bool> {
protected:
	Predicate pred;
public:
	explicit binary_negate(const Predicate& x):pred(x){}
	bool operator() (const typename Predicate::first_argument_type& x,
		const typename Predicate::Second_argument_type& y) const {
		return !pred(x, y);
	}
};

//辅助函数
template<class Predicate>
inline binary_negate<Predicate> not2(const Predicate& pred) {
	return binary_negate<Predicate>(pred);
}


//以下配接器把一个一元函数指针包起来
//当仿函数被使用的时候，就调用该函数指针
template<class Arg, class Result>
class pointer_to_unary_function :public unary_function<Arg, Result>
{
protected:
	Result(*ptr)(Arg);   //内部成员，一个函数指针
public:
	pointer_to_unary_function() {}
	//以下constructor将函数指针记录于内部成员之中
	explicit pointer_to_unary_function(Result (*x)(Arg)):ptr(x){}

	//以下 通过函数指针执行函数
	Result operator()(Arg x) const { return ptr(x); }
};

//辅助函数，让我们得以方便运用pointer_to_unary_function
template<class Arg, class Result>
inline pointer_to_unary_function<Arg, Result> ptr_fun(Result(*x)(Arg)) {
	return pointer_to_unary_function<Arg, Result>(x);
}