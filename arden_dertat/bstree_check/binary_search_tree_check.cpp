#include "BSTreeImplChildMinMax.hpp"
#include "TreeNodeImplChildMinMax.hpp"
#include <cassert>
#include <iostream>

int main(int argc, char* argv[])
{
	using namespace ds;
	std::size_t test_case = 2;

	switch(test_case)
	{
	case 0:
		{
			// testing TreeNode
			TreeNodeChildMinMax<float> node0(3.4);
			TreeNodeChildMinMax<float> node1(4.5,&node0);
			TreeNodeChildMinMax<float> node2(6,NULL,NULL,&node0);
			
			std::cout << "min of subtree rooted at node1: " << (node1).getMin() << std::endl;
			std::cout << "max of subtree rooted at node1: " << (node1).getMax() << std::endl;
			std::cout << "min of subtree rooted at node2: " << (node2).getMin() << std::endl;
			std::cout << "max of subtree rooted at node2: " << (node2).getMax() << std::endl;
			int gh = 0;
		}
		break;
	case 1:
		{
			// testing Binary Search Tree
			BSTreeChildMinMax<int> bstree0;
			TreeNodeChildMinMax<int> node0(3);
			BSTreeChildMinMax<int> bstree1(&node0);
			bstree0.insert(5,&node0);
			int gh = 0;
		}
		break;
	case 2:
		{
			BSTreeChildMinMax<int> bsTree;
			int arr[] = {1, 4, 2, 6, 3};
			std::size_t count = 0;
			while (count < sizeof(arr)/sizeof(arr[0]))
			{
				bsTree.insert(arr[count]);
				++count;
			}
			bool validity = true;
			bsTree.bstree_validity_check(bsTree.root(),validity);
			std::cout << "validity = " << validity << std::endl;
			// Now inserting an element which will violate BST
			TreeNodeChildMinMax<int>* searchNode = bsTree.search(6);
			bsTree.insert(3,searchNode);
			bsTree.bstree_validity_check(bsTree.root(),validity);
			std::cout << "validity = " << validity << std::endl;
			int gh = 0;
		}
		break;
	}

	return 0;
}