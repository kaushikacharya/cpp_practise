#ifndef BSTree_Impl_LR_count_hpp
#define BSTree_Impl_LR_count_hpp

#include "TreeNodeImplLRCount.hpp"
#include "../../utils/Version.hpp"

namespace ds
{
	template<class T>
	class BSTreeLRCount;

	template<class T>
	class BSTreeLRCount
	{
	public:
		BSTreeLRCount(TreeNodeLRCount<T>* root=NULL);
		~BSTreeLRCount();
	public:
		void insert(T item);
		bool empty();
		TreeNodeLRCount<T>* root();
		TreeNodeLRCount<T>* search(T item);
	private:
		TreeNodeLRCount<T>* root_;
	};

	template<class T>
	BSTreeLRCount<T>::BSTreeLRCount(ds::TreeNodeLRCount<T> *root = NULL)
		: root_(root)
	{
	}

	template<class T>
	BSTreeLRCount<T>::~BSTreeLRCount()
	{
		//TBD
	}

	// iterative implementation
	template<class T>
	void BSTreeLRCount<T>::insert(T item)
	{
		if ((*this).empty())
		{
			root_ = new TreeNodeLRCount<T>(item);
			return;
		}
		
		TreeNodeLRCount<T>* curNode = root_;
		while (curNode)
		{
			if (item < (*curNode).item())
			{
				if ((*curNode).left())
				{
					//increment the left counter of curNode
					(*curNode).setCountLeft((*curNode).getCountLeft()+1);
					curNode = static_cast<TreeNodeLRCount<T>*>((*curNode).left());
				}
				else
				{
					TreeNodeLRCount<T>* newNode = new TreeNodeLRCount<T>(item,NULL,NULL,curNode);
					(*curNode).setLeft(newNode);
					//increment the left counter of curNode
					(*curNode).setCountLeft(1);
					//curNode = static_cast<TreeNodeLRCount<T>*>((*curNode).left());
					curNode = NULL;
				}
			}
			else
			{
				if ((*curNode).right())
				{
					//increment the right counter of curNode
					(*curNode).setCountRight((*curNode).getCountRight()+1);
					curNode = static_cast<TreeNodeLRCount<T>*>((*curNode).right());
				}
				else
				{
					TreeNodeLRCount<T>* newNode = new TreeNodeLRCount<T>(item,NULL,NULL,curNode);
					(*curNode).setRight(newNode);
					//increment the right counter of curNode
					(*curNode).setCountRight(1);
					//curNode = static_cast<TreeNodeLRCount<T>*>((*newNode).right());
					curNode = NULL;
				}
			}
		}
	}

	// iterative implementation
	template<class T>
	TreeNodeLRCount<T>* BSTreeLRCount<T>::search(T item)
	{
		TreeNodeLRCount<T>* curNode = root_;
		while (curNode)
		{
			if (item == (*curNode).item())
			{
				break;
			}
			else if (item < (*curNode).item())
			{
				curNode = static_cast<TreeNodeLRCount<T>*>((*curNode).left());
			}
			else
			{
				curNode = static_cast<TreeNodeLRCount<T>*>((*curNode).right());
			}
		}

		return curNode;
	}

	template<class T>
	bool BSTreeLRCount<T>::empty()
	{
		return root_ == NULL;
	}

	template<class T>
	TreeNodeLRCount<T>* BSTreeLRCount<T>::root()
	{
		return root_;
	}
}

#endif

/* learning:
http://www.velocityreviews.com/forums/t284007-casting-from-base-to-derived-class.html
*/