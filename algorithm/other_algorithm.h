#pragma once

//adjacent_find
//查找相邻的重复元素，版本1
template<class ForwardIterator>
ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last) {
	if (first1 == last) return last;
	ForwardIterator next = first;
	while (++next != last) {
		if (*first == *next) return first;
		first = next;
	}
	return last;
}

//查找相邻的重复元素 版本2
template<class ForwardIterator, class BinaryPredicate>
ForwardIterator adjacnet_find(ForwardIterator first, ForwardIterator last, BinaryPredicate binary_pred) {
	if (first == last) return last;
	ForwardIterator next = ++first;
	while (++next != last) {
		if (binary_pred(*first, *next)) return first;
		first = next;
	}
	return last;
}


//count
//运用equality操作符，将【first，last）区间内的每一个元素拿来和指定值value比较，并返回与value相等的元素个数
template<class InputIterator, class T>
typename iterator_traits<InputIterator>::difference_type
count(InputIterator first, InputIterator last, const T& value) {
	//以下声明一个计数器n
	typename iterator_traits<InputIterator>::difference_type n = 0;
	for (; first!- last; ++first)
		if (*first == value)
			++n;
	return n;
}

//count_if
//将指定操作pred实施于【first，last）区间内的每一个元素身上，并将“造成pred之计算结果为true”的所有元素个数返回
template<class InputIterator, class Predicate>
typename iterator_traits<InputIterator>::difference_type
count_if(InputIterator first, InputIterator last, Predicate pred) {
	//以下声明一个计数器n
	typename iterator_traits<InputIterator>::difference_type n = 0;
	for (; first != last; ++first)
		if (pred(*first))
			++n;
	return n;
}


//find
//根据equality操作符，找出第一个匹配等同条件的元素，如果找到就返回一个inputiterator指向该元素
//如果没找到就返回迭代器last
template<class InputIterator, class T>
InputIterator find(InputIterator first, InputIterator last, const T& value) {
	while (first != last && *first != value) ++first;
	return first;
}

//find_if
//指定pred,如果满足pred者就返回
template<class InputIterator, class Predicate>
InputIterator find_if(InputIterator first, InputIterator last, Predicate pred) {
	while (first != last && !pred(*first)) ++first;
	return first;
}

//find_end
//在序列1【first1，last1）所涵盖的区间中，查找序列2【first2，last2）的最后一次出现点
//如果序列1之内不存在“完全匹配序列2”的子序列，便返回迭代器last1，

//版本1
template<class ForwardIterator1,class ForwardIterator2>
inline ForwardIterator1 
find_end(ForwardIterator1 first1, ForwardIterator1 last1,
	ForwardIterator2 first2, ForwardIterator2 last2)
{
	typedef typename iterator_traits<ForwardIterator1>::iterator_category category1;
	typedef typename iterator_traits<ForwardIterator2>::iterator_category category2;

	//以下根据两个区间的类属，调用不同的下层函数
	return __find_end(first1, last1, first2, last2, category1(), category2());
	//型别名称之后加上一堆对小括号，会产生一个临时对象

}


template<class ForwardIterator1, class ForwardIterator2>
ForwardIterator1 __find_end(ForwardIterator1 first1, ForwardIterator1 last1,
	ForwardIterator2 first2, ForwardIterator2 last2, forward_iterator_tag, forward_iterator_tag) {
	if (first2 == last2)   //若空，则返回
		return last1;
	else {
		ForwardIterator1 result = last1;
		while (1) {
			//以下利用search（）查找某个子序列的首次出现点，找不到的话就返回last1
			ForwardIterator1 new_result = search(first1, last1, first2, last2);
			if (new_result == last1)   //没找到
				return result;
			else {
				result = new_result;   //调动一下标兵，准备下一次查找行动
				first1 = new_result;
				++first1;
			}
		}
	}
}

//以下是bidirentional iterator版
template<class BidirectionalIterator1, class BidirectionalIterator2>
BidirectionalIterator1
__find_end(BidirectionalIterator1 first1, BidirectionalIterator1 last1,
	BidirectionalIterator2 first2, BidirectionalIterator2 last2,
	bidirectional_iterator_tag, bidirectional_iterator_tag)
{
	//由于查找的是“最后出现地点”，因此反向查找比较块，利用reverse_iterator
	typedef reverse_iterator<BidirectionalIterator1> reviter1;
	typedef reverse_iterator<BidirectionalIterator2> reviter2;

	reviter1 rlast1(first1);
	reviter2 rlast2(first2);
	//查找时，将序列1和序列2统统逆转方向
	reviter1 rresult = search(reviter1(last1), rlast1, reviter2, rlast2);

	if (rresult == rlast1) //没找到
		return last1;
	else {
		BidirectionalIterator1 result = rresult.base();    //转回正常（非逆向）迭代器
		advance(result, -distance(first2, last2));   //调整回到子序列的起头处
		return result;
	}
}

//find_first_of
//本算法以【first2，last2）区间内的某些元素作为查找目标，寻找他们在【first1，last1）区间内的第一次出现地点
//如果第一序列并未内涵第二序列的任何元素，返回的将是last1
//版本1
template<class InputIterator, class ForwardIterator>
InputIterator find_first_of(InputIterator first1, InputIterator last1,
	ForwardIterator first2, ForwardIterator last2)
{
	for (; first1 != last1; ++first1) {
		//以下，根据序列2的每个元素
		for (ForwardIterator iter = first2; iter != last2; ++iter)
			if (*first1 == *iter)
				return first1;
		return last1;
	}
}

