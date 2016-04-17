#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

#define READ_FROM_FILE 1

template<typename C, typename D>
class Grid
{
public:
	Grid(C nPeople);
	~Grid();
public:
	void read_input(std::fstream& pFile);
	D compute_min_sum_travel_time();
private:
	struct Point
	{
		D x;
		D y;
	};
private:
	C nPeople_;
	std::vector<Point> vecPos_;
	D minSumTravelTime_;
};
//---
template<typename C, typename D>
Grid<C,D>::Grid(C nPeople)
: nPeople_(nPeople)
{
	vecPos_.reserve(nPeople_);
	minSumTravelTime_ = std::numeric_limits<D>::max();
}
template<typename C, typename D>
Grid<C,D>::~Grid()
{}
template<typename C, typename D>
void Grid<C,D>::read_input(std::fstream& pFile)
{
	D xPos,yPos;
	
	for (C i = 0; i != nPeople_; ++i)
	{
		if (READ_FROM_FILE)
		{
			pFile >> xPos >> yPos;
		} 
		else
		{
			std::cin >> xPos >> yPos;
		}

		Point pos;
		pos.x = xPos;
		pos.y = yPos;
		vecPos_.push_back(pos);
	}
}
template<typename C, typename D>
D Grid<C,D>::compute_min_sum_travel_time()
{
	for (C i = 0; i != nPeople_; ++i)
	{
		D sum_travel_time = 0;

		for (C j = 0; j != nPeople_; ++j)
		{
			if (i == j)
			{
				continue;
			}

			D x_diff = vecPos_[j].x - vecPos_[i].x;
			D y_diff = vecPos_[j].y - vecPos_[i].y;

			if (x_diff < 0)
			{
				x_diff *= -1;
			}
			if (y_diff < 0)
			{
				y_diff *= -1;
			}

			if (x_diff < y_diff)
			{
				sum_travel_time += y_diff;
			}
			else
			{
				sum_travel_time += x_diff;
			}

			if (minSumTravelTime_ < sum_travel_time)
			{
				break; // No need to compute travel time from rest of the points
			}
		}

		if (sum_travel_time < minSumTravelTime_)
		{
			minSumTravelTime_ = sum_travel_time;
		}
	}

	return minSumTravelTime_;
}
//---
int main(int argc, char* argv[])
{
	unsigned long N;
	std::fstream pFile;

	if (READ_FROM_FILE)
	{
		pFile.open("D:/cpp_practise/online_judge/hackerrank/meeting_point_input.txt",std::ios::in);
		pFile >> N;
	} 
	else
	{
		std::cin >> N;
	}

	Grid<unsigned long, long long> grid(N);
	grid.read_input(pFile);

	if (READ_FROM_FILE)
	{
		pFile.close();
	}

	std::cout << grid.compute_min_sum_travel_time();

	return 0;
}

/*
http://stackoverflow.com/questions/7154978/shortest-distance-travel-common-meeting-point
*/
