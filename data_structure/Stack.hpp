#ifndef Stack_HPP
#define Stack_HPP

#include "ListNode.hpp"
#include "..\utils\Version.hpp"

namespace ds
{
    template <Version::Enum v, class T>
	class Stack;
}

#include "impl\StackImpl0.hpp"

#endif

/*
source: http://www.cplusplus.com/reference/stack/stack/
Elements are pushed/popped from the "back" of the specific container, which is known as the top of the stack.
    back()
    push_back()
    pop_back()

*/