//版本2
template<class InputIterator, class ForwardIterator, class BinaryPredicate>
InputIterator find_first_of(InputIterator first1, InputIterator last1,
	ForwardIterator first2, ForwardIterator last2, BinaryPredicate comp)
{
	for (; first1 != last1; ++first1) {
		//以下，根据序列2的每个元素
		for (ForwardIterator iter = first2; iter != last2; ++iter)
			if (comp(*first1,*iter)
				return first1;
		return last1;
	}
}

//for_each
//将仿函数f施行于【first，last）区间内的每一个元素身上，f不可改变元素的内容，因为first和last都是inputiterator，不保证赋值行为
//如果想要一一修改元素，应该使用算法transform()
template<class InputIterator, class Function>
Function for_each(InputIterator first, InputIterator last, Function f) {
	for (; first != last; ++first)
		f(*first);
	return f;     //调用仿函数f的function call操作符，返回值被忽略
}

//generate
//将仿函数gen的运算结果填写在【first，last）区间内的所有元素身上，所谓填写
//用的是迭代器所指元素之assignment操作符
template<class ForwardIterator, class Generator>
void generate(ForwardIterator first, ForwardIterator last, Generator gen) {
	for (; first != last; ++first)
		*first = gen();        //整个序列区间
}

//generate_n
//将仿函数gen的运算结果填写在从迭代器first开始的n个元素身上，所谓填写，用的是迭代器所指元素的assignment操作符
template<class OutputIterator, class Size, class Generator>
OutputIterator generate_n(OutputIterator first, Size n, Generator gen) {
	for (; n > 0; --n, ++first)     //只限n个元素
		*first = gen();
	return first;
}


//includes(应用于有序区间)
//判断序列2是否  涵盖于 序列1  ，s1和s2 都必须是有序集合
//其中元素可以重复（不必唯一）
//版本1，判断区间二的每个元素值是否都存在于区间一
//前提，区间二和区间一都是有序的
template<class InputIterator1, class InputIterator2>
bool includes(InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2) {
	while (first1 != last1 && first2 != last2)
		if (*first2 < *first1)
			return false;
		else if (*first1 < *first2)
			++first1;
		else
			++first1, ++first2;
	return first2 == last2;      //有一个序列走完了，判断最后一关
}

//版本2
template<class InputIterator1, class InputIterator2, class Compare>
bool includes(InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2, Compare comp) {
	while (first1 != last1 && first2 != last2)
		if (comp(*first2,*first1))
			return false;
		else if (comp(*first1, *first2))
			++first1;
		else
			++first1, ++first2;
	return first2 == last2;      //有一个序列走完了，判断最后一关
}
//注意：compare并非随便的一个二元运算，而是必须满足   case3能保证*first1 == *first2 否则导致算法includes()崩溃
/*
  if(comp(*first2, *first1))   //case1
  ...
  else if (comp(*first1, *first2))  //case2
	...
  else   //case3
	...
*/


//max_element
//返回一个迭代器，只想序列中数值最大的元素
//版本1
template<class ForwardIterator>
ForwardIterator max_element(ForwardIterator first, ForwardIterator last) {
	if (first == last) return first;
	ForwardIterator result = first;
	while (++first != last)
		if (*result < *first) result = first;
	return result;
 }

//版本2
template<class ForwardIterator, class Compare>
ForwardIterator max_element(ForwardIterator first, ForwardIterator last, Compare comp) {
	if (first == last) return first;
	ForwardIterator result = first;
	while (++first != last)
		if (comp(*result, *first)) result = first;
	return result;
}

//merge（应用于有序区间）
//将两个有序集合s1和s2，合并起来放置于另一段空间
//所得结果也是一段有序序列，返回迭代器，指向最后结果序列的最后一个元素的下一个位置(即last)
//版本1
template<class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator merge(InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2,
	OutputIterator result) {
	while (first1 != last1 && first2 != last2) {
		if (*first2 < *first1) {
			*result = *first2;
			++first2;
		}
		else {
			*result = *first1;
			++first1;
		}
		++result;
	}
	//最后剩余元素以copy复制到目的端，以下两个序列一定至少有一个为空
	return copy(first2, last2, copy(first1, last1, result));
}

//版本2
template<class InputIterator1, class InputIterator2, class OutputIterator,class Compare>
OutputIterator merge(InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2,
	OutputIterator result,Compare comp) {
	while (first1 != last1 && first2 != last2) {
		if (comp(*first2, *first1)) {
			*result = *first2;
			++first2;
		}
		else {
			*result = *first1;
			++first1;
		}
		++result;
	}
	//最后剩余元素以copy复制到目的端，以下两个序列一定至少有一个为空
	return copy(first2, last2, copy(first1, last1, result));
}


//min_element
//版本1
template<class ForwardIterator>
ForwardIterator min_element(ForwardIterator first, ForwardIterator last) {
	if (first == last) return first;
	ForwardIterator result = first;
	while (++first!=last) {
		if(*first<*result) result = first;
	}
	return result;
}
//版本2
template<class ForwardIterator, class Compare>
ForwardIterator min_element(ForwardIterator first, ForwardIterator last, Compare comp) {
	if (first == last) return first;
	ForwardIterator result = first;
	while (++first != last) {
		if (comp(*first,*result)) result = first;
	}
	return result;
}

//partition
//partition会将区间【first，last）中的元素重新排列，所有被一元条件运算pred判定为true的元素，都会被放在区间二点前端，被判定为false的元素
//都会被放在区间后段，这个算法不保证元素的原始相对位置，如果需要保留相对位置，需要使用stable_partition

template<class BidirectionalIterator, class Predicate>
BidirectionalIterator partition(BidirectionalIterator first, BidirectionalIterator last, Predicate pred) {
	while (true) {
		while (true) {
			if (first == last)
				return first;
			else if (pred(*first))
				++first;
			else
				break;
		}
		while (true)
		{
			if (first == last)
				return first;
			else if (!pred(*first))
				--last;
			else
				break;
		}
		iter_swap(first, last);
		++first;
	}
}

//remove移除但不删除
template<class ForwardIterator, class T>
ForwardIterator remove(ForwardIterator first, ForwardIterator last, const T& value) {
	first = find(first, last, value);   //利用循序查找法中找出第一个相等的元素
	ForwardIterator next = first;
	//以下利用remove_copy()允许新旧容器重叠的性质，进行移除操作
	//并将结果指定置于原容器中
	return first == last ? first : remove_copy(++next, last, first, value);

}

//remove_copy
template<class InputIterator,class OutputIterator, class T>
OutputIterator remove_copy(InputIterator first, InputIterator last, OutputIterator result, const T& value) {
	for(;first!=last;++first)
		if (*first != value) {
			*result = *first;
			++first;
		}
	return result;
}

//remove_if
//移除【first，last）区间内所有被仿函数pred核定为true的元素，它并不真正从容器中删除那些元素，
//array（）不适合使用remove()和remove_if()，因为array无法缩小尺寸，导致残余数据一直存在
//对array而言，较收欢迎的算法是remove_copy()和remove_copy_if()
template<class ForwardIterator, class Predicate>
ForwardIterator remove_if(ForwardIterator first, ForwardIterator last, Predicate pred) {
	first = find_if(first, last, pred);
	ForwardIterator next = first;
	return first == last ? first; remove_copy_if(++next, last, first, pred);
}

//remove_copy_if
template<class ForwardIterator,class OutputIterator, class Predicate>
ForwardIterator remove_if(ForwardIterator first, ForwardIterator last, OutputIterator result, Predicate pred) {
	for(;first!=last;++first)
		if (!pred(*first)) {
			*result = *first;
			++first;
		}
	return result;
}

//replace
//将【first，last）区间所有的old_value 都用 new_value取代
template<class ForwardIterator, class T>
void replace(ForwardIterator first, ForwardIterator last, const T& old_value, const T& new_value) {
	for (; first != last; ++first)
		if (*first == old_value) *first = new_value;
}

//replace_copy
template<class ForwardIterator, class OutputIterator, class T>
void replace(ForwardIterator first, ForwardIterator last, OutputIterator result, const T& old_value, const T& new_value) {
	for (; first != last; ++first, ++result)
		*result = *first == old_value ? new_value : *first;
}


//replace_if
template<class ForwardIterator, class Predicate, class T>
void replace(ForwardIterator first, ForwardIterator last,Predicate pred, const T& new_value) {
	for (; first != last; ++first)
		if (pred(*first) ) *first = new_value;
}

//replace_copy_if
template<class Iterator,class OutputIterator, class Predicate, class T>
void replace(Iterator first, Iterator last,OutputIterator result, Predicate pred, const T& new_value) {
	for (; first != last; ++first,++result)
		*result = (pred(*first))? new_value: *first;
}

//reverse
//将序列【first，last）的元素在原容器中倒转，迭代器的双向或随机定位能力，影响了这个算法的效率， 所以设计了双层架构
//分派函数
template<class BidirectionalIterator>
inline void reverse(BidirectionalIterator frist, BidirectionalIterator last) {
	__reverse(first, last, iterator_category(first));
}

//reverse的bidirectional iterator版
template<class BidirectionalIterator>
void __reverse(BidirectionalIterator first, BidirectionalIterator last, bidirectional_iterator_tag) {
	while (true)
		if (first == last || first == --last)
			return;
		else
			iter_swap(first++, last);
}
//reverse的random sccess iterator版
template<class RandomAccessIterator>
void __reverse(RandomAccessIterator first, RandomAccessIterator last, random_iterator_tag) {
	//以下，头尾两辆互换，然后头部累进一个位置，尾部累退一个位置，两者交错时即停止
	//注意，只有random iterators才能做以下的first<last判断
	while (first < last) iter_swap(first++, last--);
}

//reverse_copy
//类似reverse()，但产生出来的新序列会被置于result指出的容器中，返回值outputiterator指向新产生给二点最后元素的
//下一个位置，原苏联没有任何改变
template<class BidirectionalIterator, class OutputIterator>
OutputIterator reverse_copy(BidirectionalIterator first, BidirectionalIterator last, OutputIterator result) {
	while (first != last) {
		--last;
		*result = *last;
		++result;
	}
	return result;
}


//rotate
//将【first，last）内的元素和【middle，last）内的元素互换，middle所指的元素会成为容器的第一个元素
//如果对{1，2，3，4，5，6，7}对元素3进行旋转操作，那么结果是{3，4，5，6，7，1,2}
//看似与swap_ranges()功能颇为近似，但swap_ranges()只能交换两个长度相同的区间，rotate可以交换两个长度不同的区间

//由于迭代器的移动能力，影响了这个算法的效率，所以设计为双层架构
template<class forwardIterator>
inline void rotate(forwardIterator first, forwardIterator middle, forwardIterator last) {
	if (first == last||middle ==last) return;
	__rotate(first, middle, last, distance_type(first), iterator_category(first));
}

//下面是根据不同的迭代器类型而完成的三个旋转操作
//rotate的forward iterator版
template<class ForwardIterator, class Distance>
void __rotate(ForwardIterator first, ForwardIterator middle, ForwardIterator last, Distance*, forward_iterator_tag) {
	for (ForwardIterator i = middle;;) {
		iter_swap(first, i);   //前段、后段的元素一一交换
		++first;
		++i;
		//以下判断是前段先结束还是后段先结束
		if (first == middle) {
			//前段结束了
			if (i == last) return;
			middle = i;
		}
		else if (i == last)
			i = middle;
	}
}
//rotate的bidirectional iterator版
template<class BidirectionalIterator, class Distance>
void __rotate(BidirectionalIterator first, BidirectionalIterator middle, BidirectionalIterator last, Distance*, 
	bidirectional_iterator_tag) {
	reverse(first, middle);
	reverse(middle, last);
	reverse(first, last);
}

//rotate的random access iterator版
template<class RandomAccessIterator, class Distance>
void __rotate(RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last, Distance*,
	random_access_iterator_tag) {
	//以下迭代器的相减操作，只适合于random access iterators
	//取全长和前段长度的最大公因子
	Distance n = __gcd(last - first, middle - first);
	while (n--)
		__rotate_cycle(first, last, first + n, middle - first, value_type(first));
}
//最大公因子，利用辗转相除法
//__gcd()应用于__rotate()的random access iterator版
template<class EuclideanRingElement>
EuclideanRingElement __gcd(EuclideanRingElement m, EuclideanRingElement n)
{
	while (n != 0) {
		EuclideanRingElement t = m % n;
		m = n;
		n = t;
	}
	return m;
}
template<class RandomAccessIterator, class Distance, class T>
void __rotate_cycle(RandomAccessIterator first, RandomAccessIterator last, RandomAccessIterator initial,
	Distance shift, T*) {
	T value = *initial;
	RandomAccessIterator ptr1 = initial;
	RandomAccessIterator ptr2 = ptr1 + shift;
	while (ptr2 != initial) {
		*ptr1 = *ptr2;
		ptr1 = ptr2;
		if (last - ptr2 > shift)
			ptr2 += shift;
		else
			ptr2 = first + (shift - (last - ptr2));
	}
	*ptr1 = value;
}

//rotate_copy
template<class ForwardIterator, class OutputIterator>
OutputIterator rotate_copy(ForwardIterator first, ForwardIterator middle, ForwardIterator last,
	OutputIterator result) {
	return copy(first, middle, copy(middle, last, result));
}

//search
//在系列1【first1，last1）所涵盖的区间中，查找序列2【first2，last2）的首次出现点，如果序列1内不存在与序列2完全匹配的子序列
//便返回迭代器last1
template<class ForwardIterator1, class ForwardIterator2>
inline ForwardIterator1 search(ForwardIterator1 first1, ForwardIterator1 last1,
	ForwardIterator2 first2, ForwardIterator2 last2) {
	return __search(first1, last1, first2, last2, distance_type(first), distance_type(first2));
}
template<class ForwardIterator1, class ForwardIterator2, class Distance1,
class Distance2>
ForwardIterator1 __search(ForwardIterator1 first1, ForwardIterator1 last1,
	ForwardIterator2 first2, ForwardIterator2 last2, Distance1*, Distance2*) {
	Distance1 d1 = 0;
	distance(first1, last1, d1);
	Distance2 d2 = 0;
	distance(first2, last2, d2);
	if (d1 << d2) return last1;   //如果第一序列小于第二序列，不可能成为其子序列

	ForwardIterator1 current1 = first1;
	ForwardIterator2 current2 = first2;

	while(current2!=last2)
		if (*current1 == *current2) {
			++current1;
			++current2;
		}
		else {
			if (d1 == d2)           //如果这两个元素不相等
				return last1;       //如果序列一样长，表示不可能成为了
			else {                  //序列不一样长，调整第一序列的标兵  以及 从第二序列的第一个元素继续判断是否为子序列
				current1 = ++first1;    
				current2 = first2;
				--d1;
			}
		}
	return first1;      //注意，上述first迭代器也在递增，确保返回值是子序列的第一个相等元素
}

//search_n
//查找“连续count个符合条件的元素”，返回迭代器指向该子序列的起始处
//查找连续两个8，所形成的子序列可以这么写
//  iter1 = search_n(iv.begin(),iv.end(),2,8);
//连续三个小于8的元素
//iter2 = search_n(iv.begin(),iv.end(),3,8,less<int>());


//版本1，查找连续count次出现形成子序列，返回其发生位置
template<class ForwardIterator, class Integer, class T>
ForwardIterator search_n(ForwardIterator first, ForwardIterator last,
	Integer count, const T& value) {
	if (count <= 0)
		return first;
	else {
		first = find(first, last, value);
		while (first!= last) {
			Integer n = count - 1;
			ForwardIterator i = first;
			++i;
			while (i!= last && n != 0 && *i == value) {
				++i;
				--n;
			}
			if (n == 0)
				return first;     //之所以返回first，请注意find(first, last, value)
			                      //若找到，则first是子序列的第一个元素
			else
				first = find(i, last, value);     //若未找到，重新找
		}
		return last;
	}
}

//版本2
//查找，连续count个元素皆满足指定条件 所形成的那个子序列的起点
template<class ForwardIterator, class Integer, class T,
class BinaryPredicate>
ForwardIterator search_n(ForwardIterator first, ForwardIterator last,
	Integer count, const T& value,
	BinaryPredicate binary_pred) {
	if (count <= 0)
		return frist;
	else {
		while (first != last) {
			if (binary_pred(*first, value)) break;  //先找出第一个符合要求的元素
			++first;
		}
		while (first != last) {
			Integer n = count - 1;
			ForwardIterator i = first;
			++i;
			//以下循环确定接下来count-1个元素是否都符合条件
			while (i != last && n != 0 && *binary_pred(*i, value) {
				++i;
				--n;
			}
			if (n == 0)
				return first;
			else {
				while (i != last) {
					if (binary_pred(*i, value))  break;
					++i;
				}
				first = i;   //重新指定子序列的第一个元素
			}
		}
		return last;
	}
}


//swap_ranges
template<class ForwardIterator1, class ForwardIterator2>
ForwardIterator2 swap_rangs(ForwardIterator1 firs1, ForwardIterator1 last1,
	ForwardIterator2 fris2) {
	for (; first1 != last1; ++first1, ++first2) {
		iter_swap(first1, first2);   // std::iter_swap(it1, it2);  // 交换 it1 和 it2 指向的元素
		return first2;
	}
}


//transform
// 第一版本以仿函数op作用于【first，last）中的每一个元素，并以其结果产生一个新序列
// 第二版本以仿函数binary_op作用于一双元素身上（其中一个元素来自【first1， last1），另一个元素来自“从first2开始的序列”）
//trasnform()运算结果result可以指向源端容器，那么结果就会取代该容器内的元素
//返回值outputiterator将指向结果序列最后元素的下一个位置

//版本1
template<class InputIterator, class OutputIterator, class UnaryOperation>
OutputIterator transform(InputIterator first, InputIterator last,
	OutputIterator result, UnaryOperation op) {
	for (; first != last; ++first, ++result)
		*result = op(*first);
	return result;
}
//版本2
template<class InputIterator1, class InputIterator2, class OutputIterator, class BinaryOperation>
OutputIterator transform(InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, OutputIterator result, BinaryOperation binary_op) {
	for (; first1 != last1; ++first1, ++first2, ++result) {
		*result = binary_op(*first1, *first2);
		return result;
	}
}


//unique
//unique能够移除重复的元素
//注意unique只移除相邻的重复元素，如果你想要移除所有的重复元素，必须先将序列排序，使得所有重复元素都相邻
//版本1
template<class ForwardIterator>
ForwardIterator unique(ForwardIterator first, ForwardIterator last) {
	first adjacent_find(first, last);
	return unique_copy(first, last, first);    //利用unique_copy完成
}

//unique_copy
//unique_copy可从【first，last）中将元素复制到以result开头的区间上，如果面对相邻重复元素集，只会复制其中第一个元素
//返回的得带起指向以result开头的区间的尾端

//版本1
template<class InputIterator, class OutputIterator>
inline OutputIterator unique_copy(InputIterator first,
	InputIterator last, OutputIterator result) {
	if (first == last) return result;
	//以下，根据result的iterator category做不同的处理
	return __unique_copy(first, last, result, iterator_category(result));
}
//版本1 辅助函数 forward_iterator_tag
template<class InputIterator, class ForwardIterator>
ForwardIterator __unique_copy(InputIterator first, InputIterator last, ForwardIterator result,
	forward_iterator_tag) {
	*result = *first;
	while (++first != last)
		//以下元素不同则记录，否则跳过
		if (*result != *first) *++result = *first;
	return ++result;
}
//版本1 辅助函数 output_iterator_tag
template<class InputIterator, class OutputIterator>
inline OutputIterator __unique_copy(InputIterator first, InputIterator last,
	OutputIterator result, output_iterator_tag) {
	//以下，output iterator有一些功能限制，所以必须先知道其value type
	return __unique_copy(first, last, result, value_type(first));
}
//由于output是write only，无法像froward iterator那般可以读取
//所以不能有类似*result！=*first这样的判断操作，所以才需要专门设计这一版本
template<class InputIterator, class OututIterator, class T>
OututIterator __unique_copy(InputIterator frist, InputIterator last,
	OututIterator result, T*) {
	//T为output iterator的value type
	T value = *first;
	*result = value;
	while(++first!=last)
		if (value != *first) {
			value = *first;
			*++result = value;
		}
	return ++result;
}



/***********************************************************************************************************
*                 单纯数据处理之外的其他算法
************************************************************************************************************/
//lower_bound（应用于有序区间）

//若value存在，则返回迭代器指向第一个与value相同的元素
//若不存在，则返回迭代器，指向第一个“不小于value”的元素
//换句话说，返回值就是“在不破坏排序状态的原则下，可插入value的第一个位置”

//版本1
template<class ForwardIterator, class T>
inline ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, const T& value) {
	return __lower_bound(first, last, value, distance_type(first), iterator_category(first));
}
//版本2
template<class ForwardIterator, class T,class Compare>
inline ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, const T& value, Compare comp {
	return __lower_bound(first, last, value, comp, distance_type(first), iterator_category(first));
}

//辅助函数
//forward_iterator版本
template<class ForwardIterator, class T ,class Distance>
ForwardIterator __lower_bound(ForwardIterator first, ForwardIterator last,
	const T& value, Distance*, forward_iterator_tag) {
	Distance len = 0;
	distance(first, last, len);   //求取整个区间长度len
	Distance half;
	ForwardIterator middle;

	while (len > 0) {
		half = len >> 1;   //除以2
		//对于二进制来说，向右移动一位（>> 操作符）代表将一个数除以2。
		// //这是因为在二进制中，右移一位等于将二进制表示的数值除以2，而左移一位（<< 操作符）等于将其乘以2。
		middle = first;
		adavnce(middle, half);
		if (*middle < value) {
			first = middle;
			++first;
			len = len - half - 1;
		}
		else
			len = half;
	}
	return first;
}

//random_access_iterator版本
template<class RandomAccessIterator, class T, class Distance>
RandomAccessIterator __lower_bound(RandomAccessIterator first, RandomAccessIterator last,
	const T& value, Distance*, random_access_iterator) {
	Distance len = last - first;
	Distance half;
	RandomAccessIterator middle;

	while (len > 0) {
		half = len >> 1;
		middle = first + half;
		if (*middle < value) {
			first = middle + 1;
			len = len - half - 1;
		}
		else
			len = half;
	}
	return first;
}

//upper_bound(应用于有序区间)
//如果value存在，那么upper_bound返回的迭代器将指向value的下一个位置，而非指向value本身

//版本1
template<class ForwardIterator, class T>
inline ForwardIterator uper_bound(ForwardIterator first, ForwardIterator last, const T& value) {
	return __upper_bound(first, last, value, distance_type(first), iterator_category(first));
}
//版本2
template<class ForwardIterator, class T ,class Compare>
inline ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last,
	const T& value, Compare comp) {
	return __upper_bound(first, last, value, comp, distance_type(first), iterator_category(first));
}

