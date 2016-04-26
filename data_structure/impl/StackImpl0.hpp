#ifndef Stack_Impl0_HPP
#define Stack_Impl0_HPP

#include "..\ListNode.hpp"
#include "..\utils\Version.hpp"
#include <cassert>

//TBD: top() should return item and not ListNode. See the changes in Queue.
//	   Implementation detail of Stack shouldn't be exposed to public.
namespace ds
{
	template <Version::Enum, class T>
	class Stack;

	template <class T>
	class Stack<Version::V0, typename T>
	{
	public:
		Stack();
		~Stack();
	public:
        void push(T item);
        ListNode<Version::V0,T>* top();
        void pop();
		bool isEmpty();
		void empty();
	private:
		ListNode<Version::V0,T>* top_;
	};

	template <class T>
	Stack<Version::V0,T>::Stack()
	{
		top_ = NULL;
	}

	template <class T>
	Stack<Version::V0,T>::~Stack()
	{
		empty();
	}

    template <class T>
    void Stack<Version::V0,T>::push(T item)
    {
        ListNode<Version::V0,T>* newNode = new ListNode<Version::V0,T>(item,top_);
        top_ = newNode;
    }

    template <class T>
    ListNode<Version::V0,T>* Stack<Version::V0,T>::top()
    {
        return top_;
    }

	template <class T>
	void Stack<Version::V0,T>::pop()
	{
		assert(!isEmpty() && "can't pop from empty stack");

		ListNode<Version::V0,T>* topNode = top_;
		top_ = top_->next();
		delete topNode;
	}

	template <class T>
	bool Stack<Version::V0,T>::isEmpty()
	{
		return top_ == NULL;
	}

	template <class T>
	void Stack<Version::V0,T>::empty()
	{
		while (top_)
		{
			ListNode<Version::V0,T>* delNode = top_;
			top_ = top_->next();
			delete delNode;
		}
	}
}

#endif