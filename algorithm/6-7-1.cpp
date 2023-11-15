#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

template <class T> struct display {
  void operator()(const T &x) const { cout << x << ' '; }
};

struct even {
  bool operator()(int x) const { return x % 2 ? false : true; }
};

class even_by_two {
public:
  int operator()() const { return _x += 2; }

private:
  static int _x;
};

int even_by_two::_x = 0;

int main() {
  int ia[] = {0, 1, 2, 3, 4, 5, 6, 6, 6, 7, 8};
  vector<int> iv(ia, ia + sizeof(ia) / sizeof(int));

  // 找出iv之中相邻元素值相等的第一个元素
  cout << *adjacent_find(iv.begin(), iv.end());
  cout << endl; // 6

  // 找出iv之中相邻元素值相等的第一个元素
  cout << *adjacent_find(iv.begin(), iv.end(), equal_to<int>()) << endl;

  // 找出iv之中元素值为6的元素个数
  cout << count(iv.begin(), iv.end(), 6) << endl;
  // 找出iv之中小于7的元素个数
  //cout << count_if(iv.begin(), iv.end(), bind2nd(less<int>(), 7)) << endl;
  // 找出iv之中元素值为4的第一个元素的所在位置的值
  cout << *find(iv.begin(), iv.end(), 4) << endl;

  // 找出iv之中子序列iv2所出现的最后一个位置（再往后3个位置的值）
  vector<int> iv2(ia + 6, ia + 8);
  cout << *(find_end(iv.begin(), iv.end(), iv2.begin(), iv2.end()) + 3) << endl;

  // 找出iv之中子序列iv2所出现的第一个位置（再往后3个位置的值）
  cout << *(find_first_of(iv.begin(), iv.end(), iv2.begin(), iv2.end()) + 3)
       << endl;

  // 迭代器遍历整个iv区间，对每一个元素施行操作
  for_each(iv.begin(), iv.end(), display<int>());
  cout<<endl;
  cout << "===========================" << endl;

  for_each(iv2.begin(), iv2.end(), display<int>());
  cout << endl;
  // 迭代整个iv2区间，对每个元素施行even_by_two操作
  generate(iv2.begin(), iv2.end(), even_by_two());
  for_each(iv2.begin(), iv2.end(), display<int>());
  cout<<endl;
  cout << "===========================" << endl;

  // 迭代遍历指定区间（起点与长度），对每个元素施行even_by_two操作
  generate_n(iv.begin(), 3, even_by_two());
  for_each(iv.begin(), iv.end(), display<int>());
   cout<<endl;
  cout << "===========================" << endl;

  // 删除元素6，尾端可能有残余数据（可令以容器之erase函数去除之）
  //remove(iv.begin(), iv.end(), 6);
  for_each(iv.begin(), iv.end(), display<int>());
  cout<<endl;
  cout << "===========================" << endl;

  // 删除元素6，结果置于另外一个区间
  vector<int> iv3;
  remove_copy(iv.begin(), iv.end(), iv3.begin(), 6);
  for_each(iv3.begin(), iv3.end(), display<int>());
  cout<<endl;
  cout << "===========================" << endl;
cout<<"我终于好了"<<endl;

  system("pause");
  return 0;
}