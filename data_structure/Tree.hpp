#include "TreeNode.hpp"
#include "LinkedList.hpp"
#include "..\utils\Version.hpp"

// Binary Search Tree
namespace ds
{
	class Tree
	{
	public:
		Tree();
		~Tree();
		void insert(std::string str);
		void remove(TreeNode* node);
		//bool search(std::string str);
		TreeNode* search(std::string str);
		bool search(TreeNode* curNode, std::string str);
		TreeNode* successor(TreeNode* curNode);
		TreeNode* min(TreeNode* node);
		void inOrderTraversal(TreeNode* curNode, LinkedList& list);
	public:
		TreeNode* root();
	private:
		TreeNode* root_;
	};
}