#include "..\data_structure\LinkedList.hpp"
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

	// now reversing the linked list
	Node* newHead = NULL;
	Node* curNode = linkedList.head();

	while (curNode != NULL)
	{
		Node* nextNode = curNode->next();
		curNode->setNext(newHead);
		newHead = curNode;
		curNode = nextNode;
	}

	linkedList.head(newHead);
	
	// now print the reverse lined list
	curNode = linkedList.head();
	while (curNode)
	{
		std::string str = curNode->item();
		std::cout << str << " ";
		curNode = curNode->next();
	}

    return 0;
}