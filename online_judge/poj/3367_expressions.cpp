// http://poj.org/problem?id=3367
// 30th June 2013
// http://stackoverflow.com/questions/8018686/binary-search-tree-destructor
// http://stackoverflow.com/questions/728068/how-to-calculate-a-time-difference-in-c  bayda's solution
// http://stackoverflow.com/questions/16354166/scalar-deleting-destructor

#include <cstdio>
#include <iostream>
#include <cctype> // isupper
#include <stack>
#include <queue>
#include <cassert>
#include <ctime>
#include <string>
#include <vector>
#include <map>

#define READ_FROM_FILE 0
#define WRITE_INTO_FILE 0
#define MAX_STR_LENGTH 10001

//std::map<void*,bool> ptr_map_;

template<typename T>
class TreeNode
{
public:
	TreeNode(T item, TreeNode* parent=NULL, TreeNode* left=NULL, TreeNode* right=NULL);
	~TreeNode();
public:
	T item();
	TreeNode* left();
	TreeNode* right();
	TreeNode* parent();
	void setLeft(TreeNode* leftNode);
	void setRight(TreeNode* rightNode);
	void setParent(TreeNode* parentNode);
private:
	T item_;
	TreeNode* parent_;
	TreeNode* left_;
	TreeNode* right_;
	unsigned int delCount_;
};

template<typename T>
TreeNode<T>::TreeNode(T item, TreeNode* parent, TreeNode* left, TreeNode* right)
: item_(item)
, parent_(parent)
, left_(left)
, right_(right)
{
	//delCount_ = 0;
}

template<typename T>
TreeNode<T>::~TreeNode()
{
	//++delCount_;
	//printf(" %c%d ",(*this).item(),delCount_);
	/*
	std::map<void*,bool>::iterator it = ptr_map_.find(this);
	assert((it==ptr_map_.end()) && "pointer already deleted");
	ptr_map_.insert(std::make_pair(this,true));
	*/
	//std::cout << static_cast<void*>(this);
	//delete left_;
	//delete right_;
	
}

template<typename T>
T TreeNode<T>::item()
{
	return item_;
}

template<typename T>
TreeNode<T>* TreeNode<T>::left()
{
	return left_;
}

template<typename T>
TreeNode<T>* TreeNode<T>::right()
{
	return right_;
}

template<typename T>
TreeNode<T>* TreeNode<T>::parent()
{
	return parent_;
}

template<typename T>
void TreeNode<T>::setLeft(TreeNode* leftNode)
{
	left_ = leftNode;
}

template<typename T>
void TreeNode<T>::setRight(TreeNode* rightNode)
{
	right_ = rightNode;
}

template<typename T>
void TreeNode<T>::setParent(TreeNode* parentNode)
{
	parent_ = parentNode;
}
// ------------

template<typename T>
class Tree
{
public:
	Tree(TreeNode<T>* root=NULL);
	~Tree();
public:
	void read_input(FILE* pFile);
	void readInput(FILE* pFile);
	bool readChar(FILE* pFile, char& ch);
	void traversal();
	void writeOutput(FILE* pFile);
	void write_output(FILE* pFile);
	unsigned int size();
private:
	TreeNode<T>* root_;
	//std::stack<TreeNode<T>* > stk_;
	std::vector<T> vec_;
	std::string str_;
	unsigned int size_;
};

template<typename T>
Tree<T>::Tree(TreeNode<T>* root)
: root_(root)
{
	size_ = 0;
}

// http://stackoverflow.com/questions/16258213/non-recursive-destructor-for-binary-search-tree-by-implementing-stack
template<typename T>
Tree<T>::~Tree()
{
	//delete root_;
	//printf("\n");
}

template<typename T>
void Tree<T>::read_input(FILE* pFile)
{
	std::stack<TreeNode<T>* > stk;
	//char* str = (char*)malloc(MAX_STR_LENGTH);
	// http://stackoverflow.com/questions/51592/is-there-a-need-to-destroy-char-string-or-char-new-char6
	char* str = new char[MAX_STR_LENGTH];
	
	if (READ_FROM_FILE)
	{
		fgets(str,MAX_STR_LENGTH+1,pFile);
		str = strtok(str,"\n");
	}
	else
	{
		gets(str);
	}
	
	unsigned int i = 0;

	while (str[i] != '\0')
	{
		char ch = str[i];
		TreeNode<T>* node = new TreeNode<T>(ch);

		if (isupper(ch))
		{
			TreeNode<T>* rightNode = stk.top();
			stk.pop();
			TreeNode<T>* leftNode = stk.top();
			stk.pop();
			// set the parent-child relations
			(*node).setRight(rightNode);
			(*rightNode).setParent(node);
			(*node).setLeft(leftNode);
			(*leftNode).setParent(node);
		}

		stk.push(node);
		++i;
		++size_;
	} // while

	delete[] str;
	//free(str);

	// assign the root of the tree
	root_ = stk.top();
	stk.pop();
}

