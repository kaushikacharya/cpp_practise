// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1406
#include <cstdio>
#include <algorithm> // std::swap
#include <limits>

void compute_max_burger(int num1, int num2, int total_time)
{
	if (num2 < num1)
	{
		std::swap(num1,num2);
	}
	// num1 <= num2
	int count_num1 = total_time/num1;
	int count_num2 = 0;
	int beer_time = std::numeric_limits<int>::max();
	int total_burger_count = 0;
	
	while (count_num1 >= 0)
	{
		count_num2 = (total_time - num1*count_num1)/num2;
		int cur_beer_time = total_time - (num1*count_num1 + num2*count_num2);
		int cur_burger_count = count_num1 + count_num2;
		
		if (cur_beer_time == 0)
		{
			beer_time = 0;
			total_burger_count = cur_burger_count;
			break;
		}
		else
		{
			if (cur_beer_time < beer_time)
			{
				beer_time = cur_beer_time;
				total_burger_count = cur_burger_count;
			}
			/*
			if (total_burger_count < cur_burger_count)
			{
				total_burger_count = cur_burger_count;
				beer_time = cur_beer_time;
			} 
			else if (total_burger_count == cur_burger_count)
			{
				if (cur_beer_time < beer_time)
				{
					beer_time = cur_beer_time;
				}
			}
			*/
		}

		--count_num1;
	}

	if (beer_time == 0)
	{
		printf("%d\n",total_burger_count);
	} 
	else
	{
		printf("%d %d\n",total_burger_count,beer_time);
	}
	int gh = 0;
}

int main(int argc, char* argv[])
{
	unsigned int m,n,t;

	while (scanf("%d",&m) != EOF)
	{
		scanf("%d",&n);
		scanf("%d",&t);
		compute_max_burger(m,n,t);
	}

	return 0;
}

/*
http://online-judge.uva.es/board/viewtopic.php?f=23&t=11081&p=96233&hilit=homer+simpson#p96233

http://acm.uva.es/board/viewtopic.php?f=23&t=11081
If Simpson has to drink some beer, then the time of drinking shuld be minimized
*/