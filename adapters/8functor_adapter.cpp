#include<algorithm>
#include<functional>
#include<vector>
#include<iostream>

void print(int i)
{
	std::cout << i << ' ';
}

class Int
{
public:
	explicit Int(int i):m_i(i) {}

	void print1() const { std::cout << '[' << m_i >> ']'; }
private:
	int m_i;
};

int main()
{
	std::ostream_iterator<int> outite(std::cout, " ");
	int ia[6] = { 2,21,12,7,19,23 };
	std::vector<int> iv(ia, ia + 6);

	//找出不小于12的元素个数
	std::cout << count_if(iv.begin(), iv.end(),
		not1(std::bind2nd(std::less<int>(), 12)));
	std::cout<<std::endl;

	//令每个元素v执行（v+2）*3 然后输往outite
	std::transform(iv.begin(), iv.end(), outite, compose1(
		std::bind2nd(std::multiplies<int>(), 3), std::bind2nd(std::plus<int>(), 2)));


}