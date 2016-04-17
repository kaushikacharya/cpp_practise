// http://poj.org/problem?id=1401
// July 04,2013
#include <cstdio>
#include <limits>
#include <ctime>

#define WRITE_INTO_FILE 0

unsigned int zero_count_func(unsigned int n);

unsigned int zero_count_func(unsigned int n)
{
	unsigned int count = 0;

	while (5 <= n)
	{
		n /= 5;
		count += n;
	}

	return count;
}

int main(int argc, char* argv[])
{
	// http://stackoverflow.com/questions/1855459/maximum-value-of-int
	/*
	int imax = std::numeric_limits<int>::max();
	printf("int max: %d\n",imax);
	*/
	unsigned int nCase;
	char ch;
	unsigned int num;
	FILE* pFile;

	if (WRITE_INTO_FILE)
	{
		pFile = fopen("D:/cpp_practise/online_judge/poj/1401_factorial_output.txt","w");
	}
	else
	{
		pFile = 0;
	}

	scanf("%d",&nCase);
	scanf("%c",&ch); // read new line

	clock_t total_time = clock();

	for (unsigned int case_i = 0; case_i < nCase; ++case_i)
	{
		scanf("%d",&num);
		scanf("%c",&ch); // read new line

		if (WRITE_INTO_FILE)
		{
			fprintf(pFile,"%d\n",zero_count_func(num));
		} 
		else
		{
			printf("%d\n",zero_count_func(num));
		}
	}
	total_time = clock() - total_time;
	printf("TOTAL:: clicks: %d :: time(in sec): %f\n",total_time,((float)total_time)/CLOCKS_PER_SEC);

	return 0;
}
/*
http://contest.felk.cvut.cz/00cerc/solved/index.html#factor

Run ID	User	Problem	Result	Memory	Time	Language	Code Length	Submit Time
11732572	kaushik_acharya	1401	Accepted	164K	125MS	C++	1269B	2013-07-04 21:39:10
But in my m/c(Intel Core 2 duo, 2.93 GHz, 3 GB RAM) it shows 2.95 sec
*/