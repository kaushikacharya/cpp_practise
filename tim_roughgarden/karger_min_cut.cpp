#include <iostream>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>
#include "GraphVertex.hpp"
#include "GraphEdge.hpp"
#include <ctime>
#include <limits>

//http://stackoverflow.com/a/2931359/282155
//on need of prefixing with 'typename'
template<typename T>
typename std::vector<ds::GraphVertex<T> >::iterator searchVertex(std::vector<ds::GraphVertex<T> >& vertexVec, T id);

template<typename T>
typename std::vector<ds::GraphEdge<T> >::iterator searchEdge(std::vector<ds::GraphEdge<T> >& edgeVec, T id1, T id2);

template<typename T>
int compute_graph_cut(std::vector<ds::GraphVertex<T> >& vertexVec, std::vector<ds::GraphEdge<T> >& edgeVec);

template<typename T>
void textReader(const char* textFile, std::vector<T>& vecVertex, std::vector<std::pair<T,T> >& vecEdge);

void tokenize(std::string& line,std::vector<std::string>& lineSplit);

int main(int argc, char* argv[])
{
	using namespace ds;
	std::size_t test_case = 1;

	switch (test_case)
	{
	case 0:
		{
			std::vector<GraphVertex<int> > vertexVec;
			for (int i=1; i < 5; ++i)
			{
				GraphVertex<int> vertex(i);
				vertexVec.push_back(vertex);
			}
			//now add edges
			std::vector<GraphEdge<int> > edgeVec;

			//input data
			//assumption: undirected graph
			//            Hence (i,j) (j,i) Both come as input but edgeVec stores only the first one
			std::vector<std::pair<int,int> > inputEdgeVec;
			inputEdgeVec.push_back(std::make_pair<int,int>(1,3));
			inputEdgeVec.push_back(std::make_pair<int,int>(1,2));
			inputEdgeVec.push_back(std::make_pair<int,int>(2,1));
			inputEdgeVec.push_back(std::make_pair<int,int>(3,1));
			//inputEdgeVec.push_back(std::make_pair<int,int>(2,3));

			for (std::vector<std::pair<int,int> >::iterator it=inputEdgeVec.begin(); it != inputEdgeVec.end(); ++it)
			{
				int i = (*it).first;
				int j = (*it).second;

				std::vector<GraphVertex<int> >::iterator it0;
				std::vector<GraphVertex<int> >::iterator it1;

				it0 = searchVertex(vertexVec,i);
				assert(it0 != vertexVec.end() && "vertex not found");
				it1 = searchVertex(vertexVec,j);
				assert(it1 != vertexVec.end() && "vertex not found");

				(*it0).push_adjacent_vertex((*it1).id());
				//(*it1).push_adjacent_vertex((*it0).id());

				std::vector<ds::GraphEdge<int> >::iterator itEdge = searchEdge(edgeVec, i, j);
				if (itEdge == edgeVec.end())
				{
					GraphEdge<int> edge(i,j);
					edgeVec.push_back(edge);
				}
			}

			int gh = 0;
			//vertexVec[0].push_adjacent_vertex(3);
		}
		break;
	case 1:
		{
			std::vector<int> inputVertexVec;
			std::vector<std::pair<int,int> > inputEdgeVec;
			inputVertexVec.reserve(200);
			inputEdgeVec.reserve(200*10);
			textReader("D:/cpp_practise/test_cases/kargerMinCut.txt",inputVertexVec,inputEdgeVec);
			
			std::vector<GraphVertex<int> > vertexVec;
			std::vector<GraphEdge<int> > edgeVec;
			vertexVec.reserve(inputVertexVec.size());
			edgeVec.reserve(inputEdgeVec.size()/2);

			//populating vertices
			for (std::vector<int>::iterator it = inputVertexVec.begin(); it != inputVertexVec.end(); ++it)
			{
				GraphVertex<int> vertex((*it));
				vertexVec.push_back(vertex);
			}
			//populating edges
			for (std::vector<std::pair<int,int> >::iterator it = inputEdgeVec.begin(); it != inputEdgeVec.end(); ++it)
			{
				// -- first populating adjacent vertices
				std::vector<GraphVertex<int> >::iterator it0;
				std::vector<GraphVertex<int> >::iterator it1;

				it0 = searchVertex(vertexVec,(*it).first);
				assert(it0 != vertexVec.end() && "vertex not found");
				it1 = searchVertex(vertexVec,(*it).second);
				assert(it1 != vertexVec.end() && "vertex not found");

				(*it0).push_adjacent_vertex((*it1).id());
				// --

				std::vector<GraphEdge<int> >::iterator itEdge = searchEdge(edgeVec, (*it).first, (*it).second);
				if (itEdge == edgeVec.end())
				{
					GraphEdge<int> edge((*it).first,(*it).second);
					edgeVec.push_back(edge);
				}
			}

			//http://stackoverflow.com/questions/1855459/maximum-value-of-int
			//2^n is giving (-) because probably it goes beyond the limit of int range.
			//TBD: find a way to handle that.
			//int min_cut = (int)std::pow(2.0,(int)inputVertexVec.size()); //max possible cut
			int min_cut = std::numeric_limits<int>::max();
			int n_iteration = (int)(inputVertexVec.size()*inputVertexVec.size()*log(1.0*inputVertexVec.size()));

			for (int iteration=0; iteration < n_iteration; ++iteration)
			{
				std::vector<GraphVertex<int> > vertexVecTest;
				std::vector<GraphEdge<int> > edgeVecTest;
				vertexVecTest = vertexVec;
				edgeVecTest = edgeVec;

				int cut = compute_graph_cut(vertexVecTest,edgeVecTest);
				std::cout << "iteration#: " << iteration << " : cut: " << cut << std::endl;
				if (cut < min_cut)
				{
					min_cut = cut;
				}
			}

			std::cout << "\nmin cut: " << min_cut << std::endl;
			int gh = 0;
		}
		break;
	}

	return 0;
}

