#include "../BSTree.hpp"
#include "../../utils/Version.hpp"
#include <string>
#include <iostream>

/* TBD:
successor, predecessor
minimum, maximum
*/

int main( int argc, char* argv[] )
{
	using namespace ds;

	std::size_t test_case = 2;

	switch (test_case)
	{
	case 0:
		{
			BSTree<Version::V0,std::string> bstree0;
			TreeNode<Version::V0,std::string> treeNode0("my");
			bstree0.insert(&treeNode0);
			TreeNode<Version::V0,std::string> treeNode1("name");
			bstree0.insert(&treeNode1);
			TreeNode<Version::V0,std::string> treeNode2("is");
			//bstree0.insert(bstree0.root(),&treeNode2);
			bstree0.insert(&treeNode1,&treeNode2);
			std::string str = "is";
			//Next line violates BST
			TreeNode<Version::V0,std::string>* treeNode = bstree0.search(bstree0.root(),str);
			if (treeNode == NULL)
			{
				std::cout << str << " Not Found" << std::endl;
			}
			LinkedList<Version::V0,std::string> list;
			bstree0.inOrderTraversal(bstree0.root(),list);
			LinkedList<Version::V0,std::string> list1;
			bstree0.bfsTraversal(list1);
		}
		break;
	case 1:
		{
			BSTree<Version::V1,std::string> bstree;
			bstree.insert("my");
			bstree.insert("name");
			TreeNode<Version::V0,std::string>* node = bstree.search("name");
			if (node)
			{
				//Next line violates BST
				bstree.insert("is",node);
			}
			else
			{
				bstree.insert("is",bstree.root());
			}
			int gh = 0;
		}
		break;
    case 2:
        {
            int arr[] = {30,25,28,10,37,43,32,31,34};
            BSTree<Version::V1,int> bstree;
            for (std::size_t i=0; i<sizeof(arr)/sizeof(arr[0]); ++i)
            {
                bstree.insert(arr[i]);
            }
            TreeNode<Version::V0,int>* node = bstree.search(34);
            if (node == NULL)
            {
                std::cout << "34 Not Found" << std::endl;
            }
            else
            {
                TreeNode<Version::V0,int>* sucNode = bstree.successor(node);
                if (sucNode == NULL)
                {
                    std::cout << "No successor of 34" << std::endl;
                } 
                else
                {
                    std::cout << "successor of 34: " << (*sucNode).item() << std::endl;
                }
            }
        }
        break;
	}

	return 0;
}