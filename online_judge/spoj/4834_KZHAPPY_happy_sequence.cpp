// http://www.spoj.com/problems/KZHAPPY/
#include <iostream>
#include<vector>
#define MAX_SIZE 500
typedef unsigned int DType;

template<typename T>
class Kruzade
{
public:
	Kruzade();
	~Kruzade();
public:
	T process(T n);
private:
	// http://stackoverflow.com/questions/12183008/using-enums-in-c
	enum Status
	{
		Happy,
		NotHappy,
		Undecided
	};
	std::vector<Status> vecStatus_;
	std::vector<bool> vecVisited_;
	std::vector<T> vecHappy_;
	T size_;
	T completedScanTill_;
};
//---
template<typename T>
Kruzade<T>::Kruzade()
{
	size_ = 500; //a random initialization
	vecStatus_.reserve(size_);
	vecVisited_.reserve(size_);
	for (T i = 0; i != size_; ++i)
	{
		vecStatus_.push_back(Undecided);
		vecVisited_.push_back(false);
	}
	vecStatus_[0] = Happy;
	vecVisited_[0] = true;
	completedScanTill_ = 1;
	vecHappy_.push_back(1);
}
template<typename T>
Kruzade<T>::~Kruzade()
{}
template<typename T>
T Kruzade<T>::process(T n)
{
	while (vecHappy_.size() < n)
	{
		T elem = completedScanTill_+1;
		std::vector<T> vecElem;
		
		while (!vecVisited_[elem-1]) //0 indexed
		{
			vecVisited_[elem-1] = true;
			vecElem.push_back(elem);
			T sum_square_digits = 0;
			while (elem)
			{
				T right_most_digit = elem % 10;
				sum_square_digits += right_most_digit*right_most_digit;
				elem /= 10;
			}
			elem = sum_square_digits;
			if (size_ < elem)
			{
				vecStatus_.resize(elem,Undecided);
				vecVisited_.resize(elem,false);
				size_ = elem;
			}
		}

		if (!vecElem.empty())
		{
			Status statusOfSeq = Happy;
			if ((vecStatus_[elem-1] == Undecided) || (vecStatus_[elem-1] == NotHappy))
			{
				statusOfSeq = NotHappy;
			}

			for (typename std::vector<T>::iterator it = vecElem.begin(); it != vecElem.end(); ++it)
			{
				vecStatus_[(*it)-1] = statusOfSeq;
			}
		}

		++completedScanTill_;
		if (vecStatus_[completedScanTill_-1] == Happy)
		{
			vecHappy_.push_back(completedScanTill_);
		}
	}

	return vecHappy_[n-1];
}
//---
int main(int argc, char* argv[])
{
	DType nCase,n;
	std::cin >> nCase;
	Kruzade<DType> kruzade;
	for (DType case_i = 0; case_i != nCase; ++case_i)
	{
		std::cin >> n;
		std::cout << kruzade.process(n) << std::endl;
	}

	return 0;
}