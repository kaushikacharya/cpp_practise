#include <iostream>
#include <vector>

//TBD: re-write this in static function format
template<class T>
void mergeSortFunc(std::vector<T>& vec, std::size_t p, std::size_t r);

template<class T>
void mergeFunc(std::vector<T>& vec, std::size_t p, std::size_t q, std::size_t r);

int main(int argc, char* argv[])
{
	std::size_t test_case = 0;

	switch (test_case)
	{
	case 0:
		{
			static const int arr[] = {3, 6, 1, 8, 4, 9, 10};
			std::vector<int> inputVec(arr, arr + sizeof(arr)/sizeof(arr[0]) );
			mergeSortFunc(inputVec,0,inputVec.size()-1);
		}
		break;
	}

	return 0;
}

template<class T>
void mergeSortFunc(std::vector<T>& vec, std::size_t p, std::size_t r)
{
	if (p < r)
	{
		std::size_t q = (p+r)/2;
		mergeSortFunc(vec,p,q);
		mergeSortFunc(vec,q+1,r);
		mergeFunc(vec,p,q,r);
	}
}

template<class T>
void mergeFunc(std::vector<T>& vec, std::size_t p, std::size_t q, std::size_t r)
{
	std::size_t i = p;
	std::size_t j = q+1;

	std::vector<T> sortedVec;
	sortedVec.reserve(r-p+1);

	while ((i <= q) && (j <= r))
	{
		if (vec[j] < vec[i])
		{
			sortedVec.push_back(vec[j]);
			++j;
		}
		else
		{
			sortedVec.push_back(vec[i]);
			++i;
		}
	}

	if (q < i)
	{
		//push rest of the elements vec[j...r] into sortedVec
		while (j <= r)
		{
			sortedVec.push_back(vec[j]);
			++j;
		}
	}
	else if (r < j)
	{
		//push rest of the elements vec[i...q] into sortedVec
		while (i <= q)
		{
			sortedVec.push_back(vec[i]);
			++i;
		}
	}

	for (std::size_t k = 0; k != (r-p+1); ++k)
	{
		vec[p+k] = sortedVec[k];
	}
}