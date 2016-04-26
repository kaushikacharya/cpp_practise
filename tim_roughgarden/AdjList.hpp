#ifndef AdjList_HPP
#define AdjList_HPP

#include <iostream>

namespace ds
{
	template<typename T>
	class AdjListNode
	{
	public:
		AdjListNode(T item, AdjListNode<T>* next=NULL);
		~AdjListNode();
	public:
		T item();
		AdjListNode<T>* next();
		void setNext(AdjListNode<T>* nextNode);
	private:
		T item_;
		AdjListNode<T>* next_;
	};

	template<typename T>
	class AdjList
	{
	public:
		AdjList();
		~AdjList();
	public:
		AdjListNode<T>* head();
		void addListNode(AdjListNode<T>* node);
		void addListNode(AdjListNode<T> node);
	private:
		AdjListNode<T>* head_;
	};

	// ---------------------------------------------------
	template<typename T>
	AdjListNode<T>::AdjListNode(T item, ds::AdjListNode<T> *next = NULL)
		: item_(item)
		, next_(next)
	{
	}

	template<typename T>
	AdjListNode<T>::~AdjListNode()
	{
		//TBD
		int gh = 0;
	}

	template<typename T>
	T AdjListNode<T>::item()
	{
		return item_;
	}

	template<typename T>
	AdjListNode<T>* AdjListNode<T>::next()
	{
		return next_;
	}

	template<typename T>
	void AdjListNode<T>::setNext(AdjListNode<T>* nextNode)
	{
		next_ = nextNode;
	}
	// -----------------------------------------------------------------------------
	template<typename T>
	AdjList<T>::AdjList()
	{
		head_ = NULL;
	}

	template<typename T>
	AdjList<T>::~AdjList()
	{
		//TBD
		int gh = 0;
	}

	template<typename T>
	AdjListNode<T>* AdjList<T>::head()
	{
		return head_;
	}

	template<typename T>
	void AdjList<T>::addListNode(AdjListNode<T>* node)
	{
		(*node).setNext(head_);
		head_ = node;
	}

	template<typename T>
	void AdjList<T>::addListNode(AdjListNode<T> node)
	{
		node.setNext(head_);
		head_ = &node;
	}
}

#endif

/*
http://www.geeksforgeeks.org/graph-and-its-representations/
http://www.cs.bu.edu/teaching/c/graph/linked/
*/