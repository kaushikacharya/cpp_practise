#ifndef AdjList_Impl1_HPP
#define AdjList_Impl1_HPP

#include <iostream>
#include <vector>

namespace ds
{
	template<typename T>
	class AdjList
	{
	public:
		AdjList();
		~AdjList();
	public:
		std::vector<T>& adjacency_list();
	public:
		void addElement(T item);
	private:
		std::vector<T> vec_;
	};

	template<typename T>
	AdjList<T>::AdjList()
	{
	}

	template<typename T>
	AdjList<T>::~AdjList()
	{
	}

	template<typename T>
	void AdjList<T>::addElement(T item)
	{
		vec_.push_back(item);
	}

	template<typename T>
	std::vector<T>& AdjList<T>::adjacency_list()
	{
		return vec_;
	}
}

#endif