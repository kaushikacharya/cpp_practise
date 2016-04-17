// http://www.spoj.com/problems/TDBFS/
#include <cstdio>
#include <vector>
#include <stack>
#include <queue>

template<typename T>
class Graph
{
public:
	Graph(T nVertex);
	~Graph();
public:
	void add_edge(T source, T target);
public:
	T nVertex() const;
	const std::vector<T>& adjacentVertices(T srcVertex) const;
private:
	T nVertex_;
	std::vector<std::vector<T> > adjList_;
};
// -----
template<typename T>
class BFS
{
public:
	BFS(Graph<T> graph);
	~BFS();
public:
	void traversal(T srcVertex, std::vector<T>& vecOutputSeq);
private:
	Graph<T> graph_;
	std::vector<bool> vecVisited_;
};
// -----
template<typename T>
class DFS
{
public:
	DFS(Graph<T> graph);
	~DFS();
public:
	void traversal(T srcVertex, std::vector<T>& vecOutputSeq);
private:
	Graph<T> graph_;
	std::vector<bool> vecVisited_;
};
// ----
template<typename T>
Graph<T>::Graph(T nVertex)
: nVertex_(nVertex)
{
	adjList_.reserve(nVertex_);
	for (T vtx_i = 0; vtx_i != nVertex_; ++vtx_i)
	{
		adjList_.push_back(std::vector<T>());
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
T Graph<T>::nVertex() const
{
	return nVertex_;
}
template<typename T>
const std::vector<T>& Graph<T>::adjacentVertices(T srcVertex) const
{
	return adjList_[srcVertex];
}
// ------
template<typename T>
BFS<T>::BFS(Graph<T> graph)
: graph_(graph)
{
	T nVertex = graph_.nVertex();
	vecVisited_.reserve(nVertex);
	for (T vtx_i = 0; vtx_i != nVertex; ++vtx_i)
	{
		vecVisited_.push_back(false);
	}
}
template<typename T>
BFS<T>::~BFS()
{}
template<typename T>
void BFS<T>::traversal(T srcVertex, std::vector<T>& vecOutputSeq)
{
	vecOutputSeq.reserve(graph_.nVertex());
	std::queue<T> queueVtx;
	queueVtx.push(srcVertex);
	vecVisited_[srcVertex] = true;

	while (!queueVtx.empty())
	{
		T frontQueueVtx = queueVtx.front();
		vecOutputSeq.push_back(frontQueueVtx);
		//vecVisited_[frontQueueVtx] = true;
		queueVtx.pop();
		const std::vector<T> adjVertices = graph_.adjacentVertices(frontQueueVtx);
		for (typename std::vector<T>::const_iterator adjIt = adjVertices.begin(); adjIt != adjVertices.end(); ++adjIt)
		{
			if (!vecVisited_[(*adjIt)])
			{
				queueVtx.push((*adjIt));
				vecVisited_[(*adjIt)] = true;
			}
		}
	}
}
// ------
template<typename T>
DFS<T>::DFS(Graph<T> graph)
: graph_(graph)
{
	T nVertex = graph_.nVertex();
	vecVisited_.reserve(nVertex);
	for (T vtx_i = 0; vtx_i != nVertex; ++vtx_i)
	{
		vecVisited_.push_back(false);
	}
}
template<typename T>
DFS<T>::~DFS()
{}
template<typename T>
void DFS<T>::traversal(T srcVertex, std::vector<T>& vecOutputSeq)
{
	vecOutputSeq.reserve(graph_.nVertex());
	std::stack<T> stackVtx;
	stackVtx.push(srcVertex);

	while (!stackVtx.empty())
	{
		T topVtx = stackVtx.top();
		stackVtx.pop();
		if (vecVisited_[topVtx])
		{
			continue;
		} 
		else
		{
			vecVisited_[topVtx] = true;
			vecOutputSeq.push_back(topVtx);
		}
		const std::vector<T> adjVertices = graph_.adjacentVertices(topVtx);
		for (typename std::vector<T>::const_reverse_iterator adjIt = adjVertices.rbegin(); adjIt != adjVertices.rend(); ++adjIt)
		{
			if (!vecVisited_[(*adjIt)])
			{
				stackVtx.push((*adjIt));
			}
		}
	}
}
// -----
void read_process_graph(FILE* pFile)
{
	typedef unsigned int DataType;
	DataType nVertex;
	scanf("%u",&nVertex);
	Graph<DataType> graph(nVertex);

	// read the adjacency list and populate the graph
	DataType srcVertex, tgtVertex;
	DataType adjVtxCount;
	for (DataType vertex_i = 0; vertex_i != nVertex; ++vertex_i)
	{
		scanf("%u",&srcVertex);
		--srcVertex;
		scanf("%u",&adjVtxCount);

		for (DataType adj_i = 0; adj_i != adjVtxCount; ++adj_i)
		{
			scanf("%u",&tgtVertex);
			--tgtVertex;
			graph.add_edge(srcVertex,tgtVertex);
		}
	}

	// Now read the test cases and do traversal
	unsigned int traversalType;
	while (true)
	{
		scanf("%u",&srcVertex);
		scanf("%u",&traversalType);

		if (srcVertex == 0)
		{
			break;
		}
		else
		{
			--srcVertex;
			std::vector<DataType> vecOutputSeq;
			if (traversalType == 1)
			{
				BFS<DataType> bfs(graph);
				bfs.traversal(srcVertex,vecOutputSeq);
			}
			else
			{
				DFS<DataType> dfs(graph);
				dfs.traversal(srcVertex,vecOutputSeq);
			}
			
			// print the traversal sequence
			printf("%u",vecOutputSeq[0]+1);
			for (std::vector<DataType>::iterator it = vecOutputSeq.begin()+1; it != vecOutputSeq.end(); ++it)
			{
				printf(" %u",(*it)+1);
			}
			printf("\n");
		}
	}
}
// ----
int main(int argc, char* argv[])
{
	FILE* pFile = 0;
	unsigned int nGraph;
	scanf("%u",&nGraph);
	for (unsigned int graph_i = 0; graph_i != nGraph; ++graph_i)
	{
		printf("graph %u\n",graph_i+1);
		read_process_graph(pFile);
	}
	return 0;
}