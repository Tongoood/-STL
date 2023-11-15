#pragma once

//所谓stream iterators，可以将迭代器绑定到一个stream（数据流）对象身上
//绑定到istream对象，成为istream_iterator，拥有输入能力
//绑定到ostream对象，成为ostream_iterator，拥有输出能力


template<class T, class Distance = ptrdiff_t>
class istream_iterator {
	friend bool operator== __STL_NIULL_TMPL_ARGS(
		const istream_iterator<T, Distance>& x,
		const istream_iterator<T, Distanec>& y);

protected:
	istream* stream;
	T value;
	bool end_marker;
	void read() {
		end_marker = (*stream) ? true : false;
		if (end_marker)   *stream >> value;
		//以上，输入之后，stream的状态可能改变，所以下面再判断一次以决定end_marker
		//当读到eof 或读到型别不符的资料， stream即处于false状态
		end_marker = (*stream) ? true : false;
	}
public:
	typedef input_iterator_tag  iterator_category;
	typedef T value_type;
	typedef Distance difference_type;
	typedef const T* pointer;
	typedef const T& reference;

	istream_iterator():stream(&cin), end_marker(false){}
	istream_iterator(istream& s) :stream(&s) { read(); }
	//以上两行的用法：
	//istream_iterator<int> eos;   造成end_marker为false
	//istream_iterator<int> initer(cin);  引发read()程序会等待输入
	//因此下面这两行客户端程序
	//istream_iterator<int> initer(cin);
	// cout<<"please input..."<<endl;	
	//会停留在第一句等待一个输入，然后才执行提示输入信息的语句，这是不合理的
	//规避之道：永远在最必要的时候，才定义一个istream_iterator

	reference operator*() const { return value; }
	pointer operator->() const { return&(operator*()); }

	istream_iterator<T, Distance>& operator++() {
		read();
		return *this;
	}
	istream_iterator<T, Distance>operator++(int) {
		istream_iterator<T, Distance> tmp = *this;
		read();
		return tmp;
	}
};

//output iterator
template<class T>
class ostream_iterator {
protected:
	ostream* stream;
	const char* string;

public:
	typedef output_iterator_tag iterator_category;
	typedef void   value_type;
	/*
	* void 通常用于表示某个类型信息是不可用的，或者不需要提供特定的类型信息。
	在你的代码中，对迭代器的类型信息进行了重新定义，将它们都设置为 void。这样做的效果是将这些类型信息设置为无效或不可用。
	*/
	typedef void difference_type;
	typedef void pointer;
	typedef void reference;

	ostream_iterator(ostream& s):stream(&s),string(0){}
	ostream_iterator(ostream& s, const char* c):stream(&s),string(c){}

	//对迭代器做赋值操作，就代表要输出一笔内容
	ostream_iterator<T>& operatopr = (const T & value){
		*stream << value;
	if (string)  *stream << string;     //如果输出状态无误，输出间隔符号
	return *this;
	}

	ostream_itertaor<T>& operator*() { return *this; }
	ostream_itertaor<T>& operator++() { return *this; }
	ostream_itertaor<T>& operator++(int) { return *this; }

};