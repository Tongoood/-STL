//#include<numeric>
//#include<vector>
//#include<functional>
//#include<iostream>
//#include<iterator>
//
//int main()
//{
//	int ia[5] = { 1,2,3,4,5 };
//	std::vector<int> iv(ia, ia + 5);
//
//	std::cout << accumulate(iv.begin(), iv.end(), 0) << std::endl;
//
//	//std::cout << accumulate(iv.begin(), iv.end(), std::minus<int>()) << std::endl;
//
//
//	std::cout << inner_product(iv.begin(), iv.end(), iv.begin(), 10) << std::endl;
//
//
//	std::cout << inner_product(iv.begin(), iv.end(), iv.begin(), 10, std::minus<int>(), std::plus<int>()) << std::endl;
//
//	//以下这个迭代器将绑定到cout，作为输出用
//	std::ostream_iterator<int> oite(std::cout, " ");
//	//这行代码定义了一个 std::ostream_iterator 类型的对象 oite，它用于将整数写入标准输出流 std::cout，并在每个整数之间用空格分隔。
//
//	std::partial_sum(iv.begin(), iv.end(), oite);
//	std::cout << std::endl;
//
//	std::partial_sum(iv.begin(), iv.end(), oite, std::minus<int>());
//	std::cout << std::endl;
//	
//	std::adjacent_difference(iv.begin(), iv.end(), oite);
//	std::cout << std::endl;
//	std::adjacent_difference(iv.begin(), iv.end(), oite, std::plus<int>());
//	std::cout << std::endl;
//
//	//std::cout << pow(10, 3) << std::endl;
//	///std::cout << pow(10, 3, std::plus<int>()) << std::endl;
//
//	int n = 3;
//	std::iota(iv.begin(), iv.end(), n);
//	for (auto e : iv)
//		std::cout << e <<' ';    //3 ,  4, 5,6 7
//
//
//
//	return 0;
//}