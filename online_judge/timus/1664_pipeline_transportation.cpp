// http://acm.timus.ru/problem.aspx?space=1&num=1664
#include <iostream>
#include <algorithm>
#include <fstream>
#include <queue>
#include <limits>
#include <vector>
#include <cassert>

const bool READ_FROM_FILE = false;

template<typename T1, typename T2>
class FlowEdge
{
public:
	FlowEdge(T1 vertex1, T1 vertex2, T2 capacity)
		: vertex1_(vertex1)
		, vertex2_(vertex2)
		, flowToVertex1_(0)
		, flowToVertex2_(0)
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
	T2 capacity() const
	{
		return capacity_;
	}
	void increase_capacity(T2 capacity)
	{
		capacity_ += capacity;
	}
	/*
	*/
	T2 residual_capacity_to(T1 vertex) const
	{
		//Note: at least flowToVertex1_ or flowToVertex2_ will be zero.
		if (vertex == vertex1_)
		{
			return capacity_ - flowToVertex1_ + flowToVertex2_;
		}
		else if (vertex == vertex2_)
		{
			return capacity_ + flowToVertex1_ - flowToVertex2_;
		}
		else
		{
			assert(false && "input should be either of the two vertices of the edge");
		}
	}
	void update_flow_to(T1 vertex, T2 delta)
	{
		if (vertex == vertex1_)
		{
			if (delta <= flowToVertex2_)
			{
				flowToVertex2_ -= delta;
			} 
			else
			{
				flowToVertex1_ += (delta - flowToVertex2_);
				flowToVertex2_ = 0;
			}

		}
		else if (vertex == vertex2_)
		{
			if (delta <= flowToVertex1_)
			{
				flowToVertex1_ -= delta;
			} 
			else
			{
				flowToVertex2_ += (delta - flowToVertex1_);
				flowToVertex1_ = 0;
			}
		} 
		else
		{
			assert(false && "input should be either of the two vertices of the edge");
		}

		assert((flowToVertex1_*flowToVertex2_ == 0) && "atleast one of the flow must be zero");
	}

	T2 flow() const
	{
		return flowToVertex1_ + flowToVertex2_;
	}
	T1 vertex1() const
	{
		return vertex1_;
	}
	T1 vertex2() const
	{
		return vertex2_;
	}
private:
	T1 vertex1_;
	T1 vertex2_;
	T2 flowToVertex1_;
	T2 flowToVertex2_;
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
		FlowEdge<T1,T2> flowEdge(vertex1,vertex2,capacity);
		vecFlowEdge_.push_back(flowEdge);
		adjList_[vertex1].push_back(vecFlowEdge_.size()-1);
		adjList_[vertex2].push_back(vecFlowEdge_.size()-1);
	}
	FlowEdge<T1,T2> edge(T1 edge_index)
	{
		return vecFlowEdge_[edge_index];
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
		pFile.open("D:/cpp_practise/online_judge/timus/1664_pipeline_transportation_input.txt",std::ios::in);
		assert(pFile.is_open() && "file not opened");
	}
	unsigned int nStation;
	if (READ_FROM_FILE)
	{
		pFile >> nStation;
	}
	else
	{
		std::cin >> nStation;
	}
	FlowNetwork<unsigned int, unsigned long> flowNetwork(nStation);
	// read the coordinates of the stations
	unsigned long stationX, stationY;
	for (unsigned int station_i = 0; station_i != nStation; ++station_i)
	{
		if (READ_FROM_FILE)
		{
			pFile >> stationX >> stationY;
		} 
		else
		{
			std::cin >> stationX >> stationY;
		}
	}

	// read the pipelines
	unsigned long nPipeline;
	if (READ_FROM_FILE)
	{
		pFile >> nPipeline;
	}
	else
	{
		std::cin >> nPipeline;
	}
	unsigned long stationA, stationB, costPipeline;
	for (unsigned long pipe_i = 0; pipe_i != nPipeline; ++pipe_i)
	{
		if (READ_FROM_FILE)
		{
			pFile >> stationA >> stationB >> costPipeline;
		} 
		else
		{
			std::cin >> stationA >> stationB >> costPipeline;
		}
		--stationA;
		--stationB;
		flowNetwork.add_edge(stationA,stationB,costPipeline);
	}

	unsigned int sourceStation = 0;
	unsigned int sinkStation = nStation-1;
	std::cout << flowNetwork.compute_maxflow(sourceStation, sinkStation) << std::endl;
	for (unsigned long pipe_i = 0; pipe_i != nPipeline; ++pipe_i)
	{
		FlowEdge<unsigned int, unsigned long> flowEdge = flowNetwork.edge(pipe_i);
		std::cout << flowEdge.vertex1()+1 << " " << flowEdge.vertex2()+1 << " " << flowEdge.flow() << std::endl;
	}

	if (READ_FROM_FILE)
	{
		pFile.close();
	}

	return 0;
}