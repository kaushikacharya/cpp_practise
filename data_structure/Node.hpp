#ifndef NODE_HPP
#define NODE_HPP

#include <string>

namespace ds
{
    class Node
    {
    public:
        Node(std::string item, Node* next=NULL);
    public:
        void setNext(Node* next);
        Node* next();
        std::string item();
    private:
        std::string item_;
        Node* next_;
    };
}

#endif