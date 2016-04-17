// https://www.hackerrank.com/challenges/pairs
#include <iostream>
#include <unordered_set>

template<typename T1, typename T2>
class Pair
{
public:
	Pair(T1 nNum, T2 diff);
	~Pair();
public:
	void read_input();
	T1 process();
private:
	T1 nNum_;
	T2 diff_;
	std::tr1::unordered_set<T2> unorderedSet_;
};
//---
template<typename T1, typename T2>
Pair<T1,T2>::Pair(T1 nNum, T2 diff)
: nNum_(nNum)
, diff_(diff)
{
}
template<typename T1, typename T2>
Pair<T1,T2>::~Pair()
{}
template<typename T1, typename T2>
void Pair<T1,T2>::read_input()
{
	T2 num;
	for (T1 i=0; i != nNum_; ++i)
	{
		std::cin >> num;
		unorderedSet_.insert(num);
	}
}
template<typename T1, typename T2>
T1 Pair<T1,T2>::process()
{
	T1 countDiffK = 0;

	for (typename std::tr1::unordered_set<T2>::iterator it = unorderedSet_.begin(); it != unorderedSet_.end(); ++it)
	{
		T2 num = (*it) + diff_;
		typename std::tr1::unordered_set<T2>::iterator it2 = unorderedSet_.find(num);
		
		if ( it2 != unorderedSet_.end() )
		{
			++countDiffK;
		}
	}

	return countDiffK;
}
//---
int main(int argc, char* argv[])
{
	unsigned long N,K;

	std::cin >> N >> K;
	Pair<unsigned long, unsigned long> pairs(N,K);
	pairs.read_input();
	std::cout << pairs.process();

	return 0;
}