//forward_iterator版本
template<class ForwardIterator, class T,class Distance>
ForwardIterator __upper_bound(ForwardIterator first, ForwardIterator last, const T& value, Distance*,
	forwar_iterator_tag) {
	Distance len = 0;
	distance(first, last, len);
	Distance half;
	ForwardIterator middle;

	while (len > 0) {
		half = len >> 1;
		middle = first;
		advance(middle, half);
		if (value < *middle)
			len = half;
		else {
			first = middle;
			++first;
			len = len - half - 1;
		}
	}
	return first;
}

//random_access_iterator版本
template<class RandomAccessIterator, class T, class Distance>
RandomAccessIterator __upper_bound(RandomAccessIterator first, RandomAccessIterator last, const T& value, Distance*,
	random_access_iterator_tag) {

	Distance len = last - first;
	Distance half;
	RandomAccessIterator middle;

	while (len > 0) {
		half = len >> 1;
		middle = first+half;
		if (value < *middle)
			len = half;
		else {
			first = middle + 1;
			len = len - half - 1;
		}
	}
	return first;
}

//binary_search(应用于有序区间)
//二分查找
//版本1
template<class ForwardIterator, class T>
bool binary_search(ForwardIterator first, ForwardIterator last, const T& value) {
	ForwardIterator i = lower_bound(first, last, value);      //*i <=value
	return i != last && !(value < *i);              //既不小于也不大于  那么就是等于
}

