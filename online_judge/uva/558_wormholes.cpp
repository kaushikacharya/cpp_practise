// http://uva.onlinejudge.org/external/5/558.html
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

const bool READ_FROM_FILE = false;

template<typename T1, typename T2>
class Edge
{
public:
	Edge(T1 src, T1 tgt, T2 weight)
		: src_(src)
		, tgt_(tgt)
		, weight_(weight)
	{}
public:
	T1 src(){return src_;};
	T1 tgt(){return tgt_;};
	T2 weight(){return weight_;};
private:
	T1 src_;
	T1 tgt_;
	T2 weight_;
};
//---------------------
template<typename T1, typename T2>
class Graph
{
public:
	Graph(T1 nVertex, T1 nEdge);
public:
	void read_input(std::ifstream& pFile);
	std::vector<Edge<T1,T2> > incoming_edges(T1 tgt);
public:
	T1 nVertex();
private:
	T1 nVertex_;
	T1 nEdge_;
	// we are storing incoming edges
	std::vector<std::vector<Edge<T1,T2> > > adjList_;
};
//-----------
template<typename T1, typename T2>
class BellmanFord
{
public:
	BellmanFord(const Graph<T1,T2>& graph);
	bool check_negative_cycle(T1 source);
private:
	Graph<T1,T2> graph_;
	std::vector<std::vector<T2> > costMatrix_;
};

//-----------
template<typename T1, typename T2>
Graph<T1,T2>::Graph(T1 nVertex, T1 nEdge)
: nVertex_(nVertex)
, nEdge_(nEdge)
{
	adjList_.reserve(nVertex_);

	for (T1 vtx_i = 0; vtx_i != nVertex_; ++vtx_i)
	{
		adjList_.push_back(std::vector<Edge<T1,T2> >());
	}
}

template<typename T1, typename T2>
void Graph<T1,T2>::read_input(std::ifstream& pFile)
{
	T1 src;
	T1 tgt;
	T2 weight;

	for (T1 edge_i = 0; edge_i != nEdge_; ++edge_i)
	{
		if (READ_FROM_FILE)
		{
			pFile >> src >> tgt >> weight;
		} 
		else
		{
			std::cin >> src >> tgt >> weight;
		}

		Edge<T1,T2> edge(src,tgt,weight);
		adjList_[tgt].push_back(edge);
	}
}

template<typename T1, typename T2>
typename std::vector<Edge<T1,T2> > Graph<T1,T2>::incoming_edges(T1 tgt)
{
	return adjList_[tgt];
}

template<typename T1, typename T2>
T1 Graph<T1,T2>::nVertex()
{
	return nVertex_;
}
//-----------

template<typename T1, typename T2>
BellmanFord<T1,T2>::BellmanFord(const Graph<T1,T2>& graph)
: graph_(graph)
{
	costMatrix_.reserve(2);
	for (T1 i = 0; i != 2; ++i)
	{
		costMatrix_.push_back(std::vector<T2>());
	}
	//initialize with inf cost
	for (T1 i = 0; i != 2; ++i)
	{
		costMatrix_[i].reserve(graph_.nVertex());
		for (T1 vtx_i = 0; vtx_i != graph_.nVertex(); ++vtx_i)
		{
			costMatrix_[i].push_back(std::numeric_limits<T2>::max());
		}
	}
}

template<typename T1, typename T2>
bool BellmanFord<T1,T2>::check_negative_cycle(T1 source)
{
	bool iteration = false;
	T1 iterCount = 0;
	costMatrix_[iteration][source] = 0;

	while (iterCount != (graph_.nVertex()+1))
	{
		++iterCount;
		iteration = !iteration;

		for (T1 vtx_i = 0; vtx_i != graph_.nVertex(); ++vtx_i)
		{
			T2 minCost = costMatrix_[!iteration][vtx_i];
			std::vector<Edge<T1,T2> > vecEdge = graph_.incoming_edges(vtx_i);

			for (typename std::vector<Edge<T1,T2> >::iterator inEdgeIt = vecEdge.begin(); inEdgeIt != vecEdge.end(); ++inEdgeIt)
			{
				if (costMatrix_[!iteration][inEdgeIt->src()] == std::numeric_limits<T2>::max())
				{
					continue;
				}
				T2 cost = costMatrix_[!iteration][inEdgeIt->src()] + inEdgeIt->weight();
				if (cost < minCost)
				{
					minCost = cost;
				}
				int gh = 0;
			}

			costMatrix_[iteration][vtx_i] = minCost;
		}
		// check if there's any update
		bool updated_flag = false;
		for (T1 vtx_i = 0; vtx_i != graph_.nVertex(); ++vtx_i)
		{
			if (costMatrix_[iteration][vtx_i] != costMatrix_[!iteration][vtx_i])
			{
				updated_flag = true;
				break;
			}
		}

		if (!updated_flag)
		{
			break;
		}
	}

	if (iterCount < (graph_.nVertex()+1))
	{
		return false;
	} 
	else
	{
		bool negative_cycle_found = false;
		for (T1 vtx_i = 0; vtx_i != graph_.nVertex(); ++vtx_i)
		{
			if (costMatrix_[iteration][vtx_i] != costMatrix_[!iteration][vtx_i])
			{
				negative_cycle_found = true;
				break;
			}
		}
		return negative_cycle_found;
	}
}
//-----------
int main(int argc, char* argv[])
{
	unsigned int nCase;
	std::ifstream pFile;

	if (READ_FROM_FILE)
	{
		pFile.open("d:/cpp_practise/online_judge/uva/558_wormholes_input.txt",std::ios::in);
		pFile >> nCase;
	} 
	else
	{
		std::cin >> nCase;
	}

	for (unsigned int case_i = 0; case_i != nCase; ++case_i)
	{
		unsigned int nVertex, nEdge;
		
		if (READ_FROM_FILE)
		{
			pFile >> nVertex >> nEdge;
		} 
		else
		{
			std::cin >> nVertex >> nEdge;
		}

		Graph<unsigned int, long> graph(nVertex,nEdge);
		graph.read_input(pFile);
		BellmanFord<unsigned int, long> bellmanFord(graph);
		unsigned int source = 0;
		if (bellmanFord.check_negative_cycle(source))
		{
			std::cout << "possible" << std::endl;
		}
		else
		{
			std::cout << "not possible" << std::endl;
		}
		int gh = 0;
	}

	return 0;
}
