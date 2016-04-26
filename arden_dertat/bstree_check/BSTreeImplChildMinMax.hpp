#ifndef BSTree_Impl_Child_MinMax_HPP
#define BSTree_Impl_Child_MinMax_HPP

#include "TreeNodeImplChildMinMax.hpp"

namespace ds
{
	template<typename T>
	class BSTreeChildMinMax;

	template<typename T>
	class BSTreeChildMinMax
	{
	public:
		BSTreeChildMinMax(TreeNodeChildMinMax<T>* root=NULL);
	public:
		TreeNodeChildMinMax<T>* root();
		void insert(T item, TreeNodeChildMinMax<T>* root=NULL);
		TreeNodeChildMinMax<T>* search(T item);
		void bstree_validity_check(TreeNodeChildMinMax<T>* root, bool& validityFlag=True);
	private:
		TreeNodeChildMinMax<T>* root_;
	};

	template<typename T>
	BSTreeChildMinMax<T>::BSTreeChildMinMax(TreeNodeChildMinMax<T>* root)
		: root_(root)
	{
	}

	template<typename T>
	TreeNodeChildMinMax<T>* BSTreeChildMinMax<T>::root()
	{
		return root_;
	}

	// Note wrong choice of root may violate BST validity
	template<typename T>
	void BSTreeChildMinMax<T>::insert(T item, TreeNodeChildMinMax<T>* root)
	{
		if (root_ == NULL)
		{
			root_ = new TreeNodeChildMinMax<T>(item);
			return;
		}
		if (root == NULL)
		{
			root = root_;
		}
		
		if ((*root).item() < item)
		{
			// insert into right subtree
			if ((*root).right() == NULL)
			{
				TreeNodeChildMinMax<T>* newNode = new TreeNodeChildMinMax<T>(item,NULL,NULL,root);
				(*root).setRight(newNode);
			}
			else
			{
				insert( item,static_cast<TreeNodeChildMinMax<T>*>((*root).right()) );
			}
		}
		else
		{
			// insert into left subtree
			if ((*root).left() == NULL)
			{
				// NU: This gives "error C2078: too many initializers"
				//TreeNodeChildMinMax<T>* newNode(item,NULL,NULL,root);
				TreeNodeChildMinMax<T>* newNode = new TreeNodeChildMinMax<T>(item,NULL,NULL,root);
				(*root).setLeft(newNode);
			}
			else
			{
				insert(item,static_cast<TreeNodeChildMinMax<T>*>((*root).left()));
			}
		}
		
	}

	template<typename T>
	TreeNodeChildMinMax<T>* BSTreeChildMinMax<T>::search(T item)
	{
		TreeNodeChildMinMax<T>* curNode = (*this).root();

		while (curNode)
		{
			if ((*curNode).item() == item)
			{
				break;
			}
			else if ((*curNode).item() < item)
			{
				curNode = static_cast<TreeNodeChildMinMax<T>*>((*curNode).right());
			}
			else
			{
				curNode = static_cast<TreeNodeChildMinMax<T>*>((*curNode).left());
			}
		}

		return curNode;
	}

	// Here we also assign min/max for subtree at each node. Min/max also includes the node itself.
	template<typename T>
	void BSTreeChildMinMax<T>::bstree_validity_check(TreeNodeChildMinMax<T>* root, bool& validityFlag)
	{
		if (!validityFlag)
		{
			return; // no more processing needed
		}
		if ( ( (*root).left() == NULL ) && ( (*root).right() == NULL ) )
		{
			(*root).setMin((*root).item());
			(*root).setMax((*root).item());
			return;
		}
		// initializing the root's value as min,max. It will be later changed depending on left/right subtree
		(*root).setMin((*root).item());
		(*root).setMax((*root).item());

		if ( (*root).left() )
		{
			TreeNodeChildMinMax<T>* leftNode = static_cast<TreeNodeChildMinMax<T>*>((*root).left());
			bstree_validity_check(leftNode, validityFlag);
			if ((*root).item() < (*leftNode).getMax())
			{
				//BST violation
				validityFlag = false;
				return;
			}
			(*root).setMin((*leftNode).getMin());
		}
		if ( (*root).right() )
		{
			TreeNodeChildMinMax<T>* rightNode = static_cast<TreeNodeChildMinMax<T>*>((*root).right());
			bstree_validity_check(rightNode, validityFlag);
			if ( (*root).item() < (*rightNode).getMin() )
			{
			}
			else
			{
				// BST violation
				validityFlag = false;
				return;
			}
			(*root).setMax((*rightNode).getMax());
		}

	}

}

#endif

/* learning:
http://stackoverflow.com/questions/12573816/what-is-an-undefined-reference-unresolved-external-symbol-error-and-how-do-i-fix
*/