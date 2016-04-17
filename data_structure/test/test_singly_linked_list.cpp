#include "..\LinkedList.hpp"
#include "..\..\file_reader\TextReader.hpp"
#include <iostream>

int main( int argc, char* argv[] )
{
    using namespace ds;

	std::size_t test_case = 1;

	switch (test_case)
	{
	case 0:
#if 0
		ds::TextReader textReader("D:\\cpp_practise\\file_reader\\text.txt");
		textReader();
		std::vector<std::string> strVec = textReader.strVec();

		LinkedList<Version::V0,std::string> linkedList;

		//populating linkedList
		for (std::vector<std::string>::iterator strIt = strVec.begin(); strIt != strVec.end(); ++strIt)
		{
			linkedList.addNode(*strIt);
		}

		std::cout << "list size: " << linkedList.size() << std::endl;
#if 0
		linkedList.empty();
		std::cout << "list size(after emptying): " << linkedList.size() << std::endl;
#endif
		linkedList.remove("of");
		std::cout << "list size(after removal): " << linkedList.size() << std::endl;
#endif
		break;
	case 1:
		// http://www.ardendertat.com/2011/09/29/programming-interview-questions-5-linkedlist-remove-nodes/
		LinkedList<Version::V0,int> linkedList;
		linkedList.remove(5);
		std::cout << "list size: " << linkedList.size() << std::endl;
		linkedList.empty();

		linkedList.addNode(1);
		linkedList.remove(5);
		std::cout << "list size: " << linkedList.size() << std::endl;
		linkedList.empty();

		linkedList.addNode(5);
		linkedList.remove(5);
		std::cout << "list size: " << linkedList.size() << std::endl;
		linkedList.empty();

		linkedList.addNode(2);
		linkedList.addNode(1);
		linkedList.remove(5);
		std::cout << "list size: " << linkedList.size() << std::endl;
		linkedList.empty();

		linkedList.addNode(5);
		linkedList.addNode(5);
		linkedList.addNode(5);
		linkedList.remove(5);
		std::cout << "list size: " << linkedList.size() << std::endl;
		linkedList.empty();

		linkedList.addNode(5);
		linkedList.addNode(5);
		linkedList.addNode(2);
		linkedList.addNode(1);
		linkedList.remove(5);
		std::cout << "list size: " << linkedList.size() << std::endl;
		linkedList.empty();

		linkedList.addNode(3);
		linkedList.addNode(5);
		linkedList.addNode(5);
		linkedList.addNode(2);
		linkedList.addNode(1);
		linkedList.remove(5);
		std::cout << "list size: " << linkedList.size() << std::endl;
		linkedList.empty();
	}

#if 0
    linkedList.addNode("my");
	linkedList.addNode("name");
#endif
    
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