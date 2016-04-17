// http://www.spoj.com/problems/SUMTRIAN/
#include <cstdio>
#include <vector>
#include <algorithm>

#define READ_FROM_FILE 0
typedef unsigned int DType;

template<typename T>
class Triangle
{
public:
	Triangle(T nNum);
	~Triangle();
public:
	void read_input(FILE* pFile);
	T process();
private:
	T nNum_;
	std::vector<std::vector<T> > vecRows_;
};
//---
template<typename T>
Triangle<T>::Triangle(T nNum)
: nNum_(nNum)
{
	vecRows_.reserve(nNum_);
	for (T row_i=0; row_i != nNum_; ++row_i)
	{
		vecRows_.push_back(std::vector<T>());
	}
}
template<typename T>
Triangle<T>::~Triangle()
{}

template<typename T>
void Triangle<T>::read_input(FILE* pFile)
{
	T num;
	for (T row_i=0; row_i != nNum_; ++row_i)
	{
		vecRows_[row_i].reserve(row_i);
		for (T col_i=0; col_i != (row_i+1); ++col_i)
		{
			if (READ_FROM_FILE)
			{
				fscanf(pFile,"%u",&num);
			}
			else
			{
				scanf("%u",&num);
			}
			vecRows_[row_i].push_back(num);
		}
	}
}

template<typename T>
T Triangle<T>::process()
{
	std::vector<T> vecMax, vecPrevMax;
	vecMax.reserve(nNum_);
	vecPrevMax.reserve(nNum_);

	for (T i=0; i != nNum_; ++i)
	{
		vecMax.push_back(0);
		vecPrevMax.push_back(0);
	}
	vecMax[0] = vecRows_[0][0];
	vecPrevMax[0] = vecRows_[0][0];

	for (T row = 1; row != nNum_; ++row)
	{
		for (T col = 0; col != (row+1); ++col)
		{
			if (col == 0)
			{
				vecMax[col] = vecPrevMax[col] + vecRows_[row][col];
			} 
			else
			{
				vecMax[col] = std::max<T>(vecPrevMax[col-1],vecPrevMax[col]) + vecRows_[row][col];
			}
		}
		vecPrevMax.assign(vecMax.begin(),vecMax.end());
	}

	return *(std::max_element(vecMax.begin(),vecMax.end()));
}
//---
int main(int arfc, char* argv[])
{
	DType nCase, nNumber;
	FILE* pFile = 0;

	if (READ_FROM_FILE)
	{
		pFile = fopen("D:/cpp_practise/online_judge/spoj/453_SUMTRIAN_sums_in_triangle_input.txt","r");
		fscanf(pFile,"%u",&nCase);
	}
	else
	{
		scanf("%u",&nCase);
	}

	for (DType case_i = 0; case_i != nCase; ++case_i)
	{
		if (READ_FROM_FILE)
		{
			fscanf(pFile,"%u",&nNumber);
		}
		else
		{
			scanf("%u",&nNumber);
		}

		Triangle<DType> triangle(nNumber);
		triangle.read_input(pFile);
		printf("%u\n",triangle.process());
	}

	return 0;
}