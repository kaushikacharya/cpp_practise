// http://poj.org/problem?id=1258
// http://www.tutorialspoint.com/cplusplus/cpp_dynamic_memory.htm
//		Good resource to understand dynamic memory in c++

// http://www.cplusplus.com/reference/new/operator%20new%5B%5D/
//		Allocate memory without constructing object

#include <cstdio>
#include <limits>
#include <vector>
#include <bitset>

#define READ_FROM_FILE 0

template<typename T>
class Graph
{
public:
	Graph(unsigned int n);
	~Graph();
public:
	void add_element(T num, unsigned int row, unsigned int col);
	T get_element(unsigned int row, unsigned int col);
	void show_matrix();
	unsigned int size();
	T* adjMatrix();
private:
	unsigned int n_;
	T* adjMatrix_;
};

template<typename T>
Graph<T>::Graph(unsigned int n)
: n_(n)
{
	// http://stackoverflow.com/questions/10062655/how-do-i-allocate-memory-for-a-2d-array
	/* Mike DeSimone explains both way of doing 2 dimensional array.
	   a) converting it to one dimension array.
	   b) creating a helper class for 2 dimension.
	*/
	adjMatrix_ = NULL;
	adjMatrix_ = new T [n*n];
}

template<typename T>
Graph<T>::~Graph()
{
	delete[] adjMatrix_;
}

template<typename T>
void Graph<T>::add_element(T num, unsigned int row, unsigned int col)
{
	// row*numCols + col
	adjMatrix_[row*n_ + col] = num;
}

template<typename T>
T Graph<T>::get_element(unsigned int row, unsigned int col)
{
	return adjMatrix_[row*n_ + col];
}

template<typename T>
void Graph<T>::show_matrix()
{
	for (unsigned int i = 0; i < n_; ++i)
	{
		for (unsigned int j = 0; j < n_; ++j)
		{
			if (j > 0)
			{
				printf(" ");
			}
			printf("%d",adjMatrix_[i*n_+j]);
		}
		printf("\n");
	}
}

template<typename T>
unsigned int Graph<T>::size()
{
	return n_;
}

template<typename T>
T* Graph<T>::adjMatrix()
{
	return adjMatrix_;
}

// ---------------------------------

template<typename T>
class Prim
{
public:
	Prim(Graph<T>& graph);
	~Prim();
public:
	void compute_MST();
	T cost_MST();
private:
private:
	Graph<T>& graph_;
	std::vector<T> vecCost_;
};

template<typename T>
Prim<T>::Prim(Graph<T>& graph)
: graph_(graph)
{
	// initialize cost for each vertex node
	vecCost_.reserve(graph_.size());
	for (unsigned int i = 0; i < graph_.size(); ++i)
	{
		vecCost_.push_back(std::numeric_limits<T>::max());
	}
}

template<typename T>
Prim<T>::~Prim()
{
	int gh = 0;
}

template<typename T>
void Prim<T>::compute_MST()
{
	unsigned int nVertex = graph_.size();
	//printf("nVertex: %d\n",nVertex);

	//std::bitset<graph_.size()> myBitSet;
	std::vector<bool> vecBool;
	vecBool.reserve(graph_.size());
	for (unsigned int i = 0; i < graph_.size(); ++i)
	{
		vecBool.push_back(false);
	}

	unsigned int curIndex = 0; //Can start from any vertex
	vecCost_[curIndex] = 0;
	unsigned int count = 0;
	
	while (count < nVertex)
	{
		vecBool[curIndex] = true;
		unsigned int minIndex = curIndex; // dummy initialization
		T minCost = std::numeric_limits<T>::max();

		for (unsigned int i = 0; i < graph_.size(); ++i)
		{
			if (!vecBool[i])
			{
				T elem = graph_.get_element(curIndex,i);
				if (elem < vecCost_[i])
				{
					vecCost_[i] = elem;
				}
				if (vecCost_[i] < minCost)
				{
					minCost = vecCost_[i];
					minIndex = i;
				}
			}
		}

		curIndex = minIndex;
		++count;
	}

}

template<typename T>
T Prim<T>::cost_MST()
{
	T cost = 0;
	for (std::vector<T>::iterator it = vecCost_.begin(); it != vecCost_.end(); ++it)
	{
		cost += (*it);
	}

	return cost;
}

// -----------------------------

int main(int argc, char* argv[])
{
	unsigned int n;
	FILE* pFile;

	if (READ_FROM_FILE)
	{
		pFile = fopen("D:/cpp_practise/online_judge/poj/1258_agri_net_input.txt","r");
	} 
	else
	{
		pFile = 0;
	}
 
	while(true)
	{
		if (READ_FROM_FILE)
		{
			if (fscanf(pFile,"%d",&n) == EOF)
			{
				break;
			}
		} 
		else
		{
			if (scanf("%d",&n) == EOF)
			{
				break;
			}
		}

		Graph<int> graph(n);
		int dist;
		
		for (unsigned int i = 0; i < n; ++i)
		{
			for (unsigned int j = 0; j < n; ++j)
			{
				if (READ_FROM_FILE)
				{
					fscanf(pFile,"%d",&dist);
				} 
				else
				{
					scanf("%d",&dist);
				}
				graph.add_element(dist,i,j);
			}
		}

		// graph.show_matrix(); // for debugging
		Prim<int> prim(graph);
		prim.compute_MST();
		printf("%d\n",prim.cost_MST());
		
	}
	return 0;
}

/*
The solution here is O(V^2).

http://stackoverflow.com/questions/716341/prims-algorithm-time-complexity
http://stackoverflow.com/questions/2011753/why-do-kruskal-and-prim-mst-algorithms-have-different-runtimes-for-sparse-and-de

11769509	kaushik_acharya	1258	Accepted	216K	16MS	C++	4677B	2013-07-12 14:19:45

TBD: Random Graph generation: http://www.cs.rit.edu/~rlc/Courses/Algorithms/Projects/project-mst.html
Alternate solution is http://en.wikipedia.org/wiki/Edmonds%27_algorithm

http://en.wikipedia.org/wiki/Prim%27s_algorithm
Check the time complexity based on various implementation.
*/