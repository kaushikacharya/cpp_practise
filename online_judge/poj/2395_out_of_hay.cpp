// http://poj.org/problem?id=2395
#include <cstdio>
#include <vector>
#include <limits>
#include <queue>
#include <set>

#define READ_FROM_FILE 0

template<typename T>
class Edge
{
public:
	Edge(unsigned int source, unsigned int target, T weight);
	~Edge();
public:
	unsigned int source();
	unsigned int target();
	T weight();
private:
	unsigned int source_;
	unsigned int target_;
	T weight_;
};
// ---------------------------------------------------
template<typename T>
class Graph
{
public:
	Graph(unsigned int nVertex);
	~Graph();
public:
	unsigned int nVertex();
	void addEdge(unsigned int vertex1, unsigned int vertex2, T weight);
	void adjacentEdges(unsigned int vertex, std::vector<Edge<T>*>& vecAdjEdges);
private:
	unsigned int nVertex_;
	std::vector<std::vector<Edge<T>*> > adjList_;
};
// ---------------------------------------------------
// minimum bottleneck spanning tree
// http://en.wikipedia.org/wiki/Minimum_spanning_tree#Minimum_bottleneck_spanning_tree
template<typename T>
class MBST
{
public:
	MBST(Graph<T>& graph);
	~MBST();
public:
	void min_spanning_tree(unsigned int source);
	void update_priority_queue(unsigned int vertex);
	T get_bottleneck();
private:
	Graph<T>& graph_;
	std::vector<bool> vecVisited_;
	std::vector<T> vecCost_;
	//std::vector<T> vecMSTcost_;
	//std::vector<T> vecMBSTcost_;
// priority queue
private:
	struct VertexCost
	{
		unsigned int vertex;
		T cost;
	};

	struct Comp
	{
		bool operator()(const VertexCost& vc1, const VertexCost& vc2) const
		{
			if (vc1.cost == vc2.cost)
			{
				return vc1.vertex < vc2.vertex;
			} 
			else
			{
				return vc1.cost < vc2.cost;
			}
		}
	};

	typedef std::set<VertexCost,Comp> SetVertexCost;
	SetVertexCost setVertexCost_;
};
// ---------------------------------------------------
template<typename T>
Edge<T>::Edge(unsigned int source, unsigned int target, T weight)
: source_(source)
, target_(target)
, weight_(weight)
{
}

template<typename T>
Edge<T>::~Edge()
{
}

template<typename T>
unsigned int Edge<T>::source()
{
	return source_;
}

template<typename T>
unsigned int Edge<T>::target()
{
	return target_;
}

template<typename T>
T Edge<T>::weight()
{
	return weight_;
}
// ---------------------------------------------------
template<typename T>
Graph<T>::Graph(unsigned int nVertex)
: nVertex_(nVertex)
{
	//initialize adjacency list
	// http://www.cplusplus.com/forum/general/833/#msg2999
	adjList_.reserve(nVertex);

	for (unsigned int vertex_i = 0; vertex_i != nVertex; ++vertex_i)
	{
		// add empty row
		adjList_.push_back(std::vector<Edge<T>*>());
	}
}

template<typename T>
Graph<T>::~Graph()
{
	int gh = 0;
}

template<typename T>
unsigned int Graph<T>::nVertex()
{
	return nVertex_;
}

template<typename T>
void Graph<T>::addEdge(unsigned int vertex1, unsigned int vertex2, T weight)
{
	// undirected graph
	Edge<T>* edge1 = new Edge<T>(vertex1, vertex2, weight);
	adjList_[vertex1].push_back(edge1);
	Edge<T>* edge2 = new Edge<T>(vertex2, vertex1, weight);
	adjList_[vertex2].push_back(edge2);
}

template<typename T>
void Graph<T>::adjacentEdges(unsigned int vertex, std::vector<Edge<T>*>& vecAdjEdges)
{
	vecAdjEdges = adjList_[vertex];
}
// ---------------------------------------------------
template<typename T>
MBST<T>::MBST(Graph<T>& graph)
: graph_(graph)
{
	vecVisited_.reserve(graph.nVertex());
	vecCost_.reserve(graph.nVertex());
	//vecMSTcost_.reserve(graph.nVertex());
	//vecMBSTcost_.reserve(graph.nVertex());

	for (unsigned int vertex_i = 0; vertex_i != graph.nVertex(); ++vertex_i)
	{
		vecVisited_.push_back(false);
		vecCost_.push_back(std::numeric_limits<T>::max());
		//vecMSTcost_.push_back(std::numeric_limits<T>::max());
		//vecMBSTcost_.push_back(std::numeric_limits<T>::max());
	}

	VertexCost vtxCost;
	for (unsigned int vertex_i = 0; vertex_i != graph.nVertex(); ++vertex_i)
	{
		vtxCost.vertex = vertex_i;
		vtxCost.cost = std::numeric_limits<T>::max();
		setVertexCost_.insert(vtxCost);
	}
	//printf("size: %d\n",setVertexCost_.size());

	int gh = 0;
}

template<typename T>
MBST<T>::~MBST()
{
	int gh = 0;
}

