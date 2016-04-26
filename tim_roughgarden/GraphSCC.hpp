#ifndef Graph_SCC_HPP
#define Graph_SCC_HPP

#include <iostream>
#include <algorithm>
#include <cassert>
#include <map>
#include <set>
#include <vector>

namespace ds
{
	template<typename T>
	class Graph
	{
	public:
		Graph();
		~Graph();
	public:
		//TBD: change to const T&
		void add_vertex(T vertex);
		void add_edge(T vertex1, T vertex2);
		std::size_t nVertex();
		std::vector<T> vertices();
		std::set<T> adjacentVertices(T vertex);
		bool isExplored(T vertex);
		void setExplored(T vertex);
	private:
		std::map<T,std::set<T>> graph_container_;
		std::vector<int> vecExplored_; //bool
		std::size_t nVertex_;
		std::vector<T> vecVertex_;
	};

	template<typename T>
	Graph<T>::Graph()
	{
		nVertex_ = 0;
	}

	template<typename T>
	Graph<T>::~Graph()
	{
		//TBD
	}

	template<typename T>
	void Graph<T>::add_vertex(T vertex)
	{
		std::set<T> adjacentVertices;
		graph_container_.insert(std::pair<T,std::set<T>>(vertex,adjacentVertices) );
		vecExplored_.push_back(0);
		++nVertex_;
		vecVertex_.push_back(vertex);
	}

	template<typename T>
	void Graph<T>::add_edge(T vertex1, T vertex2)
	{
		std::map<T,std::set<T>>::iterator it = graph_container_.find(vertex1);
		std::set<T>& adjacentVertices = (*it).second;
		adjacentVertices.insert(vertex2);
	}

	template<typename T>
	std::size_t Graph<T>::nVertex()
	{
		return nVertex_;
	}

	template<typename T>
	std::vector<T> Graph<T>::vertices()
	{
		return vecVertex_;
	}

	template<typename T>
	std::set<T> Graph<T>::adjacentVertices(T vertex)
	{
		std::map<T,std::set<T>>::iterator it = graph_container_.find(vertex);
		std::set<T> adjacentVertices = (*it).second;
		return adjacentVertices;
	}

	template<typename T>
	bool Graph<T>::isExplored(T vertex)
	{
		std::vector<T>::iterator it = std::find(vecVertex_.begin(),vecVertex_.end(), vertex);
		//std::vector<T>::iterator it = vecVertex_.find(vertex);
		return vecExplored_[std::distance(vecVertex_.begin(),it)] == 1;
	}

	template<typename T>
	void Graph<T>::setExplored(T vertex)
	{
		std::vector<T>::iterator it = std::find(vecVertex_.begin(),vecVertex_.end(), vertex);
		//std::vector<T>::iterator it = vecVertex_.find(vertex);
		vecExplored_[std::distance(vecVertex_.begin(),it)] = 1;
	}
}

#endif