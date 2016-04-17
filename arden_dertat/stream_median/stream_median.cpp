#include "../../data_structure/impl/TreeNodeImplLRCount.hpp"
#include "../../data_structure/impl/BSTreeImplLRCount.hpp"
#include <cassert>
#include <iostream>

// TBD: Here its implemented using BST. Check Arden's solution.
//      Balanced BST may be a good idea.
template<typename T>
float get_current_median(ds::TreeNodeLRCount<T>* root);

template<typename T>
T get_pos_k_element(ds::TreeNodeLRCount<T>* root, std::size_t k);

// problem source: http://www.ardendertat.com/2011/11/03/programming-interview-questions-13-median-of-integer-stream/
int main(int argc, char* argv[])
{
	using namespace ds;
	std::size_t test_case = 2;

	switch (test_case)
	{
	case 0:
		{
			TreeNodeLRCount<int> treeNode0(45);
			TreeNodeLRCount<int> treeNode1(23,NULL,NULL,&treeNode0);
			int gh = 0;
		}
		break;
	case 1:
		{
			BSTreeLRCount<int> bsTree;
			bsTree.insert(3);
			bsTree.insert(5);
			TreeNodeLRCount<int>* searchNode = bsTree.search(5);
			std::cout << "left count: " << (*searchNode).getCountLeft() << std::endl;
			int gh = 0;
		}
		break;
	case 2:
		{
			BSTreeLRCount<int> bsTree;
			int arr[] = {1, 4, 2, 6, 5, 10, 7};
			std::cout << "total count: " << sizeof(arr)/sizeof(arr[0]) << std::endl;
			std::size_t count = 0;
			while (count < sizeof(arr)/sizeof(arr[0]))
			{
				bsTree.insert(arr[count]);
				float median = get_current_median(bsTree.root());
				std::cout << "median: " << median << std::endl;
				++count;
			}
			int gh = 0;
		}
		break;
	}

	return 0;
}

template<typename T>
float get_current_median(ds::TreeNodeLRCount<T>* root)
{
	//TBD: complete it
	std::size_t leftCount = (*root).getCountLeft();
	std::size_t rightCount = (*root).getCountRight();

	//std::cout << (leftCount+rightCount+1)%2 << std::endl;

	if (leftCount == rightCount)
	{
		return static_cast<float>((*root).item());
	}
	else
	{
		if ((leftCount+rightCount+1)%2 == 1)
		{
			// odd
			std::size_t pos_median = (leftCount+rightCount+1+1)/2;
			T median = get_pos_k_element(root,pos_median);
			return static_cast<float>(median);
		}
		else
		{
			// even
			std::size_t pos_median_1 = (leftCount+rightCount+1)/2;
			std::size_t pos_median_2 = pos_median_1+1;
			T median_1 = get_pos_k_element(root,pos_median_1);
			T median_2 = get_pos_k_element(root,pos_median_2);
			return static_cast<float>( (median_1*1.0 + median_2*1.0)/2 );
		}
	}

	return static_cast<float>((*root).item());
}

// k is wrt 1 based indexing
template<typename T>
T get_pos_k_element(ds::TreeNodeLRCount<T>* root, std::size_t k)
{
	using namespace ds;
	std::size_t leftCount;
	std::size_t count_till_now = 0; //This keeps track of how many elements are on the left side
									// of curNode if the nodes are in places in sorted order(ascending).
	ds::TreeNodeLRCount<T>* curNode = root;

	while (curNode)
	{
		leftCount = (*curNode).getCountLeft();

		if ( (leftCount+count_till_now) < k )
		{
			// kth node can be either
			// a) curNode
			// c) right descendant of curNode
			count_till_now += (leftCount+1);
			if ((count_till_now) == k)
			{
				// case (a)
				break;
			}
			else
			{
				// case (b)
				curNode = static_cast<TreeNodeLRCount<T>*>((*curNode).right());
			}
		}
		else
		{
			//kth node is in the left descendant of curNode
			assert(((*curNode).left()) && "left child should be present");
			curNode = static_cast<TreeNodeLRCount<T>*>((*curNode).left());
		}
	}

	return (*curNode).item();

}