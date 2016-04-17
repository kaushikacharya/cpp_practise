//http://uva.onlinejudge.org/external/8/820.html
#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <limits>
#include <cassert>

const bool READ_FROM_FILE = false;

template<typename T1, typename T2>
class FlowEdge
{
public:
	FlowEdge(T1 vertex1, T1 vertex2, T2 capacity)
		: vertex1_(vertex1)
		, vertex2_(vertex2)
		, flow_(0)
		, capacity_(capacity)
	{}
public:
	T1 other(T1 vertex) const
	{
		if (vertex == vertex1_)
		{
			return vertex2_;
		}
		else if (vertex == vertex2_)
		{
			return vertex1_;
		} 
		else
		{
			assert(false && "input should be either of the two vertices of the edge");
		}
	}
	T2 flow() const
	{
		return flow_;
	}
	T2 capacity() const
	{
		return capacity_;
	}
    void increase_capacity(T2 capacity)
    {
        capacity_ += capacity;
    }
	/*
	"connections are bi-directional...but the sum of the amount of data transmitted in both directions must be less than the bandwidth."
	*/
	T2 residual_capacity_to(T1 vertex) const
	{
		if ((vertex == vertex1_) || (vertex == vertex2_))
		{
			return capacity_ - flow_;
		} 
		else
		{
			assert(false && "input should be either of the two vertices of the edge");
		}
	}
	void update_flow_to(T1 vertex, T2 delta)
	{
		if ((vertex == vertex1_) || (vertex == vertex2_))
		{
			increase_flow(delta);
		} 
		else
		{
			assert(false && "input should be either of the two vertices of the edge");
		}
	}
private:
	void increase_flow(T2 delta)
	{
		flow_ += delta;
		assert((flow_ <= capacity_) && "overflow");
	}
	void decrease_flow(T2 delta)
	{
		assert((delta <= flow_) && "underflow");
		flow_ -= delta;
	}
private:
	T1 vertex1_;
	T1 vertex2_;
	T2 flow_;
	T2 capacity_;
};
//-----------------
template<typename T1, typename T2>
class FlowNetwork
{
public:
	FlowNetwork(T1 nVertex)
		: nVertex_(nVertex)
	{
		adjList_.reserve(nVertex_);
		vecVisited_.reserve(nVertex_);
		vecEdgeTo_.reserve(nVertex_);

		for (T1 vtx_i = 0; vtx_i != nVertex_; ++vtx_i)
		{
			adjList_.push_back(std::vector<T1>());
			vecVisited_.push_back(false);
			vecEdgeTo_.push_back(std::numeric_limits<T1>::max());
		}
	}
public:
	T1 nVertex() const
	{
		return nVertex_;
	}
	void add_edge(T1 vertex1, T1 vertex2, T2 capacity)
	{
        T1 edge_index;
        
        if (edge_already_exists(vertex1,vertex2, edge_index))
        {
            vecFlowEdge_[edge_index].increase_capacity(capacity);
        }
        else
        {
            FlowEdge<T1,T2> flowEdge(vertex1,vertex2,capacity);
            vecFlowEdge_.push_back(flowEdge);
            adjList_[vertex1].push_back(vecFlowEdge_.size()-1);
            adjList_[vertex2].push_back(vecFlowEdge_.size()-1);
        }
	}
private:
    bool edge_already_exists(T1 vertex, T1 otherVertex, T1& edge_index)
    {
        for (typename std::vector<T1>::iterator it = adjList_[vertex].begin(); it != adjList_[vertex].end(); ++it)
        {
            edge_index = *it;
            if (vecFlowEdge_[edge_index].other(vertex) == otherVertex)
            {
                return true;
            }
        }
        return false;
    }
public:
	// maxflow algorithm
	T2 compute_maxflow(T1 source, T1 sink);
private:
	bool has_augment_path(T1 source, T1 sink);
private:
	std::vector<bool> vecVisited_;
	std::vector<T1> vecEdgeTo_;
private:
	T1 nVertex_;
	std::vector<FlowEdge<T1,T2> > vecFlowEdge_;
	std::vector<std::vector<T1> > adjList_;
};
//---------------------
template<typename T1, typename T2>
T2 FlowNetwork<T1,T2>::compute_maxflow(T1 source, T1 sink)
{
	T2 maxFlow = 0;
	
	while (has_augment_path(source,sink))
	{
		//compute the bottleneck
		T1 vtx = sink;
		T2 bottleNeckCapacity = std::numeric_limits<T2>::max();
		while (vtx != source)
		{
			FlowEdge<T1,T2> edge = vecFlowEdge_[vecEdgeTo_[vtx]];
			bottleNeckCapacity = std::min(edge.residual_capacity_to(vtx), bottleNeckCapacity);
			vtx = edge.other(vtx);
		}

		// now update the flow of this augment path
		vtx = sink;
		while (vtx != source)
		{
			FlowEdge<T1,T2>& edge = vecFlowEdge_[vecEdgeTo_[vtx]];
			edge.update_flow_to(vtx,bottleNeckCapacity);
			vtx = edge.other(vtx);
		}

		maxFlow += bottleNeckCapacity;
	}

	return maxFlow;
}

