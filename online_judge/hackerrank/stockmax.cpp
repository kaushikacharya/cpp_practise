// https://www.hackerrank.com/challenges/stockmax
#include <iostream>
#include <vector>
#include <limits>
#include <fstream>

#define READ_FROM_FILE 1

template<typename N, typename P>
class Stock
{
public:
	Stock(N nDays);
	~Stock();
public:
	void read_input(std::fstream& pFile);
	P process();
	P process_memory_efficient();
private:
	N nDays_;
	std::vector<P> vecPrice_;
};
//---
template<typename N, typename P>
Stock<N,P>::Stock(N nDays)
: nDays_(nDays)
{
	vecPrice_.reserve(nDays_);
}
template<typename N, typename P>
Stock<N,P>::~Stock()
{
}
template<typename N, typename P>
void Stock<N,P>::read_input(std::fstream& pFile)
{
	P price;
	for (N day_i = 0; day_i != nDays_; ++day_i)
	{
		if (READ_FROM_FILE)
		{
			pFile >> price;
		}
		else
		{
			std::cin >> price;
		}
		
		vecPrice_.push_back(price);
	}
}
template<typename N, typename P>
P Stock<N,P>::process()
{
	//solve using Dynamic Programming
	// vecMat[row:0,1,...,N;  col:0,1,...,N-1]
	std::vector<P> vecMat;
	vecMat.reserve((nDays_+1)*nDays_);
	// row: stocks in hand
	// col: days
	for (N i=0; i != nDays_; ++i)
	{
		vecMat.push_back(0);
	}
	for (N i = nDays_; i != nDays_*(nDays_+1); ++i)
	{
		vecMat.push_back(std::numeric_limits<P>::min());
	}

	// vecMat[1,0]
	vecMat[nDays_] = -1*vecPrice_[0];

	for (N j = 1; j != nDays_; ++j)
	{
		N i_max = (j < (nDays_-1))?(j+1):0;
		for (N i = 0; i != (i_max+1); ++i)
		{
			P bestProfit = vecMat[i*nDays_+j];
			P profit;
			if (i > 0)
			{
				profit = vecMat[(i-1)*nDays_+(j-1)] - vecPrice_[j];
				if (bestProfit < profit)
				{
					bestProfit = profit;
				}
			}
			for (N k = i; k != (j+1); ++k)
			{
				profit = vecMat[k*nDays_+(j-1)] + (k-i)*vecPrice_[j];
				if (bestProfit < profit)
				{
					bestProfit = profit;
				}
			}

			vecMat[i*nDays_+j] = bestProfit;
		}
	}

	return vecMat[nDays_-1];
}
template<typename N, typename P>
P Stock<N,P>::process_memory_efficient()
{
	std::vector<P> vecMat;
	vecMat.reserve((nDays_+1)*2);

	for (N i = 0; i != 2; ++i)
	{
		vecMat.push_back(0);
	}
	for (N stk_i = 1; stk_i != (nDays_+1); ++stk_i)
	{
		for (N i = 0; i != 2; ++i)
		{
			vecMat.push_back(std::numeric_limits<P>::min());
		}
	}
	//vecMat[1,0]
	vecMat[2] = -1*vecPrice_[0];
	bool curIndex = false;

	for (N day_i = 1; day_i != nDays_; ++day_i)
	{
		curIndex = !curIndex;
		N stk_i_max = (day_i < (nDays_-1))?(day_i+1):0;

		for (N stk_i = 0; stk_i != (stk_i_max+1); ++stk_i)
		{
			P bestProfit = vecMat[2*stk_i+curIndex];
			P profit;
			
			if (stk_i > 0)
			{
				profit = vecMat[2*(stk_i-1)+(!curIndex)] - vecPrice_[day_i];
				if (bestProfit < profit)
				{
					bestProfit = profit;
				}
			}
			for (N k = stk_i; k != (day_i+1); ++k)
			{
				profit = vecMat[2*k+(!curIndex)] + (k-stk_i)*vecPrice_[day_i];
				if (bestProfit < profit)
				{
					bestProfit = profit;
				}
			}

			vecMat[2*stk_i+curIndex] = bestProfit;
		}
	}

	return vecMat[curIndex];
}
//---
int main(int argc, char* argv[])
{
	unsigned int nCase, N;
	std::fstream pFile;

	if (READ_FROM_FILE)
	{
		pFile.open("D:/cpp_practise/online_judge/hackerrank/stockmax_input_1.txt",std::ios::in);
		pFile >> nCase;
	}
	else
	{
		std::cin >> nCase;
	}

	for (unsigned int case_i = 0; case_i != nCase; ++case_i)
	{
		if (READ_FROM_FILE)
		{
			pFile >> N;
		}
		else
		{
			std::cin >> N;
		}
		
		Stock<unsigned int, long> stock(N);
		stock.read_input(pFile);
		//std::cout << stock.process() << std::endl;
		std::cout << stock.process_memory_efficient() << std::endl;
	}

	if (READ_FROM_FILE)
	{
		pFile.close();
	}

	return 0;
}