#ifndef GraphEdge_HPP
#define GraphEdge_HPP

#include <utility>
#include <vector>

namespace ds
{
	template<typename T>
	class GraphEdge
	{
	public:
		GraphEdge(T id0, T id1);
	public:
		std::pair<T,T> edge();
	private:
		std::pair<T,T> edge_;
	};

	template<class T>
	GraphEdge<T>::GraphEdge(T id0, T id1)
	{
		edge_ = std::make_pair(id0,id1);
	}

	template<class T>
	std::pair<T,T> GraphEdge<T>::edge()
	{
		return edge_;
	}
	 
}

#endif