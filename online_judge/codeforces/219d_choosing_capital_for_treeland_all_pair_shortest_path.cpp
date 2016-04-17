// http://codeforces.com/problemset/problem/219/D
#include <cstdio>
#include <vector>
#include <set>
#include <limits>
#include <cassert>

#define READ_FROM_FILE 0

// http://www.cplusplus.com/forum/general/30626/
template<typename T1, typename T2>
class Edge
{
public:
	Edge(T1 source, T1 target, T2 weight);
	~Edge();
public:
	T1 source();
	T1 target();
	T2 weight();
private:
	T1 source_;
	T1 target_;
	T2 weight_;
};
// ----------------------------------------
template<typename T1, typename T2>
class Graph
{
public:
	Graph(T1 nVertex);
	~Graph();
public:
	T1 nVertex();
	void add_edge(T1 source, T1 target, T2 weight);
	std::vector<Edge<T1,T2>> outEdges(T1 vertex);
private:
	T1 nVertex_; //vertices indexed [0,1,...,(nVertex_-1)]
	std::vector<std::vector<Edge<T1,T2> > > adjacencyList_;
};
// ----------------------------------------
template<typename T1, typename T2>
class Prim
{
public:
	Prim(Graph<T1,T2> graph);
	~Prim();
public:
	void compute_shortest_paths();
private:
	T2 min_spanning_tree(T1 source);
private:
	Graph<T1,T2> graph_;
private:
	struct KeyVal
	{
		T1 key; // vertex
		T2 val; // score
		// http://stackoverflow.com/questions/9145822/struct-constructor-sytax
		KeyVal(T1 k, T2 v)
			: key(k)
			, val(v)
		{
		}
	};

	struct Comp
	{
		bool operator()(const KeyVal kv1, const KeyVal kv2)
		{
			if (kv1.val == kv2.val)
			{
				return kv1.key < kv2.key;
			}
			else
			{
				return kv1.val < kv2.val;
			}
		}
	};

	typedef std::set<KeyVal,Comp> SetKeyVal;

	std::vector<bool> vecVisited_;
	std::vector<T2> vecVal_;
};
// ----------------------------------------
template<typename T1, typename T2>
Edge<T1,T2>::Edge(T1 source, T1 target, T2 weight)
: source_(source)
, target_(target)
, weight_(weight)
{
}

template<typename T1, typename T2>
Edge<T1,T2>::~Edge()
{
	int gh = 0;
}

template<typename T1, typename T2>
T1 Edge<T1,T2>::source()
{
	return source_;
}

template<typename T1, typename T2>
T1 Edge<T1,T2>::target()
{
	return target_;
}

template<typename T1, typename T2>
T2 Edge<T1,T2>::weight()
{
	return weight_;
}
// ----------------------------------------
template<typename T1, typename T2>
Graph<T1,T2>::Graph(T1 nVertex)
: nVertex_(nVertex)
{
	adjacencyList_.reserve(nVertex);

	for (T1 i = 0; i != nVertex; ++i)
	{
		adjacencyList_.push_back(std::vector<Edge<T1,T2> >());
	}
}

template<typename T1, typename T2>
Graph<T1,T2>::~Graph()
{
	int gh = 0;
}

template<typename T1, typename T2>
T1 Graph<T1,T2>::nVertex()
{
	return nVertex_;
}

template<typename T1, typename T2>
void Graph<T1,T2>::add_edge(T1 source, T1 target, T2 weight)
{
	Edge<T1,T2> edge(source,target,weight);
	adjacencyList_[source].push_back(edge);
}

template<typename T1, typename T2>
std::vector<Edge<T1,T2>> Graph<T1,T2>::outEdges(T1 vertex)
{
	return adjacencyList_[vertex];
}
// ----------------------------------------
template<typename T1, typename T2>
Prim<T1,T2>::Prim(Graph<T1,T2> graph)
: graph_(graph)
{
	vecVisited_.reserve(graph_.nVertex());
	vecVal_.reserve(graph_.nVertex());
	for (T1 vertex=0; vertex != graph_.nVertex(); ++vertex)
	{
		vecVisited_.push_back(false);
		vecVal_.push_back(std::numeric_limits<T2>::max());
	}
}

template<typename T1, typename T2>
Prim<T1,T2>::~Prim()
{
	int gh = 0;
}

