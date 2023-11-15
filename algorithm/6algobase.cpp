#include<algorithm>
#include<vector>
#include<functional>
#include<iostream>
#include<iterator>

template<class T>
struct display{
    void operator()(const T& x) const{
        std::cout<<x<<' ';
    }
};

int main()
{
    int ia[9] = {0,1,2,3,4,5,6,7,8};
    std::vector<int> iv1(ia, ia+5);
    std::vector<int> iv2(ia, ia+9);

    // std::cout<<*(std::mismatch(iv1.begin(),iv1.end(),iv2.begin()).first);
    // std::cout<<*(std::mismatch(iv1.begin(),iv1.end(),iv2.begin()).second);
    //以上判断两个区间的第一个不匹配点，返回一个由两个迭代器组成的pair
    //其中第一个迭代器指向第一区间的不匹配点，第二区间指向第二区间的不匹配点
    //以上内容很危险， 会报错应该先判断得带起是否不等于容器的end()，然后才可以做输出操作

    //如果两个序列在[first, last)区间内相等，equal()返回true
    //如果第二序列的元素比较多，多出来的元素不予考虑
    std::cout<<std::equal(iv1.begin(),iv1.end(),iv2.begin());
    std::cout<<std::equal(iv1.begin(),iv1.end(),&ia[3]);
    std::cout<<std::equal(iv1.begin(),iv1.end(),&ia[3],std::less<int>());


return 0;
}