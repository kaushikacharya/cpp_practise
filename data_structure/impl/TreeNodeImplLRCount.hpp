#ifndef TreeNode_Impl_LR_Count_HPP
#define TreeNode_Impl_LR_Count_HPP

#include "TreeNodeImpl0.hpp"
/*
Here we keep count of left/right descendants for each node
*/
namespace ds
{
	template<class T>
	class TreeNodeLRCount;

	template<class T>
	class TreeNodeLRCount : public TreeNode<Version::V0,T>
	{
	public:
		TreeNodeLRCount(T item, TreeNodeLRCount* left=NULL, TreeNodeLRCount* right=NULL, TreeNodeLRCount* parent=NULL);
	public:
		std::size_t getCountLeft();
		std::size_t getCountRight();
		void setCountLeft(std::size_t count);
		void setCountRight(std::size_t count);
	private:
		std::size_t countLeft_;
		std::size_t countRight_;
	};

	template<class T>
	TreeNodeLRCount<T>::TreeNodeLRCount(T item, TreeNodeLRCount* left, TreeNodeLRCount* right, TreeNodeLRCount* parent)
		: TreeNode<Version::V0,T>(item,left,right,parent)
	{
		//TBD: These would depend on presence of left/right
		countLeft_ = 0;
		countRight_ = 0;
	}

	template<class T>
	std::size_t TreeNodeLRCount<T>::getCountLeft()
	{
		return countLeft_;
	}

	template<class T>
	std::size_t TreeNodeLRCount<T>::getCountRight()
	{
		return countRight_;
	}

	template<class T>
	void TreeNodeLRCount<T>::setCountLeft(std::size_t count)
	{
		countLeft_ = count;
	}

	template<class T>
	void TreeNodeLRCount<T>::setCountRight(std::size_t count)
	{
		countRight_ = count;
	}

}

#endif