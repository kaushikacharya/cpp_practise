#include "Tree.hpp"
#include <cassert>

namespace ds
{
	Tree::Tree()
	{
		root_ = NULL;
	}

	Tree::~Tree()
	{
		//TBD
	}

	TreeNode* Tree::root()
	{
		return root_;
	}

	// iterative implementation
	void Tree::insert(std::string str)
	{
		if (root_ == NULL)
		{
			TreeNode* newNode = new TreeNode(str,NULL,NULL,NULL);
			root_ = newNode;
			return;
		}

		TreeNode* curNode = root_;

		while(curNode)
		{
			if (curNode->item() < str)
			{
				//go to Right child
				if (curNode->right())
				{
					curNode = curNode->right();
				}
				else
				{
					//create a new node
					TreeNode* newNode = new TreeNode(str,NULL,NULL,curNode);
					curNode->setRight(newNode);
					return;
				}
			}
			else
			{
				//go to Left child
				if (curNode->left())
				{
					curNode = curNode->left();
				}
				else
				{
					//create a new node
					TreeNode* newNode = new TreeNode(str,NULL,NULL,curNode);
					curNode->setLeft(newNode);
					return;
				}
			}
		}
	}

	void Tree::remove(TreeNode* node)
	{
		if(node == NULL)
		{
			return;
		}
		//case1: No children
		//case2: only 1 child present
		//case3: both child present
		//Also the case when root is being deleted
		if ( (node->left() == NULL) && (node->right() == NULL) )
		{
			if (node == root_)
			{
				root_ = NULL;
			}
			else
			{
				TreeNode* parent = node->parent();
				if(parent->left() == node)
				{
					parent->setLeft(NULL);
				}
				else
				{
					parent->setRight(NULL);
				}
			}
			delete node;
		}
		else if ( (node->left() == NULL) || (node->right() == NULL) )
		{
			//single child
			if (node == root_)
			{
				if (node->left())
				{
					root_ = node->left();
				}
				else
				{
					root_ = node->right();
				}
			}
			else
			{
				TreeNode* parent = node->parent();
				TreeNode* child = (node->left()) ? node->left() : node->right();

				if (parent->left() == node)
				{
					parent->setLeft(child);
				}
				else
				{
					parent->setRight(child);
				}
				child->setParent(parent);
			}
			delete node;
		}
		else
		{
			//both child present
			//replace node with its successor
			TreeNode* parent = node->parent();
			TreeNode* successorNode = successor(node);
			assert((successorNode->left() == NULL) && "successor of a node can't have left child");

			if (node->right() == successorNode)
			{
				//case: right child of node doesn't have any left descendant
			}
			else
			{
				assert( ((successorNode->parent())->left() == successorNode) && "successorNode should be left child of its parent" );
				if (successorNode->right())
				{
					//right child of successorNode should replace as left child of successorNode's parent
					(successorNode->right())->setParent(successorNode->parent());
					(successorNode->parent())->setLeft(successorNode->right());
				}
				else
				{
					(successorNode->parent())->setLeft(NULL);
				}

				//now place successorNode in place of node
				successorNode->setRight(node->right());
				(node->right())->setParent(successorNode);
			}

			successorNode->setLeft(node->left());
			(node->left())->setParent(successorNode);
			successorNode->setParent(parent);
			if (parent)
			{
				if (parent->left() == node)
				{
					parent->setLeft(successorNode);
				}
				else
				{
					parent->setRight(successorNode);
				}
			}
			else
			{
				root_ = successorNode;
			}
		}
	}

#if 0	
	//iterative implementation
	bool Tree::search(std::string str)
	{
		if (root_ == NULL)
		{
			return false;
		}

		TreeNode* curNode = root_;

		bool found(false);
		while (curNode)
		{
			if (curNode->item() == str)
			{
				found = true;
				break;
			}
			else if (curNode->item() < str)
			{
				//check right side
				curNode = curNode->right();
			}
			else
			{
				//check left side
				curNode = curNode->left();
			}
		}

		return found;
	}
#endif
	//iterative implementation
	TreeNode* Tree::search(std::string str)
	{
		TreeNode* curNode = root_;

		while (curNode)
		{
			if (curNode->item() == str)
			{
				break;
			}
			else if (curNode->item() < str)
			{
				//check right side
				curNode = curNode->right();
			}
			else
			{
				//check left side
				curNode = curNode->left();
			} 
		}

		return curNode;
	}


	// recursive implementation
	bool Tree::search(TreeNode* curNode, std::string str)
	{
		if (curNode == NULL)
		{
			return false;
		}
		if (curNode->item() == str)
		{
			return true;
		}
		else if (curNode->item() < str)
		{
			// check right side
			return search(curNode->right(),str);
		}
		else
		{
			//check left side
			return search(curNode->left(),str);
		}
	}

	TreeNode* Tree::successor(TreeNode* curNode)
	{
		if (curNode == NULL)
		{
			return NULL;
		}
		if (curNode->right())
		{
			return min(curNode->right());
		}
		else
		{
			//curNode is left descendant of successor (if present) 
			TreeNode* parentNode = curNode->parent();
			
			while (parentNode)
			{
				if (parentNode->left() == curNode)
				{
					break;
				}
				else
				{
					curNode = parentNode;
					parentNode = curNode->parent();
				}
			}

			return parentNode;
		}
	}

	//min of subtree with node as root
	TreeNode* Tree::min(TreeNode* node)
	{
		if (node == NULL)
		{
			return NULL;
		}
		while(node->left())
		{
			node = node->left();
		}
		return node;
	}

	void Tree::inOrderTraversal(TreeNode* curNode, LinkedList& list)
	{
		if (curNode == NULL)
		{
			return;
		}
		inOrderTraversal(curNode->left(), list);
		list.addNode(curNode->item());
		inOrderTraversal(curNode->right(), list);
	}

}