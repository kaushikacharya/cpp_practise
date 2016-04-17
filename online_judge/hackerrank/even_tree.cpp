// https://www.hackerrank.com/challenges/even-tree
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

#define READ_FROM_FILE 0

template<typename T>
class Graph
{
public:
	Graph(T nVertex, T nEdge);
	~Graph();
public:
	void read_input(std::fstream& pFile);
	T process_forest();
private:
	T nVertex_;
	T nEdge_;
	std::vector<std::vector<T> > adjacencyList_;
private:
	std::vector<T> vecParent_;
	std::vector<T> vecSubtreeSize_;
	std::vector<bool> vecVisited_;
};
//---
template<typename T>
Graph<T>::Graph(T nVertex, T nEdge)
: nVertex_(nVertex)
, nEdge_(nEdge)
{
	adjacencyList_.reserve(nVertex_);
	vecParent_.reserve(nVertex_);
	vecSubtreeSize_.reserve(nVertex_);
	vecVisited_.reserve(nVertex_);

	for (T vtx_i = 0; vtx_i != nVertex_; ++vtx_i)
	{
		adjacencyList_.push_back(std::vector<T>());
		vecParent_.push_back(vtx_i); // dummy initialization
		vecSubtreeSize_.push_back(1); // at least the node will be there by default in its subtree
		// We are including the subtree root also.
		vecVisited_.push_back(false);
	}
}
template<typename T>
Graph<T>::~Graph()
{}
template<typename T>
void Graph<T>::read_input(std::fstream& pFile)
{
	T vtx1, vtx2;
	for (T edge_i = 0; edge_i != nEdge_; ++edge_i)
	{
		if (READ_FROM_FILE)
		{
			pFile >> vtx1 >> vtx2;
		} 
		else
		{
			std::cin >> vtx1 >> vtx2;
		}
		adjacencyList_[vtx1-1].push_back(vtx2-1);
		adjacencyList_[vtx2-1].push_back(vtx1-1);
	}
}
template<typename T>
T Graph<T>::process_forest()
{
	// we can consider any node as the root of the tree
	T root = 0;
	// do BFS traversal:
	//		Keep identifying the parent as we do the traversal
	std::vector<T> vecNodes;
	vecNodes.reserve(nVertex_);
	std::queue<T> queueNodes;
	queueNodes.push(root);
	
	while (!queueNodes.empty())
	{
		T frontNode = queueNodes.front();
		queueNodes.pop();

		if (vecVisited_[frontNode])
		{
			continue;
		}
		vecVisited_[frontNode] = true;
		vecNodes.push_back(frontNode);

		for (typename std::vector<T>::iterator adjIt = adjacencyList_[frontNode].begin(); adjIt != adjacencyList_[frontNode].end(); ++adjIt)
		{
			if (vecVisited_[*adjIt])
			{
				continue;
			}
			queueNodes.push(*adjIt);
			vecParent_[*adjIt] = frontNode;
		}
	}

	for (typename std::vector<T>::reverse_iterator rit = vecNodes.rbegin(); rit != vecNodes.rend(); ++rit)
	{
		T curNode = *rit;
		T parentNode = vecParent_[curNode];
		
		if (curNode != parentNode)
		{
			vecSubtreeSize_[parentNode] += vecSubtreeSize_[curNode];
		}
	}

	T count_even = 0;
	for (typename std::vector<T>::iterator it = vecSubtreeSize_.begin(); it != vecSubtreeSize_.end(); ++it)
	{
		if (std::distance(vecSubtreeSize_.begin(),it) != root)
		{
			if ((*it)%2 == 0)
			{
				++count_even;
			}
		}
	}

	return count_even;
}
//---
int main(int argc, char* argv[])
{
	unsigned int N,M;
	std::fstream pFile;

	if (READ_FROM_FILE)
	{
		pFile.open("D:/cpp_practise/online_judge/hackerrank/even_tree_input.txt", std::ios::in);
		pFile >> N >> M;
	}
	else
	{
		std::cin >> N >> M;
	}

	Graph<unsigned int> graph(N,M);
	graph.read_input(pFile);
	
	if (READ_FROM_FILE)
	{
		pFile.close();
	}

	std::cout << graph.process_forest() << std::endl;
	return 0;
}

/*
Reading integers from file
http://www.cplusplus.com/forum/beginner/70136/
*/