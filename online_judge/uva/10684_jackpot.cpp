// http://uva.onlinejudge.org/external/106/10684.html
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <cassert>

const bool READ_FROM_FILE = false;

template<typename T>
class Jackpot
{
public:
	Jackpot(T size)
		: size_(size)
	{
		seq_.reserve(size_);
		subSeqMaxVal_.reserve(size_);
	}
public:
	void read_input_sequence(std::ifstream& pFile)
	{
		T elem;
		for (T elem_i = 0; elem_i != size_; ++elem_i)
		{
			if (READ_FROM_FILE)
			{
				pFile >> elem;
			} 
			else
			{
				std::cin >> elem;
			}
			
			seq_.push_back(elem);
			subSeqMaxVal_.push_back(elem); //assigning the self value as default subsequence max value ending at this index
		}
	}

	void compute_max_value_sub_sequence();
	
	T max_sub_sequence_val()
	{
		return maxSubSeqVal_;
	}
	T max_sub_sequence_index()
	{
		return maxSubSeqIndex_;
	}
private:
	T size_;
	std::vector<T> seq_;
	// subsequence related info
	std::vector<T> subSeqMaxVal_; //for each index we store the max value subsequence ending at that index
	T maxSubSeqVal_;
	T maxSubSeqIndex_;
};

template<typename T>
void Jackpot<T>::compute_max_value_sub_sequence()
{
	maxSubSeqIndex_ = 0;
	maxSubSeqVal_ = subSeqMaxVal_[maxSubSeqIndex_];
	
	for (T elem_i = 1; elem_i != size_; ++elem_i)
	{
		if (subSeqMaxVal_[elem_i-1] > 0)
		{
			subSeqMaxVal_[elem_i] = subSeqMaxVal_[elem_i-1] + seq_[elem_i];
		}
		if (maxSubSeqVal_ < subSeqMaxVal_[elem_i])
		{
			maxSubSeqIndex_ = elem_i;
			maxSubSeqVal_ = subSeqMaxVal_[maxSubSeqIndex_];
		}
	}
}

int main(int argc, char* argv[])
{
	typedef long DType;
	DType nElem;
	std::ifstream pFile;

	if (READ_FROM_FILE)
	{
		pFile.open("D:/cpp_practise/online_judge/uva/10684_jackpot_input.txt",std::ios::in);
		assert(pFile.is_open() && "input file failed to open");
	}

	while (true)
	{
		if (READ_FROM_FILE)
		{
			pFile >> nElem;
		} 
		else
		{
			std::cin >> nElem;
		}

		if (nElem == 0)
		{
			break;
		}
		else
		{
			Jackpot<DType> jackpot(nElem);
			jackpot.read_input_sequence(pFile);
			jackpot.compute_max_value_sub_sequence();

			if (jackpot.max_sub_sequence_val() <= 0)
			{
				std::cout << "Losing streak." << std::endl;
			}
			else
			{
				std::cout << "The maximum winning streak is " << jackpot.max_sub_sequence_val() << "." << std::endl;
			}
		}
	}

	if (READ_FROM_FILE)
	{
		pFile.close();
	}

	return 0;
}

/*
This is a max value contiguous subsequence problem.
*/