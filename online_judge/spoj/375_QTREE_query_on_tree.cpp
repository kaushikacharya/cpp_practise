#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <stack>
#include <limits>
#include <string>
#include <cstring>
#include <cassert>

#define READ_FROM_FILE 1

template<typename T, typename C>
class Edge
{
public:
	Edge(T node1, T node2, C cost);
	~Edge();
public:
	C cost();
	T adjacent_vertex(T node); //return the other vertex of this edge
	void update_cost(C cost);
private:
	T node1_;
	T node2_;
	C cost_;
};
//---
template<typename T, typename C>
class Graph
{
public:
	Graph(T nVertex);
	~Graph();
public:
	void add_edge(T node1, T node2, C cost);
	void traversal(T srcNode, T tgtNode);
	C max_cost_in_path(T srcNode, T tgtNode);
	void update_edge_cost(T edge_index, C cost);
private:
	void reset_tree();
private:
	T nVertex_;
	std::vector<T> vecVertex_;
	std::vector<Edge<T,C> > vecEdge_;
	std::vector<std::vector<T> > adjList_;
private:
	std::vector<bool> vecVisited_;
	std::vector<T> vecParent_; //set it to self for vertices whose parent hasn't been identified yet
};
//---
template<typename T, typename C>
Edge<T,C>::Edge(T node1, T node2, C cost)
: node1_(node1)
, node2_(node2)
, cost_(cost)
{}
template<typename T, typename C>
Edge<T,C>::~Edge()
{}
template<typename T, typename C>
C Edge<T,C>::cost()
{
	return cost_;
}
template<typename T, typename C>
T Edge<T,C>::adjacent_vertex(T node)
{
	if (node == node1_)
	{
		return node2_;
	}
	else if (node == node2_)
	{
		return node1_;
	} 
	else
	{
		assert(false && "node is not part of this edge");
	}
}
template<typename T, typename C>
void Edge<T,C>::update_cost(C cost)
{
	cost_ = cost;
}
//---
template<typename T, typename C>
Graph<T,C>::Graph(T nVertex)
: nVertex_(nVertex)
{
	vecVertex_.reserve(nVertex_);
	vecEdge_.reserve(nVertex_-1); //problem specific
	adjList_.reserve(nVertex_);
	vecVisited_.reserve(nVertex_);
	vecParent_.reserve(nVertex_);
	
	for (T vtx_i=0; vtx_i != nVertex_; ++vtx_i)
	{
		vecVertex_.push_back(vtx_i);
		adjList_.push_back(std::vector<T>());
		vecVisited_.push_back(false);
		vecParent_.push_back(vtx_i);
	}
}
template<typename T, typename C>
Graph<T,C>::~Graph()
{}
template<typename T, typename C>
void Graph<T,C>::add_edge(T node1, T node2, C cost)
{
	Edge<T,C> edge(node1,node2,cost);
	vecEdge_.push_back(edge);
	adjList_[node1].push_back(vecEdge_.size()-1);
	adjList_[node2].push_back(vecEdge_.size()-1);
}
template<typename T, typename C>
void Graph<T,C>::reset_tree()
{
	for (T vtx_i=0; vtx_i != nVertex_; ++vtx_i)
	{
		vecParent_[vtx_i] = vtx_i;
		vecVisited_[vtx_i] = false;
	}
}
template<typename T, typename C>
void Graph<T,C>::traversal(T srcNode, T tgtNode)
{
	//dfs
	(*this).reset_tree();
	std::stack<T> stk;
	stk.push(srcNode);
	while (!stk.empty())
	{
		T node = stk.top();
		stk.pop();

		if (vecVisited_[node])
		{
			continue;
		}
		else
		{
			vecVisited_[node] = true;
		}
		if (node == tgtNode)
		{
			break;
		}
		std::vector<T> vecEdge = adjList_[node];
		for (typename std::vector<T>::iterator edgeIt=vecEdge.begin(); edgeIt != vecEdge.end(); ++edgeIt)
		{
			Edge<T,C> edge = vecEdge_[(*edgeIt)];
			T adjNode = edge.adjacent_vertex(node);
			if (!vecVisited_[adjNode])
			{
				vecParent_[adjNode] = node;
				stk.push(adjNode);
			}
		}
	}
}
template<typename T, typename C>
C Graph<T,C>::max_cost_in_path(T srcNode, T tgtNode)
{
	C maxCost = std::numeric_limits<C>::min();
	T node = tgtNode;

	while (node != srcNode)
	{
		T parentNode = vecParent_[node];
		std::vector<T> vecEdge = adjList_[node];
		for (typename std::vector<T>::iterator edgeIt=vecEdge.begin(); edgeIt != vecEdge.end(); ++edgeIt)
		{
			Edge<T,C> edge = vecEdge_[(*edgeIt)];
			if (edge.adjacent_vertex(node) == parentNode)
			{
				if (maxCost < edge.cost())
				{
					maxCost = edge.cost();
				}
			}
		}
		node = parentNode;
	}
	return maxCost;
}
template<typename T, typename C>
void Graph<T,C>::update_edge_cost(T edge_index, C cost)
{
	vecEdge_[edge_index].update_cost(cost);
}
//---
// http://stackoverflow.com/questions/8425260/error-c2248-stdbasic-ios-elem-traitsbasic-ios-cannot-access-private
void process(std::ifstream& pFile)
{
	using namespace std;
	unsigned int nVertex,vtx1,vtx2,edge_i;
	long cost;

	if (READ_FROM_FILE)
	{
		pFile >> nVertex;
	} 
	else
	{
		cin >> nVertex;
	}
	Graph<unsigned int,long> graph(nVertex);
	for (edge_i=0; edge_i != (nVertex-1); ++edge_i)
	{
		if (READ_FROM_FILE)
		{
			pFile >> vtx1;
			pFile >> vtx2;
			pFile >> cost;
		}
		else
		{
			cin >> vtx1;
			cin >> vtx2;
			cin >> cost;
		}
		graph.add_edge(vtx1-1,vtx2-1,cost);
	}
	string str;
	while (true)
	{
		if (READ_FROM_FILE)
		{
			pFile >> str;
		}
		else
		{
			cin >> str;
		}
		if (strcmp(str.c_str(),"DONE") == 0)
		{
			break;
		} 
		else
		{
			if (strcmp(str.c_str(),"QUERY") == 0)
			{
				if (READ_FROM_FILE)
				{
					pFile >> vtx1;
					pFile >> vtx2;
				}
				else
				{
					cin >> vtx1;
					cin >> vtx2;
				}
				graph.traversal(vtx1-1,vtx2-1);
				printf("%ld\n",graph.max_cost_in_path(vtx1-1,vtx2-1));
			}
			else if (strcmp(str.c_str(),"CHANGE") == 0)
			{
				if (READ_FROM_FILE)
				{
					pFile >> edge_i;
					pFile >> cost;
				}
				else
				{
					cin >> edge_i;
					cin >> cost;
				}
				graph.update_edge_cost(edge_i-1,cost);
			} 
			else
			{
				assert(false && "wrong command");
			}
		}
	}
}
//---
int main(int argc, char* argv[])
{
	unsigned int nCase;
	std::ifstream pFile;

	if (READ_FROM_FILE)
	{
		pFile.open("D:/cpp_practise/online_judge/spoj/375_QTREE_query_on_tree_input.txt");
		pFile >> nCase;
	}
	else
	{
		std::cin >> nCase;
	}

	for (unsigned int case_i=0; case_i != nCase; ++case_i)
	{
		process(pFile);
	}
	return 0;
}