// https://www.hackerrank.com/contests/startatastartup/challenges/zartan-roads
#include <iostream>
#include <vector>
#include <fstream>

const bool READ_FROM_FILE = false;

template<typename T>
class Zartan
{
public:
	Zartan(T nJunction, T nRoad);
	~Zartan();
public:
	void read_input(std::fstream& pFile);
	bool process();
private:
	T nJunction_;
	T nRoad_;
private:
	std::vector<T> vecVisited_;
	std::vector<std::vector<T> > adjList_;
	std::vector<T> vecVisitIteration_;
	std::vector<T> vecInEdgeCount_;
};
//---
template<typename T>
Zartan<T>::Zartan(T nJunction, T nRoad)
: nJunction_(nJunction)
, nRoad_(nRoad)
{
	vecVisited_.reserve(nJunction_);
	adjList_.reserve(nJunction_);
	vecVisitIteration_.reserve(nJunction_);
	vecInEdgeCount_.reserve(nJunction_);

	for (T junc_i = 0; junc_i != nJunction_; ++junc_i)
	{
		vecVisited_.push_back(false);
		adjList_.push_back(std::vector<T>());
		vecVisitIteration_.push_back(0);
		vecInEdgeCount_.push_back(0);
	}
}
template<typename T>
Zartan<T>::~Zartan()
{
}
template<typename T>
void Zartan<T>::read_input(std::fstream &pFile)
{
	T source_junction, target_junction;
	for (T road_i = 0; road_i != nRoad_; ++road_i)
	{
		if (READ_FROM_FILE)
		{
			pFile >> source_junction >> target_junction;
		}
		else
		{
			std::cin >> source_junction >> target_junction;
		}
		adjList_[source_junction].push_back(target_junction);
		++vecInEdgeCount_[target_junction];
	}
}
template<typename T>
bool Zartan<T>::process()
{
	bool flag_cycle_present = false;
	T iter = 0;
	for (T junc_i = 0; junc_i != nJunction_; ++junc_i)
	{
		if (vecVisited_[junc_i])
		{
			continue;
		}

		++iter;
		T curJunction = junc_i;
		
		while (true)
		{
			if (vecVisited_[curJunction])
			{
				if (vecVisitIteration_[curJunction] == iter)
				{
					flag_cycle_present = true;
				}
				else
				{
					//we had visited curJunction in a previous iteration
				}
				break;
			}
			else
			{
				vecVisited_[curJunction] = true;
				vecVisitIteration_[curJunction] = iter;
				// In this problem there's atmost a single exit from a junction
				if (adjList_[curJunction].empty() || (adjList_[curJunction].front() == curJunction))
				{
					break;
				}
				else
				{
					curJunction = adjList_[curJunction].front();
				}
			}
		}

		/*
		if (vecInEdgeCount_[junc_i] > 0)
		{
			continue;
		}
		T curJunction = junc_i;
		bool flag_next_present = true;
		while (flag_next_present)
		{
			if (vecVisited_[curJunction])
			{
				flag_cycle_present = true;
				break;
			}
			vecVisited_[curJunction] = true;
			
			// In this problem there's atmost a single exit from a junction
			if (adjList_[curJunction].empty() || (adjList_[curJunction].front() == curJunction))
			{
				flag_next_present = false;
			}
			else
			{
				curJunction = adjList_[curJunction].front();
			}
		}
		*/

		if (flag_cycle_present)
		{
			break;
		}
	}

	return flag_cycle_present;
}
//---
int main(int argc, char* argv[])
{
	unsigned int N,R;
	std::fstream pFile;

	if (READ_FROM_FILE)
	{
		pFile.open("D:/cpp_practise/online_judge/hackerrank/zartan_roads_input.txt",std::ios::in);
		pFile >> N >> R;
	}
	else
	{
		std::cin >> N >> R;
	}

	Zartan<unsigned int> zartan(N,R);
	zartan.read_input(pFile);
	bool cycle_present = zartan.process();
	
	if (cycle_present)
	{
		std::cout << "YES" << std::endl;
	}
	else
	{
		std::cout << "NO" << std::endl;
	}

	return 0;
}