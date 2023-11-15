
//针对char int long等整数型别
//这里的大部分hash functions什么也没做，只是返回原值，但对于字符字符串(const char*),就设计了一个转换函数
//如下：
template<class Key>struct hash {};

inline size_t __stl_hash_string(const char* s)
{
	unsigned long h = 0;
	for (; *s; ++s)
		h = 5 * h + *s;

	return size_t(h);
}

__STL_TEMPLATE_NULL sturct hash<char*>
{

}