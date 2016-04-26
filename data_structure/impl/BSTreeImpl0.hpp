#ifndef BSTreeImpl0_HPP
#define BSTreeImpl0_HPP

#include "../TreeNode.hpp"
#include "../LinkedList.hpp"
#include "../Queue.hpp"
#include "../utils/Version.hpp"

//TBD: insert(T item) :: introduce this function
namespace ds
{
    template<Version::Enum v, class T>
    class BSTree;

    template<class T>
    class BSTree<Version::V0, typename T>
    {
    public:
        BSTree(TreeNode<Version::V0,T>* root=NULL);
        ~BSTree();
    public:
        void insert(TreeNode<Version::V0,T>* node);
        void insert(TreeNode<Version::V0,T>* curRoot, TreeNode<Version::V0,T>* node);
        bool isEmpty();
        TreeNode<Version::V0,T>* root();
        TreeNode<Version::V0,T>* search(TreeNode<Version::V0,T>* curRoot, T& item);
		void remove(T& item);

		//traversals
		void inOrderTraversal(TreeNode<Version::V0,T>* curRoot, LinkedList<Version::V0,T>& linkedList);
		//TBD: preOrder and postOrder traversals
		//TBD: DFS traversal
		void bfsTraversal(LinkedList<Version::V0,T>& linkedList);
    private:
        TreeNode<Version::V0,T>* root_;
    };

    template<typename T>
    BSTree<Version::V0,T>::BSTree(ds::TreeNode<Version::V0,T> *root = NULL)
        : root_(root)
    {
    }

    template<typename T>
    BSTree<Version::V0,T>::~BSTree()
    {
        //TBD
    }

    //iterative implementation
    template<typename T>
    void BSTree<Version::V0,T>::insert(TreeNode<Version::V0,T>* node)
    {
        if ((*this).isEmpty())
        {
            root_ = node;
        }
		else
		{
			TreeNode<Version::V0,T>* curNode = root_;
			while(true)
			{
				if (curNode->item() < node->item())
				{
					//check right child
					if (curNode->right() == NULL)
					{
						curNode->setRight(node);
						node->setParent(curNode);
						break;
					}
					else
					{
						curNode = curNode->right();
					}
				}
				else
				{
					//check left child
					if (curNode->left() == NULL)
					{
						curNode->setLeft(node);
						node->setParent(curNode);
						break;
					}
					else
					{
						curNode = curNode->left();
					}
				}
			}
		}
    }

    //recursive implementation
    template<typename T>
    void BSTree<Version::V0,T>::insert(TreeNode<Version::V0,T>* curRoot, TreeNode<Version::V0,T>* node)
    {
        if (curRoot == NULL)
        {
            root_ = node;
        }
        if (curRoot->item() < node->item())
        {
            //check right child
            if (curRoot->right() == NULL)
            {
                curRoot->setRight(node);
                node->setParent(curRoot);
            } 
            else
            {
                insert(curRoot->right(),node);
            }
        } 
        else
        {
            //check left child
            if (curRoot->left() == NULL)
            {
                curRoot->setLeft(node);
                node->setParent(curRoot);
            } 
            else
            {
                insert(curRoot->left(),node);
            }
        }
    }

    template<typename T>
    bool BSTree<Version::V0,T>::isEmpty()
    {
        return root_ == NULL;
    }

    template<typename T>
    TreeNode<Version::V0,T>* BSTree<Version::V0,T>::root()
    {
        return root_;
    }

	//recursive implementation
    template<typename T>
    TreeNode<Version::V0,T>* BSTree<Version::V0,T>::search(TreeNode<Version::V0,T>* curRoot, T& item)
    {
        if (curRoot == NULL)
        {
            return NULL;
        }
        if (curRoot->item() < item)
        {
            return search(curRoot->right(),item);
        } 
        else if (item < curRoot->item())
        {
            return search(curRoot->left(),item);
        } 
        else
        {
            return curRoot;
        }
    }

	template<typename T>
	void BSTree<Version::V0,T>::remove(T& item)
	{
		TreeNode<Version::V0,T>* node = (*this).search(item);
		assert((node != NULL) && "element not available");
		//TBD: complete it
	}

	template<typename T>
	void BSTree<Version::V0,T>::inOrderTraversal(TreeNode<Version::V0,T>* curRoot, LinkedList<Version::V0,T>& linkedList)
	{
		if (curRoot == NULL)
		{
			return;
		}
		inOrderTraversal(curRoot->left(),linkedList);
		linkedList.addNode(curRoot->item());
		inOrderTraversal(curRoot->right(),linkedList);
	}

	template<typename T>
	void BSTree<Version::V0,T>::bfsTraversal(LinkedList<Version::V0,T>& linkedList)
	{
		if (root_ == NULL)
		{
			return;
		}

		Queue<Version::V0,TreeNode<Version::V0,T>* > queue;
		queue.push_back(root_);

		while (!queue.empty())
		{
			TreeNode<Version::V0,T>* node = queue.front();
			linkedList.addNode((*node).item());
			if ((*node).left())
			{
				queue.push_back((*node).left());
			}
			if ((*node).right())
			{
				queue.push_back((*node).right());
			}
			queue.pop_front();
		}
	}

}

#endif

/*
http://www.cs.bu.edu/teaching/c/tree/breadth-first/
*/