//版本2
template<class ForwardIterator, class T, class Compare>
bool binary_search(ForwardIterator firts, ForwardIterator last, const T& value, Compare comp) {
	ForwardIterator o = lower_bound(first, last, value, comp);
	return i != last && !comp(value, *i);
} 

//next_permutation
//next_permutation()会取得【first，last）所标示的下一个排列组合，如果没有下一个排列组合，便返回false，否则返回true

//版本1
template<class BidirectionalIterator>
bool next_permutation(BidirectionalIterator first, BidirectionalIterator last) {
	if (first == last) return false;
	BidirectionalIterator i = first;
	++i;
	if (i == last) return false;
	i = last;
	--i;

	for (;;) {
		BidirectionalIterator ii = i;
		--i;
		//以上，锁定一组（两个）相邻元素
		if (*i < *ii) {   //如果前一个元素小于后一个元素     //此时，【ii,last）部分是递减
			BidirectionalIterator j = last;
			while (!(*i < *--j));   //由后往前找，直到遇到比*i大的元素
			iter_swap(i, j);
			reverse(ii, last);   //将ii指挥的元素全部逆向重排
/*   字典序排序与反转的原理说明
*    对一个字典序来说，如果一个序列是递增的，说明是最小字典序排列，
*    在i与j交换元素之前的状态是【ii，last）之间是递减，i和ii之间是递增，i之前的元素咱们不考虑，由于要找下一个序列，与i之前固定的元素无关
*    所以当第一个比*i大的元素（即为j）与i交换之后，由于*j>*i而且【ii，last）又是递减序列
*    所以交换后【ii，last）仍然保持递减状态，但是又由于我们将刚好比i大的第一个元素交换到了i的位置
*    之前也说过对一个字典序，序列递增则为最小，反之递减为最大，我们交换之后不需要i之后的序列是一个最大的，我们需要一个最小的
*    这样才能保证是原序列字典序的下一个序列，"下一个"指的是比目前的序列要大，但是新序列应该是最小的那个大序列，
*    所以这里反转之后产生的递增序列保证了我们生成的新序列恰好是最小的那个大序列（【ii，last）之间的元素都递增了，你还能找到比这个新序列更小的大于
     目前序列的序列吗，显然是不能的）
	 最后所得即所求
*/
			return true;
		}
		if (i == first) {
			reverse(first, last);   //进行到最前面了
			return false;
		}
	}
}


