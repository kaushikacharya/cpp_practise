// http://poj.org/problem?id=1330
// http://stackoverflow.com/questions/2853438/c-vector-of-pointers
//      Do I just make two vectors - one of pointers and one of Movies and make a one-to-one mapping of the two vectors?

// http://poj.org/showmessage?message_id=162276  Gives suggestion for LCA --> RMQ
// http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=lowestCommonAncestor

#include <cstdio>
#include <vector>
#include <algorithm> // std::find
#include <functional> // std::equal_to
#include <set>
#include <cassert>

#define READ_FROM_FILE 0

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

// http://www.cplusplus.com/reference/set/set/set/
template<class T>
struct Comp
{
	bool operator()(const T& node1, const T& node2) const
	{
		return (*node1).item() < (*node2).item();
		//Pred p;
		//return p((*node1).item(),(*node2).item());
	}
};

// http://www.learncpp.com/cpp-tutorial/143-template-classes/
// http://www.learncpp.com/cpp-tutorial/69-dynamic-memory-allocation-with-new-and-delete/
// http://www.eee.metu.edu.tr/~vision/LectureNotes/EE441/Chapt3.html
//		Example for static and dynamic memory allocation
template<typename T>
class TreeNode
{
public:
	TreeNode(T elem, TreeNode* parent=NULL);
	~TreeNode();
public:
	void setParent(TreeNode* parent);
	void addChild(TreeNode* child);
	T item() const;
	TreeNode* parent();
	std::vector<TreeNode<T>* > children(); 
private:
	T elem_;
	TreeNode<T>* parent_;
	std::vector<TreeNode<T>* > vecChild_;
};
// http://stackoverflow.com/questions/8686725/what-is-the-difference-between-stdset-and-stdvector
// http://stackoverflow.com/questions/10332789/stdlist-vs-stdvector-iteration

template<typename T>
TreeNode<T>::TreeNode(T elem, TreeNode* parent)
: elem_(elem)
, parent_(parent)
{
}

template<typename T>
TreeNode<T>::~TreeNode()
{
	int gh = 0;
}

template<typename T>
void TreeNode<T>::setParent(TreeNode* parent)
{
	parent_ = parent;
}

template<typename T>
void TreeNode<T>::addChild(TreeNode* child)
{
	vecChild_.push_back(child);
	/*
	//first check if the child is not present already in the vec of children of this TreeNode
	std::vector<TreeNode<T> >::iterator it = std::find_if(vecChild_.begin(),vecChild_.end(),equal_item<TreeNode<T>,T>(child.item()));
	if (it == vecChild_.end())
	{
		printf("Not found");
		vecChild_.push_back(*it);
	}
	*/
}

template<typename T>
T TreeNode<T>::item() const
{
	return elem_;
}

template<typename T>
TreeNode<T>* TreeNode<T>::parent()
{
	return parent_;
}

template<typename T>
std::vector<TreeNode<T>* > TreeNode<T>::children()
{
	return vecChild_;
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
	void writeOutput(); // prints out the input we have read
	T compute_nearest_common_ancestor(T item1, T item2);
private:
	//TreeNode<T>* addNode(T item);
	void addNode(T item);
	void setParentChildRelation(T parentItem, T childItem);
	TreeNode<T>* add_node(T item);
	void setParentChildRelation(TreeNode<T>* parent, TreeNode<T>* child);
private:
	std::vector<TreeNode<T>* > vecTreeNode_;
	typedef std::set<TreeNode<T>*,Comp<TreeNode<T>* > > SetTreeNode;
	SetTreeNode setTreeNode_;
};

template<typename T>
Tree<T>::Tree()
{
}

template<typename T>
Tree<T>::~Tree()
{
	//TBD: Handle 'scalar deleting destructor' error
	/*
	for (std::vector<TreeNode<T>* >::iterator it=vecTreeNode_.begin(); it != vecTreeNode_.end(); ++it)
	{
		TreeNode<T>* ptr = (*it);
		delete ptr;
		ptr = 0;
	}
	*/
	int gh = 0;
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
			scanf("%d",&parentItem);
			scanf("%d",&childItem);
		}
		/*
		TreeNode<T>* parentNode = addNode(parentItem);
		TreeNode<T>* childNode = addNode(childItem);

		(*childNode).setParent(parentNode);
		(*parentNode).addChild(childNode);
		*/
		/*
		addNode(parentItem);
		addNode(childItem);
		setParentChildRelation(parentItem,childItem);
		*/
		TreeNode<T>* parent = add_node(parentItem);
		TreeNode<T>* child = add_node(childItem);
		setParentChildRelation(parent,child);
	}
}

// debug function
template<typename T>
void Tree<T>::writeOutput()
{
	for (std::vector<TreeNode<T>* >::iterator it = vecTreeNode_.begin(); it != vecTreeNode_.end(); ++it)
	{
		printf("Node: %d",(**it).item());
		TreeNode<T>* parent = (**it).parent();
		std::vector<TreeNode<T>* > vecChild = (**it).children();
		if (parent)
		{
			printf(" :: parent: %d",(*parent).item());
		}
		if (!vecChild.empty())
		{
			printf(" :: children:");
			for (std::vector<TreeNode<T>* >::iterator chIt=vecChild.begin(); chIt != vecChild.end(); ++chIt)
			{
				printf(" %d",(**chIt).item());
			}
		}
		printf("\n");
	}
}

