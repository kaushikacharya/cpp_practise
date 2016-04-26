#ifndef LinkedList_HPP
#define LinkedList_HPP

#include "Node.hpp"

namespace ds
{
    //singly linked list
    class LinkedList
    {
    public:
        LinkedList();
		~LinkedList();
    public:
        void addNode(std::string str);
        bool isEmpty();
		void empty();
        std::size_t size();
		Node* head();
		void head(Node* head);
        void remove(std::string str);
    private:
        //operator <(std::string const& str1, std::string const& str2);
    private:
        Node* front_;
        Node* rear_;
    };

}

#endif