template<typename T>
void MBST<T>::update_priority_queue(unsigned int vertex)
{
	typedef std::vector<Edge<T>*> VecEdge;
	VecEdge vecAdjEdges;
	graph_.adjacentEdges(vertex,vecAdjEdges);

	for (VecEdge::iterator it = vecAdjEdges.begin(); it != vecAdjEdges.end(); ++it)
	{
		Edge<T>* outEdge = *it;
		T cost = (*outEdge).weight(); // vecMSTcost_[vertex] + 

		if ( !vecVisited_[(*outEdge).target()] && (cost <  vecCost_[(*outEdge).target()]) ) //vecMSTcost_
		{
			//decrease-key is implemented by two steps: a) erase, b) insert using the updated value
			VertexCost vtxCost;
			vtxCost.vertex = (*outEdge).target();
			vtxCost.cost = vecCost_[(*outEdge).target()]; //vecMSTcost_
			SetVertexCost::iterator it = setVertexCost_.find(vtxCost);
			setVertexCost_.erase(it);
			vtxCost.cost = cost;
			setVertexCost_.insert(vtxCost);

			vecCost_[(*outEdge).target()] = cost;
			//vecMSTcost_[(*outEdge).target()] = cost;
			//vecMBSTcost_[(*outEdge).target()] = (*outEdge).weight();
		}
	}
}

template<typename T>
void MBST<T>::min_spanning_tree(unsigned int source)
{
	SetVertexCost::iterator it;
	VertexCost vtxCost;
	// first remove the element corresponding to source from setVertexCost_
	vtxCost.vertex = source;
	vtxCost.cost = vecCost_[source]; //vecMSTcost_
	it = setVertexCost_.find(vtxCost);
	vecCost_[source] = 0;
	//vecMSTcost_[source] = 0;
	//vecMBSTcost_[source] = 0;
	setVertexCost_.erase(it);
	update_priority_queue(source);
	vecVisited_[source] = true;
	
	while (!setVertexCost_.empty())
	{
		it = setVertexCost_.begin();
		unsigned int vertex = (*it).vertex;
		setVertexCost_.erase(it);
		update_priority_queue(vertex);
		vecVisited_[vertex] = true;
	}
}

template<typename T>
T MBST<T>::get_bottleneck()
{
	T max_value = 0;

	//vecMBSTcost_
	for (unsigned int vtx_i = 0; vtx_i != vecCost_.size(); ++vtx_i)
	{
		if (max_value < vecCost_[vtx_i])
		{
			max_value = vecCost_[vtx_i];
		}
	}

	return max_value;
}

// ---------------------------------------------------
int main(int argc, char* argv[])
{
	unsigned int nFarm, nRoad;
	FILE* pFile = 0;

	//printf("%ld\n",std::numeric_limits<unsigned long>::max()/2 + 2);
	//printf("%lu\n",std::numeric_limits<unsigned long>::max()/2 + 2);
	
	if (READ_FROM_FILE)
	{
		pFile = fopen("d:/cpp_practise/online_judge/poj/2395_out_of_hay_input.txt","r");
	}

	if (READ_FROM_FILE)
	{
		fscanf(pFile,"%d",&nFarm);
		fscanf(pFile,"%d",&nRoad);
	} 
	else
	{
		scanf("%d",&nFarm);
		scanf("%d",&nRoad);
	}

	Graph<unsigned long> graph(nFarm);

	for (unsigned int road_i = 0; road_i != nRoad; ++road_i)
	{
		unsigned int farm1, farm2;
		unsigned long weight;

		if (READ_FROM_FILE)
		{
			fscanf(pFile,"%d",&farm1);
			fscanf(pFile,"%d",&farm2);
			fscanf(pFile,"%ld",&weight);
		} 
		else
		{
			scanf("%d",&farm1);
			scanf("%d",&farm2);
			scanf("%ld",&weight);
		}

		// 0 indexed
		graph.addEdge(farm1-1,farm2-1,weight);
		int gh = 0;
	}

	MBST<unsigned long> mbst(graph);
	unsigned int source = 0;
	mbst.min_spanning_tree(source);
	printf("%lu\n",mbst.get_bottleneck());

	return 0;
}
/*
http://cs.stackexchange.com/questions/2226/how-to-find-spanning-tree-of-a-graph-that-minimizes-the-maximum-edge-weight
http://algs4.cs.princeton.edu/43mst/  (web exercise #1)

http://stackoverflow.com/questions/9209323/easiest-way-of-using-min-priority-queue-with-key-update-in-c
Discusses alternate of heap based priority queue implementation.

http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=standardTemplateLibrary2#dijkstra3
Dijkstra via set

Following people populate priority queue one by one instead of putting all the V-X elements as taught by
RoughGarden as well as mentioned in wiki page of Dijkstra's algo.
TBD: check if this method is also correct.
http://zobayer.blogspot.in/2009/12/dijkstras-algorithm-in-c.html
http://codeclassics.blogspot.in/2012/12/dijkstras-algorithm-in-c-using-stl.html

Facing issue similar to mine.
http://stackoverflow.com/questions/1482397/delete-element-from-priority-queue-in-c-stl
http://forums.codeguru.com/showthread.php?518967-Priority-Queue-Decrease-Function

http://www.geeksforgeeks.org/greedy-algorithms-set-5-prims-minimum-spanning-tree-mst-2/
tried with Test cases taken from here.

*/