#include <algorithm>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/unordered_set.hpp>

template<typename T>
std::size_t compute_count_target(std::vector<T>& inputVec, T tgt_min, T tgt_max);

template<typename T>
void textReader(const char* textFile, std::vector<T>& inputVec);

void tokenize(std::string& line,std::vector<std::string>& lineSplit);

int main(int argc, char* argv[])
{
	//using namespace ds;
	std::size_t test_case = 1;

	switch (test_case)
	{
	case 0:
		{
			std::vector<int> inputVec;
			inputVec.reserve(500000);
			textReader("D:/cpp_practise/test_cases/HashInt.txt",inputVec);
			//sort is for debugging: i.e. see the elements in a sorted order
			//std::sort(inputVec.begin(),inputVec.end());
			
			int tgt_min = 2500;
			int tgt_max = 4000;
			std::size_t count_tgt = compute_count_target(inputVec, tgt_min, tgt_max);
			std::cout << "count of tgt values: " << count_tgt << std::endl;
			int gh = 0;
		}
		break;
	case 1:
		{
			// https://class.coursera.org/algo-003/forum/thread?thread_id=669#post-3181
			std::vector<int> inputVec;
			inputVec.reserve(100);
			textReader("D:/cpp_practise/test_cases/two_sum_variant/twosummedium.txt",inputVec);
			
			int tgt_min = 30;
			int tgt_max = 60;
			std::size_t count_tgt = compute_count_target(inputVec, tgt_min, tgt_max);
			std::cout << "count of tgt values: " << count_tgt << std::endl;
			int gh = 0;
		}
		break;
	}

	return 0;
}

template<typename T>
void textReader(const char* textFile, std::vector<T>& inputVec)
{
	std::ifstream textFileStream;
	textFileStream.open(textFile);
	assert(textFileStream.is_open() && "invalid input text file");

	int countLine = 0;
	while (!textFileStream.eof())
	{
		std::string line;
		std::getline(textFileStream,line);
		if (!line.empty())
		{
			std::vector<std::string> lineSplit;
			tokenize(line,lineSplit);
			if (!lineSplit.empty())
			{
				//Note: atoi converts empty string to 0
				assert((lineSplit.size()==1) && "only 1 int expected");
				inputVec.push_back(std::atoi(lineSplit[0].c_str()));
			}
		}
		++countLine;
	}

	textFileStream.close();
}

//TBD: input paramter: delimiters
void tokenize(std::string& line,std::vector<std::string>& lineSplit)
{
	if (line == "")
	{
		return;
	}
	std::string::size_type start = 0;
	std::string::size_type end = 0;
	while(end < line.npos)
	{
		start = line.find_first_not_of(" ",end);
		end   = line.find_first_of(" ",start);
		if (start == end)
		{
			break;
		}
		lineSplit.push_back(line.substr(start,(end-start)));
	}
}


template<typename T>
std::size_t compute_count_target(std::vector<T>& inputVec, T tgt_min, T tgt_max)
{
	boost::unordered_set<int> hash_table;
	for (std::vector<int>::iterator it = inputVec.begin(); it != inputVec.end(); ++it)
	{
		boost::unordered_set<int>::iterator hIt = hash_table.find(*it);
		if (hIt == hash_table.end())
		{
			hash_table.insert(*it);
		}
	}

	boost::unordered_set<int> hash_tgt;
	for (boost::unordered_set<int>::iterator hIt = hash_table.begin(); hIt != hash_table.end(); ++hIt)
	{
		int elem1 = *hIt;
		//Using the fact that input ints are positive integers
		if (elem1 < tgt_max)
		{
			int tgt = (elem1 < tgt_min) ? tgt_min : (elem1+1);
			while (tgt <= tgt_max)
			{
				//first check if we have already found a combination whose sum is tgt
				boost::unordered_set<int>::iterator tgtIt = hash_tgt.find(tgt);
				if (tgtIt == hash_tgt.end())
				{
					int elem2 = tgt - elem1;
					if (elem1 != elem2)
					{
						boost::unordered_set<int>::iterator hIt2 = hash_table.find(elem2);
						if (hIt2 != hash_table.end())
						{
							//combination found whose sum is tgt
							hash_tgt.insert(tgt);
						}
					}
				}
				++tgt;
			}
		}
	}

	return hash_tgt.size();
}
/* Learnings:
http://stackoverflow.com/questions/133569/hashtable-in-c
mentions usage of boost hash map

http://stackoverflow.com/questions/4422893/boost-unordered-set-tutorial-examples-anything
example usage

http://www.cplusplus.com/reference/unordered_set/unordered_set/
*/