#ifndef Graph_Impl1_HPP
#define Graph_Impl1_HPP

#include "AdjListImpl1.hpp"
#include <cassert>
#include <cstdlib>

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
		//bool explored(T vtx);
		bool explored(int pos);
		void setExplored(int pos);
		std::vector<T>& vertices();
		std::vector<T>& adjacencyList(int pos);
	private:
		std::vector<T> vecVertices_;
		std::vector<AdjList<T> > vecAdjList_;
		//std::vector<bool> vecExplored_;
        std::vector<int> vecExplored_;
	};

	template<typename T>
	Graph<T>::Graph(std::vector<T>& vecVertices)
		: vecVertices_(vecVertices)
	{
		vecExplored_.reserve(vecVertices.size());
		vecAdjList_.reserve(vecVertices.size());
		//initialize empty adjacent list
		for (int i = 0; i < vecVertices.size(); ++i)
		{
			AdjList<T> newAdjList;
			vecAdjList_.push_back(newAdjList);
			//initialize explored flag as false for every vertex
			//vecExplored_.push_back(false);
            vecExplored_.push_back(0);
		}
	}

	template<typename T>
	Graph<T>::~Graph()
	{
		//TBD
	}

	template<typename T>
	void Graph<T>::addEdge(T src, T tgt)
	{
		/* commenting out the search
		std::vector<T>::iterator it = std::find(vecVertices_.begin(), vecVertices_.end(), src);
		int pos = std::distance(vecVertices_.begin(), it);
*/
        assert(src>0 && "src should be > 0");
		int pos = src-1;
		(vecAdjList_[pos]).addElement(tgt);
	}
/*
	template<typename T>
	bool Graph<T>::explored(T vtx)
	{
		std::vector<T>::iterator it = std::find(vecVertices_.begin(), vecVertices_.end(), vtx);
		int pos = std::distance(vecVertices_.begin(), it);

		return vecExplored_[pos];
	}
*/
	template<typename T>
	bool Graph<T>::explored(int pos)
	{
		return vecExplored_[pos] == 1;
	}

	template<typename T>
	void Graph<T>::setExplored(int pos)
	{
        assert(pos < vecExplored_.size() && "invalid pos");
		vecExplored_[pos] = 1; //true
	}

	template<typename T>
	std::vector<T>& Graph<T>::vertices()
	{
		return vecVertices_;
	}

	template<typename T>
	std::vector<T>& Graph<T>::adjacencyList(int pos)
	{
		return vecAdjList_[pos].adjacency_list();
	}
}

#endif