// http://codeforces.com/problemset/problem/5/C
#include <cstdio>
#include <stack>
#include <vector>
#include <limits>

#define READ_FROM_FILE 0
#define MAX_STR_LEN 1000001

template<typename T>
class Sequence
{
public:
	Sequence();
	~Sequence();
public:
	void readInput(FILE* pFile);
	void process();
	void print_output();
private:
	void update_seq_list(T pos_opening_bracket, T pos_closing_bracket);
private:
	struct LongestRegular
	{
		T length;
		T count;
	};

	struct BracketPos
	{
		char bracket;
		T pos;
	};

	struct RangeSeq
	{
		T openPos;
		T closedPos;
	};
private:
	char* str_;
	//LongestRegular longest_regular_seq_;
	std::vector<RangeSeq> vecRangeSeq_;
};

template<typename T>
Sequence<T>::Sequence()
{
	str_ = new char[MAX_STR_LEN];
	/*
	longest_regular_seq_.length = 0;
	longest_regular_seq_.count = 1;
	*/
}

template<typename T>
Sequence<T>::~Sequence()
{
	delete[] str_;
}

template<typename T>
void Sequence<T>::readInput(FILE* pFile)
{
	if (READ_FROM_FILE)
	{
		fgets(str_,MAX_STR_LEN+1,pFile);
		str_ = strtok(str_,"\n");
	} 
	else
	{
		gets(str_);
	}
}

template<typename T>
void Sequence<T>::process()
{
	std::stack<BracketPos> stackBracketPos;
	/*
	T pos_prev_opening_bracket = 0;
	T pos_prev_closing_bracket = 0;
	*/
	T i = 0;

	while (str_[i] != '\0')
	{
		char ch = str_[i];
		bool flag_regular_seq_found = false;
		
		if (!stackBracketPos.empty() && (ch == ')'))
		{
			BracketPos topBracketPos = stackBracketPos.top();
			
			if (topBracketPos.bracket == '(')
			{
				T pos_opening_bracket = topBracketPos.pos;
				T pos_closing_bracket = i;

				/*
				if (pos_prev_opening_bracket < pos_prev_closing_bracket)
				{
					// Atleast one regular sequence has been identified before the current one.
					if (pos_opening_bracket == (pos_prev_closing_bracket + 1))
					{
						pos_opening_bracket = pos_prev_opening_bracket;
					}
				}
				T length_regular_seq = i - pos_opening_bracket + 1;

				if (longest_regular_seq_.length == length_regular_seq)
				{
					++longest_regular_seq_.count;
				}
				else if (longest_regular_seq_.length < length_regular_seq)
				{
					longest_regular_seq_.length = length_regular_seq;
					longest_regular_seq_.count = 1;
				}
			
				pos_prev_opening_bracket = pos_opening_bracket;
				pos_prev_closing_bracket = i;
				*/

				flag_regular_seq_found = true;
				stackBracketPos.pop();
				update_seq_list(pos_opening_bracket,pos_closing_bracket);
			}
		}

		if (!flag_regular_seq_found)
		{
			BracketPos elem;
			elem.bracket = ch;
			elem.pos = i;
			stackBracketPos.push(elem);
		}

		++i;
	}
}

template<typename T>
void Sequence<T>::update_seq_list(T pos_opening_bracket, T pos_closing_bracket)
{
	RangeSeq curRangeSeq;
	curRangeSeq.openPos = pos_opening_bracket;
	curRangeSeq.closedPos = pos_closing_bracket;

	if (vecRangeSeq_.empty())
	{
		vecRangeSeq_.push_back(curRangeSeq);
	}
	else
	{
		while (!vecRangeSeq_.empty())
		{
			RangeSeq prevRangeSeq = vecRangeSeq_.back();

			if (curRangeSeq.openPos < (prevRangeSeq.closedPos+2))
			{
				if (prevRangeSeq.openPos < curRangeSeq.openPos)
				{
					curRangeSeq.openPos = prevRangeSeq.openPos;
				}
				vecRangeSeq_.pop_back();
			}
			else
			{
				break;
			}
		}

		vecRangeSeq_.push_back(curRangeSeq);
	}
}

template<typename T>
void Sequence<T>::print_output()
{
	LongestRegular longest_regular_seq;
	longest_regular_seq.length = 0;
	longest_regular_seq.count = 1;
	T i = 0;

	while (i < vecRangeSeq_.size())
	{
		T curSeqLength = vecRangeSeq_[i].closedPos - vecRangeSeq_[i].openPos + 1;
		
		if (longest_regular_seq.length < curSeqLength)
		{
			longest_regular_seq.length = curSeqLength;
			longest_regular_seq.count = 1;
		}
		else if (longest_regular_seq.length == curSeqLength)
		{
			++longest_regular_seq.count;
		}

		++i;
	}

	printf("%u %u\n",longest_regular_seq.length,longest_regular_seq.count);
}

int main(int argc, char* argv[])
{
	FILE* pFile = 0;
	if (READ_FROM_FILE)
	{
		pFile = fopen("d:/cpp_practise/online_judge/codeforces/5c_longest_regular_bracket_sequence_input.txt","r");
	}

	//printf("max(unsigned int): %u\n",std::numeric_limits<unsigned int>::max());
	Sequence<unsigned int> seq;
	seq.readInput(pFile);
	seq.process();
	seq.print_output();

	return 0;
}