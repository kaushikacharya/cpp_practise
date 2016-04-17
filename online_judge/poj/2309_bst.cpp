// http://poj.org/problem?id=2309
#include <cstdio>
#include <cmath>
#include <limits>

void compute_interval(unsigned int num, unsigned int& left_interval, unsigned int& right_interval);

void compute_interval(unsigned int num, unsigned int& left_interval, unsigned int& right_interval)
{
	unsigned int p = (int)(log((double)num)/log(2.0));

	if (pow(2.0,(double)p) == num)
	{
		left_interval = 1;
		right_interval = (int)(pow(2.0,(double)(p+1))) - 1;
	}
	else
	{
		left_interval = (int)(pow(2.0,(double)(p)));
		right_interval = (int)(pow(2.0,(double)(p+1)));
		unsigned int mid = (left_interval + right_interval)/2;

		while (num != mid)
		{
			if (num < mid)
			{
				right_interval = mid;
			}
			else
			{
				left_interval = mid;
			}

			mid = (left_interval + right_interval)/2;
		}

		left_interval += 1;
		right_interval -= 1;
	}
}

int main(int argc, char* argv[])
{
	unsigned int nCase;
	char ch;

	//printf("%d",(int)3.9);
	/*
	unsigned int max_int = std::numeric_limits<int>::max();
	double pw = pow(2.0,31.0);
	if (pow(2.0,31.0) < max_int)
	{
		printf("within max");
	}
	else
	{
		printf("beyond max");
	}
	*/
	scanf("%d",&nCase);
	scanf("%c",&ch); // read new line

	for (unsigned int case_i = 0; case_i < nCase; ++case_i)
	{
		unsigned int num;
		unsigned int min_subtree, max_subtree;
		scanf("%d",&num);
		scanf("%c",&ch);
		compute_interval(num,min_subtree,max_subtree);
		printf("%d %d\n",min_subtree,max_subtree);
		int gh = 0;
	}

	return 0;
}