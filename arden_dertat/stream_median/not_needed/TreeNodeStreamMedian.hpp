#ifndef TreeNode_Stream_Median_HPP
#define TreeNode_Stream_Median_HPP

#include "../../data_structure/impl/TreeNodeImpl0.hpp"

namespace ds
{
	template<class T>
	class TreeNodeStreamMedian;

	template<class T>
	class TreeNodeStreamMedian : public TreeNode<Version::V0,T>
	{
	public:
		TreeNodeStreamMedian(T item, TreeNode* left=NULL, TreeNode* right=NULL, TreeNode* parent=NULL);
	public:
		std::size_t countLeft();
		std::size_t countRight();
	private:
		std::size_t countLeft_;
		std::size_t countRight_;
	};

	template<class T>
	TreeNodeStreamMedian<T>::TreeNodeStreamMedian(T item, TreeNode* left, TreeNode* right, TreeNode* parent)
		: TreeNode<Version::V0,T>(item,left,right,parent)
	{
		countLeft_ = 0;
		countRight_ = 0;
	}

}

#endif

/*
http://www.cs.bu.edu/teaching/cpp/inheritance/intro/
Note: Classes don't explicitly inherit constructors. 

http://www.cplusplus.com/forum/beginner/8529/#msg39586
size_t is a typedef of an unsigned type 
*/