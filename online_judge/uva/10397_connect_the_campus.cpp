// http://uva.onlinejudge.org/external/103/10397.html
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <limits>
#include <cmath>
#include <iomanip> //std::setprecision

const bool READ_FROM_FILE = false;

template<typename T>
struct Node
{
	Node(T build_index, T lead_index, Node<T>* nextNode=NULL)
		: building_index(build_index)
		, leader_index(lead_index)
		, next(nextNode)
	{
	}

    T building_index;
    T leader_index;
    Node<T>* next;
};

template<typename T>
struct List
{
	List(Node<T>* headNode=NULL)
		: head(headNode)
	{
	}
    Node<T>* head;
};

template<typename T1, typename T2>
struct Edge
{
    Edge(T1 node1, T1 node2, T2 weight)
        : node_i(node1)
        , node_j(node2)
        , cost(weight)
    {}

    T1 node_i;
    T1 node_j;
    T2 cost;
};

template<typename T1, typename T2>
struct Comp
{
    bool operator()(const Edge<T1,T2>& edge1, const Edge<T1,T2>& edge2)
    {
        return edge1.cost < edge2.cost;
    }
};

template<typename T>
class Building
{
public:
	Building(T x, T y)
		: x_(x)
		, y_(y)
	{}
public:
	T x(){ return x_;}
	T y(){ return y_;}
private:
	T x_;
	T y_;
};

// T1 - index
// T2 - coordinate
// T3 - cost
template<typename T1, typename T2, typename T3>
class Campus
{
public:
	Campus(T1 nBuilding)
		: nBuilding_(nBuilding)
	{
		vecBuilding_.reserve(nBuilding_);
		T1 matSize = nBuilding_*nBuilding_;
		distMatrix_.reserve(matSize);
		vecCablePresent_.reserve(matSize);

		// initialize with inf
		for (T1 sz = 0; sz != matSize; ++sz)
		{
			distMatrix_.push_back(std::numeric_limits<T3>::max());
			vecCablePresent_.push_back(false);
		}

		// create vector of edges for MST
		vecEdge_.reserve((nBuilding_ - 1)*nBuilding_/2);
		vecNode_.reserve(nBuilding_);
		vecList_.reserve(nBuilding_);
		vecCount_.reserve(nBuilding_);

		for (T1 node_i = 0; node_i != nBuilding_; ++node_i)
		{
			Node<T1>* node = new Node<T1>(node_i,node_i);
			vecNode_.push_back(node);
			vecList_.push_back(node);
			vecCount_.push_back(1);
		}
	}
	~Campus()
	{
		for (typename std::vector<Node<T1>* >::iterator nodeIt = vecNode_.begin(); nodeIt != vecNode_.end(); ++nodeIt)
		{
			Node<T1>* node = (*nodeIt);
			delete node;
		}
	}
public:
	void add_building(Building<T2>& building)
	{
		vecBuilding_.push_back(building);
	}
	void existing_cable(T1 i, T1 j)
	{
		vecCablePresent_[i*nBuilding_ + j] = true;
		vecCablePresent_[j*nBuilding_ + i] = true;
	}
	void update_cable_cost(T1 i, T1 j, T3 cost)
	{
		distMatrix_[i*nBuilding_ + j] = cost;
		distMatrix_[j*nBuilding_ + i] = cost;
		// get the vecEdge_ index
		if (j < i)
		{
			std::swap(i,j);
		}
		T1 ind = 0;
		T1 row = 0;
		for (; row != i; ++row)
		{
			ind += (nBuilding_ - row - 1);
		}
		ind += (j - row - 1);
		vecEdge_[ind].cost = cost;
	}
	void compute_distance_matrix()
	{
		for (T1 i = 0; i != nBuilding_; ++i)
		{
			for (T1 j = i+1; j != nBuilding_; ++j)
			{
				T3 xGap = static_cast<T3>(vecBuilding_[i].x() - vecBuilding_[j].x());
				T3 yGap = static_cast<T3>(vecBuilding_[i].y() - vecBuilding_[j].y());
				T3 dist = std::sqrt(xGap*xGap + yGap*yGap);

				distMatrix_[i*nBuilding_ + j] = dist;
				distMatrix_[j*nBuilding_ + i] = dist;

                Edge<T1,T3> edge(i,j,dist);
				vecEdge_.push_back(edge);
			}
		}
	}
	void compute_kruskal_mst();
private:
	T1 nBuilding_;
	std::vector<Building<T2> > vecBuilding_;
	std::vector<T3> distMatrix_;
	std::vector<bool> vecCablePresent_;
private:

private:
	// Kruskal's Minimum Spanning Tree algorithm	
	std::vector<Edge<T1,T3> > vecEdge_;
	std::vector<T1> vecCount_; //
	std::vector<Node<T1>* > vecNode_;
	std::vector<List<T1> > vecList_; //List<T1>
};