template<typename T>
typename std::vector<ds::GraphVertex<T> >::iterator searchVertex(std::vector<ds::GraphVertex<T> >& vertexVec, T id)
{
	typedef std::vector<ds::GraphVertex<T> >::iterator VertexVecIterator;
	VertexVecIterator itId = vertexVec.end();

	for (VertexVecIterator it = vertexVec.begin(); it != vertexVec.end(); ++it)
	{
		if ( (*it).id() == id)
		{
			itId = it;
			break;
		}
	}

	return itId;
}

//Note: This returns the first edge that matches the edge[id1,id2] or edge[id2,id1] which are considered same
//      in undirected graph.
template<typename T>
typename std::vector<ds::GraphEdge<T> >::iterator searchEdge(std::vector<ds::GraphEdge<T> >& edgeVec, T id1, T id2)
{
	typedef std::vector<ds::GraphEdge<T> >::iterator EdgeVecIterator;
	EdgeVecIterator itEdge = edgeVec.end();

	for (EdgeVecIterator it = edgeVec.begin(); it != edgeVec.end(); ++it)
	{
		if ( (*it).edge().first == id1 && (*it).edge().second == id2)
		{
			itEdge = it;
			break;
		}
		else if ( (*it).edge().first == id2 && (*it).edge().second == id1)
		{
			itEdge = it;
			break;
		}
	}

	return itEdge;
}