//prev_permutation
//版本1
template<class BidirentionalIterator>
bool prev_permutation(BidirentionalIterator first, BidirentionalIterator last) {
	if (first == last) reurn false;
	BidirentionalIterator i = first;
	++i;
	if (i == last) return false;
	i = last;
	--i;

	for (;;) {
		BidirentionalIterator ii = i;
		--i;
		if (*ii < *i) {
			BidirentionalIterator j = last;
			while (!(*--j < *i));
			iter_swap(i, j);
			reverse(ii, last);
			return true;
		}
		if (i == first) {
			reverse(first, last);
			return false;
		}
	}
}

//random_shuffle
//这个算法将【first，last）的元素次序随机重排，也就是说，在N！种可能的元素排列顺序中随机选出一种，此处N为last- first
//SGI版本1
template<class RandomAccessIterator>
inline void random_shuffle(RandomAccessIterator first, RandomAccessIterator last) {
	__random_shuffle(first, last, distance_type(first));
}

template<class RandomAccessIterator, class Distance>
void __random_shuffle(RandomAccessIterator first, RandomAccessIterator last, Distance*) {
	if (first == last) return;
	for (RandomAccessIterator i = first + 1; i != last; ++i)
#ifdef __STL_NO_DRAND48
		iter_swap(i, first + Distance(rand() % ((i - first) + 1)));
#else
		iter_swap(i, first + Distance(lrand48() % ((i - first) + 1)));
#endif
}
//版本2
template<class RandomAccessIterator, class RandomAccessIterator>
void random_shuffle(RandomAccessIterator first, RandomAccessIterator last,
	RandomAccessIterator& rand) {
	if (first == last) return;
	for (RandomAccessIterator i = first + 1; i != last; ++i)
		iter_swap(i, first + rand((i - first) + 1));
}
//partial_sort/partial_sort_copy
//本算法接受一个middle迭代器位于【first，last）之内，
//使序列middle-first 个元素以递增顺序排序，置于【first，middle）中，其余last-middle 个元素安置于【middle，last）中，不保证有任何特定顺序

