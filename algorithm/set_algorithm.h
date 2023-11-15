#pragma once

//数学上的set允许元素重复并且无序
//stl定义的set要求元素不能重复并且有序
//multiset可以元素重复，但仍然需要有序
//以下提到的set的四个算法，必须是有序区间，元素可以重复出现

//由于s1和s2内每个元素都不需唯一，因为如果某个值在s1出现n次，s2出现m次，那么该值在输出区间中会出现max（m，n）次，其中n个来自s1，其余来自s2

//set_union是一种稳定的操作，意思是输入区间内的每个元素的相对顺序都不会改变，set_union有两个版本

//版本1
//set是sorted range，这是以下算法的前提
template<class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator set_union(InputIterator1 first1, InputIterator1 last1,
	InputIterator1 first2, InputIterator1 last2, OutputIterator result) {
	//当两个区间都尚未到达尾端时，执行以下操作
	while (first1 != last1 && first2 != last2) {
		if (*first1 < *first2) {
			*result = *first1;
			++first;
		}
		else if (*first2 < *first1) {
			*result = *first2;
			++first1;
		}
		else {
			*reslut = *first1;
			++first1;
			++first2;
		}
		++result;    //返回值为一个迭代器，指向输出区间的尾端
	}
	//只要两区之中有一区到达尾端，就结束while循环
	//此刻的【first1，last1）和【first2，last2）之中有一个是空白区间
	/*这是因为 std::copy 函数会检查迭代器范围是否为空，如果为空，它会立即返回 result 迭代器，不执行任何复制操作。
	这个检查确保了只有非空区间的内容才会被复制，而空白区间不会对结果产生任何影响。*/
	//copy的设计非常精妙
	return copy(first2, last2,copy(first1, last1, result));
}



//set_intersection
//s1,s2和其交集都是以排序区间表示（有序），返回值为一个迭代器，指向输出区间的尾端
//set_intersection是一种稳定的操作，意思是输出区间内的每个元素的相对顺序和s1内的相对顺序相同

//版本1
template<class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator set_intersection(InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2,
	OutputIterator result) {
	//当两个区间未到尾端时，执行以下操作
	while (first1 != last1 && first2 != last2) {
		if (*first1 < *first2)
			++first1;
		else if (*first2 < *first1)
			++first2;
		else {
			*result = *first1;
			++first1;
			++first2;
		}
		return result;
	}
	//多余之内容不用考虑，因为是交集
}


//set_difference
//set_difference可以构造出集合s1-s2   s1，s2都是以排序区间表示，返回值为一个迭代器，指向输出区间的尾端
//set_difference是一种稳定的操作，意思是输出区间的每个元素的相对顺序都和s1内的相对顺序相同

//版本1
template<class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator set_difference(InputIterator1 first1, InputIterator1 last1,
	InputIterator1 first2, InputIterator1 last2, OutputIterator result) {
	//当两个区间都尚未到达尾端时，执行以下操作
	while (first1 != last1 && first2 != last2) {
		/*
		在两区间内分别移动迭代器，当第一区间的元素等于第二区间的元素（表示此值存在于两区间）
		就让两区间同时前进；当第一区间的元素大于第二区间的元素，就让第二区间前进，有了这两种处理，就保证当第一区间的元素小于第二区间的原始时，
		第一区间的元素只存在于第一区间中，不存在第二区间中，于是将它记录于目标区
		*/
		if (*first1 < *first2) {
			*result = *first;
			++first1;
			++result;
		}
		else if (*first2 < *first1) {
			++first2;
		}
		else {
			++first1;
			++first2;
		}
		return copy(first1, last1, result);   //由于是s1-s2，所以只需将s1剩余内容保存
	}
}


//set_symmetric_difference
//set_symmetric_difference可构造s1，s2之对称差集
//也就是说可以构造出集合（s1-s2）∪（s2-s1），此集合内容“出现于s1但不出现于s2”以及“出现于s2但不出现于s1”
//由于s1和s2内的每个元素都不需唯一，因此如果某个值在s1出现n次，s2出现m次，那么该值在输出区间会出现|n-m|次
//如果n>m,输出区间的最后n-m个元素将从s1复制而来，否则从s2复制来
//set_symmetric_difference是一种稳定的操作
template<class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator set_symmetric_difference(InputIterator1 first1,
	InputIterator1 last1,
	InputIterator1 first2,
	InputIterator2 last2,
	OutputIterator result) {
	//当两个区间都尚未到达尾端时，
	while (first1!=last1 && first2 != last2) {
		//在两区间分别移动迭代器，如果元素相等，就让两区同时前进
		//当两区内的元素不等时，就记录较小值于目标区，并令较小值在区间前进
		if (*first1 < *first2) {
			*result = *first1;
			++first1;
			++result;
		}
		else if (*first2 < *first1) {
			*result = *first2;
			++first2;
			++result;
		}
		else {
			++first1;
			++first2;
		}
		return copy(first2, last2, copy(first1, last1, result));
	}
}