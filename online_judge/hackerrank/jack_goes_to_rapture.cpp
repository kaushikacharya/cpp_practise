// https://www.hackerrank.com/contests/101sep13/challenges/jack-goes-to-rapture
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <set>
#include <cassert>

const bool READ_FROM_FILE=false;

/*
  source and target: misnomer. It should be vertex1 and vertex2
*/
template<typename T1, typename T2>
class Road
{
public:
	Road(T1 src, T1 tgt, T2 fare);
	~Road();
public:
	T1 source();
	T1 target();
	T2 fare();
private:
	T1 src_;
	T1 tgt_;
	T2 fare_;
};
//---
template<typename T1, typename T2>
class City
{
public:
	City(T1 nStation, T1 nRoad);
	~City();
public:
	void read_input(std::fstream& pFile);
	void process(T1 srcStation, T2 tgtStation);
private:
	T1 nStation_;
	T1 nRoad_;
private:
	std::vector<Road<T1,T2> > vecRoad_;
	std::vector<std::vector<T1> > adjList_; //we store vector of roads for each station
private:
	struct Comp
	{
		//first - station
		//second - cost
		bool operator()(const std::pair<T1,T2> s1, const std::pair<T1,T2> s2) const
		{
			if (s1.second == s2.second)
			{
				return (s1.first < s2.first);
			} 
			else
			{
				return (s1.second < s2.second);
			}
		}
	};
private:
	typedef std::set<std::pair<T1,T2>,Comp> SetStationCostPair;
	SetStationCostPair setStationCost_;
	std::vector<T2> vecCost_; //keeps total cost of reaching till the station from the source station
	std::vector<bool> vecVisited_; //flag of whether a station has been processed i.e. removed from the set
};
//---
template<typename T1, typename T2>
City<T1,T2>::City(T1 nStation, T1 nRoad)
: nStation_(nStation)
, nRoad_(nRoad)
{
	vecRoad_.reserve(nRoad_);
	adjList_.reserve(nRoad_);
	for (T1 road_i = 0; road_i != nRoad_; ++road_i)
	{
		adjList_.push_back(std::vector<T1>());
	}
}
template<typename T1, typename T2>
City<T1,T2>::~City()
{}
template<typename T1, typename T2>
void City<T1,T2>::read_input(std::fstream& pFile)
{
	T2 fare;
	T1 srcStation, tgtStation;
	
	for (T1 edge_i=0; edge_i != nRoad_; ++edge_i)
	{
		if (READ_FROM_FILE)
		{
			pFile >> srcStation >> tgtStation >> fare;
		}
		else
		{
			std::cin >> srcStation >> tgtStation >> fare;
		}
		//Its two way road
		Road<T1,T2> road(srcStation-1, tgtStation-1, fare);
		vecRoad_.push_back(road);
		adjList_[srcStation-1].push_back(vecRoad_.size()-1);
		adjList_[tgtStation-1].push_back(vecRoad_.size()-1);
	}
}
template<typename T1, typename T2>
void City<T1,T2>::process(T1 srcStation, T2 tgtStation)
{
	// Here we apply algo similar to Dijkstra's
	//initialization
	vecCost_.reserve(nStation_);
	vecVisited_.reserve(nStation_);
	for (T1 stn_i = 0; stn_i != nStation_; ++stn_i)
	{
		T2 cost = std::numeric_limits<T2>::max();
		if (stn_i == srcStation)
		{
			cost = 0;
		}
		setStationCost_.insert(std::make_pair(stn_i,cost));
		vecCost_.push_back(cost);
		vecVisited_.push_back(false);
	}

	while (!setStationCost_.empty())
	{
		typename SetStationCostPair::iterator it = setStationCost_.begin();
		T1 curStation = (*it).first;
		vecVisited_[curStation] = true;
		
		if (curStation == tgtStation)
		{
			break; // reached target station
		}
		setStationCost_.erase(it);

		for (typename std::vector<T1>::iterator roadIt = adjList_[curStation].begin(); roadIt != adjList_[curStation].end(); ++roadIt)
		{
			T1 nextStation = (curStation == vecRoad_[*roadIt].source()) ? vecRoad_[*roadIt].target() : vecRoad_[*roadIt].source();
			
			if (!vecVisited_[nextStation])
			{
				T2 nextCost = (vecCost_[curStation] < vecRoad_[*roadIt].fare()) ? vecRoad_[*roadIt].fare() : vecCost_[curStation];
				if (nextCost < vecCost_[nextStation])
				{
					//we need to update the cost of next station.
					//implementation: remove first and then insert again with updated cost.
					it = setStationCost_.find(std::make_pair(nextStation,vecCost_[nextStation]));
					assert((it != setStationCost_.end()) && "something wrong");
					setStationCost_.erase(it);
					setStationCost_.insert(std::make_pair(nextStation,nextCost));
					vecCost_[nextStation] = nextCost;
				}
			}
		}
		
	}

	if (vecVisited_[tgtStation])
	{
		std::cout << vecCost_[tgtStation] << std::endl;
	}
	else
	{
		std::cout << "NO PATH EXISTS" << std::endl;
	}
}
//---
template<typename T1, typename T2>
Road<T1,T2>::Road(T1 src, T1 tgt, T2 fare)
: src_(src)
, tgt_(tgt)
, fare_(fare)
{}
template<typename T1, typename T2>
Road<T1,T2>::~Road()
{}
template<typename T1, typename T2>
T1 Road<T1,T2>::source()
{
	return src_;
}
template<typename T1, typename T2>
T1 Road<T1,T2>::target()
{
	return tgt_;
}
template<typename T1, typename T2>
T2 Road<T1,T2>::fare()
{
	return fare_;
}
//---
int main(int argc, char* argv[])
{
	unsigned long N;
	unsigned long E;
	std::fstream pFile;

	//std::cout << std::numeric_limits<unsigned int>::max() << std::endl;

	if (READ_FROM_FILE)
	{
		pFile.open("d:/cpp_practise/online_judge/hackerrank/jack_goes_to_rapture_input_2.txt",std::ios::in);
		pFile >> N >> E;
	}
	else
	{
		std::cin >> N >> E;
	}

	City<unsigned long, unsigned long> city(N,E);
	city.read_input(pFile);
	
	if (READ_FROM_FILE)
	{
		pFile.close();
	}

	city.process(0,N-1);
	return 0;
}

/*
http://compgroups.net/comp.lang.c++/std-map-error-message-only-in-in-release-mode/1048477
Comp::operator() needs to made as const function otherwise fails to compile in Release mode in Visual Studio 2008
*/