#include <iostream>
#include <vector>

template<typename T>
void quickSort(std::vector<T>& vec, int p, int r);

template<typename T>
int partition(std::vector<T>& vec, int p, int r);

int main(int argc, char* argv[])
{
	std::size_t test_case = 3;

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
			int arr[] = {1,3,4,5,6};
			std::vector<int> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));
			quickSort(vec,0,vec.size()-1);
			int gh = 0;
		}
		break;
	case 2:
		{
			int arr[] = {8,7,6,4};
			std::vector<int> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));
			quickSort(vec,0,vec.size()-1);
			int gh = 0;
		}
		break;
	case 3:
		{
			int arr[] = {8,7,6,4,5};
			std::vector<int> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));
			quickSort(vec,0,vec.size()-1);
			int gh = 0;
		}
		break;
	}

	return 0;
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
	int i = p-1;
	int j = p;
	T x = A[r]; //pivot element

	while (j <= r)
	{
		if (x < A[j])
		{
		}
		else
		{
			++i;
			std::swap(A[i],A[j]);
		}

		++j;
	}

	return i;
}