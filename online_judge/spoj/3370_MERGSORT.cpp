// http://www.spoj.com/problems/MERGSORT/
#include <cstdio>
#include <vector>
#include <algorithm>

#define READ_FROM_FILE 0
#define N 100000
typedef unsigned long CType;

template<typename T>
class MergeSort
{
public:
	MergeSort(CType size, std::vector<T> vec);
	~MergeSort();
public:
	void mergeSort(CType posBegin, CType posEnd);
	void merge(CType posBegin, CType posMid, CType posEnd);
	void output();
private:
	CType size_;
	std::vector<T> vec_;
};
//---
template<typename T>
MergeSort<T>::MergeSort(CType size, std::vector<T> vec)
: size_(size)
, vec_(vec)
{}

template<typename T>
MergeSort<T>::~MergeSort()
{}

template<typename T>
void MergeSort<T>::mergeSort(CType posBegin, CType posEnd)
{
	if (posBegin == posEnd)
	{
		return;
	}
	if ((posEnd - posBegin) == 1)
	{
		if (vec_[posEnd] < vec_[posBegin])
		{
			std::swap(vec_[posBegin],vec_[posEnd]);
		}
		return;
	}

	CType posMid = (posBegin + posEnd)/2;
	mergeSort(posBegin, posMid);
	mergeSort(posMid+1,posEnd);
	merge(posBegin,posMid,posEnd);
}

template<typename T>
void MergeSort<T>::merge(CType posBegin, CType posMid, CType posEnd)
{
	//merge vec[posBegin...posMid] and vec[(posMid+1)...posEnd]
	std::vector<T> tempVec;
	tempVec.reserve(posEnd-posBegin+1);

	CType i = posBegin;
	CType j = posMid+1;

	while ((i <= posMid) && (j <= posEnd))
	{
		if (vec_[j] < vec_[i])
		{
			tempVec.push_back(vec_[j]);
			++j;
		}
		else
		{
			tempVec.push_back(vec_[i]);
			++i;
		}
	}
	while (i <= posMid)
	{
		tempVec.push_back(vec_[i]);
		++i;
	}
	while (j <= posEnd)
	{
		tempVec.push_back(vec_[j]);
		++j;
	}

	i = posBegin;
	while (i <= posEnd)
	{
		vec_[i] = tempVec[i-posBegin];
		++i;
	}
}

template<typename T>
void MergeSort<T>::output()
{
	printf("%d",vec_[0]);
	for (typename std::vector<T>::iterator it = vec_.begin()+1; it != vec_.end(); ++it)
	{
		printf(" %d",(*it));
	}
	printf("\n");
}
//---
int main(int argc, char* argv[])
{
	std::vector<int> vec;
	int num;
	CType count = 0;
	vec.reserve(N);

	if (READ_FROM_FILE)
	{
		FILE* pFile = fopen("d:/cpp_practise/online_judge/spoj/3370_MERGSORT_input.txt","r");
		while (fscanf(pFile,"%d",&num) != EOF)
		{
			++count;
			vec.push_back(num);
		}
	} 
	else
	{
		while (scanf("%d",&num) != EOF)
		{
			++count;
			vec.push_back(num);
		}
	}

	vec.resize(count);
	MergeSort<int> mSort(count,vec);
	mSort.mergeSort(0,count-1);
	mSort.output();

	return 0;
}