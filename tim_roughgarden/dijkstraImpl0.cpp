#include "GraphDijkstra.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>

//This implementation is without using heap

template<typename T>
void shortest_path_computation(T srcVertex, ds::Graph<T>& G);

template<typename T>
void textReader(const char* textFile, ds::Graph<T>& G);

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

			int nVertex = 200; //
			for (int i = 1; i <= nVertex; ++i)
			{
				G.add_vertex(i);
			}

			textReader("D:/cpp_practise/test_cases/dijkstraData.txt",G);
			int srcVertex = 1;
			shortest_path_computation(srcVertex,G);
			// Now print the shortest path distances of some of the vertices
			int arrVertices[] = {7,37,59,82,99,115,133,165,188,197};
			std::size_t countArrVertices = sizeof(arrVertices)/sizeof(arrVertices[0]);
			for (std::size_t i = 0; i < countArrVertices; ++i)
			{
				std::cout << "vertex# " << arrVertices[i] << " : " << G.shortestPathDistance(arrVertices[i]) << std::endl;
			}

			int gh = 0;
		}
		break;
	case 1:
		{
			Graph<int> G;

			int nVertex = 4;
			for (int i = 1; i <= nVertex; ++i)
			{
				G.add_vertex(i);
			}

			textReader("D:/cpp_practise/test_cases/dijkstraDataCase0.txt",G);
			int srcVertex = 1;
			shortest_path_computation(srcVertex,G);
			// Now print the shortest path distances of some of the vertices
			int arrVertices[] = {1,2,3,4};
			std::size_t countArrVertices = sizeof(arrVertices)/sizeof(arrVertices[0]);
			for (std::size_t i = 0; i < countArrVertices; ++i)
			{
				std::cout << "vertex# " << arrVertices[i] << " : " << G.shortestPathDistance(arrVertices[i]) << std::endl;
			}

			int gh = 0;
		}
		break;
	}

	return 0;
}

template<typename T>
void shortest_path_computation(T srcVertex, ds::Graph<T>& G)
{
	using namespace ds;
	G.setProcessed(srcVertex,0);
	std::size_t countProcessedVertices = 1;

	while (countProcessedVertices < G.count_vertices())
	{
		std::vector<T> vecVertices = G.vertices();

		T vertexWStar;
		T shortestPathWStar = 1000000; //considered as inf
		//get the edge which satisfies Dijkstra's greedy criterion
		for (std::vector<T>::iterator vIt = vecVertices.begin(); vIt != vecVertices.end(); ++vIt)
		{
			//consider the outEdge of current vertex whose other end is not in the processed set
			T vertex1 = *vIt;
			if (G.isProcessed(vertex1))
			{
				//vertex is in processed set
				Graph<T>::VecPair adjacentVerticesWeightVec = G.adjacent_vertices_weight(vertex1);
				
				for (Graph<T>::VecPair::iterator tgtIt = adjacentVerticesWeightVec.begin(); tgtIt != adjacentVerticesWeightVec.end(); ++tgtIt)
				{
					T tgtVertex = (*tgtIt).first;
					if (!G.isProcessed(tgtVertex))
					{
						T edgeWeight = (*tgtIt).second;
						T shortestPathDistanceVtx1 = G.shortestPathDistance(vertex1);
						T shortestPathDistance = shortestPathDistanceVtx1 + edgeWeight;
						
						if (shortestPathDistance < shortestPathWStar)
						{
							vertexWStar = tgtVertex;
							shortestPathWStar = shortestPathDistance;
						}
					}
				}
				
			}
		}

		G.setProcessed(vertexWStar,shortestPathWStar);

		++countProcessedVertices;
	}
}

template<typename T>
void textReader(const char* textFile, ds::Graph<T>& G)
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
				//assert((lineSplit.size() == 2) && "only two vertices expected to form an edge");
				T vertex1 = std::atoi(lineSplit[0].c_str());
				
				//now push the edges and their respective weights
				std::size_t i = 0;
				while ((i+1) < lineSplit.size())
				{
					T vertex2 = std::atoi(lineSplit[i+1].c_str());
					T weight = std::atoi(lineSplit[i+2].c_str());
					G.add_edge(vertex1,vertex2,weight);
					i += 2;
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
		start = line.find_first_not_of("\t,",end);
		end   = line.find_first_of("\t,",start);
		if (start == end)
		{
			break;
		}
		lineSplit.push_back(line.substr(start,(end-start)));
	}
}