template<typename T1, typename T2>
void Prim<T1,T2>::compute_shortest_paths()
{
	SetKeyVal setShortestSourceCost;
	T2 cost;

	for(T1 vertex=0; vertex != graph_.nVertex(); ++vertex)
	{
		cost = min_spanning_tree(vertex);
		KeyVal keyCost(vertex,cost);
		setShortestSourceCost.insert(keyCost);
	}

	SetKeyVal::iterator it = setShortestSourceCost.begin();
	KeyVal minKeyCost = (*it);
	printf("%lu\n",minKeyCost.val);

	for (;it != setShortestSourceCost.end(); ++it)
	{
		KeyVal keyCost = (*it);
		if (keyCost.val != minKeyCost.val)
		{
			break;
		}
		else
		{
			printf("%lu ",keyCost.key+1); //vertices were 0 indexed
		}
	}

	int gh = 0;
}

template<typename T1, typename T2>
T2 Prim<T1,T2>::min_spanning_tree(T1 source)
{
	SetKeyVal setKeyVal;

	// initialize: insert all elements in the set V-X
	for (T1 vertex=0; vertex != graph_.nVertex(); ++vertex)
	{
		T2 val = std::numeric_limits<T2>::max();
		if (vertex == source)
		{
			val = 0;
		}
		
		KeyVal keyVal(vertex, val);
		setKeyVal.insert(keyVal);
		// reset visited flag
		vecVisited_[vertex] = false;
		vecVal_[vertex] = val;
	}

	while (!setKeyVal.empty())
	{
		SetKeyVal::iterator beginIt = setKeyVal.begin();
		T1 curVertex = (*beginIt).key;
		vecVisited_[curVertex] = true;
		setKeyVal.erase(beginIt);

		// update val of the neighboring vertices
		std::vector<Edge<T1,T2>> vecOutEdges = graph_.outEdges(curVertex);
		for (std::vector<Edge<T1,T2>>::iterator edgeIt = vecOutEdges.begin(); edgeIt != vecOutEdges.end(); ++edgeIt)
		{
			T1 nextVertex = (*edgeIt).target();
			if (vecVisited_[nextVertex])
			{
				continue;
			}
			// If not visited, check if we need to update its val
			T2 weight = (*edgeIt).weight();
			if (weight < vecVal_[nextVertex])
			{
				//as an alternate to update we remove and insert back with updated weight
				SetKeyVal::iterator it = setKeyVal.find(KeyVal(nextVertex,vecVal_[nextVertex]));
				assert((it != setKeyVal.end()) && "element not present in set");
				setKeyVal.erase(it);
				setKeyVal.insert(KeyVal(nextVertex,weight));
				vecVal_[nextVertex] = weight;
			}
		}
	}

	// http://stackoverflow.com/questions/3221812/sum-of-elements-in-a-stdvector
	T2 sumVal = 0;
	for (std::vector<T2>::iterator valIt = vecVal_.begin(); valIt != vecVal_.end(); ++valIt)
	{
		sumVal += (*valIt);
	}

	return sumVal;
}
// ----------------------------------------
void process(FILE* pFile, unsigned long nCities)
{
	typedef unsigned long VertexType;
	typedef unsigned long WeightType;

	// according to the problem, there are (nCities-1) roads
	Graph<VertexType,WeightType> graph(nCities);

	// read the edges
	VertexType sourceCity, targetCity;
	for (VertexType edge_i = 1; edge_i != nCities; ++edge_i)
	{
		if (READ_FROM_FILE)
		{
			fscanf(pFile,"%lu",&sourceCity);
			fscanf(pFile,"%lu",&targetCity);
		}
		else
		{
			scanf("%lu",&sourceCity);
			scanf("%lu",&targetCity);
		}

		// vertices are indexed starting with 0
		--sourceCity;
		--targetCity;

		graph.add_edge(sourceCity,targetCity,0);
		graph.add_edge(targetCity,sourceCity,1); // assigning weight 1 to change the direction of road
	}

	Prim<VertexType,WeightType> prim(graph);
	prim.compute_shortest_paths();

	int gh = 0;
}
// ----------------------------------------
int main(int argc, char* argv[])
{
	unsigned long nCities;
	FILE* pFile = 0;

	if (READ_FROM_FILE)
	{
		pFile = fopen("D:/cpp_practise/online_judge/codeforces/219d_choosing_capital_for_treeland_input.txt","r");
		fscanf(pFile,"%lu",&nCities);
	} 
	else
	{
		scanf("%lu",&nCities);
	}

	process(pFile,nCities);

	return 0;
}

/*
http://en.cppreference.com/w/cpp/language/initializer_list
*/