#ifndef Graph_HPP
#define Graph_HPP

#include "AdjList.hpp"
#include <algorithm>
#include <vector>

namespace ds
{
	template<typename T>
	class Graph
	{
	public:
		Graph(std::vector<T>& vecVertices);
		~Graph();
	public:
		void addEdge(T src, T tgt);
	private:
		std::vector<T> vecVertices_;
		std::vector<AdjList<T> > vecAdjList_;
	};

	template<typename T>
	Graph<T>::Graph(std::vector<T>& vecVertices)
		: vecVertices_(vecVertices)
	{
		vecAdjList_.reserve(vecVertices.size());
		for (std::size_t i = 0; i < vecVertices.size(); ++i)
		{
			AdjList<T> newAdjList;
			vecAdjList_.push_back(newAdjList);
		}

		//trial testing
		AdjListNode<T> tgtNode0 = AdjListNode<T>(5);
		(vecAdjList_[0]).addListNode(&tgtNode0);

		AdjListNode<T> tgtNode1 = AdjListNode<T>(3);
		(vecAdjList_[1]).addListNode(&tgtNode1);

		int gh = 0;
	}

	template<typename T>
	Graph<T>::~Graph()
	{
		//TBD
	}

	template<typename T>
	void Graph<T>::addEdge(T src, T tgt)
	{
		std::vector<T>::iterator it = std::find(vecVertices_.begin(), vecVertices_.end(), src);
		std::size_t pos = std::distance(vecVertices_.begin(), it);

		AdjListNode<T> tgtNode = AdjListNode<T>(tgt);
		(*(vecAdjList_.begin()+pos)).addListNode(&tgtNode);
		//(vecAdjList_[pos]).addListNode(&tgtNode);
	}
}

#endif