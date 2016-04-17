#include "ListNode.hpp"

namespace ds
{
	template <typename T>
	ListNode<T>::ListNode(T item, ListNode<T>* next)
		: item_(item)
		, next_(next)
	{
	}

	template <typename T>
	T ListNode<T>::item()
	{
		return item_;
	}

	template <typename T>
	void ListNode<T>::setNext(ListNode<T>* next)
	{
		next_ = next;
	}

	template <typename T>
	ListNode<T>* ListNode<T>::next()
	{
		return next_;
	}
}