template<typename T1, typename T2>
bool FlowNetwork<T1,T2>::has_augment_path(T1 source, T1 sink)
{
	// do a BFS traversal exploring the edges only if either
	// a) forward edge has flown less than its capacity
	// b) backward edge is non-empty

	// reset visited flag as false for finding next augment path
	for (T1 vtx_i = 0; vtx_i != nVertex_; ++vtx_i)
	{
		vecVisited_[vtx_i] = false;
	}

	std::queue<T1> queue;
	vecVisited_[source] = true;
	queue.push(source);

	while (!queue.empty())
	{
		T1 frontElem = queue.front();
		queue.pop();

		std::vector<T1> adjEdges = adjList_[frontElem];
		for (typename std::vector<T1>::iterator it = adjEdges.begin(); it != adjEdges.end(); ++it)
		{
			FlowEdge<T1,T2> edge = vecFlowEdge_[*it];
			T1 otherVtx = edge.other(frontElem);

			if ((edge.residual_capacity_to(otherVtx) > 0) && !vecVisited_[otherVtx])
			{
				vecVisited_[otherVtx] = true;
				vecEdgeTo_[otherVtx] = *it;
				queue.push(otherVtx);
			}
		}
	}

	return vecVisited_[sink];
}
//----------------------
int main(int argc, char* argv[])
{
	std::ifstream pFile;
	if (READ_FROM_FILE)
	{
		pFile.open("D:/cpp_practise/online_judge/uva/820_internet_bandwidth_input.txt",std::ios::in);
		assert(pFile.is_open() && "failed to open file");
	}

    unsigned int network_i = 0;
	while (true)
	{
		unsigned int nVertex;
		if (READ_FROM_FILE)
		{
			pFile >> nVertex;
		}
		else
		{
			std::cin >> nVertex;
		}

		if (nVertex == 0)
		{
			break;
		}

        ++network_i;
		FlowNetwork<unsigned int,unsigned long> flowNetwork(nVertex);
		
		unsigned int source,sink,nConnections;
		if (READ_FROM_FILE)
		{
			pFile >> source >> sink >> nConnections;
		}
		else
		{
			std::cin >> source >> sink >> nConnections;
		}
        --source;
        --sink;

		unsigned int vertex1, vertex2, capacity;

		for (unsigned int connection_i = 0; connection_i != nConnections; ++connection_i)
		{
			if (READ_FROM_FILE)
			{
				pFile >> vertex1 >> vertex2 >> capacity;
			}
			else
			{
                std::cin >> vertex1 >> vertex2 >> capacity;
			}
            --vertex1;
            --vertex2;
			flowNetwork.add_edge(vertex1,vertex2,capacity);
		}
		
        std::cout << "Network " << network_i << std::endl;
		std::cout << "The bandwidth is " << flowNetwork.compute_maxflow(source,sink) << "." << std::endl;
        std::cout << std::endl;
	}

	if (READ_FROM_FILE)
	{
		pFile.close();
	}

	return 0;
}

/*
"There might be more than one connection between a pair of nodes, but a node cannot be connected to itself"
My solution: in case of multiple connection add the capacities and keep a single edge between the pair of nodes.
*/