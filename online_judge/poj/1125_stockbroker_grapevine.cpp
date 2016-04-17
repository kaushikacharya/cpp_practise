// http://poj.org/problem?id=1125
#include <cstdio>
#include <vector>
#include <cassert>
#include <limits>
#include <algorithm>

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

template<typename T>
class Graph
{
public:
	Graph(unsigned int nVertex);
	~Graph();
public:
	void addAdjacentEdges(unsigned int vertex, std::vector<unsigned int>& vecAdjVertex, std::vector<T>& vecWeight);
	void getAdjacentVertices(unsigned int vertex, std::vector<unsigned int>& vecAdjVertex, std::vector<T>& vecAdjWeight);
	unsigned int nVertex();
private:
	unsigned int nVertex_;
	// http://www.cplusplus.com/forum/general/833/#msg2999
	// multi-dimension vector with different no of elements for each row
	std::vector<std::vector<Edge<T>*> > adjList_;
};

// Improvements needed:
//			Use priority class nested inside Dijkstra
template<typename T>
class Dijkstra
{
public:
	Dijkstra(Graph<T>& graph);
	~Dijkstra();
public:
	bool compute_shortest_path(unsigned int source);
	T maxCost();
private:
	Graph<T>& graph_;
	// at any point there are two groups: X, V-X
	// only nodes in V-X are put into priority queue
	// V-X represents the set of elements not yet selected
	std::vector<bool> vecVisited_; //true - particular node is in X i.e. already extracted from priority queue
	std::vector<T> vecCost_; // Here we store the final cost
	std::vector<T> vecKey_; // Here we store the intermediate cost
// priority queue members
private:
	bool update_priority_queue();
private:
	struct KeyVal
	{
		unsigned int key;
		T val;
	};
	//std::vector<KeyVal> priorityQueue_; //min-priority queue
	//unsigned int countPQ_;
	unsigned int minIndexPQ_;
	//T minVal_;
};
// --------------------------------
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
	int gh = 0;
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
// --------------------------------
template<typename T>
Graph<T>::Graph(unsigned int nVertex)
: nVertex_(nVertex)
{
	adjList_.reserve(nVertex);
	for (unsigned int i = 0; i < nVertex; ++i)
	{
		adjList_.push_back(std::vector<Edge<T>*>());
	}
}

template<typename T>
Graph<T>::~Graph()
{
	int gh = 0;
}

template<typename T>
void Graph<T>::addAdjacentEdges(unsigned int vertex, std::vector<unsigned int>& vecAdjVertex, std::vector<T>& vecWeight)
{
	// vertex is the source
	assert((vecAdjVertex.size() == vecWeight.size()) && "unequal vectors of adjacent vertices and weights");
	adjList_[vertex].reserve(vecAdjVertex.size());

	for (unsigned int i = 0; i < vecAdjVertex.size(); ++i)
	{
		Edge<T>* edge = new Edge<T>(vertex,vecAdjVertex[i],vecWeight[i]);
		adjList_[vertex].push_back(edge);
	}
}

template<typename T>
void Graph<T>::getAdjacentVertices(unsigned int vertex, std::vector<unsigned int>& vecAdjVertex, std::vector<T>& vecAdjWeight)
{
	vecAdjVertex.clear();
	vecAdjWeight.clear();

	std::vector<Edge<T>*> vecEdges = adjList_[vertex];
	for (std::vector<Edge<T>*>::iterator it = vecEdges.begin(); it != vecEdges.end(); ++it)
	{
		vecAdjVertex.push_back((**it).target());
		vecAdjWeight.push_back((**it).weight());
	}
}

template<typename T>
unsigned int Graph<T>::nVertex()
{
	return nVertex_;
}
// --------------------------------
template<typename T>
Dijkstra<T>::Dijkstra(Graph<T>& graph)
: graph_(graph)
{
	vecKey_.reserve(graph.nVertex());
	vecCost_.reserve(graph.nVertex());
	vecVisited_.reserve(graph.nVertex());
	
	//priorityQueue_.reserve(graph.nVertex());
	//countPQ_ = 0;
}

template<typename T>
Dijkstra<T>::~Dijkstra()
{
	int gh = 0;
}

template<typename T>
T Dijkstra<T>::maxCost()
{
	return *( std::max_element(vecCost_.begin(), vecCost_.end()) );
}

template<typename T>
bool Dijkstra<T>::compute_shortest_path(unsigned int source)
{
	// first empty the priority queue
	//countPQ_ = 0;
	//priorityQueue_.clear();

	vecKey_.clear();
	vecCost_.clear();
	vecVisited_.clear();

	for (unsigned int i = 0; i < graph_.nVertex(); ++i)
	{ 
		vecKey_.push_back(std::numeric_limits<T>::max());
		vecCost_.push_back(std::numeric_limits<T>::max());
		vecVisited_.push_back(false);
	}

	// initialize for the source
	vecKey_[source] = 0;
	//vecVisited_[source] = true;

	/*
	while(!priorityQueue_.empty()) // TBD: also take care if all nodes are not reachable from source
	{
	}
	*/
	bool flag;
	for (unsigned int i = 0; i < graph_.nVertex(); ++i)
	{
		flag = update_priority_queue();
		if (!flag)
		{
			break;
		}
	}

	return flag;
}

