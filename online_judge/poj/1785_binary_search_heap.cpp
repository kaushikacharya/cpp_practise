// http://poj.org/problem?id=1785
#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring> // strcpy
#include <cstdlib> // atoi, itoa
#include <algorithm>
#include <vector>
#include <limits>
#include <stack>
#include <ctime>
#include <cassert>

#define READ_FROM_FILE 0
#define MAX_N 10

template<typename T1, typename T2>
class Node
{
public:
	Node(T1 label, T2 priority, Node<T1,T2>* leftNode=NULL, Node<T1,T2>* rightNode=NULL, Node<T1,T2>* parentNode=NULL);
	~Node();
public:
	T1 label();
	T2 priority();
	bool visited();
	void setVisited(bool flag=true);
	void setLeft(Node<T1,T2>* leftNode);
	void setRight(Node<T1,T2>* rightNode);
	void setParent(Node<T1,T2>* parentNode);
	Node<T1,T2>* left();
	Node<T1,T2>* right();
	Node<T1,T2>* parent();
private:
	T1 label_;
	T2 priority_;
	bool visited_;
	Node<T1,T2>* leftNode_;
	Node<T1,T2>* rightNode_;
	Node<T1,T2>* parentNode_;
};

template<typename T1, typename T2>
class Treap
{
public:
	Treap(std::vector<Node<T1,T2>*>& vecNode);
	~Treap();
public:
	bool isEmpty();
	void add_node_to_tree(unsigned int node_i);
	void construct_treap();
	void inOrderTraversal(std::string& str);
private:
	Node<T1,T2>* construct_treap_recursive(unsigned int beginIndex, unsigned int endIndex, std::string& str);
private:
	std::vector<Node<T1,T2>*> vecNode_;
	Node<T1,T2>* root_;
};
// -------------------------------------------------------------
template<typename T1, typename T2>
Node<T1,T2>::Node(T1 label, T2 priority, Node<T1,T2>* leftNode, Node<T1,T2>* rightNode, Node<T1,T2>* parentNode)
: label_(label)
, priority_(priority)
, leftNode_(leftNode)
, rightNode_(rightNode)
, parentNode_(parentNode)
{
	visited_ = false;
}

template<typename T1, typename T2>
Node<T1,T2>::~Node()
{
	//delete leftNode_;
	//delete rightNode_;
}

template<typename T1, typename T2>
T1 Node<T1,T2>::label()
{
	return label_;
}

template<typename T1, typename T2>
T2 Node<T1,T2>::priority()
{
	return priority_;
}

template<typename T1, typename T2>
bool Node<T1,T2>::visited()
{
	return visited_;
}

template<typename T1, typename T2>
void Node<T1,T2>::setVisited(bool flag)
{
	visited_ = flag;
}

template<typename T1, typename T2>
void Node<T1,T2>::setLeft(Node<T1,T2>* leftNode)
{
	leftNode_ = leftNode;
}

template<typename T1, typename T2>
void Node<T1,T2>::setRight(Node<T1,T2> *rightNode)
{
	rightNode_ = rightNode;
}

template<typename T1, typename T2>
void Node<T1,T2>::setParent(Node<T1,T2>* parentNode)
{
	parentNode_ = parentNode;
}

template<typename T1, typename T2>
Node<T1,T2>* Node<T1,T2>::left()
{
	return leftNode_;
}

template<typename T1, typename T2>
Node<T1,T2>* Node<T1,T2>::right()
{
	return rightNode_;
}

template<typename T1, typename T2>
Node<T1,T2>* Node<T1,T2>::parent()
{
	return parentNode_;
}

// http://stackoverflow.com/questions/2057610/stl-map-with-custom-compare-function-object
// http://www.codeproject.com/Articles/38381/STL-Sort-Comparison-Function
// http://fusharblog.com/3-ways-to-define-comparison-functions-in-cpp/
template<typename T1, typename T2>
bool Comp(Node<T1,T2>* node1, Node<T1,T2>* node2)
{
	return node1->label() < node2->label();
}
// -------------------------------------------------------------
template<typename T1, typename T2>
Treap<T1,T2>::Treap(std::vector<Node<T1,T2>*>& vecNode)
: vecNode_(vecNode)
{
	// if node labels in the vector not in sorted form then sort them
	root_ = NULL;
	bool sortedFlag = true;
	for (unsigned int i = 1; i != vecNode_.size(); ++i)
	{
		if (vecNode_[i]->label() < vecNode_[i-1]->label())
		{
			sortedFlag = false;
			break;
		}
	}

	if (!sortedFlag)
	{
		std::sort(vecNode_.begin(), vecNode_.end(), Comp<T1,T2>);
	}
}

template<typename T1, typename T2>
Treap<T1,T2>::~Treap()
{
	//delete root_;
	for (std::vector<Node<T1,T2>*>::iterator it = vecNode_.begin(); it != vecNode_.end(); ++it)
	{
		delete (*it);
	}
}

