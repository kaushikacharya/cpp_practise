#ifndef Queue_Impl0_HPP
#define Queue_Impl0_HPP

#include "../ListNode.hpp"
#include "../../utils/Version.hpp"
#include <cassert>

//Ques: do we need another push_back() which takes ListNode as input
namespace ds
{
	template<Version::Enum v, class T>
	class Queue;

	template<class T>
	class Queue<Version::V0,typename T>
	{
    public:
        Queue();
        ~Queue();
    public:
		bool empty();
        T front(); //ListNode<Version::V1,T>*
        T back(); //ListNode<Version::V1,T>*
        void push_back(T item);
        void pop_front();
    private:
        ListNode<Version::V1,T>* rear_;
        ListNode<Version::V1,T>* front_;
	};

    template<typename T>
    Queue<Version::V0,T>::Queue()
        : rear_(NULL)
        , front_(NULL)
    {
    }

	template<typename T>
	Queue<Version::V0,T>::~Queue()
	{
		//TBD
	}

	template<typename T>
	T Queue<Version::V0,T>::front()
	{
		return (*front_).item();
	}

	template<typename T>
	T Queue<Version::V0,T>::back()
	{
		return (*rear_).item();
	}

	template<typename T>
	void Queue<Version::V0,T>::push_back(T item)
	{
		ListNode<Version::V1,T>* newNode = new ListNode<Version::V1,T>(item,NULL,rear_);
		if ((*this).empty())
		{
			front_ = newNode;
		}
		rear_ = newNode;
	}

	template<typename T>
	void Queue<Version::V0,T>::pop_front()
	{
		assert(!(*this).empty() && "queue is empty");
		ListNode<Version::V1,T>* newFront = (*front_).prev();
		ListNode<Version::V1,T>* delNode = front_;
		if (rear_ == front_)
		{
			rear_ = newFront;
		}
		front_ = newFront;
		delete delNode;
	}

	template<typename T>
	bool Queue<Version::V0,T>::empty()
	{
		return ((front_ == NULL) && (rear_ == NULL));
		//return front_ == rear_ == NULL;
	}
}

#endif