template<typename T>
int compute_graph_cut(std::vector<ds::GraphVertex<T> >& vertexVec, std::vector<ds::GraphEdge<T> >& edgeVec)
{
	using namespace ds;

	//http://www.cplusplus.com/reference/cstdlib/rand/
	//http://stackoverflow.com/questions/4331371/c-random-seed-at-runtime
	/* initialize random seed: */
	srand (time(NULL));

	while (vertexVec.size() > 2)
	{
		//step #1: select a random edge whose vertices will be merged
		std::size_t indexEdge = rand() % edgeVec.size();
		T idVertex1 = edgeVec[indexEdge].edge().first;
		T idVertex2 = edgeVec[indexEdge].edge().second;
		// now start the merge of idVertex1, idVertex2
		// as part of this step, all the in-edges to idVertex2 should now replace idVertex2 by idVertex1
		// This change should also reflect in the adjacent list of vertices which had edge with idVertex2.
		// It should also reflect in the adjacent list of idVertex1
		std::vector<GraphVertex<T> >::iterator itVtx1;
		itVtx1 = searchVertex(vertexVec,idVertex1);
		assert(itVtx1 != vertexVec.end() && "vertex1 not found");
		std::vector<T>& adjacent_vertices_of_vtx1 = (*itVtx1).adjacentList();

		std::vector<GraphVertex<T> >::iterator itVtx2;
		itVtx2 = searchVertex(vertexVec,idVertex2);
		assert(itVtx2 != vertexVec.end() && "vertex2 not found");
		std::vector<T> adjacent_vertices_of_vtx2 = (*itVtx2).adjacentList();

		for (std::vector<T>::iterator it = adjacent_vertices_of_vtx2.begin(); it != adjacent_vertices_of_vtx2.end(); ++it)
		{
			if ((*it) == idVertex1)
			{
				//remove idVertex2 from adjacentList of vertex1
				std::vector<T>::iterator posIt = std::find(adjacent_vertices_of_vtx1.begin(),adjacent_vertices_of_vtx1.end(),idVertex2);
				assert(posIt != adjacent_vertices_of_vtx1.end() && "vertex2 not found in adjacent list of vertex3");
				adjacent_vertices_of_vtx1.erase(posIt);
				continue;
			}

			std::vector<GraphVertex<T> >::iterator itVtx3;
			itVtx3 = searchVertex(vertexVec,(*it));
			assert(itVtx3 != vertexVec.end() && "vertex not found");
			std::vector<T>& adjacent_vertices_of_vtx3 = (*itVtx3).adjacentList();

			//remove idVertex2 from adjacentList of vertex3
			std::vector<T>::iterator posIt = std::find(adjacent_vertices_of_vtx3.begin(),adjacent_vertices_of_vtx3.end(),idVertex2);
			assert(posIt != adjacent_vertices_of_vtx3.end() && "vertex2 not found in adjacent list of vertex3");
			adjacent_vertices_of_vtx3.erase(posIt);

			T idVertex3 = (*itVtx3).id();

			//add vtx1 in adjacent list of vtx3(in not present)
			posIt = std::find(adjacent_vertices_of_vtx3.begin(),adjacent_vertices_of_vtx3.end(),idVertex1);
			if (posIt == adjacent_vertices_of_vtx3.end())
			{
				adjacent_vertices_of_vtx3.push_back(idVertex1);
			}

			//add vtx3 in adjacent list of vtx1(in not present)
			posIt = std::find(adjacent_vertices_of_vtx1.begin(),adjacent_vertices_of_vtx1.end(),idVertex3);
			if (posIt == adjacent_vertices_of_vtx1.end())
			{
				adjacent_vertices_of_vtx1.push_back(idVertex3);
			}

			//remove the edge(s) [vtx2 - vtx3] and add corresponding edge [vtx1 - vtx3]
			std::vector<GraphEdge<T> >::iterator itEdge = searchEdge(edgeVec, idVertex2, idVertex3);
			assert(itEdge != edgeVec.end() && "edge [vtx2 - vtx3] not found");
			while (itEdge != edgeVec.end())
			{
				edgeVec.erase(itEdge);
				//add edge [vtx1 - vtx3]
				GraphEdge<int> edge(idVertex1,idVertex3);
				edgeVec.push_back(edge);
				//search again [vtx2 - vtx3]
				itEdge = searchEdge(edgeVec, idVertex2, idVertex3);
			}
		}

		//remove the edge(s) [vtx1 - vtx2]
		std::vector<GraphEdge<T> >::iterator itEdge = searchEdge(edgeVec, idVertex1, idVertex2);
		assert(itEdge != edgeVec.end() && "edge [vtx1 - vtx2] not found");
		while (itEdge != edgeVec.end())
		{
			edgeVec.erase(itEdge);
			itEdge = searchEdge(edgeVec, idVertex1, idVertex2);
		}

		//delete vertex2
		vertexVec.erase(itVtx2);
	}

	return edgeVec.size();
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
		start = line.find_first_not_of('\t',end);
		end   = line.find_first_of('\t',start);
		if (start == end)
		{
			break;
		}
		lineSplit.push_back(line.substr(start,(end-start)));
	}
}

/**
Learnings:
1. http://stackoverflow.com/questions/2931345/c-trouble-with-dependent-types-in-templates
typename needs to be added in return type: typename std::vector<ds::GraphVertex<T> >::iterator	
*/