#ifndef GraphVertex_HPP
#define GraphVertex_HPP

#include <vector>

namespace ds
{
	template <class T>
	class GraphVertex
	{
	public:
		GraphVertex(T id);
	public:
		T id();
		std::vector<T>& adjacentList();
		void push_adjacent_vertex(T adjId);
	private:
		T id_;
		std::vector<T> adjacentList_; //list of adjacent vertices
	};

	template <class T>
	GraphVertex<T>::GraphVertex(T id)
		: id_(id)
	{
	}

	template <class T>
	T GraphVertex<T>::id()
	{
		return id_;
	}

	template<class T>
	std::vector<T>& GraphVertex<T>::adjacentList()
	{
		return adjacentList_;
	}

	template<class T>
	void GraphVertex<T>::push_adjacent_vertex(T adjId)
	{
		adjacentList_.push_back(adjId);
	}

}
#endif