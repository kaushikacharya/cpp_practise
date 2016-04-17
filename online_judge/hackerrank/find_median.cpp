// https://www.hackerrank.com/challenges/find-median
#include <cstdio>
#include <cstdlib> //rand
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <ctime>

#define READ_FROM_FILE 0

template<typename T1, typename T2>
class Median
{
public:
	Median(T1 count);
	~Median();
public:
	void read_input(FILE* pFile);
	void process();
	T2 median_element();
private:
	T1 partition(T1 beginPos, T1 endPos); // range: [beginPos,endPos) Note brackets
private:
	T1 count_;
	std::vector<T2> vecNum_;
};
//---
template<typename T1, typename T2>
Median<T1,T2>::Median(T1 count)
: count_(count)
{
	vecNum_.reserve(count_);
}
template<typename T1, typename T2>
Median<T1,T2>::~Median()
{}
template<typename T1, typename T2>
void Median<T1,T2>::read_input(FILE* pFile)
{
	T1 i = 0;
	T2 num;

	while (i < count_)
	{
		if (READ_FROM_FILE)
		{
			fscanf(pFile,"%d",&num);
		}
		else
		{
			std::cin >> num;
		}
		
		vecNum_.push_back(num);
		++i;
	}
}
template<typename T1, typename T2>
void Median<T1,T2>::process()
{
	//according to problem constraint, count_ is odd number.
	T1 medianPos = (count_-1)/2;
	T1 beginPos = 0;
	T1 endPos = count_;
	srand(time(NULL));

	while (true)
	{
		T1 partitionPos = partition(beginPos,endPos);
		
		if (partitionPos == medianPos)
		{
			break;
		}
		else if (medianPos < partitionPos)
		{
			endPos = partitionPos;
		}
		else
		{
			beginPos = partitionPos + 1;
		}
	}
}
template<typename T1, typename T2>
T1 Median<T1,T2>::partition(T1 beginPos, T1 endPos)
{
	//range: [beginPos,endPos)
	// first handle the special cases
	if (beginPos == (count_-1)/2)
	{
		//put the min element in the range [beginPos,endPos) in beginPos
		typename std::vector<T2>::iterator minIt = std::min_element(vecNum_.begin()+beginPos, vecNum_.begin()+endPos);
		T1 minPos = std::distance(vecNum_.begin(),minIt);
		std::swap(vecNum_[beginPos],vecNum_[minPos]);
		return beginPos;
	}
	if ((endPos-1) == (count_-1)/2)
	{
		//put the max element in the range [beginPos,endPos) in endPos-1
		typename std::vector<T2>::iterator maxIt = std::max_element(vecNum_.begin()+beginPos, vecNum_.begin()+endPos);
		T1 maxPos = std::distance(vecNum_.begin(),maxIt);
		std::swap(vecNum_[endPos-1],vecNum_[maxPos]);
		return (endPos-1);
	}

	T1 pivotPos = rand()%(endPos-beginPos) + beginPos;
	std::swap(vecNum_[beginPos],vecNum_[pivotPos]);

	T1 i = beginPos;
	T1 j = beginPos+1;

	while (j < endPos)
	{
		if (vecNum_[j] <= vecNum_[beginPos])
		{
			++i;
			if (i < j)
			{
				std::swap(vecNum_[i],vecNum_[j]);
			}
		}
		/*
		// The issue with the following is that the pivot element keeps changing
		if (vecNum_[j] <= vecNum_[i])
		{
			if ((j-i) > 1)
			{
				++i;
			}
			std::swap(vecNum_[i],vecNum_[j]);
		}
		*/
		++j;
	}

	// now put the pivot element in its appropriate position
	std::swap(vecNum_[i],vecNum_[beginPos]);
	//i is the partition position
	return i;
}
template<typename T1, typename T2>
T2 Median<T1,T2>::median_element()
{
	return vecNum_[count_/2];
}
//---
int main()
{
	FILE* pFile = 0;
	unsigned long count;

	if (READ_FROM_FILE)
	{
		pFile = fopen("D:/cpp_practise/online_judge/hackerrank/find_median_input.txt","r");
		assert((pFile != 0) && "file not opened");
		fscanf(pFile,"%lu",&count);
	} 
	else
	{
		std::cin >> count;
	}
	
	Median<unsigned long, int> median(count);
	median.read_input(pFile);
	median.process();
	std::cout << median.median_element();

	return 0;
}

/*
http://discuss.codechef.com/questions/1489/find-median-in-an-unsorted-array-without-sorting-it

http://stackoverflow.com/questions/2596522/c-standard-input-from-file-when-debugging-from-ide
*/