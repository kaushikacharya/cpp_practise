#ifndef ListNode_Impl0_HPP
#define ListNode_Impl0_HPP

#include <cstdlib>
#include "..\utils\Version.hpp"
// node for singly linked list

namespace ds
{
	template <Version::Enum v, class T>
	class ListNode;

	template <class T>
	class ListNode<Version::V0, typename T>
	{
	public:
		ListNode(T item, ListNode<Version::V0,T>* next=NULL);
	public:
		T item();
		void setNext(ListNode<Version::V0,T>* next);
		ListNode<Version::V0,T>* next();
	private:
		T item_;
		ListNode<Version::V0,T>* next_;
	};

	template <typename T>
	ListNode<Version::V0,T>::ListNode(T item, ListNode<Version::V0,T>* next)
		: item_(item)
		, next_(next)
	{
	}

	template <typename T>
	T ListNode<Version::V0,T>::item()
	{
		return item_;
	}

	template <typename T>
	void ListNode<Version::V0,T>::setNext(ListNode<Version::V0,T>* next)
	{
		next_ = next;
	}

	template <typename T>
	ListNode<Version::V0,T>* ListNode<Version::V0,T>::next()
	{
		return next_;
	}
}

#endif

/*
1. // http://www.cs.bu.edu/teaching/c/queue/linked-list/funcs.html
2. included cstdlib otherwise NULL not defined. Need to include atleast one of the C library.
*/