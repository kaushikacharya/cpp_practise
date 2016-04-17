#include "GraphSCC.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>

template<typename T>
void compute_scc(ds::Graph<T>& G, ds::Graph<T>& Grev);

template<typename T>
void dfs_traversal_loop(ds::Graph<T>& G, std::vector<std::size_t> orderOfNodes, std::vector<std::size_t>& vecFinishingOrder, std::vector<std::size_t>& vecLeader);

template<typename T>
void dfs_traversal(ds::Graph<T>& G, T vertex, std::vector<std::size_t>& vecFinishingOrder, std::vector<std::size_t>& vecLeader, T leader);

void scc_count(std::vector<std::size_t>& vecLeader, std::map<std::size_t,std::size_t>& scc_count_map);

template<typename T>
void textReader(const char* textFile, ds::Graph<T>& G, ds::Graph<T>& Grev);

void tokenize(std::string& line,std::vector<std::string>& lineSplit);

int main(int argc, char* argv[])
{
	using namespace ds;
	std::size_t test_case=5;

	switch (test_case)
	{
	case 0:
		{
			Graph<int> G;
			Graph<int> Grev;

			int nVertex = 9;
			for (int i = 1; i <= nVertex; ++i)
			{
				G.add_vertex(i);
				Grev.add_vertex(i);
			}
			textReader("D:/cpp_practise/test_cases/scc/SCCCase0.txt",G,Grev);
			compute_scc(G,Grev);
			int gh = 0;
		}
		break;
	case 1:
		{
			Graph<int> G;
			Graph<int> Grev;

			int nVertex = 11;
			for (int i = 1; i <= nVertex; ++i)
			{
				G.add_vertex(i);
				Grev.add_vertex(i);
			}
			textReader("D:/cpp_practise/test_cases/scc/SCCCase2.txt",G,Grev);
			compute_scc(G,Grev);
			int gh = 0;
		}
		break;
	case 2:
		{
			Graph<int> G;
			Graph<int> Grev;

			int nVertex = 12;
			for (int i = 1; i <= nVertex; ++i)
			{
				G.add_vertex(i);
				Grev.add_vertex(i);
			}
			textReader("D:/cpp_practise/test_cases/scc/SCCCase5.txt",G,Grev);
			compute_scc(G,Grev);
			int gh = 0;
		}
		break;
	case 3:
		{
			Graph<int> G;
			Graph<int> Grev;

			int nVertex = 50;
			for (int i = 1; i <= nVertex; ++i)
			{
				G.add_vertex(i);
				Grev.add_vertex(i);
			}
			textReader("D:/cpp_practise/test_cases/scc/SCCCase7.txt",G,Grev);
			compute_scc(G,Grev);
			int gh = 0;
		}
		break;
	case 4:
		{
			Graph<int> G;
			Graph<int> Grev;

			int nVertex = 8;
			for (int i = 1; i <= nVertex; ++i)
			{
				G.add_vertex(i);
				Grev.add_vertex(i);
			}
			textReader("D:/cpp_practise/test_cases/scc/SCCCase4.txt",G,Grev);
			compute_scc(G,Grev);
			int gh = 0;
		}
		break;
	case 5:
		{
			Graph<int> G;
			Graph<int> Grev;

			int nVertex = 875714;
			for (int i = 1; i <= nVertex; ++i)
			{
				G.add_vertex(i);
				Grev.add_vertex(i);
			}
			textReader("D:/cpp_practise/test_cases/scc/SCC.txt",G,Grev);
			compute_scc(G,Grev);
			int gh = 0;
		}
		break;
	}

	return 0;
}

template<typename T>
void compute_scc(ds::Graph<T>& G, ds::Graph<T>& Grev)
{
	//TBD: Grev can be created here.
	std::size_t nVertex = G.nVertex();
	
	// step #2: run dfs_traversal_loop for Grev and get the finishing time for each vertex
	std::vector<std::size_t> orderOfNodes;
	orderOfNodes.reserve(nVertex);
	std::size_t i = nVertex;
	while(i > 0)
	{
		orderOfNodes.push_back(i-1);
		--i;
	}
	std::vector<std::size_t> vecFinishingOrder;
	vecFinishingOrder.reserve(nVertex);
	std::vector<std::size_t> vecLeader;
	vecLeader.reserve(nVertex);
	//populate dummy values for vecLeader
	for (i=0; i < nVertex; ++i)
	{
		vecLeader.push_back(nVertex);
	}
	dfs_traversal_loop(Grev, orderOfNodes, vecFinishingOrder, vecLeader);

	// step #3: run dfs_traversal_loop for G in decreasing order of finishing time computed in previous step
	orderOfNodes.clear();
	for (std::vector<std::size_t>::reverse_iterator it = vecFinishingOrder.rbegin(); it != vecFinishingOrder.rend(); ++it)
	{
		orderOfNodes.push_back(*it);
	}
	vecFinishingOrder.clear();
	//vecLeader.clear(); //didn't matter what was populated in 1st dfs loop i.e dfs loop of Grev
	dfs_traversal_loop(G, orderOfNodes, vecFinishingOrder, vecLeader);

	std::map<std::size_t,std::size_t> scc_count_map;
	scc_count(vecLeader,scc_count_map);
	int gh = 0;
}

template<typename T>
void dfs_traversal_loop(ds::Graph<T>& G, std::vector<std::size_t> orderOfNodes, std::vector<std::size_t>& vecFinishingOrder, std::vector<std::size_t>& vecLeader)
{
	std::vector<T> vecVertex = G.vertices();

	for (std::vector<std::size_t>::iterator it = orderOfNodes.begin(); it != orderOfNodes.end(); ++it)
	{
		T vertex = vecVertex[(*it)];
		//if not explored
		if (!G.isExplored(vertex))
		{
			dfs_traversal(G,vertex,vecFinishingOrder,vecLeader,vertex);
		}
	}
}

template<typename T>
void dfs_traversal(ds::Graph<T>& G, T vertex, std::vector<std::size_t>& vecFinishingOrder, std::vector<std::size_t>& vecLeader, T leader)
{
	std::vector<T> vecVertex = G.vertices();
	std::vector<T>::iterator it = std::find(vecVertex.begin(), vecVertex.end(), vertex);

	G.setExplored(vertex);
	//TBD: set leader for vertex
	std::vector<T>::iterator leaderIt = std::find(vecVertex.begin(), vecVertex.end(), leader);
	//std::cout << std::distance(vecVertex.begin(),it) << " : " << std::distance(vecVertex.begin(),leaderIt) << std::endl;
	vecLeader[std::distance(vecVertex.begin(),it)] = std::distance(vecVertex.begin(),leaderIt);
	//std::map<T,std::set<T>>::iterator it = graph_container_.find(vertex);
	//std::set<T> adjacentVertices = (*it).second;
	std::set<T> adjacentVertices = G.adjacentVertices(vertex);

	for (std::set<T>::iterator adjIt = adjacentVertices.begin(); adjIt != adjacentVertices.end(); ++adjIt)
	{
		T adjVertex = (*adjIt);
		if (!G.isExplored(adjVertex))
		{
			dfs_traversal(G,adjVertex,vecFinishingOrder, vecLeader, leader);
		}
	}

	//TBD: set finishing time for vertex
	vecFinishingOrder.push_back(std::distance(vecVertex.begin(),it));
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

/*
https://class.coursera.org/algo-003/forum/thread?thread_id=490
*/
