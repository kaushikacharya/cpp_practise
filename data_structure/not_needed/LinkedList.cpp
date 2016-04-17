#include "LinkedList.hpp"
#include <iostream>

namespace ds
{
    LinkedList::LinkedList()
    {
        front_ = NULL;
        rear_ = NULL;
    }

	LinkedList::~LinkedList()
	{
		empty();
	}

    void LinkedList::addNode(std::string str)
    {
        Node* newNode = new Node(str);

        if ((*this).isEmpty())
        {
            front_ = newNode;
            rear_ = newNode;
        } 
        else
        {
            rear_->setNext(newNode);
            rear_ = newNode;
        }
    }

    bool LinkedList::isEmpty()
    {
        if ( (front_ == NULL) ) // && (rear_ == NULL)
        {
            return true;
        } 
        else
        {
            return false;
        }
    }

	void LinkedList::empty()
	{
		while(!isEmpty())
		{
			Node* prevFront = front_;
			front_ = front_->next();
			delete prevFront;
		}
		rear_ = NULL;
	}

    std::size_t LinkedList::size()
    {
        if ((*this).isEmpty())
        {
            return 0;
        }

        std::size_t sz = 0;
        Node* curNode = front_;

        while (curNode != rear_->next())            
        {
            ++sz;
            curNode = curNode->next();
        }
        return sz;
    }

	Node* LinkedList::head()
	{
		return front_;
	}

	void LinkedList::head(Node* head)
	{
		front_ = head;
		Node* curNode = front_;

		while(curNode->next())
		{
			curNode = curNode->next();
		}
		rear_ = curNode;
	}

    void LinkedList::remove(std::string str)
    {
		//first check if we need to remove items from front
		while (!(*this).isEmpty() && (front_->item() == str))
		{
			Node* prevFront = front_;
			front_ = front_->next();
			delete prevFront;
		}

		if ((*this).isEmpty())
		{
			rear_ = NULL;
			return;
		}

		Node* prevNode = front_;
		Node* curNode = front_->next();

		while (curNode != NULL)
		{
			if (curNode->item() == str)
			{
				Node* delNode = curNode;
				curNode = curNode->next();
				delete delNode;
				prevNode->setNext(curNode);
			}
			else
			{
#if 0
				if (prevNode->next() != curNode)
				{
					prevNode->setNext(curNode);
				}
#endif
				prevNode = curNode;
				curNode = curNode->next();
			}
		}

		rear_ = prevNode;

        // Remember when deleting nodes in list
        //1. change the next pointers of the list
        //2. free the memory of deleted nodes

		//test cases:
		// remove the word - a
		// case 1a: a->b->c
		// case 1b: a->a->b->c
		// case 2a: b->a->c
		// case 2b: b->a->a->c
		// case 3a: b->c->a
		// case 3b: b->c->a->a
		// case 4a: a
		// case 4b: a->a
		// case 5: b->c

    }

}