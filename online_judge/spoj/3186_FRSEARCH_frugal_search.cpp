//http://www.spoj.com/problems/FRSEARCH/
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <unordered_set>

#define READ_FROM_FILE 0
#define MAX_WORD_SIZE 20
#define MAX_QUERY_SIZE 79
typedef unsigned int DType;

class Frugal
{
public:
	Frugal();
	~Frugal();
public:
	void add_word(std::string word);
	void lex_sort();
	void create_unorder_set();
	void split_terms(char* query, std::vector<std::string>& vecTerm);
	DType evaluate_term(const std::string term);
	void evaluate_query(const std::vector<std::string>& vecTerm);
private:
	std::vector<std::string> vecWord_;
	typedef std::tr1::unordered_set<char> CharUnorderedSet;
	typedef std::vector<CharUnorderedSet> VecCharUnorderedSet;
	VecCharUnorderedSet vecCharUnOrderSet_;
};
//---
Frugal::Frugal()
{}
Frugal::~Frugal()
{}
void Frugal::add_word(std::string word)
{
	vecWord_.push_back(word);
}
void Frugal::lex_sort()
{
	std::sort(vecWord_.begin(),vecWord_.end());
}
void Frugal::create_unorder_set()
{
	vecCharUnOrderSet_.reserve(vecWord_.size());
	for(unsigned int word_i=0; word_i != vecWord_.size(); ++word_i)
	{
		unsigned int i = 0;
		CharUnorderedSet charUnorderSet;
		while (vecWord_[word_i][i] != '\0')
		{
			charUnorderSet.insert(vecWord_[word_i][i]);
			++i;
		}
		vecCharUnOrderSet_.push_back(charUnorderSet);
	}
}
void Frugal::split_terms(char* query, std::vector<std::string>& vecTerm)
{
	char* pch;
	pch = strtok(query,"|");
	while (pch != NULL)
	{
		vecTerm.push_back(pch);
		pch = strtok(NULL,"|");
	}
}
DType Frugal::evaluate_term(const std::string term)
{
	std::vector<char> vecNeutralChar;
	std::vector<char> vecPosChar;
	std::vector<char> vecNegChar;
	for (unsigned int i=0; i != term.size(); ++i)
	{
		if ((term[i] != '+') && (term[i] != '-'))
		{
			if (i == 0)
			{
				vecNeutralChar.push_back(term[i]);
			}
			else if (term[i-1] == '+')
			{
				vecPosChar.push_back(term[i]);
			}
			else if (term[i-1] == '-')
			{
				vecNegChar.push_back(term[i]);
			}
			else
			{
				vecNeutralChar.push_back(term[i]);
			}
		}
	}
	DType word_i;
	for (word_i = 0; word_i != vecWord_.size(); ++word_i)
	{
		bool flag_match = true;
		unsigned int char_i;
		for (char_i = 0; char_i != vecPosChar.size(); ++char_i)
		{
			CharUnorderedSet::iterator it = vecCharUnOrderSet_[word_i].find(vecPosChar[char_i]);
			if (it == vecCharUnOrderSet_[word_i].end())
			{
				flag_match = false;
				break;
			}
		}
		if (!flag_match)
		{
			continue;
		}
		for (char_i = 0; char_i != vecNegChar.size(); ++char_i)
		{
			CharUnorderedSet::iterator it = vecCharUnOrderSet_[word_i].find(vecNegChar[char_i]);
			if (it != vecCharUnOrderSet_[word_i].end())
			{
				flag_match = false;
				break;
			}
		}
		if (!flag_match)
		{
			continue;
		}
		flag_match = false;
		for (char_i = 0; char_i != vecNeutralChar.size(); ++char_i)
		{
			CharUnorderedSet::iterator it = vecCharUnOrderSet_[word_i].find(vecNeutralChar[char_i]);
			if (it != vecCharUnOrderSet_[word_i].end())
			{
				flag_match = true;
				break;
			}
		}
		if (flag_match)
		{
			break;
		}
	}
	return word_i;
}
void Frugal::evaluate_query(const std::vector<std::string>& vecTerm)
{
	DType word_i;
	for (std::vector<std::string>::const_iterator termIt = vecTerm.begin(); termIt != vecTerm.end(); ++termIt)
	{
		word_i = evaluate_term((*termIt));
		if (word_i < vecWord_.size())
		{
			printf("%s\n",vecWord_[word_i].c_str());
			return;
		}
	}
	printf("NONE\n");
}
//---
void read_and_process()
{
	FILE* pFile = 0;
	if (READ_FROM_FILE)
	{
		pFile = fopen("D:/cpp_practise/online_judge/spoj/3186_FRSEARCH_frugal_search_input.txt","r");
	} 

	char* wordStr = new char[MAX_WORD_SIZE+2];
	char* queryStr = new char[MAX_QUERY_SIZE+2];
	bool flagInputEnd = false;
	
	while (!flagInputEnd)
	{
		Frugal frugal;
		while(!flagInputEnd)
		{
			if (READ_FROM_FILE)
			{
				fgets(wordStr,MAX_WORD_SIZE+2,pFile);
				wordStr = strtok(wordStr,"\n");
			} 
			else
			{
				gets(wordStr);
			}

			if (strcmp(wordStr,"*") == 0)
			{
				break;
			}
			else if (strcmp(wordStr,"#") == 0)
			{
				flagInputEnd = true;
			}
			else
			{
				frugal.add_word(wordStr);
			}
		}
		if(!flagInputEnd)
		{
			frugal.lex_sort();
			frugal.create_unorder_set();
		}

		while(!flagInputEnd)
		{
			if (READ_FROM_FILE)
			{
				fgets(queryStr,MAX_QUERY_SIZE+2,pFile);
				queryStr = strtok(queryStr,"\n");
			} 
			else
			{
				gets(queryStr);
			}
			if (strcmp(queryStr,"**") == 0)
			{
				printf("$\n");
				break;
			}
			else
			{
				std::vector<std::string> vecTerm;
				frugal.split_terms(queryStr,vecTerm);
				frugal.evaluate_query(vecTerm);
			}
		}
	}
	delete[] wordStr;
	delete[] queryStr;
}
int main(int argc, char* argv[])
{
	read_and_process();
	return 0;
}
/*
For g++ 4.3.2:
http://stackoverflow.com/questions/9049506/errors-with-unordered-map-in-c
http://stackoverflow.com/questions/4563340/what-are-the-differences-between-g-version-4-0-0-8-and-4-3-2
http://stackoverflow.com/questions/3973659/c-unordered-map-compiling-issue-with-g

#include <tr1/unordered_set>
std::tr1::unordered_set
*/