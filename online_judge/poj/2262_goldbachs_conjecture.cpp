// http://poj.org/problem?id=2262
// http://stackoverflow.com/questions/1538644/c-determine-if-a-number-is-prime
//     suggestion for "Sieve Of Eratosthenes" by monksy
#include <cstdio>
#include <bitset>
#include <ctime>

#define N 1000000
#define READ_FROM_FILE 0
#define WRITE_INTO_FILE 0

class Sieve
{
public:
	Sieve();
	~Sieve();
public:
	void compute_prime_pair(unsigned int num, unsigned int& p1, unsigned int& p2);
private:
	unsigned int n_; // till here prime numbers have been checked and 
					 // corresponding position in myBitSet_ has been set
	std::bitset<N> myBitSet_; //each bit initialized 0
	//position 0 is for 2 and so on
};

Sieve::Sieve()
{
	myBitSet_.set(); //sets to 1 all the bits
	n_ = 3; // setting this because both 2,3 are prime
}

Sieve::~Sieve()
{
}

void Sieve::compute_prime_pair(unsigned int num, unsigned int& p1, unsigned int& p2)
{
	p1 = 0;
	p2 = 0;
	unsigned int offset = 2;

	if (n_ < num)
	{
		unsigned int p,start;
		//check and populate prime nos in the range[n_+1,num]
		p = 2;
		while (p*p <= num)
		{
			// TBD: keep incrementing p till p^2 is not greater than n
			// start from p^2. But if p^2 < n_, then start from the multiple of p which is just after n_
			start = p*p;
			if (start < n_)
			{
				start = (n_/p)*p;
			}
			while (start <= num)
			{
				myBitSet_[start-offset] = 0;
				start += p;
			}
			// choose the next p (next prime) and keep doing in while loop
			//p += 1;
			while (myBitSet_[++p-offset] == 0)
			{
				//p += 1;
			}
		}

		n_ = num;
	}

	unsigned int lower = 3;
	while (lower <= num/2)
	{
		if (myBitSet_[lower-offset] && myBitSet_[num-lower-offset])
		{
			p1 = lower;
			p2 = num-lower;
			break;
		}
		lower += 2;
	}

}

int main(int argc, char* argv[])
{
	unsigned int num;
	char ch;
	Sieve sieve;
	unsigned int p1,p2;
	FILE* pOutFile;

	if (WRITE_INTO_FILE)
	{
		pOutFile = fopen("D:/cpp_practise/online_judge/poj/2262_goldbachs_conjecture_output.txt","w");
	} 
	else
	{
		pOutFile = 0;
	}
	
	//clock_t total_time = clock();

	while (true)
	{
		scanf("%d",&num);
		if (num == 0)
		{
			break; //End of Input
		}
		scanf("%c",&ch); //reads newline
		sieve.compute_prime_pair(num,p1,p2);
		
		if (p1 == 0)
		{
			if (WRITE_INTO_FILE)
			{
				fprintf(pOutFile,"Goldbach's conjecture is wrong.\n");
			} 
			else
			{
				printf("Goldbach's conjecture is wrong.\n");
			}
		} 
		else
		{
			if (WRITE_INTO_FILE)
			{
				fprintf(pOutFile,"%d = %d + %d\n",num,p1,p2);
			}
			else
			{
				printf("%d = %d + %d\n",num,p1,p2);
			}
		}
	}

	//total_time = clock() - total_time;
	//printf("Total time: clicks: %d :: (in sec): %f\n",total_time,((float)total_time)/CLOCKS_PER_SEC);
	return 0;
}

/*
http://en.wikipedia.org/wiki/Primality_test
original source: http://www.informatik.uni-ulm.de/acm/Locals/1998/
*/