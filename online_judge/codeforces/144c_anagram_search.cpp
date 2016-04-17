// http://codeforces.com/problemset/problem/144/C
#include <cstdio>
#include <vector>
#include <cstring>

#define READ_FROM_FILE 0
#define MAX_LEN 100000
#define CHAR_SIZE 26

template<typename T>
class Anagram
{
public:
	Anagram(std::string strS, std::string strP);
	~Anagram();
public:
	void process();
	T countGoodSubstr();
private:
	std::string strS_;
	std::string strP_;
	std::vector<T> vecCountStrP_;
	T countGoodSubstr_;
};
//---
template<typename T>
Anagram<T>::Anagram(std::string strS, std::string strP)
: strS_(strS)
, strP_(strP)
{
	vecCountStrP_.reserve(CHAR_SIZE);
	for (unsigned int i = 0; i != CHAR_SIZE; ++i)
	{
		vecCountStrP_.push_back(0);
	}
	T j = 0;
	while (j != strP_.size())
	{
		unsigned int pos = strP_[j] - 'a';
		++vecCountStrP_[pos];
		++j;
	}
	countGoodSubstr_ = 0;
}
template<typename T>
Anagram<T>::~Anagram()
{}
template<typename T>
void Anagram<T>::process()
{
	if (strS_.size() < strP_.size())
	{
		return;
	}

	std::vector<T> vecCountStr;
	vecCountStr.reserve(CHAR_SIZE);
	for (unsigned int i = 0; i != CHAR_SIZE; ++i)
	{
		vecCountStr.push_back(0);
	}

	T posLeft = 0;
	T posRight = 0;
	T posBeginUpperLimit = strS_.size() - strP_.size() + 1;

	while ((posLeft < posBeginUpperLimit) && (posRight < strS_.size()))
	{
		char ch = strS_[posRight];
		bool flagShiftLeft = false;
		
		if (ch != '?')
		{
			unsigned int posVecCount = ch - 'a';
			++vecCountStr[posVecCount];

			if (vecCountStrP_[posVecCount] < vecCountStr[posVecCount])
			{
				flagShiftLeft = true;
				while (true)
				{
					char curChar = strS_[posLeft];
					if (curChar != '?')
					{
						--vecCountStr[strS_[posLeft] - 'a'];
					}
					++posLeft;
					
					if (curChar == ch)
					{
						break;
					}
				}
				/*
				if (posRight < posLeft)
				{
					posRight = posLeft;
				}
				*/
			}
		}

		if (!flagShiftLeft)
		{
			//check if we have got a substring [posLeft,posRight] same as strP_ size
			if ((posRight - posLeft + 1) == strP_.size())
			{
				++countGoodSubstr_;
				//Now shift posLeft a single value
				char curChar = strS_[posLeft];
				if (curChar != '?')
				{
					--vecCountStr[strS_[posLeft] - 'a'];
				}
				++posLeft;
			}
		}

		++posRight;
	}
}
template<typename T>
T Anagram<T>::countGoodSubstr()
{
	return countGoodSubstr_;
}
//---
int main(int argc, char* argv[])
{
	char* strS = new char[MAX_LEN+2];
	char* strP = new char[MAX_LEN+2];

	if (READ_FROM_FILE)
	{
		FILE* pFile = fopen("d:/cpp_practise/online_judge/codeforces/144c_anagram_search_input.txt","r");
		fgets(strS,MAX_LEN+2,pFile);
		fgets(strP,MAX_LEN+2,pFile);
		strS = strtok(strS,"\n");
		strP = strtok(strP,"\n");
	} 
	else
	{
		gets(strS);
		gets(strP);
	}

	Anagram<unsigned long> anagram(strS,strP);
	anagram.process();
	printf("%lu\n",anagram.countGoodSubstr());

	return 0;
}