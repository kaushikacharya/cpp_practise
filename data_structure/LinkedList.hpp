#ifndef LinkedList_HPP
#define LinkedList_HPP

#include "ListNode.hpp"
#include "..\utils\Version.hpp"

namespace ds
{
	template <Version::Enum v, class T>
	class LinkedList;
}

#include "impl\LinkedListImpl0.hpp"

// TBD:
// 1. using two pointers : head & tail for a singly linked list
// 1a. introduce push_front(), push_back() functions
// 2. doubly linked list

#endif