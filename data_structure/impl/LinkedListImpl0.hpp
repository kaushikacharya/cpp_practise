#ifndef LinkedList_Impl0_HPP
#define LinkedList_Impl0_HPP

#include "..\ListNode.hpp"
#include "..\utils\Version.hpp"

// singly linkedlist with only one pointer i.e. to head
namespace ds
{
	template <Version::Enum v, class T>
	class LinkedList;

	template <class T>
	class LinkedList<Version::V0, typename T>
	{
	public:
		LinkedList();
		~LinkedList();
	public:
		void addNode(T item);
		bool isEmpty();
		void empty();
        std::size_t size();
		ListNode<Version::V0,T>* head();
		//void head(ListNode<Version::V0,T>* head);
        void remove(T item);
	private:
		ListNode<Version::V0,T>* head_;
	};

	template <class T>
	LinkedList<Version::V0,T>::LinkedList()
	{
		head_ = NULL;
	}

	template <class T>
	LinkedList<Version::V0,T>::~LinkedList()
	{
		empty();
	}

	template <class T>
	void LinkedList<Version::V0,T>::addNode(T item)
	{
		ListNode<Version::V0,T>* newNode = new ListNode<Version::V0,T>(item, head_);
		head_ = newNode;
	}

	template <class T>
	bool LinkedList<Version::V0,T>::isEmpty()
	{
		head_ == NULL;
	}

	template <class T>
	void LinkedList<Version::V0,T>::empty()
	{
		while (head_)
		{
			ListNode<Version::V0,T>* node = head_;
			head_ = head_->next();
			delete node;
		}
	}

	template <class T>
	std::size_t LinkedList<Version::V0,T>::size()
	{
		std::size_t count = 0;
		ListNode<Version::V0,T>* node = head_;

		while(node)
		{
			++count;
			node = node->next();
		}

		return count;
	}

	template <class T>
	ListNode<Version::V0,T>* LinkedList<Version::V0,T>::head()
	{
		return head_;
	}

	template <class T>
	void LinkedList<Version::V0,T>::remove(T item)
	{
		//Note: there can be multiple instances of item in the linked list
		ListNode<Version::V0,T>* node = head_;

		//first handling if item is present in the beginning of the list
		while(node && (node->item() == item))
		{
			head_ = head_->next();
			delete node;
			node = head_;
		}

		while (node)
		{
			ListNode<Version::V0,T>* nextNode = node->next();

			while (nextNode && (nextNode->item() == item))
			{
				ListNode<Version::V0,T>* delNode = nextNode;
				nextNode = nextNode->next();
				delete delNode;
			}

			node->setNext(nextNode);
			node = nextNode;
		}

	}
}

/*
TBD: find out why this gives compile error: "error C2649: 'typename' : is not a 'class'"

template <class T>
class LinkedList<Version::V0, class T>

*/

#endif