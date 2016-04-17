#include <iostream>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <string>

template<typename T>
void textReader(const char* textFile, std::vector<T>& vec);

template<typename T>
std::size_t sort_count_inversion(std::vector<T>& vec, std::size_t p, std::size_t r);

template<typename T>
std::size_t sort_count_split_inversion(std::vector<T>& vec, std::size_t p, std::size_t q, std::size_t r);

int main(int argc, char* argv[])
{
	std::size_t test_case = 0;
	std::size_t count_inv;

	switch (test_case)
	{
	case 0:
		{
			std::vector<int> inputVec;
			inputVec.reserve(100000);
			textReader("D:/cpp_practise/test_cases/IntegerArray.txt",inputVec);
			count_inv = sort_count_inversion(inputVec,0,inputVec.size()-1);
			int gh = 0;
		}
		break;
	case 1:
		{
			std::vector<int> inputVec;
			inputVec.reserve(100000);
			textReader("D:/cpp_practise/test_cases/IntegerArray.txt",inputVec);
			count_inv = sort_count_inversion(inputVec,0,9); //considering only the first 10 elements			
		}
		break;
	case 2:
		{
			static const int arr[] = {1, 5, 3, 2, 4, 6};
			std::vector<int> inputVec(arr,arr+sizeof(arr)/sizeof(arr[0]));
			count_inv = sort_count_inversion(inputVec,0,inputVec.size()-1);
			int gh = 0;
		}
		break;
	}

	std::cout << "inversions(count): " << count_inv << std::endl;
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
std::size_t sort_count_inversion(std::vector<T>& vec, std::size_t p, std::size_t r)
{
	std::size_t count_inversion = 0;

	if (p == r)
	{
		return count_inversion;
	}

	std::size_t q = (p+r)/2;
	std::size_t count_inv1 = sort_count_inversion(vec,p,q);
	std::size_t count_inv2 = sort_count_inversion(vec,q+1,r);
	std::size_t count_split_inv = sort_count_split_inversion(vec,p,q,r);

	std::size_t total_inv = count_inv1 + count_inv2 + count_split_inv;
	return total_inv;
}

template<typename T>
std::size_t sort_count_split_inversion(std::vector<T>& vec, std::size_t p, std::size_t q, std::size_t r)
{
	// sorted vector#1: vec[p...q]
	// sorted vector#2: vec[q+1...r]
	std::size_t split_inv_count = 0;
	std::size_t i = p;
	std::size_t j = q+1;
	std::vector<T> mergedVec;
	mergedVec.reserve(r-p+1);

	while ((i<=q) && (j<=r))
	{
		if (vec[j] < vec[i])
		{
			split_inv_count += q+1-i;
			mergedVec.push_back(vec[j]);
			++j;
		}
		else
		{
			mergedVec.push_back(vec[i]);
			++i;
		}
	}

	//cover the half which is not yet fully covered
	if (r < j)
	{
		//insert vec[i....q]
		//vec[i] has already been considered for its contribution to split_inv_count
		//mergedVec.push_back(vec[i]);
		//++i;

		while (i<=q)
		{
			//++split_inv_count;
			mergedVec.push_back(vec[i]);
			++i;
		}
	}
	else
	{
		while (j <= r)
		{
			mergedVec.push_back(vec[j]);
			++j;
		}
	}

	//now replace vec[p...r] with its sorted array
	i = p;
	while (i <= r)
	{
		vec[i] = mergedVec[i-p];
		++i;
	}

	return split_inv_count;
}