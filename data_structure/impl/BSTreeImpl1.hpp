#ifndef BSTree_Impl1_HPP
#define BSTree_Impl1_HPP

#include "../TreeNode.hpp"

namespace ds
{
	template<Version::Enum v,class T>
	class BSTree;

	template<typename T>
	class BSTree<Version::V1,typename T>
	{
	public:
		BSTree(TreeNode<Version::V0,T>* root=NULL);
		~BSTree();
	public:
		void insert(T item);
		void insert(T item, TreeNode<Version::V0,T>* root);
		TreeNode<Version::V0,T>* root();
		TreeNode<Version::V0,T>* search(T item);
		bool empty();
		//TBD
		//void remove(T item);
		//void inOrderTraversal(LinkedList<Version::V0,T>& linkedList);
		//void bfsTraversal(LinkedList<Version::V0,T>& linkedList);
		//successor, predecessor
        //minimum, maximum
		TreeNode<Version::V0,T>* minimum(TreeNode<Version::V0,T>* root);
		TreeNode<Version::V0,T>* maximum(TreeNode<Version::V0,T>* root);
		TreeNode<Version::V0,T>* predecessor(TreeNode<Version::V0,T>* node);
        TreeNode<Version::V0,T>* successor(TreeNode<Version::V0,T>* node);
	private:
		TreeNode<Version::V0,T>* root_;
	};

	template<typename T>
	BSTree<Version::V1,T>::BSTree(TreeNode<Version::V0,T>* root)
		: root_(root)
	{
	}

	template<typename T>
	BSTree<Version::V1,T>::~BSTree()
	{
		//TBD
	}

	template<typename T>
	TreeNode<Version::V0,T>* BSTree<Version::V1,T>::root()
	{
		return root_;
	}

	template<typename T>
	bool BSTree<Version::V1,T>::empty()
	{
		return root_ == NULL;
	}

	template<typename T>
	void BSTree<Version::V1,T>::insert(T item)
	{
		if (root_ == NULL)
		{
			root_ = new TreeNode<Version::V0,T>(item);
			return;
		}

		TreeNode<Version::V0,T>* node = root_;
		while(node)
		{
			if (item < (*node).item())
			{
				if ((*node).left())
				{
					node = (*node).left();
				}
				else
				{
					TreeNode<Version::V0,T>* newNode = new TreeNode<Version::V0,T>(item,NULL,NULL,node);
					(*node).setLeft(newNode);
					break;
				}
			}
			else
			{
				if ((*node).right())
				{
					node = (*node).right();
				}
				else
				{
					TreeNode<Version::V0,T>* newNode = new TreeNode<Version::V0,T>(item,NULL,NULL,node);
					(*node).setRight(newNode);
					break;
				}
			}
		}
	}

    //Note: This can violate BST validity.
	template<typename T>
	void BSTree<Version::V1,T>::insert(T item, TreeNode<Version::V0,T>* root)
	{
		//insert item in a sub-tree rooted at root
		TreeNode<Version::V0,T>* node = root;

		while(node)
		{
			if (item < (*node).item())
			{
				if ((*node).left())
				{
					node = (*node).left();
				}
				else
				{
					TreeNode<Version::V0,T>* newNode = new TreeNode<Version::V0,T>(item,NULL,NULL,node);
					(*node).setLeft(newNode);
					break;
				}
			}
			else
			{
				if ((*node).right())
				{
					node = (*node).right();
				}
				else
				{
					TreeNode<Version::V0,T>* newNode = new TreeNode<Version::V0,T>(item,NULL,NULL,node);
					(*node).setRight(newNode);
					break;
				}
			}
		}
	}

	template<typename T>
	TreeNode<Version::V0,T>* BSTree<Version::V1,T>::search(T item)
	{
		TreeNode<Version::V0,T>* node = root_;

		while(node)
		{
			if (item == (*node).item())
			{
				break;
			}
			else if (item < (*node).item())
			{
				node = (*node).left();
			}
			else
			{
				node = (*node).right();
			}
		}

		return node;
	}

	template<typename T>
	TreeNode<Version::V0,T>* BSTree<Version::V1,T>::minimum(TreeNode<Version::V0,T>* root)
	{
		TreeNode<Version::V0,T>* node = root;
		while ((*node).left())
		{
			node = (*node).left();
		}
		return node;
	}

	template<typename T>
	TreeNode<Version::V0,T>* BSTree<Version::V1,T>::maximum(TreeNode<Version::V0,T>* root)
	{
		TreeNode<Version::V0,T>* node = root;
		while ((*node).right())
		{
			node = (*node).right();
		}
		return node;
	}

	template<typename T>
	TreeNode<Version::V0,T>* BSTree<Version::V1,T>::predecessor(TreeNode<Version::V0,T>* node)
	{
		TreeNode<Version::V0,T>* predecessorNode = NULL;
		
		if ((*node).left())
		{
			predecessorNode = maximum((*node).left());
		}
		else
		{
			//TBD
		}
		return predecessorNode;
	}

    template<typename T>
    TreeNode<Version::V0,T>* BSTree<Version::V1,T>::successor(TreeNode<Version::V0,T>* node)
    {
        TreeNode<Version::V0,T>* successorNode = NULL;
        
		if ((*node).right())
        {
            node = (*node).right();
            //Now take the minimum of sub-tree rooted at node
			successorNode = minimum(node);
        }
        else
        {
            //keep moving up and
            //take the lowest ancestor whose left descendant is node
            TreeNode<Version::V0,T>* parent = (*node).parent();
            while (parent && ((*parent).right() == node))
            {
                node = parent;
                parent = (*node).parent();
            }
            if(parent)
            {
                successorNode = parent;
            }
        }

        return successorNode;
    }
}

#endif