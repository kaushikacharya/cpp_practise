#include "AdjList.hpp"
#include "Graph.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

template<typename T>
void textReader(const char* textFile, std::vector<T>& vecVertex, std::vector<std::pair<T,T> >& vecEdge);

void tokenize(std::string& line,std::vector<std::string>& lineSplit);

int main(int argc,char* argv[])
{
	using namespace ds;
	std::size_t test_case = 2;

	switch (test_case)
	{
	case 0:
		{
			//Testing AdjListNode
			AdjListNode<int> node0 = AdjListNode<int>(1);
			AdjListNode<int> node1 = AdjListNode<int>(9,&node0);
			AdjListNode<int> node2 = AdjListNode<int>(5);
			node2.setNext(&node1);
			int gh = 0;
		}
		break;
	case 1:
		{
			//Testing AdjList
			AdjList<int> adjList;
			AdjListNode<int> node0 = AdjListNode<int>(1);
			adjList.addListNode(&node0);
			AdjListNode<int> node1 = AdjListNode<int>(9);
			adjList.addListNode(&node1);
			AdjListNode<int> node2 = AdjListNode<int>(8);
			adjList.addListNode(node2);
			int gh = 0;
		}
		break;
	case 2:
		{
			//Tesing vector of AdjList
			std::vector<AdjList<int> > vecAdjList;
			vecAdjList.reserve(9);
			//initialize all elements to NULL
			for (std::size_t i = 0; i < 9; ++i)
			{
				AdjList<int> newAdjList;
				vecAdjList.push_back(newAdjList);
			}

			AdjListNode<int> node0 = AdjListNode<int>(5);
			vecAdjList[0].addListNode(&node0);

			AdjListNode<int> node1 = AdjListNode<int>(3);
			vecAdjList[1].addListNode(&node1);

			AdjListNode<int> node2 = AdjListNode<int>(4);
			vecAdjList[1].addListNode(node2);
			vecAdjList[2].addListNode(node2);
			//TBD: facing issues related to node's destructor getting called when node goes out of scope
			int gh = 0;
		}
		break;
	case 3:
		{
			std::vector<int> inputVertexVec;
			std::vector<std::pair<int,int> > inputEdgeVec;
			inputVertexVec.reserve(9);
			inputEdgeVec.reserve(9);
			textReader("D:/cpp_practise/test_cases/SCCCase0.txt",inputVertexVec,inputEdgeVec);
			//get unique elements for vertices
			// http://www.cplusplus.com/reference/algorithm/unique/
			std::vector<int>::iterator it = std::unique(inputVertexVec.begin(), inputVertexVec.end());
			inputVertexVec.resize(std::distance(inputVertexVec.begin(),it));
			
			Graph<int> G(inputVertexVec);
			//now add the edges
			for (std::vector<std::pair<int,int> >::iterator it = inputEdgeVec.begin(); it != inputEdgeVec.end(); ++it)
			{
				G.addEdge((*it).first,(*it).second);
			}
			int gh = 0;
		}
		break;
	}

	return 0;
}

template<typename T>
void textReader(const char* textFile, std::vector<T>& vecVertex, std::vector<std::pair<T,T> >& vecEdge)
{
	std::ifstream textFileStream;
	textFileStream.open(textFile);
	assert(textFileStream.is_open() && "invalid input text file");

	std::size_t countLine = 0;
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
				vecVertex.push_back(std::atoi(lineSplit[0].c_str()));
				//now push the edges
				for (std::vector<std::string>::iterator it = lineSplit.begin()+1; it != lineSplit.end(); ++it)
				{
					vecEdge.push_back(std::make_pair(std::atoi(lineSplit[0].c_str()),std::atoi((*it).c_str())));
				}
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
		start = line.find_first_not_of(' ',end);
		end   = line.find_first_of(' ',start);
		if (start == end)
		{
			break;
		}
		lineSplit.push_back(line.substr(start,(end-start)));
	}
}