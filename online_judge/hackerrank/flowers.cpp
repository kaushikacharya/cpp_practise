// https://www.hackerrank.com/challenges/flowers
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional> //greater

template<typename T1, typename T2>
class Flower
{
public:
	Flower(T1 nFlower, T1 nCustomer);
	~Flower();
public:
	void read_input();
	T2 process();
private:
	T1 nFlower_;
	T1 nCustomer_;
	std::vector<T2> vecCostFlower_;
	std::vector<T2> vecSpendCustomer_;
};
//---
template<typename T1, typename T2>
Flower<T1,T2>::Flower(T1 nFlower, T1 nCustomer)
: nFlower_(nFlower)
, nCustomer_(nCustomer)
{
	vecCostFlower_.reserve(nFlower_);
	vecSpendCustomer_.reserve(nCustomer_);

	for (T1 customer_i = 0; customer_i != nCustomer_; ++customer_i)
	{
		vecSpendCustomer_.push_back(0);
	}
}
template<typename T1, typename T2>
Flower<T1,T2>::~Flower()
{}
template<typename T1, typename T2>
void Flower<T1,T2>::read_input()
{
	T2 costFlower;
	for (T1 flower_i = 0; flower_i != nFlower_; ++flower_i)
	{
		std::cin >> costFlower;
		vecCostFlower_.push_back(costFlower);
	}
}
template<typename T1, typename T2>
T2 Flower<T1,T2>::process()
{
	std::sort(vecCostFlower_.begin(), vecCostFlower_.end(), std::greater<T2>());
	T2 cost = 0;
	T1 count = 0;
	T1 iterCount = 0;

	while (count < nFlower_)
	{
		++iterCount;
		T1 countCustomer_i = 0;
		while ((countCustomer_i < nCustomer_) && (count < nFlower_))
		{
			cost += iterCount*vecCostFlower_[count];
			++countCustomer_i;
			++count;
		}
	}

	return cost;
}
//---
int main(void)
{
	unsigned int N,K;
	
	std::cin >> N >> K;
	Flower<unsigned int, unsigned long> flower(N,K);
	flower.read_input();
	std::cout << flower.process();

	return 0;
}