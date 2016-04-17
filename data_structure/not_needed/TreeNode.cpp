#include "TreeNode.hpp"

namespace ds
{
	TreeNode::TreeNode(std::string item, TreeNode* left, TreeNode* right, TreeNode* parent)
		: item_(item)
		, left_(left)
		, right_(right)
		, parent_(parent)
	{
	}

	std::string TreeNode::item()
	{
		return item_;
	}

	TreeNode* TreeNode::left()
	{
		return left_;
	}

	TreeNode* TreeNode::right()
	{
		return right_;
	}

	TreeNode* TreeNode::parent()
	{
		return parent_;
	}

	void TreeNode::setLeft(TreeNode* node)
	{
		(*this).left_ = node;
	}

	void TreeNode::setRight(TreeNode* node)
	{
		(*this).right_ = node;
	}

	void TreeNode::setParent(TreeNode* node)
	{
		(*this).parent_ = node;
	}
}
