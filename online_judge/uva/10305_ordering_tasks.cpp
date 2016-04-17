#include <vector>
#include <fstream>
#include <iostream>
#include <list>

const bool READ_FROM_FILE = false;

template<typename T>
class Graph
{
public:
	Graph(T nNode);
	~Graph();
public:
	void add_edge(T source, T target);
	void topological_sort();
	void display_topological_order();
private:
	void dfs_recursive(T node);
private:
	T nNode_;
	std::vector<std::vector<T> > adjList_;
private:
	std::vector<bool> vecVisited_;
	std::list<T> topologicalList_;
};

template<typename T>
Graph<T>::Graph(T nNode)
: nNode_(nNode)
{
	adjList_.reserve(nNode_);
	vecVisited_.reserve(nNode_);
	for (T node_i = 0; node_i != nNode_; ++ node_i)
	{
		adjList_.push_back(std::vector<T>());
		vecVisited_.push_back(false);
	}
}

template<typename T>
Graph<T>::~Graph()
{}

template<typename T>
void Graph<T>::add_edge(T source, T target)
{
	adjList_[source].push_back(target);
}

template<typename T>
void Graph<T>::topological_sort()
{
	for (std::vector<bool>::iterator it = vecVisited_.begin(); it != vecVisited_.end(); ++it)
	{
		if (!(*it))
		{
			dfs_recursive(std::distance(vecVisited_.begin(),it));
		}
	}
}

template<typename T>
void Graph<T>::dfs_recursive(T node)
{
	if (vecVisited_[node])
	{
		return;
	}
	for (typename std::vector<T>::iterator adjIt = adjList_[node].begin(); adjIt != adjList_[node].end(); ++ adjIt)
	{
		if (!vecVisited_[*adjIt])
		{
			dfs_recursive(*adjIt);
		}
	}

	vecVisited_[node] = true;
	topologicalList_.push_front(node);
}

template<typename T>
void Graph<T>::display_topological_order()
{
	for (typename std::list<T>::iterator it = topologicalList_.begin(); it != topologicalList_.end(); ++it)
	{
		if (it == topologicalList_.begin())
		{
			std::cout << (*it)+1;
		} 
		else
		{
			std::cout << " " << (*it)+1;
		}
	}
	std::cout << std::endl;
}

int main(int argc, char* argv[])
{
	// n - no. of tasks
	// m - no. of precedence conditions
	unsigned int n, m;
	std::ifstream pFile;

	if (READ_FROM_FILE)
	{
		pFile.open("D:/cpp_practise/online_judge/uva/10305_ordering_tasks_input.txt",std::ios::in);
	}

	while (true)
	{
		if (READ_FROM_FILE)
		{
			pFile >> n >> m;
		} 
		else
		{
			std::cin >> n >> m;
		}

		if (n == 0 && m == 0)
		{
			break;
		}
		else
		{
			Graph<unsigned int> graph(n);
			// read the precedence conditions one by one
			for (unsigned int cond_i = 0; cond_i != m; ++cond_i)
			{
				unsigned int task_i, task_j;
				if (READ_FROM_FILE)
				{
					pFile >> task_i >> task_j;
				} 
				else
				{
					std::cin >> task_i >> task_j;
				}
				graph.add_edge(task_i-1,task_j-1);
			}
			graph.topological_sort();
			graph.display_topological_order();
			int gh = 0;
		}
	}

	if (READ_FROM_FILE)
	{
		pFile.close();
	}
}