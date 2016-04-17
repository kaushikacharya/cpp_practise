#include "AdjListImpl1.hpp"
#include "GraphImpl1.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>

std::size_t curFinishTime = 0;

template<typename T>
void DFS_Traversal_Loop(ds::Graph<T>& G, std::vector<std::size_t>& labelVec, std::vector<std::size_t>& vecFinishOrder, std::vector<std::size_t>& vecLeader); //vecFinishTime

template<typename T>
void DFS(ds::Graph<T>& G, std::size_t pos_i, std::vector<std::size_t>& vecFinishOrder, std::size_t pos_leader, std::vector<std::size_t>& vecLeader);

void scc_count(std::vector<std::size_t>& vecLeader, std::map<std::size_t,std::size_t>& scc_count_map);

template<typename T>
void textReader(const char* textFile, std::vector<T>& vecVertex, std::vector<std::pair<T,T> >& vecEdge);

void tokenize(std::string& line,std::vector<std::string>& lineSplit);

int main(int argc,char* argv[])
{
	using namespace ds;
	std::size_t test_case = 1;

	switch (test_case)
	{
	case 0:
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

			vecAdjList[0].addElement(5);
			vecAdjList[1].addElement(3);
			vecAdjList[2].addElement(4);
			vecAdjList[1].addElement(4);

			int gh = 0;
		}
		break;
	case 1:
		{
			std::vector<std::size_t> inputVertexVec;
			std::vector<std::pair<std::size_t,std::size_t> > inputEdgeVec;
			std::size_t nVertex = 875714; //875714;
			inputVertexVec.reserve(nVertex);
			inputEdgeVec.reserve(nVertex);
			textReader("E:/cpp_practise/test_cases/SCC.txt",inputVertexVec,inputEdgeVec);
			//get unique elements for vertices
			// http://www.cplusplus.com/reference/algorithm/unique/
			/*
			std::vector<int>::iterator it = std::unique(inputVertexVec.begin(), inputVertexVec.end());
			inputVertexVec.resize(std::distance(inputVertexVec.begin(),it));
			*/
			inputVertexVec.clear();
            inputVertexVec.reserve(nVertex);
			for (std::size_t i = 1; i <= nVertex; ++i)
			{
				inputVertexVec.push_back(i);
			}

			Graph<std::size_t> G(inputVertexVec);
			Graph<std::size_t> Grev(inputVertexVec);

			//now add the edges
			for (std::vector<std::pair<std::size_t,std::size_t> >::iterator it = inputEdgeVec.begin(); it != inputEdgeVec.end(); ++it)
			{
				G.addEdge((*it).first,(*it).second);
				Grev.addEdge((*it).second,(*it).first);
			}

			//step #2: DFS of Grev
			std::vector<std::size_t> labelVec; //used for traversal order in DFS loop
			labelVec.reserve(inputVertexVec.size());
			//instead of finish time for each vertex we store the order of finishing
			// so that we can traverse during 2nd pass in reverse finishing order
			std::vector<std::size_t> vecFinishOrder;
			vecFinishOrder.reserve(inputVertexVec.size());
			std::vector<std::size_t> vecLeader;
			vecLeader.reserve(inputVertexVec.size());

			for (std::size_t i = 0; i < inputVertexVec.size(); ++i)
			{
				labelVec.push_back(inputVertexVec.size()-1-i);
				vecLeader.push_back(inputVertexVec.size()); //dummy value
			}

			DFS_Traversal_Loop(Grev,labelVec,vecFinishOrder,vecLeader);
		
			//step #3: DFS of G in reverse order of vecFinishOrder
			labelVec.clear();
			vecLeader.clear();
			for (std::size_t i = 0; i < vecFinishOrder.size(); ++i)
			{
				labelVec.push_back(vecFinishOrder[vecFinishOrder.size()-1-i]);
				vecLeader.push_back(inputVertexVec.size()); //dummy value
			}
			vecFinishOrder.clear();
			DFS_Traversal_Loop(G,labelVec,vecFinishOrder,vecLeader);

			std::map<std::size_t,std::size_t> scc_count_map;
			scc_count(vecLeader,scc_count_map);
			int gh = 0;
		}
		break;
	}

	return 0;
}

template<typename T>
void DFS_Traversal_Loop(ds::Graph<T>& G, std::vector<std::size_t>& labelVec, std::vector<std::size_t>& vecFinishOrder, std::vector<std::size_t>& vecLeader)
{
    std::cout << G.explored(255079) << std::endl;
	for (std::vector<std::size_t>::iterator it = labelVec.begin(); it != labelVec.end(); ++it)
	{
		std::size_t pos_i = *it;
		if (G.explored(pos_i) == false)
		{
			std::size_t pos_leader = pos_i;
			DFS(G,pos_i,vecFinishOrder,pos_leader,vecLeader);
		}
	}

	int gh = 0;
}

void scc_count(std::vector<std::size_t>& vecLeader, std::map<std::size_t,std::size_t>& scc_count_map)
{
	for (std::vector<std::size_t>::iterator it = vecLeader.begin(); it != vecLeader.end(); ++it)
	{
		std::size_t leader = *it;
		std::map<std::size_t,std::size_t>::iterator mIt = scc_count_map.find(*it);

		if (mIt == scc_count_map.end())
		{
			scc_count_map[leader] = 1;
		}
		else
		{
			++mIt->second;
		}
	}

	//we just want to count the size of top 5 connected components
	std::vector<std::size_t> countVec;

	for (std::map<std::size_t,std::size_t>::iterator mIt = scc_count_map.begin(); mIt != scc_count_map.end(); ++mIt)
	{
		countVec.push_back((*mIt).second);
	}

	std::sort(countVec.begin(),countVec.end(),std::greater<std::size_t>());
	int gh = 0;
}

template<typename T>
void DFS(ds::Graph<T>& G, std::size_t pos_i, std::vector<std::size_t>& vecFinishOrder, std::size_t pos_leader, std::vector<std::size_t>& vecLeader)
{
	G.setExplored(pos_i);
	vecLeader[pos_i] = pos_leader; //set leader
	std::vector<T> adjList = G.adjacencyList(pos_i);
	for (std::vector<T>::iterator it = adjList.begin(); it != adjList.end(); ++it)
	{
        assert((*it > 0) && "gadbad in adjList");
		std::size_t pos_j = *it-1;
		if (G.explored(pos_j) == false)
		{
			DFS(G, pos_j, vecFinishOrder, pos_leader, vecLeader);
		}
	}

	++curFinishTime;
	vecFinishOrder.push_back(pos_i);
	//vecFinishTime[pos_i] = curFinishTime;
	int gh = 0;
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