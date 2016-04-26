#ifndef TreeNode_Impl0_HPP
#define TreeNode_Impl0_HPP

#include <cstdlib>
#include "..\..\utils\Version.hpp"

namespace ds
{
	template<Version::Enum v, class T>
	class TreeNode;

	template<class T>
	class TreeNode<Version::V0, typename T>
	{
	public:
		TreeNode(T item, TreeNode* left=NULL, TreeNode* right=NULL, TreeNode* parent=NULL);
	public:
		T item();
		TreeNode* left();
		TreeNode* right();
		TreeNode* parent();
		void setLeft(TreeNode* left);
		void setRight(TreeNode* right);
		void setParent(TreeNode* parent);
	private:
		T item_;
		TreeNode* left_;
		TreeNode* right_;
		TreeNode* parent_;
	};

	template<typename T>
	TreeNode<Version::V0,T>::TreeNode(T item, TreeNode* left, TreeNode* right, TreeNode* parent)
		: item_(item)
		, left_(left)
		, right_(right)
		, parent_(parent)
	{
	}

	template<typename T>
	T TreeNode<Version::V0,T>::item()
	{
		return item_;
	}

	template<typename T>
	TreeNode<Version::V0,T>* TreeNode<Version::V0,T>::left()
	{
		return left_;
	}

	template<typename T>
	TreeNode<Version::V0,T>* TreeNode<Version::V0,T>::right()
	{
		return right_;
	}

	template<typename T>
	TreeNode<Version::V0,T>* TreeNode<Version::V0,T>::parent()
	{
		return parent_;
	}

	template<typename T>
	void TreeNode<Version::V0,T>::setLeft(TreeNode* left)
	{
		left_ = left;
	}

	template<typename T>
	void TreeNode<Version::V0,T>::setRight(TreeNode* right)
	{
		right_ = right;
	}

	template<typename T>
	void TreeNode<Version::V0,T>::setParent(TreeNode* parent)
	{
		parent_ = parent;
	}
}

#endif