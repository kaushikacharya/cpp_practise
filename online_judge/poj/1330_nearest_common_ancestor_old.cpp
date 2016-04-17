// http://poj.org/problem?id=1330
// http://stackoverflow.com/questions/2853438/c-vector-of-pointers
//      Do I just make two vectors - one of pointers and one of Movies and make a one-to-one mapping of the two vectors?

#include <cstdio>
#include <vector>
#include <algorithm> // std::find
#include <functional> // std::equal_to

#define READ_FROM_FILE 1

// http://stackoverflow.com/questions/14437825/using-stdfind-with-a-predicate
template<class T1, class T2, class Pred = std::equal_to<T2> >
struct equal_item
{
	equal_item(const T2& idx)
		: idx_(idx)
	{
	}

	bool operator()(const T1& node)
	{
		Pred p;
		return p((*node).item(),idx_);
	}

	const T2& idx_;
};

// http://www.learncpp.com/cpp-tutorial/143-template-classes/
template<typename T>
class TreeNode
{
public:
	TreeNode(T elem, TreeNode* parent=NULL);
	~TreeNode();
public:
	void setParent(TreeNode* parent);
	void addChild(TreeNode* child);
	T item();
private:
	T elem_;
	TreeNode* parent_;
	std::vector<TreeNode<T>* > vecChild_;
};

template<typename T>
TreeNode<T>::TreeNode(T elem, TreeNode* parent)
: elem_(elem)
, parent_(parent)
{
}

template<typename T>
TreeNode<T>::~TreeNode()
{
}

template<typename T>
void TreeNode<T>::setParent(TreeNode* parent)
{
	parent_ = parent;
}

template<typename T>
void TreeNode<T>::addChild(TreeNode* child)
{
	//first check if the child is not present already in the vec of children of this treenode
}

template<typename T>
T TreeNode<T>::item()
{
	return elem_;
}

// ------------
template<typename T>
class Tree
{
public:
	Tree();
	~Tree();
public:
	void readInput(FILE* pFile, unsigned int nInputLine);
private:
	void addNode(T item);
private:
	std::vector<TreeNode<T>* > vecTreeNode_;
};

template<typename T>
Tree<T>::Tree()
{
}

template<typename T>
Tree<T>::~Tree()
{
}

template<typename T>
void Tree<T>::readInput(FILE* pFile, unsigned int nInputLine)
{
	for (unsigned int line_i = 0; line_i < nInputLine; ++line_i)
	{
		//every line contains first node as parent and second one as child
		T parentItem;
		T childItem;

		// TBD: can we make scanf,fscanf template based?
		if (READ_FROM_FILE)
		{
			fscanf(pFile,"%d",&parentItem);
			fscanf(pFile,"%d",&childItem);
		}
		else
		{
		}
		addNode(parentItem);
		addNode(childItem);
	}
}

template<typename T>
void Tree<T>::addNode(T item)
{
	// add only if there's no node with item as its element
	std::vector<TreeNode<T>* >::iterator it = std::find_if(vecTreeNode_.begin(),vecTreeNode_.end(),equal_item<TreeNode<T>*,T>(item));
	if (it == vecTreeNode_.end())
	{
		printf("Not found: %d\n",item);
		TreeNode<T> node(item);
		vecTreeNode_.push_back(&node);
	}
	else
	{
		printf("Found: %d\n",item);
	}
}

// ----------
int main(int argc[], char* argv[])
{
	FILE* pFile;
	unsigned int nCase;

	if (READ_FROM_FILE)
	{
		pFile = fopen("D:/cpp_practise/online_judge/poj/1330_nearest_common_ancestor.txt","r");
		fscanf(pFile,"%d",&nCase);
	}
	else
	{
		pFile = 0;
	}

	for (unsigned int case_i = 0; case_i < nCase; ++case_i)
	{
		unsigned int nInputLine;
		Tree<int> tree;
		
		if (READ_FROM_FILE)
		{
			fscanf(pFile,"%d",&nInputLine);
		}
		else
		{
		}

		tree.readInput(pFile,nInputLine-1);
	}

	std::vector<TreeNode<int>* > vecTreeNode;
	/*
	TreeNode<int> node0(2);
	vecTreeNode.push_back(&node0);
	TreeNode<int> node1(9);
	vecTreeNode.push_back(&node1);
	node1.setParent(&node0);

	//printf("%d\n",node1.item());
	std::vector<TreeNode<int>* >::iterator it = std::find_if(vecTreeNode.begin(),vecTreeNode.end(),equal_item<TreeNode<int>*,int>(3));
	if (it == vecTreeNode.end())
	{
		printf("Not found");
	}
	*/

	/*
	std::vector<int> vecInt;
	vecInt.push_back(5);
	vecInt.push_back(3);
	std::vector<int>::iterator it = std::find_if(vecInt.begin(),vecInt.end(),equal_item<int,int>(2));
	if (it == vecInt.end())
	{
		printf("Not found");
	}
	*/
	
	return 0;
}