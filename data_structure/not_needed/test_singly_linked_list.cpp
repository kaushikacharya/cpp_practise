#include "LinkedList.hpp"
#include "..\file_reader\TextReader.hpp"
#include <iostream>

int main( int argc, char* argv[] )
{
    using namespace ds;

    ds::TextReader textReader("D:\\cpp_practise\\file_reader\\text.txt");
    textReader();

    LinkedList linkedList;
    //populating linkedList
    std::vector<std::string> strVec = textReader.strVec();

    for (std::vector<std::string>::iterator strIt = strVec.begin(); strIt != strVec.end(); ++strIt)
    {
        linkedList.addNode(*strIt);
    }

    std::cout << "list size: " << linkedList.size() << std::endl;

#if 0
    linkedList.addNode("my");
	linkedList.addNode("name");
	//linkedList.empty();
#endif


    linkedList.remove("of");
	std::cout << "list size(after removal): " << linkedList.size() << std::endl;

    return 0;
}

/*
Learnings:

http://stackoverflow.com/questions/9050553/in-a-c-constructor-do-i-have-to-allocate-space-for-my-instance-fields
If you want your pointers to point to objects, you will need to either assign them or create objects for them to point to.

http://www.cs.fsu.edu/~jestes/cop3330/notes/dma.html
Dynamic Allocation of objects


http://codereview.stackexchange.com/a/1486
use 'delete' to free memory allocated using 'new'
*/

/*
TBD:
1. since we are trying singly linked list, we need not have rear_ field for Node.
2. recursive implementation: Try that
	http://www.cs.bu.edu/teaching/c/linked-list/delete/
*/