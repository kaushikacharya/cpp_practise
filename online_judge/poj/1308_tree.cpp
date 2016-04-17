// http://poj.org/problem?id=1308
#include <cstdio>
#include <vector>
#include <set>

template<typename T>
struct Comp
{
	bool operator()(const T& node1, const T& node2) const
	{
		return (*node1).item() < (*node2).item();
	}
};

template<typename T>
class Node
{
public:
	Node(T item, Node* parent=NULL);
	~Node();
public:
	T item();
	Node* parent();
	void setParent(Node* node);
	void add_adjacent_node(Node* adjNode);
private:
	T item_;
	Node* parent_;
	std::vector<Node*> adjacencyList_;
};

template<typename T>
Node<T>::Node(T item, Node<T>* parent)
: item_(item)
, parent_(parent)
{
}

template<typename T>
Node<T>::~Node()
{
}

template<typename T>
T Node<T>::item()
{
	return item_;
}

template<typename T>
Node<T>* Node<T>::parent()
{
	return parent_;
}

template<typename T>
void Node<T>::setParent(Node* node)
{
	parent_ = node;
}

template<typename T>
void Node<T>::add_adjacent_node(Node* adjNode)
{
	adjacencyList_.push_back(adjNode);
}

// -----------------------------------------

template<typename T>
class Graph
{
public:
	Graph();
	~Graph();
public:
	bool add_edge(T item1, T item2);
	bool check_validity();
private:
	Node<T>* add_node(T item);
private:
	typedef std::set<Node<T>*,Comp<Node<T>*> > SetNode;
	SetNode setNodes_;
};

template<typename T>
Graph<T>::Graph()
{
}

template<typename T>
Graph<T>::~Graph()
{
}

// http://stackoverflow.com/questions/2620862/using-custom-stdset-comparator
template<typename T>
bool Graph<T>::add_edge(T item1, T item2)
{
	// search for nodes corresponding to item1,item2
	// if node2 has Null parent, add the edge between the nodes
	// else return false
	
	/*
	Node<T>* node1 = new Node(item1);
	Node<T>* node2 = new Node(item2);

	SetNode::iterator it1 = setNodes_.find(node1);
	SetNode::iterator it2 = setNodes_.find(node2);

	if (it1 == setNodes_.end())
	{
		setNodes_.insert(node1);
	}
	if (it2 == setNodes_.end())
	{
		setNodes_.insert(node2);
	}
	*/

	// node addition is done as in 1330
	Node<T>* node1 = add_node(item1);
	Node<T>* node2 = add_node(item2);

	if ( (*node2).parent() )
	{
		return false;
	}
	(*node2).setParent(node1);
	(*node1).add_adjacent_node(node2);

	return true;
}

template<typename T>
bool Graph<T>::check_validity()
{
	if (setNodes_.empty())
	{
		return true;
	}

	unsigned int rootNodeCount = 0;
	for (SetNode::iterator it = setNodes_.begin(); it != setNodes_.end(); ++it)
	{
		if ( (**it).parent() == NULL)
		{
			++rootNodeCount;
		}
	}

	if (rootNodeCount == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>
Node<T>* Graph<T>::add_node(T item)
{
	Node<T>* node = new Node<T>(item);
	std::pair<SetNode::iterator,bool> ret = setNodes_.insert(node);

	if (ret.second == false)
	{
		//item already exists
		delete node;
	} 
	else
	{
		int gh = 0;
	}

	return *(ret.first);
}

int main(int argc, char* argv[])
{
	int num1, num2;
	bool inputFlag = true;
	bool caseFlag;
	unsigned int treeCount = 0;

	while (inputFlag)
	{
		Graph<int> graph;
		bool valid_tree = true;
		caseFlag = true;

		while (caseFlag)
		{
			scanf("%d",&num1);
			scanf("%d",&num2);

			if ((num1 == 0) && (num2 == 0))
			{
				caseFlag = false;
			}
			else if ((num1 == -1) && (num2 == -1))
			{
				inputFlag = false;
				caseFlag = false;
				//valid_tree = false;
			}

			if (caseFlag)
			{
				if (valid_tree)
				{
					// add the edge
					valid_tree = graph.add_edge(num1,num2);
				}
				else
				{
					// No need to add more edges once found that a node has multiple fathers
				}
			}
		} // while (caseFlag)

		if (inputFlag)
		{
			// check the validity of tree
			if (valid_tree)
			{
				valid_tree = graph.check_validity();
			}
			++treeCount;
			if (valid_tree)
			{
				printf("Case %d is a tree.\n",treeCount);
			}
			else
			{
				printf("Case %d is not a tree.\n",treeCount);
			}
		}
	}

	return 0;
}

/*
source:
http://www.ntnu.edu.tw/acm/
http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_NorthCen/1997/index.html
http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_NorthCen/1997/prob_2.html
*/