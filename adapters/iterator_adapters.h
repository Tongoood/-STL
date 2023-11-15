#pragma once

//Insert Iterators
//所谓insert iterators，可以将一般迭代器的赋值操作，转变为插入操作


//Reverse Iterators
//将一般迭代器的行进方向逆转，使原本应该前进的operator++变成了后退操作 

//IOStream Iterators
//可以将迭代器绑定到某个iostream对象身上，绑定到istream身上称为 istream_iterator
//绑定到ostream对象  称为  ostream_iterator

//应用于仿函数 functor adapters
//functor adapters是所有配接器中数量最庞大的一个族群
//配接操作包括 系结（bind）、否定（negate）、组合（compose）、以及对一般函数或成员函数的修饰
