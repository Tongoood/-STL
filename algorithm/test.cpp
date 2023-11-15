//#include<algorithm>
//#include<vector>
//#include<functional>
//#include<iostream>
//#include<iterator>
//
//template<class T>
//struct display {
//    void operator()(const T& x) const {
//        std::cout << x << ' ';
//    }
//};
//
//int main()
//{
//    int ia[9] = { 0,1,2,3,4,5,6,7,8 };
//    std::vector<int> iv1(ia, ia + 5);
//    std::vector<int> iv2(ia, ia + 9);
//
//    /*std::cout << *(std::mismatch(iv1.begin(), iv1.end(), iv2.begin()).first);
//    std::cout << *(std::mismatch(iv1.begin(), iv1.end(), iv2.begin()).second);*/
//    //以上判断两个区间的第一个不匹配点，返回一个由两个迭代器组成的pair
//    //其中第一个迭代器指向第一区间的不匹配点，第二区间指向第二区间的不匹配点
//
//    //如果两个序列在[first, last)区间内相等，equal()返回true
//    //如果第二序列的元素比较多，多出来的元素不予考虑
//    std::cout << std::equal(iv1.begin(), iv1.end(), iv2.begin());
//    std::cout << std::equal(iv1.begin(), iv1.end(), &ia[3]);
//    std::cout << std::equal(iv1.begin(), iv1.end(), &ia[3], std::less<int>());
//
//    std::cout << "==================================" << std::endl;
//std:fill(iv1.begin(), iv1.end(), 9);
//    std::for_each(iv1.begin(), iv1.end(), display<int>());
//    std::cout << std::endl;
//
//
//std::fill_n(iv1.begin(), 3,7);
//    std::for_each(iv1.begin(), iv1.end(), display<int>());
//    std::cout << "==================================" << std::endl;
//    std::vector<int>::iterator ite1 = iv1.begin();
//    std::vector<int>::iterator ite2 = ite1;
//    advance(ite2, 3);
//
//    iter_swap(ite1, ite2);
//    std::cout << *ite1 << ' ' << *ite2 << std::endl;
//    std::for_each(iv1.begin(), iv1.end(), display<int>());
//    std::cout<<std::endl;
//
//    std::cout << "==================================" << std::endl;
//    std::cout << std::max(*ite1, *ite2) << std::endl;
//    std::cout << std::min(*ite1, *ite2) << std::endl;
//    std::cout << "==================================" << std::endl;
//
//    //此刻状态，iv1：{9 7 7 7 9}， iv2{0 1 2 3 4 5 6 7 8}
//    std::swap(*iv1.begin(), *iv2.begin());
//    std::for_each(iv1.begin(), iv1.end(), display<int>());
//    std::cout << std::endl;
//
//    std::for_each(iv2.begin(), iv2.end(), display<int>());
//    std::cout << std::endl;
//
//    std::cout << "==================================" << std::endl;
//
//
//    //准备两个字符串数组
//    std::string stra1[] = { "Jamie", "JJhou", "Jason" };
//    std::string stra2[] = { "Jamie", "JJhou", "Jerry" };
//    
//    std::cout << std::lexicographical_compare(stra1, stra1 + 2, stra2, stra2 + 2);
//
//    std::cout << std::lexicographical_compare(stra1, stra1 + 2, stra2, stra2 + 2,std::greater<std::string>());
//
//
//    return 0;
//}