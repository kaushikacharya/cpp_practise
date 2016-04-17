// http://poj.org/problem?id=2488
#include <cstdio>
#include <bitset>
#include <set>
#include <vector>
#include <cassert>

#define MAX 26 // p*q <= 26 as mentioned in the problem statement
#define WRITE_INTO_FILE 0

template<typename T>
class Position
{
public:
	Position(T row, T col);
	~Position();
public:
	void add_jump_pos(T pos);
	void remove_jump_pos(T pos);
	std::set<T> jumpPos();
private:
	std::set<T> setJumpPos_; // possible positions to which the Knight can go from the current position.
							 // keep deleting the positions which has been explored.
	T row_; // represented by A,B,C ...
	T col_; // represented by 1,2,3 ...
};

template<typename T>
class Board
{
public:
	Board(T nRow, T nCol);
	~Board();
public:
	bool compute_path(std::vector<T>& path);
	void print_path(FILE* pFile, const std::vector<T>& path);
private:
	void compute_possible_moves();
private:
	//std::bitset<MAX> vecExplored_; //each bit initialized 0
	std::vector<Position<T> > vecPos_;
	T nRow_; // row size
	T nCol_; // column size
};

// --------------------------------------------
template<typename T>
Position<T>::Position(T row, T col)
: row_(row)
, col_(col)
{
}

template<typename T>
Position<T>::~Position()
{
}

template<typename T>
void Position<T>::add_jump_pos(T pos)
{
	setJumpPos_.insert(pos);
}
template<typename T>
void Position<T>::remove_jump_pos(T pos)
{
	setJumpPos_.erase(pos);
}
template<typename T>
std::set<T> Position<T>::jumpPos()
{
	return setJumpPos_;
}
// --------------------------------------------

template<typename T>
Board<T>::Board(T nRow, T nCol)
: nRow_(nRow)
, nCol_(nCol)
{
	compute_possible_moves();
}

template<typename T>
Board<T>::~Board()
{
}

template<typename T>
void Board<T>::compute_possible_moves()
{
	vecPos_.reserve(nRow_*nCol_);

	for (T row_i = 0; row_i < nRow_; ++row_i)
	{
		for (T col_i = 0; col_i < nCol_; ++col_i)
		{
			Position<T> position(row_i,col_i);

			if (row_i > 0)
			{
				if (col_i > 1)
				{
					// pos = [row_i-1,col_i-2]
					position.add_jump_pos( (row_i-1)*nCol_ + (col_i-2) );
				}
				if (col_i+2 < nCol_)
				{
					// pos = [row_i-1,col_i+2]
					position.add_jump_pos( (row_i-1)*nCol_ + (col_i+2) );
				}

				if (row_i > 1)
				{
					if (col_i > 0)
					{
						// pos = [row_i-2,col_i-1]
						position.add_jump_pos( (row_i-2)*nCol_ + (col_i-1) );
					}
					if (col_i+1 < nCol_)
					{
						// pos = [row_i-2,col_i+1]
						position.add_jump_pos( (row_i-2)*nCol_ + (col_i+1) );
					}
				}
			}

			if (row_i+1 < nRow_)
			{
				if (col_i > 1)
				{
					// pos = [row_i+1,col_i-2]
					position.add_jump_pos( (row_i+1)*nCol_ + (col_i-2) );
				}
				if (col_i+2 < nCol_)
				{
					// pos = [row_i+1,col_i+2]
					position.add_jump_pos( (row_i+1)*nCol_ + (col_i+2) );
				}

				if (row_i+2 < nRow_)
				{
					if (col_i > 0)
					{
						// pos = [row_i+2,col_i-1]
						position.add_jump_pos( (row_i+2)*nCol_ + (col_i-1) );
					}
					if (col_i+1 < nCol_)
					{
						// pos = [row_i+2,col_i+1]
						position.add_jump_pos( (row_i+2)*nCol_ + (col_i+1) );
					}
				}
			}

			vecPos_.push_back(position);
			int gh = 0;
		}
	}
}

template<typename T>
bool Board<T>::compute_path(std::vector<T>& path)
{
	//start with A1
	path.reserve(nRow_*nCol_);
	unsigned int count = 0;
	T curPos = 0;
	bool path_generated_flag = true;

	while (count < nRow_*nCol_)
	{
		std::set<T> jumpSet = vecPos_[curPos].jumpPos();

		for (std::set<T>::iterator it = jumpSet.begin(); it != jumpSet.end(); ++it)
		{
			vecPos_[(*it)].remove_jump_pos(curPos);
		}

		//vecExplored_[curPos] = true;
		path.push_back(curPos);
		++count;

		if (count < nRow_*nCol_)
		{
			if (jumpSet.empty())
			{
				path_generated_flag = false;
				break;
			}
			curPos = *jumpSet.begin();
		}
		
	}

	return path_generated_flag;
}

template<typename T>
void Board<T>::print_path(FILE* pFile, const std::vector<T>& path)
{
	for (std::vector<T>::const_iterator it = path.begin(); it != path.end(); ++it)
	{
		T pos = *it;
		if (WRITE_INTO_FILE)
		{
			fprintf(pFile,"%c%d",'A'+pos/nCol_,1+pos%nCol_);
		}
		else
		{
			printf("%c%d",'A'+pos/nCol_,1+pos%nCol_);
		}
	}

	if (WRITE_INTO_FILE)
	{
		fprintf(pFile,"\n\n");
	}
	else
	{
		printf("\n\n");
	}
}

void test_knight_move();

void test_knight_move()
{
	FILE* pFile = fopen("D:/cpp_practise/online_judge/poj/2488_knight_journey_output.txt","w");

	for (unsigned int p = 1; p <= 26; ++p)
	{
		for (unsigned int q = 1; q <= 26/p; ++q)
		{
			Board<unsigned int> board(q,p);
			std::vector<unsigned int> path;
			bool path_found = board.compute_path(path);
			fprintf(pFile,"case: p: %d q : %d\n",p,q);
			if (path_found)
			{
				board.print_path(pFile,path);
			}
			else
			{
				fprintf(pFile,"impossible\n\n");
			}
		}
	}

	fclose(pFile);
}
// --------------------------------------------
int main(int argc, char* argv[])
{
	bool test_all_case = false;
	
	if (test_all_case)
	{
		assert(WRITE_INTO_FILE && "set WRITE_INTO_FILE=1");
		test_knight_move();
	}
	else
	{
		unsigned int nCase;
		FILE* pFile = 0;

		scanf("%d",&nCase);

		for (unsigned int case_i = 0; case_i < nCase; ++case_i)
		{
			unsigned int p, q;
			scanf("%d",&p);
			scanf("%d",&q);
			Board<unsigned int> board(q,p);
			std::vector<unsigned int> path;
			bool path_found = board.compute_path(path);
			printf("Scenario #%d:\n",1+case_i);
			if (path_found)
			{
				board.print_path(pFile,path);
			}
			else
			{
				printf("impossible\n\n");
			}
			//int gh = 0;
		}
	}

	return 0;
}

/*
http://stackoverflow.com/questions/12305018/efficient-representation-of-edges-in-a-c-graph-structure

Run ID	User	Problem	Result	Memory	Time	Language	Code Length	Submit Time
11783349	kaushik_acharya	2488	Wrong Answer			C++	4830B	2013-07-14 21:01:49

http://en.wikipedia.org/wiki/Knight%27s_tour
http://www.geeksforgeeks.org/backtracking-set-1-the-knights-tour-problem/
*/