//内部使用heapsort完成
//partial_sort的任务是找出middle-first 个最小元素， 因此，首先界定出区间【first，middle）
//然后利用make_heap()将它组织成一个max-heap， 然后就可以将【middle， last）中的每一个元素拿来与max-heap最大值比较
//如果小于该最大值， 就互换位置并重新保持max-heap的状态，
//当我们走遍整个【middle， last）时，较大的元素都已经被抽离出【first， middle），这时候再以sort_heap将【first， middle）做一次排序
//所得及所求

//版本1
template<class RandomAccessIterator>
inline void partial_sort(RandomAccessIterator first, RandomAccessIterator middle,
	RandomAccessIterator last) {
	__partial_sort(first, middle, last,value_type(first));
}
template<class RandomAccessIterator, class T>
void __partial_sort(RandomAccessIterator first, RandomAccessIterator miiddle,
	RandomAccessIterator last, T*) {
	make_heap(first, middle);
	//注意，一下的i<last判断操作，只适合于random iterator
		for (RandomAccessIterator i = middle; i < last; ++i)
			if (*i < *first)
				__pop_heap(first, middle, i, T(*i), distance_type(first));
	sort_heap(first, middle);
}

//partial_sort_copy
//版本1
template<class InputIterator, class RandomAccessIterator>
inline RandomAccessIterator
partial_sort_copy(InputIterator first, InputIterator last, RandomAccessIterator result_first,
	RandomAccessIterator result_last);
//版本2
template<class InputIterator, class RandomAccessIterator, class Compare>
inline RandomAccessIterator
partial_sort_copy(InputIterator first, InputIterator last, RandomAccessIterator result_first,
	RandomAccessIterator result_last, Compare comp);


//sort

//inertion_sort   插入排序
//版本1
template<class RandomAccessIterator>
void __insertion_sort(RandomAccessIterator first, RandomAccessIterator last) {
	if (first == last) return;
	for (RandomAccessIterator i = first + 1; i != last; ++i)
		__linear_insert(first, i, value_type(first));
}
//辅助函数linear_insert
template<class RandomAccessIterator, class T>
inline void __linear_insert(RandomAccessIterator frist, RandomAccessIterator last, T*) {
	T value = *last;
	if (value < *first) {//尾比头还小
		copy_backward(first, last, last + 1);   //将整个区间向右递移一个位置
		*first = value;
	}
	else
		__unguarded_linear_insert(last, value);
}
//辅助函数unguarded_linear_insert
template<class RandomAccessIterator, class T>
void __unguarded_linear_insert(RandomAccessIterator last, T value) {
	//在这个函数中，last 是一个迭代器，指向要插入元素的位置，而不是指向容器的尾端。
	// 它的任务是在已知的递增序列中找到 value 的正确插入位置，并将其插入到该位置
	RandomAccessIterator next = last;
	--next;
	while (value < *next) {
		*last = *next;
		last = next;
		--next;
	}
	*last = value;
}