template<typename T1, typename T2>
bool Treap<T1,T2>::isEmpty()
{
	return root_ == NULL;
}

template<typename T1, typename T2>
void Treap<T1,T2>::construct_treap()
{
	// root_ = construct_treap_recursive(0,vecNode_.size(),str);
	for (unsigned int node_i = 0; node_i != vecNode_.size(); ++node_i)
	{
		//add node to treap
		add_node_to_tree(node_i);
	}
}

template<typename T1, typename T2>
void Treap<T1,T2>::add_node_to_tree(unsigned int node_i)
{
	Node<T1,T2>* curNode = vecNode_[node_i];
	if (root_ == NULL)
	{
		root_ = curNode;
		return;
	}
	
	if ( (*root_).priority() < (*curNode).priority() )
	{
		(*curNode).setLeft(root_);
		(*root_).setParent(curNode);
		root_ = curNode;
	}
	else
	{
		Node<T1,T2>* node = vecNode_[node_i-1];
		if ( (*curNode).priority() < (*node).priority() )
		{
			(*node).setRight(curNode);
			(*curNode).setParent(node);
		}
		else
		{
			// start climbing up till we reach the appropriate position
			Node<T1,T2>* parentNode = (*node).parent();
			while ( (*parentNode).priority() < (*curNode).priority() )
			{
				node = parentNode;
				parentNode = (*node).parent();
				assert( (parentNode != NULL) && "Not possible" );
			}
			(*curNode).setLeft(node);
			(*node).setParent(curNode);
			(*parentNode).setRight(curNode);
			(*curNode).setParent(parentNode);
		}
	}
}

template<typename T1, typename T2>
void Treap<T1,T2>::inOrderTraversal(std::string& str)
{
	std::stack<Node<T1,T2>*> stk;
	bool flag_itoa = true; //itoa is absent in linux
	
	stk.push(root_);
	(*root_).setVisited(true);

	unsigned int countRight = 0;
	str += '(';
	while (!stk.empty())
	{
		Node<T1,T2>* topNode = stk.top();
		Node<T1,T2>* leftNode = (*topNode).left();
		bool visitLeft = false;

		if (leftNode)
		{
			if (!(*leftNode).visited())
			{
				str += '(';
				visitLeft = true;
				stk.push(leftNode);
				(*leftNode).setVisited(true);
			}
			else
			{
				str += ')';
			}
		}

		if (!visitLeft)
		{
			// print the top of stack
			str += (*topNode).label();
			str += '/';
			
			if (flag_itoa)
			{
				char numstr[MAX_N];
				itoa((*topNode).priority(),numstr,10);
				str += numstr;
			}
			else
			{
				std::stringstream numstr;
				numstr << (*topNode).priority();
				str += numstr.str();
			}

			stk.pop();

			Node<T1,T2>* rightNode = (*topNode).right();

			if (rightNode)
			{
				str += '(';
				++countRight;
				(*rightNode).setVisited(true);
				stk.push(rightNode);
			}
			else
			{
				Node<T1,T2>* parentNode = (*topNode).parent();
				Node<T1,T2>* childNode = topNode;
				while (parentNode && ( (*parentNode).right() == childNode))
				{
					str += ')';
					childNode = parentNode;
					parentNode = (*parentNode).parent();
				}
			}
		}

/*
		if (leftNode && !(*leftNode).visited())
		{
			str += '(';
			stk.push(leftNode);
			(*leftNode).setVisited(true);
		} 
		else
		{
			str += (*topNode).label();
			str += '/';
			char numstr[MAX_N];
			itoa((*topNode).priority(),numstr,10);

			stk.pop();

			Node<T1,T2>* rightNode = (*topNode).right();
			
			if (rightNode)
			{
				str += '(';
				(*rightNode).setVisited(true);
				stk.push(rightNode);
			}
			else
			{
				str += ')';
			}
		}
*/
	}
	str += ')';
}

