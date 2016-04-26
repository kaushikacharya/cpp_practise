#ifndef Graph_Impl3_HPP
#define Graph_Impl3_HPP

#include <cassert>
#include <iostream>
#include <map>
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
		bool explored(int pos);
		void setExplored(int pos);
		std::vector<T> adjacencyList(int pos);
	public:
		//utils for debugging
		void print_adjacency_list();
	private:
		std::map<T,std::vector<T>> graph_container_; //TBD: change vector to set
		std::vector<int> vecExplored_;
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
		std::vector<T> adjacentVerticesVec;
		graph_container_.insert(std::pair<T,std::vector<T>>(vertex,adjacentVerticesVec) );
		vecExplored_.push_back(0);
	}

	template<typename T>
	void Graph<T>::add_edge(T vertex1, T vertex2)
	{
		//TBD: usage of set will ensure that we don't repeat the adjacent vertices for vertex1
		std::map<T,std::vector<T>>::iterator it = graph_container_.find(vertex1);
		std::vector<T>& adjacentVerticesVec = (*it).second;
		adjacentVerticesVec.push_back(vertex2);
	}

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
	std::vector<T> Graph<T>::adjacencyList(int pos)
	{
		if (pos == 3424)
		{
			int gh = 0;
			std::cout << "pos: " << pos << std::endl;
		}
		T vertex1 = pos+1;
		std::map<T,std::vector<T>>::iterator it = graph_container_.find(vertex1);
		assert((it != graph_container_.end()) && "vertex not found");
		std::vector<T> adjacentVerticesVec = (*it).second;
		assert(adjacentVerticesVec.size()>0 && "zero outedges");
		return adjacentVerticesVec;
	}

	template<typename T>
	void Graph<T>::print_adjacency_list()
	{
		for (std::map<T,std::vector<T>>::iterator it = graph_container_.begin(); it != graph_container_.end(); ++it)
		{
			T vertex1 = (*it).first;
			std::vector<T> adjacentVerticesVec = (*it).second;
			std::cout << vertex1 << " :";
			for (std::vector<T>::iterator adjIt = adjacentVerticesVec.begin(); adjIt != adjacentVerticesVec.end(); ++adjIt)
			{
				T vertex2 = (*adjIt);
				std::cout << " " << vertex2;
			}
			std::cout << std::endl;
		}
	}
}

#endif