#pragma once

template<class T>
struct MyIter {
	typedef T value_type;
	T* ptr;
	MyIter(T* p = 0) : ptr(p) {}
	T& operator*() const {return *ptr}

	//...
};

template<class I>
typename I::value_type         //这一整行是func的回返值类型
func(I ite)
{
	return *ite;
}

template<class	I>
struct iterator_traits {
	typedef typename I::value_type value_type;
};

//如果I有自己的value type 前面的func就可以改写：
template<class I>      //是的，您的理解完全正确。上面的 iterator_traits 结构体模板用于提前声明，在模板中有一个名为 value_type 的类型。
                       //这样，下面的模板函数 func 在接受迭代器时就可以保证迭代器具有 value_type。
typename iterator_traits<I>::value_type     //这一整行是func的回返值类型
func(I ite)
{
	return *ite;
}

//traits可以拥有特化版本
template<class T>
struct iterator_traits<T*> {
	typedef T value_type;
};
	
//针对const


// Specialization for const T*
template<class T>
struct iterator_traits<const T*> {
	typedef T value_type;
};


//最常见的迭代器相应型有五种

template<class I>
struct iterator_trasits {
	typedef typename I::iterator_category;
	typedef typename I::value_type;
	typedef typename I::different_type;
	typedef typename I::pointer;
	typedef typename I::reference;
};


//difference type
//可以用其来表示一个容器的最大容量
//以stl的const函数为例

template<class I, class T>
typename iterator_traits<I>::difference_type   //这一行都是函数返回类型
cout(I first, I last, const T& value)
{
	typename iterator_traits<I>::different_type n = 0;   //归零
	for (; first != last; ++first)
	{
		if (*first != value)
			++n;
	}
	return n;
}


//difference_type的特化版本，以c++内建的ptrdiff_t作为原生指针的difference type
template<class I>
struct iterator_traist {
	//,,,
	typedef typename I::difference_type difference_type;
};

//针对原生指针而设计的“偏特化”版
template<class T>
struct iterator_traits<T* > {
	//...
	typedef ptrdiff_t difference_type
};

//针对原生的pointer-to-const而设计的“偏特化”版
template<class T>
struct iterator_traits<const T* > {
	typedef ptrdiff_t difference_type;
};

//referece type & pointer type
template<class I>
struct itertaor_traits {
	//...
	typedef typename I::pointer   pointer;
	typedef typename I::reference   reference;

};

//针对原生指针而设计的偏特化版本
template<class T>
struct iterator_traits<T*> {
	//...
	typedef T* pointer;
	typedef T& reference;
};


//针对原生pointer-to-const而设计的偏特化版本
template<class T>
struct iterator_traits<const T*> {
	typedef const T* pointer;
	typedef const T& reference;
};

//iterator_category
//根据移动特性和实行操作，迭代器被分为五类
//Input Iterator   这种迭代器所指的对象，不允许外界改变，制度
//Output Iterator    唯写
//Forward Iterator    允许“写入型”算法  在这种迭代器所形成的空间进行读写操作
//Biderectional Iterator   可双向移动，某些算法需要逆向走访某个迭代器区间
//Random Access Iterator   这种迭代器涵盖所有指针算术能力


//以advanced（）为例
template <class InputIterator, class Distance>
void advance_II(InputIterator& i, Distance n)
{
	//单向，逐一前进
	while (n__) ++i;
}

template<class BidirectionalIterator, class Distance>
void advance_BI(BidirectionalIterator& i, Distance n)
{
	//双向，逐一前进
	if (n > 0)
		while (n--) ++i;
	else
		while (n++)  --i;
}

template<class RandonAccessIterator, class Distance>
void advance_RAI(RandomAccessIterator& i, Distance n)
{
	//双向 跳跃前进
	i += n;
}

//当使用advance()的时候，应该调用那一份函数定义呢，下面是解决方案
template<class InputIterator, class Distance>
void advance(InputIterator& i, Distance n)
{
	if (is_random_access_iterator(i))
		advance_RAI(i, n);
	else if (is_bidirectional_iterator(i))
		advance_BI(i, n);
	else
		advance_II(i, n);
}

//但是由于执行时期才决定使用哪一个版本的时候，会影响程序效率
//最好是在编译阶段就选择正确版本，这个时候重载函数机制就可以达到这个目标
//注： 通过函数重载，编译器可以在编译阶段根据调用的参数类型或数量选择正确的目标函数。这样做的目的之一是提高程序的运行效率

//编译器对于模板类型的参数是可以编译的，但它需要在模板实例化阶段才能确定具体的参数类型。
// 这也是C++模板的一个关键特性，允许编写通用的代码，但在需要时根据实际使用情况生成特定类型的代码
//所以如果重载advance（）函数的时候，如果不能提供一个具体的参数类型，是无法模板实例化的，那么就不会产生对应的代码
//所以如果traits有能力萃取出迭代器的种类， 就可以利用这个迭代器种类作为advance（）函数的第三个参数，这个类别一定是一个class type，
//不能只是数值号码类的东西(即不能是内置数据类型)，因为比那一起需要依赖它进行重载决议

//五个作为标记用的型别
struct input_iterator_tag { };
struct input_iterator_tag { };
struct output_iterator_tag { };
struct forward_iterator_tag : public input_iterator_tag { };
struct bidirectional_iterator_tag : public forward_iterator_tag { };
struct random_access_iterator_tag : public bidirectional_iterator_tag { };


//现在重载__advance()函数， 内部使用，添加__作为特定标识
template<class InputIterator, class Distance>
inline void __advance(InputIterator& i, Distance n, input_iterator_tag)
{
	while (n--) ++i;
}