template<typename T>
void Tree<T>::readInput(FILE* pFile)
{
	char ch;
	std::stack<TreeNode<T>* > stk;
	
	while ( (*this).readChar(pFile,ch) )
	{
		TreeNode<T>* node = new TreeNode<T>(ch);
		
		if (isupper(ch))
		{
			TreeNode<T>* rightNode = stk.top();
			stk.pop();
			TreeNode<T>* leftNode = stk.top();
			stk.pop();
			// set the parent-child relations
			(*node).setRight(rightNode);
			(*rightNode).setParent(node);
			(*node).setLeft(leftNode);
			(*leftNode).setParent(node);
		}

		stk.push(node);
	} // while

	// assign the root of the tree
	root_ = stk.top();
}

template<typename T>
bool Tree<T>::readChar(FILE* pFile, char& ch)
{
	if (READ_FROM_FILE)
	{
		return ( (fscanf(pFile,"%c",&ch) != EOF) && (ch != '\n') );
	}
	else
	{
		return ((scanf("%c",&ch) != EOF) && (ch != '\n'));
	}
}

template<typename T>
void Tree<T>::traversal()
{
	std::queue<TreeNode<T>* > qu;
	
	str_.reserve(size_);
	//vec_.reserve(size_);
	qu.push(root_);

	while (!qu.empty())
	{
		TreeNode<T>* node = qu.front();
		str_.push_back((*node).item());
		//vec_.push_back((*node).item());

		qu.pop();

		if ((*node).left())
		{
			qu.push((*node).left());
		}
		if ((*node).right())
		{
			qu.push((*node).right());
		}
	}
}

template<typename T>
void Tree<T>::writeOutput(FILE* pFile)
{
	/*
	while (!stk_.empty())
	{
		TreeNode<T>* node = stk_.top();
		printf("%c",(*node).item());
		stk_.pop();
	}
	printf("\n");
	*/
	std::string str;
	/*
	while (!stk_.empty())
	{
		TreeNode<T>* node = stk_.top();
		str.push_back((*node).item());
		stk_.pop();
	}
	str.push_back('\n');
	*/

	str.reserve(size_);
	for (std::vector<T>::reverse_iterator rIt=vec_.rbegin(); rIt != vec_.rend(); ++rIt)
	{
		str.push_back((*rIt));
	}
	str.push_back('\n');

	if (WRITE_INTO_FILE)
	{
		fprintf(pFile,"%s",str.c_str());
	}
	else
	{
		printf("%s",str.c_str());
		//std::cout << str;
	}
}

template<typename T>
void Tree<T>::write_output(FILE* pFile)
{
	std::string str = std::string(str_.rbegin(),str_.rend());
	//str.push_back('\n');

	if (WRITE_INTO_FILE)
	{
		fprintf(pFile,"%s\n",str.c_str());
	}
	else
	{
		printf("%s\n",str.c_str());
	}
	
}

template<typename T>
unsigned int Tree<T>::size()
{
	return size_;
}

int main(int argc, char* argv[])
{
	unsigned int nCase;
	char ch;
	FILE* pFile;
	FILE* pOutFile;

	if (READ_FROM_FILE)
	{
		pFile = fopen("D:/cpp_practise/online_judge/poj/3367_expressions.in","r");
		fscanf(pFile,"%d",&nCase);
		fscanf(pFile,"%c",&ch); // reading '\n'
	}
	else
	{
		pFile = 0;
		scanf("%d",&nCase);
		scanf("%c",&ch); // reading '\n'
	}

	//printf("nCase: %d\n",nCase);

	if (WRITE_INTO_FILE)
	{
		pOutFile = fopen("D:/cpp_practise/online_judge/poj/3367_expressions_output.txt","w");
	} 
	else
	{
		pOutFile = 0;
	}

	int total_time = 0;
	for(unsigned int case_i=0; case_i != nCase; ++case_i)
	{
		//ptr_map_.clear();
		clock_t t = clock();
		Tree<char> tree;
		tree.read_input(pFile);
		//tree.readInput(pFile);
		tree.traversal();
		//tree.writeOutput(pOutFile);
		tree.write_output(pOutFile);
		t = clock() - t;
		total_time += t;
		printf("size: %d :: clicks: %d :: time(in sec): %f\n",tree.size(),t,((float)t)/CLOCKS_PER_SEC);
	}
	printf("TOTAL:: clicks: %d :: time(in sec): %f\n",total_time,((float)total_time)/CLOCKS_PER_SEC);

	return 0;
}