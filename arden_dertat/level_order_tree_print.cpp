#include "../data_structure/BSTree.hpp"
#include "../data_structure/TreeNode.hpp"
#include "../data_structure/Queue.hpp"
#include "../utils/Version.hpp"
#include <iostream>
//problem statement: http://www.ardendertat.com/2011/12/05/programming-interview-questions-20-tree-level-order-print/

template<typename T>
void print_level_order(ds::TreeNode<ds::Version::V0,T>* root);

int main( int argc, char* argv[] )
{
	using namespace ds;
	std::size_t test_case = 2;

	switch (test_case)
	{
	case 0:
		{
			BSTree<Version::V0,int> bstree0;
			TreeNode<Version::V0,int> treeNode0(30);
			bstree0.insert(&treeNode0);
			TreeNode<Version::V0,int> treeNode1(25);
			bstree0.insert(&treeNode1);
			TreeNode<Version::V0,int> treeNode2(28);
			bstree0.insert(&treeNode2);
			TreeNode<Version::V0,int> treeNode3(10);
			bstree0.insert(&treeNode3);
			TreeNode<Version::V0,int> treeNode4(37);
			bstree0.insert(&treeNode4);
			TreeNode<Version::V0,int> treeNode5(43);
			bstree0.insert(&treeNode5);
			TreeNode<Version::V0,int> treeNode6(32);
			bstree0.insert(&treeNode6);

			print_level_order(bstree0.root());
		}
		break;
	case 1:
		{
			//balanced BST
			int arr[] = {30,25,28,10,37,43,32};
			BSTree<Version::V1,int> bstree;
			for (std::size_t i=0; i<7; ++i)
			{
				bstree.insert(arr[i]);
			}
			print_level_order(bstree.root());
		}
		break;
	case 2:
		{
			//unbalanced BST
			int arr[] = {30,25,28,10,37,43,32,31,34};
			BSTree<Version::V1,int> bstree;
			for (std::size_t i=0; i<9; ++i)
			{
				bstree.insert(arr[i]);
			}
			print_level_order(bstree.root());
		}
		break;
	}

	return 0;
}

template<typename T>
void print_level_order(ds::TreeNode<ds::Version::V0,T>* root)
{
	using namespace ds;

	if (root == NULL)
	{
		return;
	}

	//now traverse the tree in breadth first
	std::size_t count_cur_level = 0;
	std::size_t count_next_level = 0;
	Queue<Version::V0,TreeNode<Version::V0,T>* > queue;
	queue.push_back(root);
	++count_cur_level;

	while (!queue.empty())
	{
		TreeNode<Version::V0,T>* node = queue.front();

		if ((*node).left())
		{
			queue.push_back((*node).left());
			++count_next_level;
		}
		if ((*node).right())
		{
			queue.push_back((*node).right());
			++count_next_level;
		}
		std::cout << (*node).item() << " ";
		queue.pop_front();
		--count_cur_level;

		if (count_cur_level == 0)
		{
			//all items of current level have been printed out
			//now as we would be moving into next level, we would consider 
			//    next level as current level for the next iteration.
			std::cout << std::endl;
			std::swap(count_cur_level,count_next_level);
		}
	}

}

/*
Function templates
http://www.cplusplus.com/doc/tutorial/templates/

Compile error: C2360
http://msdn.microsoft.com/en-us/library/61af7cx3.aspx
You cannot jump past a declaration with an initializer unless the declaration is enclosed 
in a block.
*/