#ifndef Stack_HPP
#define Stack_HPP

#include "Node.hpp"

namespace ds
{
	class Stack
	{
	public:
		Stack();
		~Stack();
	public:
		void push(std::string str);
		std::string pop();
		bool isEmpty();
	private:
		Node* top_;
	};
}

#endif