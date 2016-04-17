#include "Stack.hpp"
#include <cassert>

namespace ds
{
	Stack::Stack()
	{
		top_ = NULL;
	}
	Stack::~Stack()
	{
		//empty the stack and free the memory
		while(!(*this).isEmpty())
		{
			Node* delNode = top_;
			top_ = top_->next();
			delete delNode;
		}
	}

	void Stack::push(std::string str)
	{
		Node* newNode = new Node(str,top_);
		top_ = newNode;
	}

	std::string Stack::pop()
	{
		if ((*this).isEmpty())
		{
			assert(false && "stack is empty");
		}
		std::string str = top_->item();
		top_ = top_->next();
		return str;
	}

	bool Stack::isEmpty()
	{
		return top_ == NULL;
	}
}