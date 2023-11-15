#pragma once
//下面是hash table的节点定义
template<class Value>
struct __hashtable_node {
	__hashtable_node* next;
	Value val;
};

//以下是hash table 的迭代器
template<class Value, class Key, class HashFcn,
class ExtractKey, class EqualKey, class Alloc>
struct __hashtable_iterator {
	typedef hashtable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> hashtable;
	typedef __hashtable_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> iterator;
	typedef __hashtable_const_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> const_iterator;
	typedef __hashtable_node<Value> node;
	
	typedef forward_iterator_tag iterator_category;
	typedef Value value_type;
	typedef ptrdiff_t difference_type;
	typedef size_t size_type;
	typedef Value& reference;
	typedef Value* pointer;

	node* cur;       //迭代器目前所指之节点
	hashtable* ht;    //保持对容器的连结关系（因为可能需要从bucket跳到bucket）

	__hashtable_iterator(node* n, hashtable* tab) :cur(n), ht(tab) {}
	__hashtabke_iterator() {}
	reference operator*()const { return cur->val; }
	pointer operator->()const { return &(operator*()); }
	iterator& operator++();
	iterator operator++(int);
	bool operator==(const iterator& it)const { return cur == it.cur; }
	bool operator!=(const iterator& it)const { return cur != it.cur; }
 };

//注意，hashtable迭代器必须永远维持着与整个“buckets vector”的关系，并记录目前所指的节点
//前进操作是首先尝试从目前所指的节点出发，前进一个位置（节点），由于节点被安置在list内，所以
//利用节点的next指针即可轻易达到前进操作，如果目前节点正巧是list的尾部，就跳至下一个bucket身上，那正是
//指向下一个list的头部节点
template<class V, class K, class HF, class ExK, class EqK, class A>
__hashtable_iterator<V, K , HF, ExK, EqK, A>& 
__hashtable_iterator<V, K, HF, ExK, EqK, A>::operator++()
{
	const node* old = cur;
	cur = cur->next;   //如果存在， 就是它，否则就进入以下if流程
	if (!cur) {
		//根据元素值，定位出下一个bucket，其起头处就是我们的目的地
		size_type bucket = ht->bkt_num(old->val);
		while (!cur && ++bucket < ht->buckets.size())
			cur = ht->buckets[bucket];
	}
	return *this;
}
template<class V, class K, class HF, class ExK, class EqK, class A>
inline __hashtable_iterator<V, K, HF, ExK, EqK, A>
__hashtable_iterator<V, K, HF, ExK, EqK, A>::operator++(int)
{
	iterator tmp = *this;
	++*this;
	return tmp;
}

//请注意 hashtable的迭代器没有后退操作（operator--（）），hashtable也没有定义所谓的逆向迭代器（reverse iterator）

//下面是hashtable的定义摘要，其中可见buckets聚合体以vector完成，以利动态扩充：
template<class Value, class Key, class HashFcn, 
class ExtractKey, class EqualKey, class Alloc>
class hashtable {
public:
	typedef HashFcn hasher;
	typedef EqualKey key_equal;
	typedef size_t size_type;

private:
	//以下三者都是function objects  <stl_hash_fun.h>中
	//定义有数个标准型别（如int， c-style， string等）的hasher
	hasher hash;
	key_equal equals;
	ExtractKey get_key;

	typedef __hashtable_node<Value> node;
	typedef simple_alloc<node, Alloc> node_allocator;

	vector<node*, Alloc> buckets;   //以vector完成
	size_type num_elements;
public:
	//bucket个数即buckets vector的大小
	size_type bucket_count() const { return buckets.size(); }

	//...

	//虽然开链法（separate chaining）并不要求表格大小必须为质数，但SGI STL仍以质数大小来设计表格大小
	//并且先将28个质数计算好，以备随时访问，同时提供一个函数，用来查询这28个质数之中，“最接近某数并大于某数”的质数

	//注意，假设long至少有32bits
	static const int __stl_num_primes = 28;
	static const unsigned long __stl_prime_list[__stl_num_primes] =
	{
		53,	97,	193,	389,	769,
		1543,	3079,	6151,	12289,	24593,
		49157,	98317,	196613,	33241,	786433,
		1572869,	3145729,	6291469,	12582917,	25165843,
		50331653,	100663319,	201326611,	402653189,	805306457,
		1610612741,	3221225473,	4294967291
	};
	//以下找出上述质数中，最接近并大于n的那个质数
	inline unsigned long __stl_next_prme(unsigned long n)
	{
		const unsigned long* first = stl_prime_list;
		const unsigned long* last = __stl_prime_list + stl_num_prime;
		const unsigned long* pos = lower_bound(first, last, n);
		return pos == last ? *(last - 1) : *pos;
	}

