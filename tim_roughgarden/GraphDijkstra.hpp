#ifndef Graph_Dijkstra_HPP
#define Graph_Dijkstra_HPP

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
		void add_edge(T vertex1, T vertex2, T edge_weight);
		std::vector<std::pair<T,T> > adjacent_vertices_weight(T vertex);
		bool isProcessed(T vertex);
		void setProcessed(T vertex, T shortestPathDistance);
		T shortestPathDistance(T vertex);
		std::size_t count_vertices();
		std::vector<T> vertices();
	public:
		//utils for debugging
		//void print_adjacency_list();
	public:
		typedef std::vector<std::pair<T,T> > VecPair;
	private:
		//TBD: create an Edge class to store edge info
		std::map<T,std::vector<std::pair<T,T> > > graph_container_;
		std::vector<T> vecShortestPathDistance_;
		std::set<T> processedSet_;
	};

	template<typename T>
	Graph<T>::Graph()
	{
	}

	template<typename T>
	Graph<T>::~Graph()
	{
		//TBD
	}

	template<typename T>
	void Graph<T>::add_vertex(T vertex)
	{
		VecPair adjacentVerticesWeightVec;
		graph_container_.insert(std::pair<T,VecPair>(vertex,adjacentVerticesWeightVec) );
		vecShortestPathDistance_.push_back(1000000);
	}

	template<typename T>
	void Graph<T>::add_edge(T vertex1, T vertex2, T edge_weight)
	{
		std::map<T,VecPair>::iterator it = graph_container_.find(vertex1);
		VecPair& adjacentVerticesWeightVec = (*it).second;
		adjacentVerticesWeightVec.push_back(std::make_pair(vertex2,edge_weight));
	}

	template<typename T>
	std::vector<std::pair<T,T> > Graph<T>::adjacent_vertices_weight(T vertex)
	{
		std::map<T,VecPair>::iterator it = graph_container_.find(vertex);
		VecPair adjacentVerticesWeightVec = (*it).second;
		return adjacentVerticesWeightVec;
	}

	template<typename T>
	bool Graph<T>::isProcessed(T vertex)
	{
		std::set<T>::iterator it = processedSet_.find(vertex);
		return (it != processedSet_.end());
	}

	template<typename T>
	void Graph<T>::setProcessed(T vertex, T shortestPathDistance)
	{
		processedSet_.insert(vertex);
		std::map<T,VecPair>::iterator it = graph_container_.find(vertex);
		assert((it != graph_container_.end()) && "vertex not present");
		//std::cout << std::distance(graph_container_.begin(),it) << std::endl;
		vecShortestPathDistance_[std::distance(graph_container_.begin(),it)] = shortestPathDistance;
	}

	template<typename T>
	T Graph<T>::shortestPathDistance(T vertex)
	{
		std::map<T,VecPair>::iterator it = graph_container_.find(vertex);
		return vecShortestPathDistance_[std::distance(graph_container_.begin(),it)];
	}

	template<typename T>
	std::size_t Graph<T>::count_vertices()
	{
		return graph_container_.size();
	}

	template<typename T>
	std::vector<T> Graph<T>::vertices()
	{
		std::vector<T> vecVertices;
		vecVertices.reserve((*this).count_vertices());
		for (std::map<T,VecPair>::iterator it = graph_container_.begin(); it != graph_container_.end(); ++it)
		{
			vecVertices.push_back((*it).first);
		}
		return vecVertices;
	}
}

#endif

/*
Yuushi's answer
http://stackoverflow.com/questions/14133115/implementation-of-an-adjacency-list-graph-representation 

Can have a look at also:
http://www.geeksforgeeks.org/graph-and-its-representations/
*/