// http://codeforces.com/problemset/problem/161/D
#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>

#define READ_FROM_FILE 0

typedef unsigned long long DType;
using namespace std;

template<typename T>
class Graph
{
public:
	Graph(T nVertex, T kDist);
	~Graph();
public:
	void read_edges(FILE* pFile);
	void bfs(T root);
	T compute_distance(T root);
private:
	vector<T> adjacentVertices(T vtx);
private:
	T nVertex_;
	T kDist_;
	//2-dim matrix stored in 1-dim. row represents vertex
	vector<T> vecDistMat_; // represents the count along a sub-tree
	vector<T> vecDistAcrossSubTree_; // represents the count of kDist_ across sub-trees
	vector<bool> vecVisited_;
	vector<vector<T> > adjList_;
	vector<T> vecParent_;
	vector<T> vecVtxBFS_;
};
//---
template<typename T>
Graph<T>::Graph(T nVertex, T kDist)
: nVertex_(nVertex)
, kDist_(kDist)
{
	T nCount = nVertex_*(kDist_+1);
	vecDistMat_.reserve(nCount);
	for (T pos_i = 0; pos_i != nCount; ++pos_i)
	{
		vecDistMat_.push_back(0);
	}
	for (T vtx_i = 0; vtx_i != nVertex_; ++vtx_i)
	{
		vecDistMat_[vtx_i*(kDist_+1)] = 1;
	}
	vecVisited_.reserve(nVertex_);
	adjList_.reserve(nVertex_);
	vecParent_.reserve(nVertex_);
	vecDistAcrossSubTree_.reserve(nVertex_);
	for (T pos_i = 0; pos_i != nVertex_; ++pos_i)
	{
		vecVisited_.push_back(false);
		adjList_.push_back(vector<T>());
		vecParent_.push_back(pos_i); //initialized as self
		vecDistAcrossSubTree_.push_back(0);
	}
}
template<typename T>
Graph<T>::~Graph()
{}
template<typename T>
void Graph<T>::read_edges(FILE* pFile)
{
	T srcVertex, tgtVertex;
	for (T edge_i = 0; edge_i != (nVertex_-1); ++edge_i)
	{
		if (READ_FROM_FILE)
		{
			fscanf(pFile,"%I64u",&srcVertex);
			fscanf(pFile,"%I64u",&tgtVertex);
		} 
		else
		{
			scanf("%I64u",&srcVertex);
			scanf("%I64u",&tgtVertex);
		}
		--srcVertex;
		--tgtVertex;
		adjList_[srcVertex].push_back(tgtVertex);
		adjList_[tgtVertex].push_back(srcVertex);
	}
}
template<typename T>
vector<T> Graph<T>::adjacentVertices(T vtx)
{
	return adjList_[vtx];
}
template<typename T>
void Graph<T>::bfs(T root)
{
	queue<T> queueVtx;
	queueVtx.push(root);

	vecVtxBFS_.reserve(nVertex_);
	T frontVtx;
	while(!queueVtx.empty())
	{
		frontVtx = queueVtx.front();
		vecVtxBFS_.push_back(frontVtx);
		queueVtx.pop();
		vecVisited_[frontVtx] = true;

		vector<T> adjVertices = adjacentVertices(frontVtx);
		for (vector<T>::iterator adjIt = adjVertices.begin(); adjIt != adjVertices.end(); ++adjIt)
		{
			T adjVtx = (*adjIt);
			if (!vecVisited_[adjVtx])
			{
				vecParent_[adjVtx] = frontVtx;
				queueVtx.push(adjVtx);
			}
		}
	}
}
template<typename T>
T Graph<T>::compute_distance(T root)
{
	for (vector<T>::reverse_iterator it = vecVtxBFS_.rbegin(); it != vecVtxBFS_.rend(); ++it)
	{
		T subTreeRoot = (*it);
		vector<T> adjVertices = adjacentVertices(subTreeRoot);
		
		for (vector<T>::iterator adjIt = adjVertices.begin(); adjIt != adjVertices.end(); ++ adjIt)
		{
			T adjVertex = (*adjIt);
			if (adjVertex == vecParent_[subTreeRoot])
			{
				continue;
			}
			for (T dist = 1; dist != (kDist_+1); ++dist)
			{
				vecDistMat_[subTreeRoot*(kDist_+1) + dist] += vecDistMat_[adjVertex*(kDist_+1) + dist-1];
			}
		}

		T countKDistAcrossSubTrees = 0;
		for (vector<T>::iterator adjIt = adjVertices.begin(); adjIt != adjVertices.end(); ++ adjIt)
		{
			T adjVertex = (*adjIt);
			if (adjVertex == vecParent_[subTreeRoot])
			{
				continue;
			}
			for (T dist = 0; dist != (kDist_-1); ++dist)
			{
				countKDistAcrossSubTrees += vecDistMat_[adjVertex*(kDist_+1)+dist]*( vecDistMat_[subTreeRoot*(kDist_+1)+(kDist_-dist-1)] - vecDistMat_[adjVertex*(kDist_+1)+(kDist_-dist-2)] );
			}
		}

		vecDistAcrossSubTree_[subTreeRoot] = countKDistAcrossSubTrees/2;
	}

	T distinctPairsKDist = 0;
	for (T vtx_i = 0; vtx_i != nVertex_; ++vtx_i)
	{
		distinctPairsKDist += vecDistMat_[vtx_i*(kDist_+1)+kDist_];
		distinctPairsKDist += vecDistAcrossSubTree_[vtx_i];
	}

	return distinctPairsKDist;
}
//---
int main(int argc, char* argv[])
{
	DType nVertex, kDist;
	FILE* pFile = 0;
	if (READ_FROM_FILE)
	{
		pFile = fopen("D:/cpp_practise/online_judge/codeforces/161d_distance_in_tree_input.txt","r");
		fscanf(pFile,"%I64u",&nVertex);
		fscanf(pFile,"%I64u",&kDist);
	}
	else
	{
		scanf("%I64u",&nVertex);
		scanf("%I64u",&kDist);
	}
	Graph<DType> graph(nVertex,kDist);
	graph.read_edges(pFile);
	DType rootVtx = 0;
	graph.bfs(rootVtx);
	printf("%I64u\n",graph.compute_distance(rootVtx));
	return 0;
}