//quick sort   快速排序
//如果利用insertion sort来处理大量数据，时间复杂度过高，所以采用quick sort，平均时间复杂度为(NlogN)

//以下是SGI STL提供的三点中值决定函数
//返回a，b，c之居中者
template<class T>
inline const T& __median(const T& a, const T& b, const T& c) {
	if (a < b)
		if (b < c)
			return b;
		else if (a < c)
			return c;
		else
			return a;
	else if (a < c)
		return a;
	else if (b < c)
		return c;
	else
		return b;
}
//分割partitionining
//分割的方法不止一种，下面介绍一种简单又好用的
//令头端迭代器first向尾端移动，尾端迭代器向头部移动，当*first大于或等于枢纽的时候停下来
//当*last小于或等于枢纽的时也停下来，然后检验两个迭代器是否交错，如果没有交错就交换first和last所指元素
//然后各自调整一个位置（向中央逼近）再进行相同的行为，如果两个迭代器交错了，表示整个序列已经调整完毕
//以此时的first为轴，将序列分为左右两半，左半部的元素值都小于或等于枢纽值，右半部的都大于或等于枢纽值

//版本1
template<class RandomAccessIterator, class T>
RandomAccessIterator __unguarded_partition(
	RandomAccessIterator first, RandomAccessIterator last, T pivot
) {
	while (true) {
		while (*first < pivot) ++first;
		--last;
		while (pivot < *last) --last;
		//注意，以下first<last的判断操作，只适用于random iterator
		if (!(first < last)) return first;
		iter_swap(first, last);
		++first;
	}
}

//阈值threshold
//适度评估序列的大小，然后决定采用quick sort 或者 insertion sort，是值得采纳的一种优化措施


//以下是SGI STL sort()源代码
//版本1
template<class RandomAccessIterator>
inline void sort(RandomAccessIterator first, RandomAccessIterator last) {
	if (first != last) {
		__introsort_loop(first, last, value_type(first), __lg(last - first) * 2);
		__final_insertion_sort(first, last);
	}
}

//其中__lg()用来控制分割恶化的情况
//找出2^k <= n的最大值k，例如n=7，得k=2，n=20，得k=4，n=8，k=3
template<class Size>
inline Size __lg(Size n) {
	Size k;
	for (k = 0; n > 1; n >>= 1) ++k;
	return k;
}

//introsort算法如下：
template<class RandomAccessIterator, class T, class Size>
void __introsort_loop(RandomAccessIterator first, RandomAccessIterator last, T*, Size depth_limit) {
	//以下__stl_threshold是个全局函数，定义为 const int 16
	while ((last - first) > __stl_threshold) {
		if (depth_limit == 0) {
			//分割恶化
			partial_sort(first, last, last);   //改成堆排序
			return;
		}
		--depth_limit;
		//以下是median-of-3 partition，选择一个够好的枢纽并决定分割点
		//分割点将落在迭代器cut身上
		RandomAccessIterator cut = __unguarded_partition(first, last, T(__median(*first, *(first + (last - first) / 2), *(last - 1))));
		//对右半段递归进行sort
		__introsort_loop(cut, last, value_type(first), depth_limit);
		last = cut;
		//现在回到while循环，准备对左半段递归进行sort
	}
}
//当__introsort_loop()结束，【first，last）内有多个“元素个数少于16”的子序列，每个子序列都有相当程度的排序
//但尚未完全排序。回到母函数sort,再进入__final_insertion_sort()
//版本1
template<class RandomAccessIterator>
void __final_insertion_sort(RandomAccessIterator first, RandomAccessIterator last) {
	if (last - frist > __stl_threshold) {
		__insertion_sort(frist, first + __stl_threshold);   //前16个元素进行插入排序
		__unguarded_intertion_sort(first + __stl_threshold, last);
	}
	else
		__insertion_sort(first, last);
}
//以上函数首先判断元素个数是否大于16，如果答案为否，就调用__insertion_sort()加以处理，如果答案为是
//就将【first，last）分割为长度16的一段子序列，和另一段剩余子序列，在针对两个子序列分别调用__insertion_sort()和__unguarded_insertion_sort(）
//以下是__unguarded_insertion_sort的源码

//版本1
template<class RandomAccessIterator>
inline void __unguarded_insertion_sort(RandomAccessIterator first, RandomAccessIterator last) {
	__unguarded_insertion_sort_aux(first, last, value_type(first));
}

template<class RandomAccessIterator, class T>
void __unguarded_insertion_sort_aux(RandomAccessIterator first, RandomAccessIterator last, T*) {
	for (RandomAccessIterator i = first; i != last; ++i)
		__unguarded_linear_insert(i, T(*i));
}


//equal_range(应用于有序区间)
//equal_range相当于返回lower_bound和upper_bound组成的区间[i,j)

//版本1
template<class ForwardIterator, class T>
inline pair<ForwardIterator, ForwardIterator>
equal_range(ForwardIterator first, ForwardIterator last, const T& value) {
	//根据迭代器的种类，采用不同策略
	return __equal_range(first, last, value, distance_type(first), iterator_category(first));
}

//版本1的random access iterator版本
template<class RandomAccessIterator, class T,class Distance>
pair<RandomAccessIterator,RandomAccessIterator>
__equal_range(RandomAccessIterator first, RandomAccessIterator last, const T& value,
	Distance*, random_access_iterator_tag) {
	Distance len = last - first;
	Distance half;
	RandomAccessIterator middle, left, right;

	while (len > 0) {
		half = len >> 1;     //找出中央位置
		middle = first + half;
		if (*middle < value) {
			first = middle + 1;
			len = len - half - 1;
		}
		else if (value < *middle)
			len = half;
		else {
			//如果中央元素等指定值
			//在前半段找lower_bound
			left = lower_bound(first, middle, value);
			//在后半段找upper_bound
			right = upper_bound(++middle, first + len, value);
			return pair<RandomAccessIterator, RandomAccessIterator>(left, right);
		}
	}
	//整个区间没有匹配值，那么应该返回一对迭代器，指向第一个大于value的元素
	return pair<RandomAccessIterator, RandomAccessIterator>(first, first);
}

