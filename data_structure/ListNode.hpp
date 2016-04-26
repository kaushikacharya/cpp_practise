#ifndef ListNode_HPP
#define ListNode_HPP

#include "..\utils\Version.hpp"

namespace ds
{
	template <Version::Enum v, class T>
	class ListNode;
}

#include "impl\ListNodeImpl0.hpp"
#include "impl\ListNodeImpl1.hpp"

//TBD: node for doubly linked list

#endif

/*
1. // http://www.cs.bu.edu/teaching/c/queue/linked-list/funcs.html
2. included cstdlib otherwise NULL not defined. Need to include atleast one of the C library.
*/