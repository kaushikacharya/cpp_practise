#ifndef TreeNode_HPP
#define TreeNode_HPP

#include <string>

namespace ds
{
	class TreeNode
	{
	public:
		TreeNode(std::string item, TreeNode* left=NULL, TreeNode* right=NULL, TreeNode* parent=NULL);
		std::string item();
		TreeNode* left();
		TreeNode* right();
		TreeNode* parent();
		void setLeft(TreeNode* node);
		void setRight(TreeNode* node);
		void setParent(TreeNode* node);
	private:
		std::string item_;
		TreeNode* left_;
		TreeNode* right_;
		TreeNode* parent_;
	};
}

#endif