	//总共可以有多少buckets，以下是hast_table的一个member function
	size_type max_bucket_count() const
	{
		return __stl_prime_list[__stl_num_prime - 1];
	}


	//下面是节点配置函数与节点释放函数
	node* new_node(const value_type& obj)
	{
		node* n = node_allocator::allocate();
		n->next = 0;
		__STL_TRY{
			construct(&n->val, obj);
		return n;
		}
		__STL_UNWIND(node_allocator::deallocate(n));
	}

	void delete_node(node* n)
	{
		destroy(&n->val);
		node_allocator::deallocate(n);
	}

	hastbale(size_type n, const HashFcn& hf, const EqualKey& eql)
		:hash(hf), equals(eql), get_key(ExtractKey()), num_elements(0)
	{
		initialize_buckets(n);
	}

	void initialize_buckets(size_type n)
	{
		const size_type n_buckets = next_size(n);
		buckets.reserve(n_buckets);
		buckets.insert(buckets.end(), n_buckets, (node*)0);
		num_elements = 0;
	}

	//插入元素，不允许重复
	pair<iterator, bool> insert_unique(const value_type& obj)
	{
		resize(num_elements + 1);          //判断是否需要重建表格，如需要就扩充
		return insert_unique_noresize(obj);
	}

	//以下函数判断是否需要重建表格，如果不需要，立刻回返，如果需要就扩充
	template<class V, class K, class HF, class Ex, class Eq, class A>
	void hashtable<V, K, HF, Ex, Eq, A>::resize(size_type num_elements_hint)
	{
		//以下 “表格重建与否”的判断原则颇为奇特，是拿元素个数（把新增元素计入后）和
		//bucket vector的大小来比， 如果前者大于后者， 就重建
		//由此可知 每个bucket(list)的最大容量和buckets vector的大小相同
		const size_type old_n = buckets.size();
		if (num_elements_hint > old_n) {    //确定真的需要重新配置
			const size_type n = next_size(num_elements_hint);   //找出下一个质数
			if (n > old_n) {
				vector<node*, A>tmp(n, (node*)0);     //设立新的buckets
				__STL_TRY{
					//以下处理每一个旧的bucket
					for (size_type bucket = 0; bucket < old_n; ++bucket) {
						node* first = buckets[bucket];    //指向节点所对应之串行的起始节点
						//以下处理每一个旧bucket所含的每一个节点
						while (first) {
							//以下找出节点落在哪一个新bucket内
							size_type new_bucket = bkt_num(first->val, n);
							//以下四个操作颇为奇妙
							//（1）令旧bucket指向其对应之串行的下一个节点（以便迭代处理）
							buckets[bucket] = first->next;
							//(2)(3)将当前节点插入到新bucket内， 成为其对应串行的第一个节点
							first->next = tmp[new_bucket];
							tmp[new_bucket] = first;
							//(4)回到旧bucket所指的待处理串行，准备处理下一个节点
							first = buckets[bucket];
						}
					}
				buckets.swap(tmp);   //vector::swap 新旧两个buckets对调
				//注意，对调两方如果大小不同， 大的会变小，小的会变大
				//离开时释放lcoal tmp的内存

				}
			}

		}
	}

	//在不需要重建表格的情况下插入新节点，键值不允许重复
	template<class V, class K, class HF, class Ex, class Eq, class A>
	pair<typename hastbale<V, K, HF, Ex, Eq, A>::iterator, bool>
		hashtable<V, K, HF, Ex, Eq, A>::insert_unique_noresize(const value_type& obj)
	{
		const size_type n = bkt_num(obj);
		node* first = buckets[n];

		//如果buckets[n]已被占用，此时first将不为0，于是进入以下循环
		//走过bucket所对应的整个链表
		for (node* cur = first; cur; cur = cur->next)
			if (equals(get_key(cur->val), get_key(obj)))
				//如果发现与链表中的某键值相同，就不插入，立即返回
				return pair<iterator, bool>(iterator(cur, this), false);

		//离开循环时， first指向bucket所指链表的头部节点
		node* tmp = new_node(obj);
		tmp->next = first;
		buckets[n] = tmp;
		++num_elements;
		return pair<iterator, bool>(iterator(tmp, this), true);
	}