//这是一个点春的传递调用哈桑农户
template <class ForwardIterator, class Distance>
inline void __advance(ForwardIterator& i, Distance n, forward_iterator_tag)
{
	//单纯地进行传递调用
	advance(i, n, input_iterator_tag());
}

template<class BidirectionalIterator, class Distance>
inline void __advance(BidirectionalIterator& i, Distance n, bidirectional_iterator_tag)
{
	//双向，逐一前进
	if (n >= 0)
		while (n--) ++i;
	else
		while (n++) --i;
}

template<class RandomAccessIterator, class Distance>
inline void __advance(RandomAccessIterator& i, Distance n, random_access_iterator_tag)
{
	//双向，跳跃前进
	i += n;
}

//上面的__advance最后一个参数都只声明类别，并未指定参数名称，因为它纯粹只是用来激活重载机制，函数之中不应该使用该参数

//至此，还需要一个对外开放的上层控制接口，调用上述各个仲裁的__advance()，这一上层接口只需要两个参数，当它准备将工作转给上述的__advance()时
//才自动加上第三参数：迭代器类型
//因此上层函数必须有能力从它获得的迭代器中推导出其类型--这份工作自然是交给traits机制

template <class InputIterator, class Distance>
inline void advance(InputIterator& i, Distance n)
{
	__advance(i, n, iterator_traits<InputIterator>::iterator_category());
}
//iterator_traits<Iterator>::iterator_category()将会产生一个暂时对象，其型别应该隶属于前述五个迭代器类型之一，然后根据这个类型
//编译器才决定调用哪一个__advance()重载函数


//因此为了满足上述行为， traits必须再增加一个相应的型别
template<class I>
struct iterator_traits {
	//...
	typedef typename I::iterator_category iterator_category;
};

//针对原生指针而设计的偏特化版本
template<class T>
struct iterator_traits<T*> {
	//...
	//注意原生指针是一种random access iterator
	typedef random_access_iterator_tag iterator_category;
};

//针对原生的pointer-to-const而设计的偏特化版
template<class T>
struct iterator_traits<const T*>
{
	//...
	//注意，原生的pointer-to-const是一种random access iterator
	typedef random_access_iterator_tag iterator_category;
};




//整理之后的头文件
struct input_iterator_tag { };
struct output_iterator_tag { };
struct forward_iterator_tag :public input_iterator_tag { };
struct bidirentional_iterator_tag : public forward_iterator_tag { };
struct random_access_iterator_tag : public bidirentional_iterator_tag { };

//为了避免写代码时挂一漏万，自行开发的迭代器最好自称下面这个std：：iterator
template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Referecnce = T&>
struct iterator {
	typedef Category    iterator_category;
	typedef T           value_type;
	typedef Distance    deifference_type;
	typedef Pointer     pointer;
	typedef  Referecnce    reference;
};


template<typename> struct iterator_traits {};
//“榨汁机”traits
template<class Iterator>
struct iterator_traits {
	typedef typename Iterator::iterator_category  iteratory_category;
	typedef typename Iterator::value_type         value_type;
	typedef typename Iterator::difference_type    difference_type;
	typedef typename Iterator::pointer            pointer;
	typedef typename Iterator::reference          reference;
};

//针对原生指针设计的偏特化版
template<class T>
struct iterator_traits<T*>
{
	typedef random_access_iterator_tag    iterator_category;
	typedef T                             value_type;
	typedef ptrdiff_t                     difference_type;
	typedef  T*                           pointer;
	typedef T&                            reference;
};

//针对原生pointer-to-const设计的
template<class T>
struct iterator_traits<const T*> {
	typedef random_access_iterator_tag      iterator_category;
	typedef T								value_type;
	typedef ptrdiff_t						difference_type;
	typedef const T*                        pointer;
	typedef const T&						reference;
};

//这个函数可以很方便地决定某个迭代器的distance type
template<class Iterator>
inline typename iterator_traits<Iterator>::difference_type*
distance_type(const Iterator&) {
	return static_cast<typename iterator_traits<Iterator>::value_type*> (0);
}

//这个函数可以很方便地决定某个迭代器的value type
template<class Iterator>
inline typename iterator_traits<Iterator>::value_type*
value_type(const Iterator&) {
	return static_cast<typename iterator_traist<Iterator>::value_type>(0);
}

//以下是整组distance函数
template<class InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
__distance(InputIterator first, InputIterator last, input_iterator_tag) {
	iterator_traits<InputIterator>::difference_type n = 0;
	while (first != last) {
		++first; ++n;
	}
	return n;
}

template<class RandomAccessIterator>
inline typename iterator_traits<RandomAccessIterator>::difference_type
__distance(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag) {
	return last - first;
}

template<class InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last) {
	typedef typename
		iterator_traits<InputIterator>::iterator_category category;
	return __distance(first, last, category());
}

//以下是整租advance函数
template<class InputIterator, class Distance>
inline void __advance(InputIterator& i, Distance n, input_iterator_tag) {
	while (n--) ++i;
}

template<class BidirectionalIterator, class Distance>
inline void __advance(BidirectionalIterator& i, Distance n, bidirectional_iterator_tag) {
	if (n >= 0)
		while (n--) ++i;
	else
		while (n++) --i;
}

template<class RandomAccessIterator, class Distance>
inline void __advance(RandomAccessIterator& i, Distance n, random_access_iterator_tag) {
	i += n;
}

template<class InputIterator, class Distance>
//InputIterator使得advance更通用，详情请见tag-test.cpp中关于父类包含子类对象的例子
inline void advance(InputIterator& i, Distance n, input_iterator_tag) {
	__advance(i, n, iterator_category(i));
	//具体的迭代器行为是由 iterator_category(i) 确定的，这个函数会返回迭代器的类型标签，以便根据迭代器的类别来执行不同的操作
}