template<typename T>
bool Dijkstra<T>::update_priority_queue()
{
	bool flag = false;
	// extract min
	T minVal = std::numeric_limits<T>::max();
	for (unsigned int i = 0; i < graph_.nVertex(); ++i)
	{
		if (!vecVisited_[i])
		{
			if (vecKey_[i] < minVal)
			{
				flag = true;
				minVal = vecKey_[i];
				minIndexPQ_ = i;
			}
		}
	}

	if (!flag)
	{
		return flag; // rest of the nodes are not accessible
	}

	vecVisited_[minIndexPQ_] = true; // moving the element into X
	vecCost_[minIndexPQ_] = vecKey_[minIndexPQ_];

	//update the key value for the nodes which are adjacent to node[minIndexPQ_]
	std::vector<unsigned int> vecAdjVertex;
	std::vector<T> vecAdjWeight;
	graph_.getAdjacentVertices(minIndexPQ_,vecAdjVertex,vecAdjWeight);

	for (unsigned int i = 0; i != vecAdjVertex.size(); ++i)
	{
		KeyVal keyVal;
		keyVal.key = vecAdjVertex[i];
		keyVal.val = vecAdjWeight[i];

		if (!vecVisited_[keyVal.key])
		{
			T newVal = vecKey_[minIndexPQ_] + keyVal.val;
			if (newVal < vecKey_[keyVal.key])
			{
				vecKey_[keyVal.key] = newVal;
			}
		}
	}

	return flag;
}

// --------------------------------
int main(int argc, char* argv[])
{
	unsigned int nPerson;
	unsigned int nContact;
	unsigned int contactPerson;
	unsigned int weight;
	FILE* pFile = 0;
	
	if (READ_FROM_FILE)
	{
		pFile = fopen("D:/cpp_practise/online_judge/poj/south_african_regionals_2001/grapevine/input.txt","r");
		assert((pFile != NULL) && "File NOT opened");
	}

	while(true)
	{
		if (READ_FROM_FILE)
		{
			fscanf(pFile,"%d",&nPerson);
		}
		else
		{
			scanf("%d",&nPerson);
		}
		if (nPerson == 0)
		{
			break;
		}
		Graph<unsigned int> graph(nPerson);
		// read the input rows
		for (unsigned int person_i = 0; person_i < nPerson; ++person_i)
		{
			// read the adjacency list of current person
			if (READ_FROM_FILE)
			{
				fscanf(pFile,"%d",&nContact);
			}
			else
			{
				scanf("%d",&nContact);
			}
			std::vector<unsigned int> vecContact;
			std::vector<unsigned int> vecWeight;
			vecContact.reserve(nContact);
			vecWeight.reserve(nContact);
			for (unsigned int contact_i = 0; contact_i < nContact; ++contact_i)
			{
				if (READ_FROM_FILE)
				{
					fscanf(pFile,"%d",&contactPerson);
					fscanf(pFile,"%d",&weight);
				}
				else
				{
					scanf("%d",&contactPerson);
					scanf("%d",&weight);
				}
				vecContact.push_back(contactPerson-1); // program considers Person#1 with index 0
				vecWeight.push_back(weight);
			}
			graph.addAdjacentEdges(person_i,vecContact,vecWeight);
		}

		// For every vertex, compute Dijkstra's algo
		Dijkstra<unsigned int> dijkstra(graph);
		bool flag_traversed = false;
		unsigned int best_souce_person;
		unsigned int best_souce_maxCost = std::numeric_limits<unsigned int>::max();
		for (unsigned int person_i = 0; person_i < nPerson; ++person_i)
		{
			bool flag = dijkstra.compute_shortest_path(person_i);
			if (flag)
			{
				flag_traversed = true;
				unsigned int max_cost = dijkstra.maxCost();
				if (max_cost < best_souce_maxCost)
				{
					best_souce_maxCost = max_cost;
					best_souce_person = person_i;
				}
			}
			//int gh = 0;
		}

		if (flag_traversed)
		{
			printf("%d %d\n",best_souce_person+1,best_souce_maxCost);
		}
		else
		{
			printf("disjoint\n");
		}
		// -----
	}

	return 0;
}

/*
Algorithm complexity: O(V*(V^2 + E)) //priority queue is done using array based implementation
Alternatively this problem can be solved using Floyd-Warshall algorithm whose complexity is theta(V^3)

source: http://www.ntnu.edu.tw/acm/  (South African Regionals)
		http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_EU_SARC/2001/index.html

http://pages.cs.wisc.edu/~siff/CS367/Notes/pqueues.html
Array implementation of priority queue

http://algs4.cs.princeton.edu/24pq/

google search:  vector of vectors with different sizes c++

http://stackoverflow.com/questions/7585534/fill-template-of-one-class-from-another-template-class

TBD: Understand the concept of template template parameter in c++
http://stackoverflow.com/questions/213761/what-are-some-uses-of-template-template-parameters-in-c
*/