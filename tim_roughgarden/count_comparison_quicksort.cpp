#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <vector>
#include "..\utils\Version.hpp"

template<typename T>
void textReader(const char* textFile, std::vector<T>& vec);

template<typename T>
int choosePivot0(std::vector<T>& A, int p, int r);

template<typename T>
int choosePivot1(std::vector<T>& A, int p, int r);

template<typename T>
int choosePivot2(std::vector<T>& A, int p, int r);

template<typename T>
void quickSort(std::vector<T>& vec, int p, int r);

template<typename T>
int partition(std::vector<T>& vec, int p, int r);

static std::size_t count_comparison=0;

int main(int argc, char* argv[])
{
	std::size_t test_case = 1;

	switch (test_case)
	{
	case 0:
		{
			int arr[] = {2,8,7,1,3,5,6,4};
			std::vector<int> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));
			quickSort(vec,0,vec.size()-1);
			int gh = 0;
		}
		break;
	case 1:
		{
			std::vector<int> inputVec;
			inputVec.reserve(100000);
			textReader("D:/cpp_practise/test_cases/QuickSort.txt",inputVec);
            quickSort(inputVec,0,inputVec.size()-1);
			int gh = 0;
		}
		break;
	}

	return 0;
}

template<typename T>
void textReader(const char* textFile, std::vector<T>& vec)
{
	std::ifstream textFileStream;
	textFileStream.open(textFile);
	assert(textFileStream.is_open() && "invalid input text file");

	std::size_t countLine = 0;
	while (!textFileStream.eof())
	{
		std::string line;
		std::getline(textFileStream,line);
		if (!line.empty())
		{
			//Note: atoi converts empty string to 0
			vec.push_back(std::atoi(line.c_str()));
		}
		++countLine;
	}

	textFileStream.close();
}

template<typename T>
int choosePivot0(std::vector<T>& A, int p, int r)
{
	return p;
}

template<typename T>
int choosePivot1(std::vector<T>& A, int p, int r)
{
    return r;
}

template<typename T>
int choosePivot2(std::vector<T>& A, int p, int r)
{
	int q = (r+p)/2;

	if (A[r] < A[p])
	{
		if (A[q] < A[r])
		{
			return r;
		}
		else if (A[p] < A[q])
		{
			return p;
		}
		else
		{
			return q;
		}
	}
	else
	{
		//A[p] <= A[r]
		if (A[q] < A[p])
		{
			return p;
		}
		else if (A[r] < A[q])
		{
			return r;
		}
		else
		{
			return q;
		}
	}
}

template<typename T>
void quickSort(std::vector<T>& vec, int p, int r)
{
    if (p < r)
    {
        int q = partition(vec,p,r);
        quickSort(vec,p,q-1);
        quickSort(vec,q+1,r);
    }
}

template<typename T>
int partition(std::vector<T>& A, int p, int r)
{
    count_comparison += r - p;
    
    int pivot_index = choosePivot2(A,p,r);
	if (pivot_index != p)
	{
		std::swap(A[p],A[pivot_index]);
	}
	T x = A[p]; //pivot element
	//This is RoughGarden's methos i.e. put the pivot element as the 1st element of the 
	// sub-array A[p...r]. This ensures the code logic remains same whatsoever is chosen as
	// pivot element.
	int i = p;
    int j = p+1;

    while (j <= r)
    {
        if (A[p] < A[j])
        {
        }
        else
        {
			++i;
            std::swap(A[i],A[j]);
        }

        ++j;
    }

	std::swap(A[i],A[p]);
    return i;
}