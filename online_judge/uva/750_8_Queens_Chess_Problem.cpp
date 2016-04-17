// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=691
// Kaushik Acharya
#include <iostream>
#include <vector>
#include <cassert>

template<typename T>
class Chess
{
public:
	Chess(T size=8)
		: size_(size)
	{
		vecOrderQueen.reserve(size_);
		vecQueenPosVec_.reserve(size_);
		vecQueenRelPos_.reserve(size_);

		for (T q_i = 0; q_i != size_; ++q_i)
		{
			vecQueenPosVec_.push_back(std::vector<T>());
			vecQueenRelPos_.push_back(size_); //initialize with invalid relative position
		}
	}
public:
	void assign_initial_queen(T row, T col)
	{
		vecOrderQueen.push_back(row);
		//now assign the rest of the queens
		for (T q_i = 0; q_i != size_; ++q_i)
		{
			if (q_i != row)
			{
				vecOrderQueen.push_back(q_i);
			}
			else
			{
				vecQueenPosVec_[q_i].push_back(col);
				vecQueenRelPos_[q_i] = 0;
			}
		}
	}

	void compute_arrangements();
	void print_header();
    void print_arrangements();
private:
    void populate_valid_positions_for_next_queen(T queen_index_in_queen_list);
private:
	T size_; //chess square is size_*size_
    // Next 3 variables correspond to queen i in ith index
	std::vector<std::vector<T> > vecQueenPosVec_; //This stores all valid positions for each queen in current state of the game
	std::vector<T> vecQueenRelPos_; //This indicates the relative index of each queen in the valid positions in vecQueenPosVec_
    std::vector<std::vector<T> > vecArrangement_;
    // Next one stores queen in a different order than above.
    std::vector<T> vecOrderQueen; //First one is the initial queen. Rest of the queens are traversed sequentially in backtracking
};

template<typename T>
void Chess<T>::compute_arrangements()
{
    T relPos = 0;
    
    while (true)
    {
        T queen_index = vecOrderQueen[relPos];
        bool flag_backtrack = false;
        
        if (relPos == (size_-1))
        {
            // current level is the last level in the hierarchy
            // collect this arrangement
            std::vector<T> arrangement;
            arrangement.reserve(size_);
            for (typename std::vector<T>::iterator it = vecQueenRelPos_.begin(); it != vecQueenRelPos_.end(); ++it)
            {
                T cur_queen_index = std::distance(vecQueenRelPos_.begin(),it);
                arrangement.push_back(vecQueenPosVec_[cur_queen_index][*it]);
            }
            vecArrangement_.push_back(arrangement);

            if ( vecQueenRelPos_[queen_index] < (vecQueenPosVec_[queen_index].size()-1) )
            {
                // in the next iteration take the next valid position of this last level
                ++vecQueenRelPos_[queen_index];
            }
            else
            {
                // backtrack to the higher level
                flag_backtrack = true;
            }
        }
        else
        {
            if (vecQueenRelPos_[queen_index] < vecQueenPosVec_[queen_index].size())
            {
                populate_valid_positions_for_next_queen(relPos+1);
                T next_queen_index = vecOrderQueen[relPos+1];

                if (vecQueenRelPos_[next_queen_index] < vecQueenPosVec_[next_queen_index].size())
                {
                    // go to lower level in the next iteration
                    ++relPos;
                }
                else
                {
                    // backtrack to higher level
                    flag_backtrack = true;
                }
            }
            else
            {
                // backtrack to higher level
                flag_backtrack = true;
            }
        }

        if (flag_backtrack)
        {
            vecQueenPosVec_[queen_index].clear();
            vecQueenRelPos_[queen_index] = size_; //assign a value which signifies that valid positions not available
            if (relPos == 0)
            {
                break;
            }
            --relPos;

            T prev_queen_index = vecOrderQueen[relPos];
            ++vecQueenRelPos_[prev_queen_index];
        }
    }
}

template<typename T>
void Chess<T>::print_header()
{
	std::cout << "SOLN       COLUMN" << std::endl;
	std::cout << " #     ";
	for (T q_i = 0; q_i != size_; ++q_i)
	{
		std::cout << " " << (q_i+1);
	}
	std::cout << std::endl;
}

template<typename T>
void Chess<T>::print_arrangements()
{
	std::cout << std::endl;
    for (T arrangement_i = 0; arrangement_i != vecArrangement_.size(); ++arrangement_i)
    {
        std::cout << " " << (arrangement_i+1) << "     ";
        for (T q_i = 0; q_i != size_; ++q_i)
        {
            std::cout << " " << vecArrangement_[arrangement_i][q_i]+1;
        }
        std::cout << std::endl;
    }
}

template<typename T>
void Chess<T>::populate_valid_positions_for_next_queen(T queen_index_in_queen_list)
{
    T queen_index = vecOrderQueen[queen_index_in_queen_list];
    assert(vecQueenPosVec_[queen_index].empty() && "valid position list for the current queen row is expected to be empty");
    // we will check validity for each column
    for (T pos = 0; pos != size_; ++pos)
    {
        bool valid_pos_flag = true;
        // check one by one the queens at higher level
        for (T q_i = 0; q_i != queen_index_in_queen_list; ++q_i)
        {
            T other_queen_index = vecOrderQueen[q_i];
            T other_queen_pos = vecQueenPosVec_[other_queen_index][vecQueenRelPos_[other_queen_index]];

            if (pos == other_queen_pos)
            {
                valid_pos_flag = false;
                break;
            }
            T diff_in_row = 0;
            if (other_queen_index < queen_index)
            {
                diff_in_row = queen_index - other_queen_index;
            }
            else
            {
                diff_in_row = other_queen_index - queen_index;
            }

            T diff_in_col = 0;
            if (pos < other_queen_pos)
            {
                diff_in_col = other_queen_pos - pos;
            }
            else
            {
                diff_in_col = pos - other_queen_pos;
            }

            if (diff_in_row == diff_in_col)
            {
                valid_pos_flag = false;
                break;
            }
        }

        if (valid_pos_flag)
        {
            vecQueenPosVec_[queen_index].push_back(pos);
        }
    }

    // assign first valid position if valid positions available
    if (!vecQueenPosVec_[queen_index].empty())
    {
        vecQueenRelPos_[queen_index] = 0;
    }
    else
    {
        vecQueenRelPos_[queen_index] = size_; //assign a value which signifies that valid positions not available
    }
}

int main(int argc, char* argv[])
{
	unsigned int nDataSet;
	std::cin >> nDataSet;

	for (unsigned int dataset_i = 0; dataset_i != nDataSet; ++dataset_i)
	{
		Chess<unsigned int> chess(8);
		unsigned int initial_queen_row, initial_queen_col;
		std::cin >> initial_queen_row >> initial_queen_col;
		// convert to zero-indexed
		--initial_queen_row;
		--initial_queen_col;

		chess.assign_initial_queen(initial_queen_row,initial_queen_col);
		chess.compute_arrangements();
		if (dataset_i == 0)
		{
			chess.print_header();
		}
		chess.print_arrangements();
	}
	
	return 0;
}