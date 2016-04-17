#include "GraphImpl3.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>

int curFinishTime = 0;

template<typename T>
void DFS_Traversal_Loop(ds::Graph<T>& G, std::vector<int>& labelVec, std::vector<int>& vecFinishOrder, std::vector<int>& vecLeader); //vecFinishTime

template<typename T>
void DFS(ds::Graph<T>& G, int pos_i, std::vector<int>& vecFinishOrder, int pos_leader, std::vector<int>& vecLeader);

void scc_count(std::vector<int>& vecLeader, std::map<int,int>& scc_count_map);

template<typename T>
void textReader(const char* textFile, ds::Graph<T>& G, ds::Graph<T>& Grev);

void tokenize(std::string& line,std::vector<std::string>& lineSplit);

int main(int argc, char* argv[])
{
	using namespace ds;
	std::size_t test_case = 0;

	switch(test_case)
	{
	case 0:
		{
			Graph<int> G;
			Graph<int> Grev;

			int nVertex = 875714; //875714
			for (int i = 1; i <= nVertex; ++i)
			{
				G.add_vertex(i);
				Grev.add_vertex(i);
			}

			textReader("D:/cpp_practise/test_cases/SCC.txt",G,Grev); //SCCCase1.txt
			/* //for debugging
			G.print_adjacency_list();
			std::cout << "----------------------------------" << std::endl;
			Grev.print_adjacency_list();
			*/
			//step #2: DFS of Grev
			std::vector<int> labelVec; //used for traversal order in DFS loop
			labelVec.reserve(nVertex);
			//instead of finish time for each vertex we store the order of finishing
			// so that we can traverse during 2nd pass in reverse finishing order
			std::vector<int> vecFinishOrder;
			vecFinishOrder.reserve(nVertex);
			std::vector<int> vecLeader;
			vecLeader.reserve(nVertex);

			for (int i = 0; i < nVertex; ++i)
			{
				labelVec.push_back(nVertex-1-i);
				vecLeader.push_back(nVertex); //dummy value
			}

			DFS_Traversal_Loop(Grev,labelVec,vecFinishOrder,vecLeader);

			//step #3: DFS of G in reverse order of vecFinishOrder
			labelVec.clear();
			vecLeader.clear();
			for (int i = 0; i < vecFinishOrder.size(); ++i)
			{
				labelVec.push_back(vecFinishOrder[vecFinishOrder.size()-1-i]);
				vecLeader.push_back(nVertex); //dummy value
			}
			vecFinishOrder.clear();
			DFS_Traversal_Loop(G,labelVec,vecFinishOrder,vecLeader);

			std::map<int,int> scc_count_map;
			scc_count(vecLeader,scc_count_map);

			int gh = 0;
		}
		break;
	}

	return 0;
}

template<typename T>
void DFS_Traversal_Loop(ds::Graph<T>& G, std::vector<int>& labelVec, std::vector<int>& vecFinishOrder, std::vector<int>& vecLeader)
{
    //std::cout << G.explored(255079) << std::endl;
	for (std::vector<int>::iterator it = labelVec.begin(); it != labelVec.end(); ++it)
	{
		int pos_i = *it;
		if (G.explored(pos_i) == false)
		{
			int pos_leader = pos_i;
			DFS(G,pos_i,vecFinishOrder,pos_leader,vecLeader);
		}
	}

	int gh = 0;
}

void scc_count(std::vector<int>& vecLeader, std::map<int,int>& scc_count_map)
{
	for (std::vector<int>::iterator it = vecLeader.begin(); it != vecLeader.end(); ++it)
	{
		int leader = *it;
		std::map<int,int>::iterator mIt = scc_count_map.find(*it);

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
	std::vector<int> countVec;

	for (std::map<int,int>::iterator mIt = scc_count_map.begin(); mIt != scc_count_map.end(); ++mIt)
	{
		countVec.push_back((*mIt).second);
	}

	std::sort(countVec.begin(),countVec.end(),std::greater<int>());
	int gh = 0;
}

template<typename T>
void DFS(ds::Graph<T>& G, int pos_i, std::vector<int>& vecFinishOrder, int pos_leader, std::vector<int>& vecLeader)
{
	G.setExplored(pos_i);
	vecLeader[pos_i] = pos_leader; //set leader
	std::vector<T> adjList = G.adjacencyList(pos_i);
	for (std::vector<T>::iterator it = adjList.begin(); it != adjList.end(); ++it)
	{
        assert((*it > 0) && "gadbad in adjList");
		int pos_j = *it-1;
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
void textReader(const char* textFile, ds::Graph<T>& G, ds::Graph<T>& Grev)
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
				assert((lineSplit.size() == 2) && "only two vertices expected to form an edge");
				T vertex1 = std::atoi(lineSplit[0].c_str());
				T vertex2 = std::atoi(lineSplit[1].c_str());

				G.add_edge(vertex1,vertex2);
				Grev.add_edge(vertex2,vertex1);
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