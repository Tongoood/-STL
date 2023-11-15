#include<iostream>
#include<hash_set>
#include<cstring>

int main()
{
	std::hash_set<int> Set;
	Set.insert(3);
	Set.insert(196);
	Set.insert(1);
	Set.insert(389);
	Set.insert(194);
	Set.insert(387);

	std::hash_set<int>::iterator ite1 = Set.begin();
	std::hash_set<int>::iterator ite2 = Set.end();
	for (; ite1 != ite2; ++ite1)
	{
		std::cout << *ite1 << " ";
	}

	return 0;
}