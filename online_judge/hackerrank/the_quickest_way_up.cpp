// https://www.hackerrank.com/challenges/the-quickest-way-up
#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <queue>
#include <bitset>
#include <string>
#include <cstdlib> //atoi
#include <limits>

#define MAX_SQUARE 100
#define READ_FROM_FILE 0

template<typename T>
class SnakeLadder
{
public:
	SnakeLadder();
	~SnakeLadder();
public:
	void read_input(std::fstream& pFile);
	void create_graph();
	T compute_shortest_path(T src, T tgt);
private:
	std::vector<T> vecJump_;
	std::vector<std::set<T> > vecAdjacencyList_;
	std::vector<T> vecShortestPathLength_;
	std::bitset<MAX_SQUARE> vecVisited_;
};
//---
template<typename T>
SnakeLadder<T>::SnakeLadder()
{
	vecVisited_.reset();
	vecJump_.reserve(MAX_SQUARE);
	vecShortestPathLength_.reserve(MAX_SQUARE);
	vecAdjacencyList_.reserve(MAX_SQUARE);

	for (T sqr_i = 0; sqr_i != MAX_SQUARE; ++sqr_i)
	{
		vecJump_.push_back(sqr_i);
		vecShortestPathLength_.push_back(std::numeric_limits<T>::max());
		vecAdjacencyList_.push_back(std::set<T>());
	}
}
template<typename T>
SnakeLadder<T>::~SnakeLadder()
{}
template<typename T>
void SnakeLadder<T>::read_input(std::fstream& pFile)
{
	std::string strLine;
	//first line: number of ladders, snakes
	if (READ_FROM_FILE)
	{
		std::getline(pFile, strLine);
	}
	else
	{
		std::getline(std::cin, strLine);
	}
	
	std::string delim = " ,";
	std::size_t posLeft = 0;
	std::size_t posRight;
	T count = 0;
	T nLadder, nSnake;

	while (true)
	{
		posRight = strLine.find_first_of(delim,posLeft);
		std::string token = strLine.substr(posLeft,posRight-posLeft);
		if (count == 0)
		{
			nLadder = atoi(token.c_str());
			++count;
		} 
		else
		{
			nSnake = atoi(token.c_str());
		}
		if (posRight == std::string::npos)
		{
			break;
		}
		posLeft = posRight+1;
	}

	//std::size_t pos = 0;
	/*
	while ((pos = strLine.find(delim)) != std::string::npos)
	{
		token = strLine.substr(0,pos);
		strLine.erase(0,pos+delim.length());
	}
	*/

	if (READ_FROM_FILE)
	{
		std::getline(pFile, strLine);
	} 
	else
	{
		std::getline(std::cin, strLine);
	}
	
	T num1, num2;
	count = 0;
	posLeft = 0;
	
	while (true)
	{
		posRight = strLine.find_first_of(delim,posLeft);
		std::string token = strLine.substr(posLeft,posRight-posLeft);
		if (count%2 == 0)
		{
			num1 = atoi(token.c_str());
		} 
		else
		{
			num2 = atoi(token.c_str());
			vecJump_[num1-1] = num2-1;
		}
		++count;
		if (posRight == std::string::npos)
		{
			break;
		}
		posLeft = posRight+1;
	}

	if (READ_FROM_FILE)
	{
		std::getline(pFile, strLine);
	} 
	else
	{
		std::getline(std::cin, strLine);
	}
	count = 0;
	posLeft = 0;

	while (true)
	{
		posRight = strLine.find_first_of(delim,posLeft);
		std::string token = strLine.substr(posLeft,posRight-posLeft);
		if (count%2 == 0)
		{
			num1 = atoi(token.c_str());
		} 
		else
		{
			num2 = atoi(token.c_str());
			vecJump_[num1-1] = num2-1;
		}
		++count;
		if (posRight == std::string::npos)
		{
			break;
		}
		posLeft = posRight+1;
	}

	int gh = 0;
}
template<typename T>
void SnakeLadder<T>::create_graph()
{
	for (T sqr_i = 0; sqr_i != MAX_SQUARE; ++sqr_i)
	{
		for (T jump_i = 1; jump_i != 7; ++jump_i)
		{
			T sqrJump = sqr_i+jump_i;
			
			if (sqrJump < MAX_SQUARE)
			{
				vecAdjacencyList_[sqr_i].insert(vecJump_[sqrJump]);
			} 
			else
			{
				break;
			}
		}
	}
}
template<typename T>
T SnakeLadder<T>::compute_shortest_path(T src, T tgt)
{
	//BFS traversal
	std::queue<T> queueSqr;
	queueSqr.push(src);
	//vecVisited_[src] = true;
	vecShortestPathLength_[src] = 0;

	while (!queueSqr.empty())
	{
		T frontElem = queueSqr.front();
		queueSqr.pop();
		
		if (vecVisited_[frontElem])
		{
			continue;
		}
		vecVisited_[frontElem] = true;
		if (frontElem == tgt)
		{
			break;
		}

		//set frontElem as visited and put its adjacent vertices into the queue
		for (typename std::set<T>::iterator adjIt = vecAdjacencyList_[frontElem].begin(); adjIt != vecAdjacencyList_[frontElem].end(); ++adjIt)
		{
			T adjElem = (*adjIt);
			if (!vecVisited_[adjElem])
			{
				T shortestPathLength = vecShortestPathLength_[frontElem] + 1;
				if (shortestPathLength < vecShortestPathLength_[adjElem])
				{
					vecShortestPathLength_[adjElem] = shortestPathLength;
				}
				queueSqr.push(adjElem);
			}
		}
	}

	return vecShortestPathLength_[tgt];
}
//---
int main(int argc, char* argv[])
{
	std::string strLine;
	unsigned int nTestCase;
	std::fstream pFile;

	if (READ_FROM_FILE)
	{
		std::string file_name = "D:/cpp_practise/online_judge/hackerrank/the_quickest_way_up_input.txt";
		pFile.open(file_name.c_str());
		std::getline(pFile,strLine);
	}
	else
	{
		std::getline(std::cin,strLine);
	}
	
	nTestCase = atoi(strLine.c_str());
	//std::cin >> nTestCase;

	for (unsigned int case_i = 0; case_i != nTestCase; ++case_i)
	{
		SnakeLadder<unsigned int> snakeLadder;
		snakeLadder.read_input(pFile);
		snakeLadder.create_graph();
		std::cout << snakeLadder.compute_shortest_path(0,MAX_SQUARE-1) << std::endl;
	}

	return 0;
}

/*
http://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
*/