	//如果客户端执行的是另一种节点插入行为（不再是insert_unique,而是insert_equal)
	//进行的操作如下
	iterator insert_eauql(const value_type& obj)
	{
		resize(num_elements + 1);
		return insert_equal_noresize(obj);
	}

	//在不需要重建表格的情况下插入新节点，键值允许重复
	template<class V, class K, class HF, class Ex, class Eq, class A>
	typename hashtable<V, K, HF, Ex, Eq, A>::iterator
		hashtable<V, K, HF, Ex, Eq, A>::insert_equal_noresize(const value_type& obj)
	{
		const size_type n = bkt_num(obj);    //决定obj应该位于哪个桶
		node* first = buckets[n];          //令first指向bucket对应之链表头

		//如果bucket[n]已被占用，此时first将不为0， 于是进入以下循环
		//走过bucket所对应的整个链表
		for(node* cur = first;cur;cur = cur->next)
			if (equals(get_key(cur->val), get_key(obj))) {
				//如果发现与链表中某键值相同，就马上插入，然后返回
				node* tmp = new_node(obj);
				tmp->next = cur->next;
				cur->next = tmp;
				++num_elements;
				return iterator(tmp, this);
			}


		//进行至此，表示没有发现重复的键值
		node* tnp = new_node(obj);
		tmp->next = first;
		bucket[n] = tmp;
		++num_elements;
		return iterator(tmp, this);
	}



	//对于以上判断元素落脚处的 bucket_num（）函数进行源码解释

	//version1  ，接受实值和buckets个数
	size_type bkt_num(const value_type& obj, size_t n) const
	{
		return bkt_num_key(get_key(obj), n);    //调用version4
	}

	//version2  只接受实值
	size_type bkt_num(const value_type& obj) cosnt
	{
		return bkt_num_key(get_key(obj);)   //调用version3
	}

	//version3 只接受键值
	size_type bkt_num_key(const key_type& key) const
	{
		return bkt_num_key(key, bucktes.size());   //调用version4
	}

	//version4 接受键值和buckets个数
	size_type bkt_num_key(const key_type& key, size_t n) const
	{
		return hash(key) % n;    
	}


	//由于整个hash table由vcetor和linked-list组合而成，因此，父子和整体都删除，都需要特别注意内存的释放问题，
	//下面是hashtable提供的copy_from和clear两个函数
	template<class V, class K, class HF, class Ex, class Eq, class A>
	void hashtable<V, K, HF, Ex, Eq, A>::clear()
	{
		//针对每一个bucket
		for (size_type i = 0; i < buckets.size(); ++i) {
			node* cur = buckets[i];
			//将bucket list中的每一个节点删除掉
			while (cur != 0) {
				node* next = cur->next;
				delete_node(cur);
				cur = next;
			}
			buckets[i] = 0;   //令bucket内容为null指针
		}
		num_elements = 0;
	}

	temlate<class V, class K, class HF, class Ex, class Eq, class A>
		void hashtable<V, K, HF, Ex, Eq, A>::copy_from(const hashtable& ht)
	{
		//先清除己方的buckets vector，这操作是调用vector::clear 造成所有元素为0  
		buckets.clear();
		//为己方的buckets vector保留空间，使与对方相同
		//如果己方空间大于对方，就不动，如果己方空间小于对方， 就会增大
		buckets.reserve(ht.bukcets.size());
		//从己方的buckets vector尾端开始，插入n个元素，其值为null指针
		//注意，此时buckets vector尾端开始，插入n个元素，其值为null指针
		//注意，此时buckets vector为空，所以所谓尾端，就是起头处
		buckets.insert(buckets.end(), ht.buckets.size(), (node*)0);
		__STL_TRY{
			//针对buckets vector
			for (size_type i = 0; i < ht.buckets.size(); ++i) {
				//复制vector的每一个元素（是个指针，指向hashtable节点）
				if (const node* cur = ht.buckets[i]) {
					node* copy = new_node(cur->val);
						buckets[i] = copy;

						//针对同一个bucket list， 复制每一个节点
						for (node* next = cur->next; next; cur = next, next = cur->next) {
							copy->next = new_node(next->val);
							copy = copy->next;
						}
				}
			}
		num_elemenets = ht.num_elements;   //重新登录节点个数
		}
		__STL_UNWIND(clear());
	}
};



/*

hashtable的模板参数很多

Value：节点的实值型别
Key: 节点的键值型别
HashFcn：hash function的函数型别
ExtractKey：从节点中取出键值的方法（函数或者仿函数）
EqualKey：判断键值相同与否的方法（函数或仿函数）
Alloc：空间配置器

*/

