#include<iostream>
#include<algorithm>
#include<deque>
using namespace std;

template<class T>
struct display{
    void operator()(const T& x)
    {
        cout<<x<<' ';
    }
};

int main()
{
    {
        int ia[] = {0,1,2,3,4,5,6,7,8};
        //以下输出区间和输入区间重叠，没问题
        copy(ia+2, ia+7, ia);
        for_each(ia, ia+9, display<int>());
        cout<<endl;
    }
    {
        int ia[] = {0,1,2,3,4,5,6,7,8};
        //以下，输出区间的起点与输入区间重叠，可能会有问题
        copy(ia+2, ia+7, ia+4);
        for_each(ia, ia+9, display<int>());
        cout<<endl;
        //本例结果正确，因为调用的copy算法使用memmove()执行实际复制操作
    }
    {
        int ia[] = {0,1,2,3,4,5,6,7,8};
        deque<int> id(ia, ia+9);

        deque<int>::iterator first = id.begin();
        deque<int>::iterator last = id.end();
        ++++first;   //anvance(first, 2)
        cout<<*first<<endl;
        ----last;
        cout<<*last<<endl;

        deque<int>::iterator result = id.begin();
        cout<<*result<<endl;

        //以下，输出区间的终点和输入区间重叠，没问题
        copy(first, last, result);
        for_each(id.begin(),id.end(),display<int>());
        cout<<endl;
    }
        {
        int ia[] = {0,1,2,3,4,5,6,7,8};
        deque<int> id(ia, ia+9);

        deque<int>::iterator first = id.begin();
        deque<int>::iterator last = id.end();
        ++++first;   //anvance(first, 2)
        cout<<*first<<endl;
        ----last;
        cout<<*last<<endl;

        deque<int>::iterator result = id.begin();
        advance(result, 4);
        cout<<*result<<endl;

        //以下，输出区间的终点和输入区间重叠，没问题
        copy(first, last, result);
        for_each(id.begin(),id.end(),display<int>());
        cout<<endl;
    }
}