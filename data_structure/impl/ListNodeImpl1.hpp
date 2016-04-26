#ifndef ListNode_Impl1_HPP
#define ListNode_Impl1_HPP

#include "../../utils/Version.hpp"
#include <cstdlib>
//node for doubly linked list

/*
Check: 1. should we have T& item in the constructor?
       2. which one should we write a) ListNode<Version::V1,T>* b) ListNode* ?
*/

namespace ds
{
    template<Version::Enum v, class T>
    class ListNode;

    template<class T>
    class ListNode<Version::V1,typename T>
    {
    public:
        ListNode(T item, ListNode<Version::V1,T>* prev=NULL, ListNode<Version::V1,T>* next=NULL);
    public:
        T item();
        ListNode<Version::V1,T>* prev();
        ListNode<Version::V1,T>* next();
        void setPrev(ListNode<Version::V1,T>* node);
        void setNext(ListNode<Version::V1,T>* node);
    private:
        T item_;
        ListNode* prev_;
        ListNode* next_;
    };

    template<typename T>
    ListNode<Version::V1,T>::ListNode(T item, ListNode<Version::V1,T>* prev, ListNode<Version::V1,T>* next)
        : item_(item)
        , prev_(prev)
        , next_(next)
    {
        if (prev)
        {
            (*prev).setNext(this);
        }
        if (next)
        {
            (*next).setPrev(this);
        }
    }

    template<typename T>
    T ListNode<Version::V1,T>::item()
    {
        return item_;
    }

    template<typename T>
    ListNode<Version::V1,T>* ListNode<Version::V1,T>::prev()
    {
        return prev_;
    }

    template<typename T>
    ListNode<Version::V1,T>* ListNode<Version::V1,T>::next()
    {
        return next_;
    }

    template<typename T>
    void ListNode<Version::V1,T>::setPrev(ListNode<Version::V1,T>* node)
    {
        prev_ = node;
    }

    template<typename T>
    void ListNode<Version::V1,T>::setNext(ListNode<Version::V1,T>* node)
    {
        next_ = node;
    }

}

#endif