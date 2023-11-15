#include <iostream>
#include <cmath>

auto square = [](double x) { return x * x; };

int main() {
    double number = 5.0;
    double squareResult = square(number);
    double squareRoot = std::sqrt(squareResult);

    std::cout << "Square root of " << squareResult << " is " << squareRoot << std::endl;

    return 0;
}


//binary_function
//binary——function用来呈现二元函数的第一参数型别、第二参数型别，以及返回值型别
template<class Argl,class Arg2, class Result>
struct binary_function {
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Result result_type;
};
template<class T>
struct plus :public binary_function<T, T, T> {
    T operator()(const T& x, const T& y) const { return x + y; }
};

template<class Operation>
class binder1st {
    //...
protected:
    Operation op;
    typename Operation::First_argument_type value;
public:
    typename Operation::result type operator()(const typename Operation::second_argument_type& x)const {
        //...
    }
};