//版本1的forward_iterator版本
template<class ForwardIterator, class T, class Distance>
pair<ForwardIterator,ForwardIterator>
__equal_range(ForwardIterator first, ForwardIterator last, const T& value,
	Distance*, forward_iterator_tag) {
	Distance len = 0;
	distance(first, last, len);
	Distance half;
	ForwardIterator middle, left, right;

	while (len > 0) {
		half = len >> 1;
		middle = first;
		advance(middle, half);   //这与上一行等同于middle = first +half；
		if (*middle < value) {
			first = middle;
			++first;
			len = len - half - 1;
		}
		else if (value < *middle)
			len = half;
		else {
			left = lower_bound(first, middle, value);
			advance(first, len);
			//将first = first+len  ，只能通过acvance进行，只有random可以直接+，最后将first当last用
			right = upper_bound(++middle, first, value);
			return pair<RandomAccessIterator, RandomAccessIterator>(left, right);
		}
	}
	return pair<RandomAccessIterator, RandomAccessIterator>(first, first);
}

//inplace_merge(应用于有序区间)
//如果两个连接在一起的序列【first，middle）和【middle，last）都已排序，那么inplace_merge可将它们结合成单一一个序列
//inplace_merge是一种稳定的操作

//版本1
template<class BidirectionalIterator>
inline void inplace_merge(BidirectionalIterator first, BidirectionalIterator middle, BidirectionalIterator last) {
	if (first == middle || middle == last) return;
	__inplace_merge_aux(first, middle, last, value_type(first), distance_type(first));
}
//辅助函数
template<class BidirectionalIterator, class T, class Distance>
inline void __inplace_merge_aux(BidirectionalIterator first, BidirectionalIterator middle, BidirectionalIterator last, T*
	, Distance*) {
	Distance len1 = 0;
	distance(first, middle, len1);
	Distance len2 = 0;
	distance(middle, last, len2);

	//本算法会使用额外的内存空间
	temporary_buffer<BidirectionalIterator T>buf(first, last);
	if (buuf.begin() == 0)  //内存配置失败
		__merge_without_buffer(first, middle, last, len1, len2);
	else   //在有暂时缓冲区的情况下进行
		__merge_adaptive(first, middle, last, len1, len2, buf.begin(), Distance(buf.size()));
}
//这个算法如果有额外的内存辅助，效率会好很多，但是在没有缓冲区或缓冲区不足的情况下，也可也运作，为了篇幅
//只讨论有缓冲区的情况
//辅助函数，有缓冲区的情况
template<class BidirectionalIterator, class Distance, class Pointer>
void __merge_adaptive(BidirectionalIterator first, BidirectionalIterator middle,
	BidirectionalIterator last, Distance len1, Distance len2, Pointer buffer, Distance buffer_size) {
	if (len1 <= len2 && len1 <= buffer_size) {
		//case1,缓冲区足够安置序列1
		Pointer end_buffer = copy(first, middle, buffer);
		merge(buffer, end_buffer, middle, last, first);
	}
	else if (len2 <= buffer_size) {
		//case2,缓冲区足够安置序列2
		Pointer end_buffer = copy(middle, last, buffer);
		__merge_backward(first, middle, buffer, end_buffer, last);
	}
	else {
		//case3 缓冲区空间不足安置任何一个序列
		BidirectionalIterator first_cut = first;
		BidirectionalIterator second_cut = middle;
		Distance len11 = 0;
		Distance len22 = 0;
		if (len1 > len2) {   //序列1比较长
			len11 = len1 / 2;
			advance(first_cut, len11);
			second_cut = lower_bound(middle, last, *first_cut);
			distance(middle, second_cut, len22);
		}
		else {
			//序列2比较长
			len22 = len2 / 2;
			advance(second_cut, len22);
			first_cut = upper_bound(first, middle, *second_cut);
			distance(first, first_cut, len11);
		}
		BidirectionalIterator new_middle = __rotate_adaptive(first_cut, middle, second_cut, len1 - len11,
			len22, buffer, buffer_size);
		//针对左段，递归调用
		__merge_adaptive(first, first_cut, new_middle, len11, len22, buffer, buffer_size);
		//针对右段，递归调用
		__merge_adaptive(new_middle, second_cut, last, len1 - len11, len2 - len22, buffer, buffer_size);
	}
}

//nth_element
//这个算法会重新排列[first, last)，是迭代器nth所指的元素，与“整个【first，last）完整排序后，同一位置的元素”同值
//此外，保证【nth，last）内没有任何一个元素小于【first，nth）内的元素（准确说是不大于）
//但对于【frist，nth）和【nth，last）两个子区间内的元素次序则无任何保证

//版本1
template<class RandomAccessIterator>
inline void nth_element(RandomAccessIterator first, RandomAccessIterator nth,
	RandomAccessIterator last) {
	__nth_element(first, nth, last, value_type(first));
}
//辅助函数
template<class RandomAccessIterator, class T>
void __nth_element(RandomAccessIterator first, RandomAccessIterator nth, RandomAccessIterator last, T*) {
	while (last - first > 3) {
		//长度超过3
		//采用median-of-3 partitioning。 参数为（first，last，pivot）
		//返回一个迭代器，指向分割后的右段第一个元素
		RandomAccessIterator cut = __unguarded_partition   //__unguarded_partition使得，在pivot左边的都比它小，右边的都比它大
		(first, last, T(__median(*first, 
								*(first + (last - first) / 2), 
								*(last - 1)));
		if (cut <= nth)
			first = cut;
		else
			last = cut;
	}
	__insertion_sort(first, last);
}

//merge_sort
template<class BidirectionalIter>
void mergesort(BidirectionalIter first, BidirectionalIter last) {
	typename iterator_traits<BidirectionalIter>::difference_type n = distance(first, last);
	if (n == 0 || n == 1)
		return;
	else {
		BidirectionalIter mid = first + n / 2;
		mergesort(first, mid);
		mergesort(mid, last);
		inplace_merge(first, mid, last);
	}
}