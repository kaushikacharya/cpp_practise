#include "..\Tree.hpp"
#include "..\..\file_reader\TextReader.hpp"
#include <iostream>

int main( int argc, char* argv[] )
{
	using namespace ds;
	Tree tree;

	ds::TextReader textReader("D:\\cpp_practise\\test_cases\\tree_test.txt");
    textReader();

	//populating linkedList
    std::vector<std::string> strVec = textReader.strVec();

	for (std::vector<std::string>::iterator strIt = strVec.begin(); strIt != strVec.end(); ++strIt)
    {
        tree.insert(*strIt);
    }
	//testing iterative search function
	bool found_1 = tree.search("one") != NULL;
	//testing recursive search function
	bool found_2 = tree.search(tree.root(),"these");
	
	//in-order traversal
	LinkedList inOrderList;
	tree.inOrderTraversal(tree.root(), inOrderList);

	std::cout << "\n in-order traversal: \n";
	Node* curNode = inOrderList.head();
	while(curNode)
	{
		std::cout << curNode->item() << " ";
		curNode = curNode->next();
	}
	std::cout << std::endl;
	//END of in-order traversal

	TreeNode* successorNode = tree.successor(tree.search("is"));
	std::cout << "successor node: ";
	if (successorNode)
	{
		std::cout << successorNode->item() << std::endl;
	}

	tree.remove(tree.search("was")); //test case: deleting an element which doesn't exist in the tree
	
	//test case: node to be deleted has only left child
	//e.g. node to be deleted: "used", node to be tested: "that"

	//test case: node to be deleted has both child. node's successor is its right child.
	//e.g. node to be deleted: "one", node to be tested: "that"

	//test case: node to be deleted has both child. node's successor is its right child's descendant.
	//e.g. node to be deleted: "introduces", node to be tested: "further" "is"
	tree.remove(tree.search("introduces"));
	TreeNode* testNode0 = tree.search("is");
	std::cout << "parent: ";
	if (testNode0->parent())
	{
		std::cout << (testNode0->parent())->item();
	}
	std::cout << std::endl;
	std::cout << "left child: ";
	if (testNode0->left())
	{
		std::cout << (testNode0->left())->item();
		std::cout << " :: left child's parent: ";
		if ((testNode0->left())->parent())
		{
			std::cout << ((testNode0->left())->parent())->item();
		}
	}
	std::cout << std::endl;

	if (testNode0->right())
	{
		std::cout << "right child: " << (testNode0->right())->item();
		std::cout << " :: right child's parent: ";
		if ((testNode0->right())->parent())
		{
			std::cout << ((testNode0->right())->parent())->item();
		}
	}
	std::cout << std::endl;

	//testing char to int conversion
	//int gh = '\r';

	return 0;
}