template<typename T1, typename T2, typename T3>
void Campus<T1,T2,T3>::compute_kruskal_mst()
{
	// first sort the edges
	std::sort(vecEdge_.begin(), vecEdge_.end(), Comp<T1,T3>());

	T3 costNewCable = 0;
	for (typename std::vector<Edge<T1,T3> >::iterator edgeIt = vecEdge_.begin(); edgeIt != vecEdge_.end(); ++edgeIt)
	{
		Edge<T1,T3> edge = (*edgeIt);
		Node<T1>* node1 = vecNode_[edge.node_i];
		Node<T1>* node2 = vecNode_[edge.node_j];

		if (node1->leader_index != node2->leader_index)
		{
			T1 small_leader, big_leader;

			if (vecCount_[node2->leader_index] <= vecCount_[node1->leader_index])
			{
				small_leader = node2->leader_index;
				big_leader = node1->leader_index;
			} 
			else
			{
				small_leader = node1->leader_index;
				big_leader = node2->leader_index;
			}

			costNewCable += edge.cost;;
// 			if (!vecCablePresent_[edge.node_i*nBuilding_ + edge.node_j])
// 			{
// 				costNewCable += edge.cost;
// 			}

			while (vecList_[small_leader].head)
			{
				Node<T1>* node = vecList_[small_leader].head;
				Node<T1>* nextNode = node->next;
				node->leader_index = big_leader;
				node->next = vecList_[big_leader].head;
				--vecCount_[small_leader];
				vecList_[big_leader].head = node;
				++vecCount_[big_leader];
				vecList_[small_leader].head = nextNode;
			}
		}
	}

	std::cout << std::fixed << std::setprecision(2) << costNewCable << std::endl;
}

std::istream& pick_input(std::ifstream& pFile)
{
    if (READ_FROM_FILE)
	{
		pFile.open("D:/cpp_practise/online_judge/uva/10397_connect_the_campus_input.txt", std::ios::in);
		assert(pFile.is_open() && "can't open the file\n");
        return pFile;
	}
    else
    {
        return std::cin;
    }
}

int main(int argc, char* argv[])
{
    std::ifstream fileP;
	std::istream& pFile = pick_input(fileP);

	typedef unsigned long VType;
    typedef long CType; // coordinate (integers)
	typedef double DType; // distance

	VType nBuilding;
	CType x,y;
	VType nExistCable;
	VType node1, node2;

    while (pFile >> nBuilding)
    {
        Campus<VType,CType,DType> campus(nBuilding);

        for (VType build_i = 0; build_i != nBuilding; ++build_i)
        {
            pFile >> x >> y;
            Building<CType> building(x,y);
            campus.add_building(building);
        }

        campus.compute_distance_matrix();

        // now read the existing cables
        pFile >> nExistCable;

        for (VType cable_i = 0; cable_i != nExistCable; ++cable_i)
        {
            pFile >> node1 >> node2;
            //campus.existing_cable(node1-1, node2-1);
			campus.update_cable_cost(node1-1, node2-1, 0.0);
        }

        campus.compute_kruskal_mst();
        int gh = 0;
    }

    if (READ_FROM_FILE)
    {
        fileP.close();
    }

	return 0;
}

/*
http://bytes.com/topic/c/answers/667481-copy-std-cin-ifstream
http://online-judge.uva.es/board/viewtopic.php?f=20&t=2957&hilit=10397+connect+the+campus
*/