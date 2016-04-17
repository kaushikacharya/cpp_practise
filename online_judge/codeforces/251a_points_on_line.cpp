// http://codeforces.com/problemset/problem/251/A
#include <cstdio>
#include <vector>
#include <cassert>

#define READ_FROM_LINE 0

template<typename T1, typename T2>
class Line
{
public:
	Line(T1 nPoint, T2 dist);
	~Line();
public:
	void read_points(FILE* pFile);
	void process();
	T1 countCombo();
private:
	void computeForGivenLeftPos();
	void updateRightPos();
private:
	T1 nPoint_;
	T2 dist_;
	std::vector<T2> vecPos_;
	T1 countCombo_;
private:
	T1 leftPos_;
	T1 rightPos_;
};
//---
template<typename T1, typename T2>
Line<T1,T2>::Line(T1 nPoint, T2 dist)
: nPoint_(nPoint)
, dist_(dist)
{
	vecPos_.reserve(nPoint_);
	countCombo_ = 0;
}
template<typename T1, typename T2>
Line<T1,T2>::~Line()
{}
template<typename T1, typename T2>
void Line<T1,T2>::read_points(FILE* pFile)
{
	T2 pointPos;
	for (T1 i=0; i != nPoint_; ++i)
	{
		if (READ_FROM_LINE)
		{
			fscanf(pFile,"%ld",&pointPos);
		} 
		else
		{
			scanf("%ld",&pointPos);
		}
		vecPos_.push_back(pointPos);
	}
}
template<typename T1, typename T2>
void Line<T1,T2>::process()
{
	leftPos_ = 0;
	rightPos_ = 2;

	if (nPoint_ < 3)
	{
		return;
	}
	while (leftPos_ < (nPoint_-2))
	{
		if (rightPos_ < (leftPos_+2))
		{
			rightPos_ = leftPos_+2;
		}
		computeForGivenLeftPos();
		++leftPos_;
	}
}
template<typename T1, typename T2>
void Line<T1,T2>::computeForGivenLeftPos()
{
	//computes the combo for the farthest points at [leftPos_,rightPos_] ..,.,.. [leftPos_,(leftPos_+2)]
	if (dist_ < (vecPos_[rightPos_] - vecPos_[leftPos_]))
	{
		return;
	}
	updateRightPos();
	T1 m = rightPos_ - leftPos_ - 1;
	countCombo_ += (m*(m+1))/2;
}
template<typename T1, typename T2>
void Line<T1,T2>::updateRightPos()
{
	// wrt leftPos_, rightPos_ is within distance dist_
	// Here we try to extend rightPos_ to the max position which will satisfy the distance condition.
	// Before doing binary search, check two special cases.
	// First check the max position.
	if ( (vecPos_[nPoint_-1] - vecPos_[leftPos_]) <= dist_ )
	{
		rightPos_ = nPoint_-1;
		return;
	}
	if (dist_ < (vecPos_[rightPos_+1] - vecPos_[leftPos_]))
	{
		return;
	}
	// Now do the binary search
	T1 leftBinaryRange = rightPos_;
	T1 rightBinaryRange = nPoint_-1;

	while (true)
	{
		if ((rightBinaryRange - leftBinaryRange) <= 1)
		{
			rightPos_ = leftBinaryRange;
			break;
		}
		T1 midBinary = (leftBinaryRange + rightBinaryRange)/2;
		if ( (vecPos_[midBinary] - vecPos_[leftPos_]) <= dist_ )
		{
			leftBinaryRange = midBinary;
		}
		else
		{
			rightBinaryRange = midBinary;
		}
	}
}
template<typename T1, typename T2>
T1 Line<T1,T2>::countCombo()
{
	return countCombo_;
}
//---
int main(int argc, char* argv[])
{
	FILE* pFile = 0;
	if (READ_FROM_LINE)
	{
		pFile = fopen("d:/cpp_practise/online_judge/codeforces/251a_points_on_line_input.txt","r");
		assert(pFile && "File not opened");
	}
	unsigned long long nPoint;
	long dist;
	if (READ_FROM_LINE)
	{
		fscanf(pFile,"%I64u",&nPoint);
		fscanf(pFile,"%ld",&dist);
	} 
	else
	{
		scanf("%I64u",&nPoint);
		scanf("%ld",&dist);
	}
	Line<unsigned long long,long> line(nPoint,dist);
	line.read_points(pFile);
	line.process();
	printf("%I64u\n",line.countCombo());
	return 0;
}