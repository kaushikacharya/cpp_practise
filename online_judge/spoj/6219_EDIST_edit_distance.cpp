// http://www.spoj.com/problems/EDIST/
#include <iostream>
#include <vector>
#include <string>
#include <limits>

const bool READ_FROM_FILE = false;
typedef unsigned int Uint;

template<typename T1, typename T2>
class EditDist
{
public:
	EditDist(T1 strX, T1 strY, T2 m, T2 n)
		: strX_(strX)
		, strY_(strY)
		, m_(m)
		, n_(n)
	{
		penaltyMatrix_.reserve((m_+1)*(n_+1));
		for (T2 col = 0; col != (n_+1); ++col)
		{
			penaltyMatrix_.push_back(col);
		}
		for (T2 row = 1; row != (m_+1); ++row)
		{
			for (T2 col = 0; col != (n_+1); ++col)
			{
				if (col == 0)
				{
					penaltyMatrix_.push_back(row);
				} 
				else
				{
					penaltyMatrix_.push_back(std::numeric_limits<T2>::max());
				}
			}
		}
	}

	T2 compute_edit_distance();
private:
	void setValue(T2 i, T2 j, T2 val)
	{
		penaltyMatrix_[i*(n_+1) + j] = val;
	}
	T2 getValue(T2 i, T2 j)
	{
		return penaltyMatrix_[i*(n_+1) + j];
	}
private:
	T1 strX_;
	T1 strY_;
	T2 m_; // length of strX_
	T2 n_; // length of strY_
private:
	std::vector<T2> penaltyMatrix_; // implemented as 1 dimension vector
};

template<typename T1, typename T2>
T2 EditDist<T1,T2>::compute_edit_distance()
{
	for (T2 i = 1; i != (m_+1); ++i)
	{
		for (T2 j = 1; j != (n_+1); ++j)
		{
			bool matchFlag = (strX_[i-1] == strY_[j-1]);
			T2 penalty = getValue(i-1,j-1) + ((strX_[i-1] == strY_[j-1]) ? 0 : 1);
			penalty = std::min(getValue(i-1,j) + 1, penalty);
			penalty = std::min(getValue(i,j-1) + 1, penalty);
			setValue(i,j,penalty);
		}
	}

	return getValue(m_,n_);
}

int main(int argc, char* argv[])
{
    Uint nCase;
    std::string strX, strY;

    std::cin >> nCase;
    strX = "blade";
	strY = "badel";

    for (Uint case_i = 0; case_i != nCase; ++case_i)
    {
        std::cin >> strX;
        std::cin >> strY;

        EditDist<std::string,Uint> edist(strX,strY,strX.size(),strY.size());
        std::cout << edist.compute_edit_distance() << std::endl;
    }
	

	return 0;
}