template<typename T1, typename T2>
Node<T1,T2>* Treap<T1,T2>::construct_treap_recursive(unsigned int beginIndex, unsigned int endIndex, std::string& str)
{
	// create sub-tree of nodes [beginIndex,endIndex) //endIndex excluded
	// root of the subtree is the node which has highest priority
	if (endIndex - beginIndex == 1)
	{
		str += '(';
		str += vecNode_[beginIndex]->label();
		str += '/';
		// http://stackoverflow.com/questions/191757/c-concatenate-string-and-int
		//char numstr[MAX_N];
		//itoa(vecNode_[beginIndex]->priority(),numstr,10);
		//str += numstr;
		// http://stackoverflow.com/questions/228005/alternative-to-itoa-for-converting-integer-to-string-c
		std::stringstream numstr;
		numstr << vecNode_[beginIndex]->priority();
		str += numstr.str();
		str += ')';
		return vecNode_[beginIndex];
	}
	unsigned int maxPriorityIndex = beginIndex;
	T2 maxPriority = (vecNode_[maxPriorityIndex])->priority();
	for (unsigned int index=beginIndex+1; index != endIndex; ++index)
	{
		if (vecNode_[index]->priority() > maxPriority)
		{
			maxPriorityIndex = index;
			maxPriority = vecNode_[maxPriorityIndex]->priority();
		}
	}
	Node<T1,T2>* curRoot = vecNode_[maxPriorityIndex];
	str.push_back('(');
	if (maxPriorityIndex > beginIndex)
	{
		Node<T1,T2>* leftSubtreeRoot = construct_treap_recursive(beginIndex,maxPriorityIndex,str);
		curRoot->setLeft(leftSubtreeRoot);
		leftSubtreeRoot->setParent(curRoot);
	}
	str += curRoot->label();
	//str.push_back((char)(curRoot->label().c_str()));
	str.push_back('/');
	/*
	char numstr[MAX_N];
	itoa(curRoot->priority(),numstr,10);
	str += numstr;
	*/
	std::stringstream numstr;
	numstr << (*curRoot).priority();
	str += numstr.str();
	//str.push_back(curRoot->priority());
	if (maxPriorityIndex < (endIndex-1))
	{
		Node<T1,T2>* rightSubtreeRoot = construct_treap_recursive(maxPriorityIndex+1,endIndex,str);
		curRoot->setRight(rightSubtreeRoot);
		rightSubtreeRoot->setParent(curRoot);
	}
	str.push_back(')');
	return curRoot;
}
// -------------------------------------------------------------
int main(int argc, char* argv[])
{
	std::fstream pFile;
	if (READ_FROM_FILE)
	{
		pFile.open("d:/cpp_practise/online_judge/poj/1785_binary_search_heap_input.txt",std::fstream::in);
	}

	//printf("max(unsigned int): %u\n",std::numeric_limits<unsigned int>::max());
	//printf("max digits(unsigned int): %d\n",std::numeric_limits<unsigned int>::digits10);

	int total_time = 0;
	while (true)
	{
		clock_t t = clock();
		std::string strLine;
		if (READ_FROM_FILE)
		{
			std::getline(pFile,strLine);
		} 
		else
		{
			std::getline(std::cin,strLine);
		}
		
		// http://learnedstuffs.wordpress.com/2012/01/08/c-strtok-and-string-manipulation/
		char* strLineArr = new char[strLine.size()+1];
		std::strcpy(strLineArr,strLine.c_str());
		char* strNodePtr = strtok(strLineArr," ");

		//std::string strNode = std::string(strNodePtr); // char* to string
		unsigned int nNode = atoi(strNodePtr);
		if (nNode == 0)
		{
			break;
		}
		strNodePtr = strtok(NULL," ");
		
		std::vector<Node<std::string,unsigned int>*> vecNode;
		vecNode.reserve(nNode);
		
		while (strNodePtr != NULL)
		{
			// http://stackoverflow.com/questions/12353973/sizeof-char-array-in-c-c
			/*
			std::size_t lenStrNode = sizeof(strNodePtr)/sizeof(strNodePtr[0]); //MISTAKE: This will give size of char data type
			std::string strNode = std::string(strNodePtr,strNodePtr+lenStrNode);
			*/
			// http://www.cplusplus.com/reference/string/string/string/
			std::string strNode = std::string(strNodePtr); // char* to string
			std::size_t pos = strNode.find("/");
			std::string strLabel = strNode.substr(0,pos);
			unsigned int priority = atoi((strNode.substr(pos+1)).c_str());
			Node<std::string,unsigned int>* node = new Node<std::string,unsigned int>(strLabel,priority);
			vecNode.push_back(node);
			
			strNodePtr = strtok(NULL," ");
			//int gk = 0;
		}

		// http://stackoverflow.com/questions/5481503/how-to-delete-char-in-c
		delete []strLineArr;

		Treap<std::string,unsigned int> treap(vecNode);
		std::string str;
		str.reserve(strLine.size()+2*vecNode.size());
		treap.construct_treap();
		treap.inOrderTraversal(str);
		printf("%s\n",str.c_str());
		t = clock() - t;
		total_time += t;
		printf("size: %d :: clicks: %d :: time(in sec): %f\n",vecNode.size(),t,((float)t)/CLOCKS_PER_SEC);
	}

	if (READ_FROM_FILE)
	{
		pFile.close();
	}

	printf("TOTAL:: clicks: %d :: time(in sec): %f\n",total_time,((float)total_time)/CLOCKS_PER_SEC);
	return 0;
}

/*
For huge no of nodes(e.g. last two test cases) recursive traversal gets into stack overflow.

Iterative in-order traversal
http://leetcode.com/2010/04/binary-search-tree-in-order-traversal.html

itoa missing in Linux o/s
http://www.jenkinssoftware.com/forum/index.php?topic=4629.0
*/