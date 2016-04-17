// https://www.hackerrank.com/challenges/icecream-parlor
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>

template<typename T>
class Flavor
{
public:
	Flavor(T budget, T nFlavor);
	~Flavor();
public:
	void read_cost_of_flavors();
	void process();
private:
	T budget_;
	T nFlavor_;
	std::vector<T> vecCost_;
};
//---
template<typename T>
Flavor<T>::Flavor(T budget, T nFlavor)
: budget_(budget)
, nFlavor_(nFlavor)
{
	vecCost_.reserve(nFlavor_);
}
template<typename T>
Flavor<T>::~Flavor()
{
}
template<typename T>
void Flavor<T>::read_cost_of_flavors()
{
	T cost;
	for (T flavor_i = 0; flavor_i != nFlavor_; ++ flavor_i)
	{
		std::cin >> cost;
		vecCost_.push_back(cost);
	}
}
template<typename T>
void Flavor<T>::process()
{
	// first populate the hash map
	std::tr1::unordered_map<T,T> flavorMap;
	for (typename std::vector<T>::iterator it = vecCost_.begin(); it != vecCost_.end(); ++it)
	{
		typename std::tr1::unordered_map<T,T>::iterator mapIt = flavorMap.find(*it);
		if (mapIt == flavorMap.end())
		{
			flavorMap.insert(std::make_pair(*it,1));
		}
		else
		{
			++(*mapIt).second;
		}
	}

	bool found = false;
	T num1, num2;
	typename std::vector<T>::iterator it;
	for (it = vecCost_.begin(); it != (vecCost_.end()-1); ++it)
	{
		num1 = (*it);
		if (budget_ <= num1)
		{
			continue;
		}
		num2 = budget_ - num1;
		
		typename std::tr1::unordered_map<T,T>::iterator mapIt = flavorMap.find(num2);
		if (num1 == num2)
		{
			if ((*mapIt).second > 1)
			{
				found = true;
				break;
			}
		}
		else
		{
			if(mapIt != flavorMap.end())
			{
				found = true;
				break;
			}
		}
	}

	if (found)
	{
		std::cout << std::distance(vecCost_.begin(),it)+1;
		std::cout << " ";
		typename std::vector<T>::iterator nextIt;
		for (nextIt = it+1; nextIt != vecCost_.end(); ++nextIt)
		{
			if ((*nextIt) == num2)
			{
				break;
			}
		}
		assert( (nextIt != vecCost_.end()) && "error");
		std::cout << std::distance(vecCost_.begin(),nextIt)+1 << std::endl;
	}
	else
	{
		std::cout << -1 << std::endl;
	}
}
//---
int main(int argc, char* argv[])
{
	unsigned int nCase, C, L;
	std::cin >> nCase;
	for (unsigned int case_i = 0; case_i != nCase; ++case_i)
	{
		std::cin >> C >> L;
		Flavor<unsigned int> flavor(C,L);
		flavor.read_cost_of_flavors();
		flavor.process();
	}
	return 0;
}
/*
http://stackoverflow.com/questions/3559344/error-no-matching-function-for-call-to-make-pairint-quest/5282125
Johannes Schaub's answer:
....make_pair is designed to be called without explicit template arguments...

http://eli.thegreenplace.net/2011/12/15/understanding-lvalues-and-rvalues-in-c-and-c/
*/