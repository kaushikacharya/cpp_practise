#include "Node.hpp"
#include <iostream>

int main( int argc, char* argv[] )
{
    using namespace ds;

    Node node0 = Node("my");
    Node node1 = Node("name",&node0);
    Node* next = node1.next();
    if (next->next() == NULL)
    {
        int gh = 0;
    }
    return 0;
}