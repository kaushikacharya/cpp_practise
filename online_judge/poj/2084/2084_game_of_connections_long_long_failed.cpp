// http://poj.org/problem?id=2084
#include <cstdio>
#include <vector>
#include <limits>
#include <ctime>

template<typename T>
class Game
{
public:
	Game(T n);
	~Game();
public:
	T connections(T num1, T num2);
private:
	T n_;
	std::vector<T> vecConnections_;
};

template<typename T>
Game<T>::Game(T n)
: n_(n)
{
	vecConnections_.reserve(n);
	//initialize
	for (T i = 0; i < n; ++i)
	{
		vecConnections_.push_back(0);
	}
}

template<typename T>
Game<T>::~Game()
{
}

template<typename T>
T Game<T>::connections(T num1, T num2)
{
	if (num2 - num1 <= 1)
	{
		return 1;
	}
	if (vecConnections_[num2-num1] > 0)
	{
		return vecConnections_[num2-num1];
	}

	T val = 0;
	T numMid = num1+1;

	while (numMid <= num2)
	{
		T val1 = 1;
		if (num1+1 < numMid)
		{
			val1 = connections(num1+1,numMid-1);
		}

		T val2 = 1;
		if (numMid < num2)
		{
			val2 = connections(numMid+1,num2);
		}

		val += val1*val2;

		numMid += 2;
	}

	if (vecConnections_[num2-num1] == 0)
	{
		vecConnections_[num2-num1] = val;
	}
	return val;
}

void test_cases()
{
	unsigned long long max_limit = std::numeric_limits<unsigned long long>::max();
	for (char i = 1; i < 101; ++i)
	{
		clock_t t = clock();
		Game<unsigned long long> game(2*i);
		unsigned long long connections = game.connections(1,2*i);
		t = clock() - t;
		if (max_limit/2 < connections)
		{
			printf("exceeded\n");
		}
		// http://stackoverflow.com/questions/38561/what-is-the-argument-for-printf-that-formats-a-long
		printf("i = %d :: connections: %llu :: time(clocks):%d  time(in sec): %f\n",i,connections,t,((float)t)/CLOCKS_PER_SEC);
	}
}

int main(int argc, char* argv[])
{
	bool test_flag = true;
	printf("max: %llu\n",std::numeric_limits<unsigned long long>::max());

	if (test_flag)
	{
		test_cases();
	}
	else
	{
		char ch;
		while (scanf("%d",&ch) != EOF)
		{
			if (ch == -1)
			{
				break;
			}
			else
			{
				Game<unsigned long long> game(2*ch);
				printf("%llu\n",game.connections(1,2*ch));
			}
		}
	}

	return 0;
}

/*
http://stackoverflow.com/questions/12102621/can-i-make-my-own-custom-data-type-larger-than-the-ones-in-c
Mark Garcia's answer

http://online-judge.uva.es/board/viewtopic.php?f=14&t=50671&p=127261&hilit=bigger+than+long+long#p127261
suggests using arrays

http://stackoverflow.com/questions/269268/how-to-implement-big-int-in-c
orcmid suggests "The Art of Computer Programming" chapter 4

http://stackoverflow.com/questions/5381882/types-bigger-than-long-long-in-c
http://stackoverflow.com/questions/589575/size-of-int-long-etc

http://mahmoud.devgator.com/?page=programming&single=1&post=125&like=0
Addition and Multiplication implemented

Libraries:
https://mattmccutchen.net/bigint/index.html
http://gmplib.org/
*/