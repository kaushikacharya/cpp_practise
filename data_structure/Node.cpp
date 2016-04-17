#include "Node.hpp"

namespace ds
{
    Node::Node(std::string item, Node* next)
        : item_(item)
        , next_(next)
    {
    }

    void Node::setNext(Node* next)
    {
        next_ = next;
    }

    Node* Node::next()
    {
        return next_;
    }

    std::string Node::item()
    {
        return item_;
    }
}