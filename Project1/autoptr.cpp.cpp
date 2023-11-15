template<class T>
class auto_ptr {
public:
	explicit auto_ptr(T* p = 0) : pointee(p) { }
	template<class U>
	auto_ptr(auto_ptr<U>& rhs) : pointee(rhs.release()) {}/*通过调用 rhs.release()，
		您实际上是释放了 rhs 持有的内存，并返回了一个指向该内存的裸指针。
		然后，将这个裸指针赋值给了当前 auto_ptr 对象的 pointee 成员*/
	~auto_ptr() { delete pointee; }

	template<class U>
	auto_ptr<T>& operator=(auto_ptr<U>& rhs) {
		if (this != &rhs) reset(rhs.release());
		return *this;
	}

	T& operator*() const { return *pointee; }
	T& operator->() const { return pointee; }
	T* GET() const { return pointee; }

private:
	T* pointee;
};