template<typename T>
TreeNode<T>* Tree<T>::add_node(T item)
{
	TreeNode<T>* node = new TreeNode<T>(item);
	//typedef std::set<TreeNode<T>*,Comp<TreeNode<T>* > >::iterator SetItr;
	//std::pair<SetItr,bool> ret = setTreeNode_.insert(node);
	std::pair<SetTreeNode::iterator,bool> ret = setTreeNode_.insert(node);
	if (ret.second == false)
	{
		//item already exists
		delete node;
	}
	else
	{
		int gh = 0;
	}
	//std::set<TreeNode<T>* >::iterator it = setTreeNode_.find(node);
	return *(ret.first);
}

template<typename T>
void Tree<T>::setParentChildRelation(TreeNode<T>* parent, TreeNode<T>* child)
{
	(*parent).addChild(child);
	(*child).setParent(parent);
}

template<typename T>
void Tree<T>::addNode(T item)
{
	// add only if there's no node with item as its element
	std::vector<TreeNode<T>* >::iterator it = std::find_if(vecTreeNode_.begin(),vecTreeNode_.end(),equal_item<TreeNode<T>*,T>(item));
	if (it == vecTreeNode_.end())
	{
		//printf("Not found: %d\n",item);
		TreeNode<T>* node = new TreeNode<T>(item);
		vecTreeNode_.push_back(node);
		//return &vecTreeNode_.back();
	}
	else
	{
		//printf("Found: %d\n",item);
		//return &(*it);
	}
}

template<typename T>
void Tree<T>::setParentChildRelation(T parentItem, T childItem)
{
	std::vector<TreeNode<T>* >::iterator pIt = std::find_if(vecTreeNode_.begin(),vecTreeNode_.end(),equal_item<TreeNode<T>*,T>(parentItem));
	std::vector<TreeNode<T>* >::iterator cIt = std::find_if(vecTreeNode_.begin(),vecTreeNode_.end(),equal_item<TreeNode<T>*,T>(childItem));

	(**pIt).addChild(*cIt);
	(**cIt).setParent(*pIt);
}

template<typename T>
T Tree<T>::compute_nearest_common_ancestor(T item1, T item2)
{
	std::vector<TreeNode<T>* > vecAncestorItem1, vecAncestorItem2;

	TreeNode<T>* node1 = new TreeNode<T>(item1);
	SetTreeNode::iterator it1 = setTreeNode_.find(node1);
	assert( (it1 != setTreeNode_.end()) && "item1 not present in tree");
	delete node1;
	//std::vector<TreeNode<T>* >::iterator it1 = std::find_if(vecTreeNode_.begin(),vecTreeNode_.end(),equal_item<TreeNode<T>*,T>(item1));
	vecAncestorItem1.push_back(*it1);

	while (true)
	{
		TreeNode<T>* prevNode = vecAncestorItem1.back();
		TreeNode<T>* parent = (*prevNode).parent();
		if (parent == NULL)
		{
			break;
		}
		vecAncestorItem1.push_back(parent);
	}

	TreeNode<T>* node2 = new TreeNode<T>(item2);
	SetTreeNode::iterator it2 = setTreeNode_.find(node2);
	assert( (it2 != setTreeNode_.end()) && "item2 not present in tree");
	delete node2;
	//std::vector<TreeNode<T>* >::iterator it2 = std::find_if(vecTreeNode_.begin(),vecTreeNode_.end(),equal_item<TreeNode<T>*,T>(item2));
	vecAncestorItem2.push_back(*it2);

	while (true)
	{
		TreeNode<T>* prevNode = vecAncestorItem2.back();
		TreeNode<T>* parent = (*prevNode).parent();
		if (parent == NULL)
		{
			break;
		}
		vecAncestorItem2.push_back(parent);
	}

	TreeNode<T>* nearestCommonAncestor = vecAncestorItem1.back();
	std::vector<TreeNode<T>* >::reverse_iterator rit1,rit2;
	for (rit1 = vecAncestorItem1.rbegin(),rit2 = vecAncestorItem2.rbegin(); ((rit1 != vecAncestorItem1.rend()) && (rit2 != vecAncestorItem2.rend())); ++rit1,++rit2)
	{
		if ( (**rit1).item() != (**rit2).item() )
		{
			break;
		}
		else
		{
			nearestCommonAncestor = *rit1;
		}
	}
	
	return (*nearestCommonAncestor).item();
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
		scanf("%d",&nCase);
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
			scanf("%d",&nInputLine);
		}

		tree.readInput(pFile,nInputLine-1);
		//tree.writeOutput();

		// Now read the two nodes whose common ancestor needs to be computed
		int item1,item2;
		if (READ_FROM_FILE)
		{
			fscanf(pFile,"%d",&item1);
			fscanf(pFile,"%d",&item2);
		}
		else
		{
			scanf("%d",&item1);
			scanf("%d",&item2);
		}

		printf("%d\n",tree.compute_nearest_common_ancestor(item1,item2));
	}

	/*
	std::vector<TreeNode<int>* > vecTreeNode;
	
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