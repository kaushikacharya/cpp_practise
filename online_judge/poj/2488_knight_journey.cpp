// http://poj.org/problem?id=2488
#include <cstdio>
#include <bitset>
#include <set>
#include <vector>
//#include <cassert>
#include <ctime>
#include <string>

#define MAX 26 // p*q <= 26 as mentioned in the problem statement
#define WRITE_INTO_FILE 0
#define WRITE_STRING 0
#define PRE_COMPUTE_JUMP 0

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
	bool compute_path_recursive(T pos, std::vector<T>& path);
	void print_path(FILE* pFile, const std::vector<T>& path);
	void getJumpPos(T pos,std::vector<T>& vecJumpPos);
private:
	void compute_possible_moves();
private:
	std::bitset<MAX> vecExplored_; //each bit initialized 0
	std::vector<Position<T> > vecPos_;
	T nRow_; // row size
	T nCol_; // column size
	T nPos_;
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
	nPos_ = nRow_*nCol_;
	if (PRE_COMPUTE_JUMP)
	{
		compute_possible_moves();
	}
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
bool Board<T>::compute_path_recursive(T pos, std::vector<T>& path)
{
	vecExplored_[pos] = true;
	path.push_back(pos);

	if (path.size() == nPos_)
	{
		return true;
	}

	bool path_found_flag = false;
	//std::set<T> jumpSet = vecPos_[pos].jumpPos();
	std::vector<T> vecJumpPos;
	getJumpPos(pos,vecJumpPos);
	
	//for (std::set<T>::iterator it = jumpSet.begin(); it != jumpSet.end(); ++it)
	for (std::vector<T>::iterator it = vecJumpPos.begin(); it != vecJumpPos.end(); ++it)
	{
		if (!vecExplored_[(*it)])
		{
			if (compute_path_recursive((*it),path))
			{
				path_found_flag = true;
				break;
			}
		}
	}

	if (!path_found_flag)
	{
		vecExplored_[pos] = false;
		path.pop_back();
	}

	return path_found_flag;
}

template<typename T>
void Board<T>::print_path(FILE* pFile, const std::vector<T>& path)
{
	if (WRITE_STRING)
	{
		std::string strPath;
		strPath.reserve(2*path.size());
		for (std::vector<T>::const_iterator it = path.begin(); it != path.end(); ++it)
		{
			T pos = *it;
			char ch;
			ch = 'A'+pos/nCol_;
			strPath.push_back(ch);
			ch = '1'+pos%nCol_;
			strPath.push_back(ch);
		}
		if (WRITE_INTO_FILE)
		{
			fprintf(pFile,"%s",strPath.c_str());
		}
		else
		{
			printf("%s",strPath.c_str());
		}
	} 
	else
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

template<typename T>
void Board<T>::getJumpPos(T pos,std::vector<T>& vecJumpPos)
{
	vecJumpPos.reserve(8);
	T row_i = pos/nCol_;
	T col_i = pos%nCol_;

	if (row_i > 1)
	{
		if (col_i > 0)
		{
			// pos = [row_i-2,col_i-1]
			vecJumpPos.push_back( (row_i-2)*nCol_ + (col_i-1) );
		}
		if (col_i+1 < nCol_)
		{
			// pos = [row_i-2,col_i+1]
			vecJumpPos.push_back( (row_i-2)*nCol_ + (col_i+1) );
		}
	}
	if (row_i > 0)
	{
		if (col_i > 1)
		{
			// pos = [row_i-1,col_i-2]
			vecJumpPos.push_back( (row_i-1)*nCol_ + (col_i-2) );
		}
		if (col_i+2 < nCol_)
		{
			// pos = [row_i-1,col_i+2]
			vecJumpPos.push_back( (row_i-1)*nCol_ + (col_i+2) );
		}
	}
	if (row_i+1 < nRow_)
	{
		if (col_i > 1)
		{
			// pos = [row_i+1,col_i-2]
			vecJumpPos.push_back( (row_i+1)*nCol_ + (col_i-2) );
		}
		if (col_i+2 < nCol_)
		{
			// pos = [row_i+1,col_i+2]
			vecJumpPos.push_back( (row_i+1)*nCol_ + (col_i+2) );
		}
	}
	if (row_i+2 < nRow_)
	{
		if (col_i > 0)
		{
			// pos = [row_i+2,col_i-1]
			vecJumpPos.push_back( (row_i+2)*nCol_ + (col_i-1) );
		}
		if (col_i+1 < nCol_)
		{
			// pos = [row_i+2,col_i+1]
			vecJumpPos.push_back( (row_i+2)*nCol_ + (col_i+1) );
		}
	}
}

void test_knight_move();

void test_knight_move()
{
	FILE* pFile = 0;
	clock_t totalTime = clock();
	
	if (WRITE_INTO_FILE)
	{
		pFile = fopen("D:/cpp_practise/online_judge/poj/2488_knight_journey_output.txt","w");
	}

	for (unsigned int p = 1; p <= 26; ++p)
	{
		for (unsigned int q = 1; q <= 26/p; ++q)
		{
			Board<unsigned int> board(q,p);
			std::vector<unsigned int> path;
			//bool path_found = board.compute_path(path);
			path.reserve(p*q);
			bool path_found = board.compute_path_recursive(0,path);
			if (WRITE_INTO_FILE)
			{
				fprintf(pFile,"case: p: %d q : %d\n",p,q);
			} 
			else
			{
				printf("case: p: %d q : %d\n",p,q);
			}
			
			if (path_found)
			{
				board.print_path(pFile,path);
			}
			else
			{
				if (WRITE_INTO_FILE)
				{
					fprintf(pFile,"impossible\n\n");
				}
				else
				{
					printf("impossible\n\n");

				}
			}
		}
	}

	if (WRITE_INTO_FILE)
	{
		fclose(pFile);
	}

	totalTime = clock() - totalTime;
	printf("\nTime: click: %d :: (in sec): %f\n",totalTime,((float)totalTime)/CLOCKS_PER_SEC);
	
}
// --------------------------------------------
int main(int argc, char* argv[])
{
	bool test_all_case = false;
	
	if (test_all_case)
	{
		//assert(WRITE_INTO_FILE && "set WRITE_INTO_FILE=1");
		test_knight_move();
	}
	else
	{
		unsigned int nCase;
		FILE* pFile = 0;
		//clock_t totalTime = clock();

		scanf("%d",&nCase);

		for (unsigned int case_i = 0; case_i < nCase; ++case_i)
		{
			unsigned int p, q;
			scanf("%d",&p);
			scanf("%d",&q);
			Board<unsigned int> board(q,p);
			std::vector<unsigned int> path;
			path.reserve(p*q);
			bool path_found = board.compute_path_recursive(0,path);
			//bool path_found = board.compute_path(path);
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

		//totalTime = clock() - totalTime;
		//printf("\nTime: click: %d :: (in sec): %f\n",totalTime,((float)totalTime)/CLOCKS_PER_SEC);
	}

	return 0;
}

/*
http://poj.org/showmessage?message_id=162294
http://stackoverflow.com/questions/12305018/efficient-representation-of-edges-in-a-c-graph-structure

Run ID	User	Problem	Result	Memory	Time	Language	Code Length	Submit Time
11783349	kaushik_acharya	2488	Wrong Answer			C++	4830B	2013-07-14 21:01:49

Run ID	User	Problem	Result	Memory	Time	Language	Code Length	Submit Time
11790988	kaushik_acharya	2488	Time Limit Exceeded			C++	7017B	2013-07-16 01:02:45

http://en.wikipedia.org/wiki/Knight%27s_tour
http://www.geeksforgeeks.org/backtracking-set-1-the-knights-tour-problem/

http://contest.informatik.hu-berlin.de/2005/results.html
contains practise problems as well test data in the download section

google search: "programming knight's move lexicographically first path"
Page 2:
http://www.cnblogs.com/freezhan/archive/2013/03/02/2950432.html
Algorithms: DFS + backtracking

http://online-judge.uva.es/board/viewtopic.php?f=17&t=290&p=206311&hilit=knight+tour#p206311
This is a discussion on a problem to determine closed tour.

http://stackoverflow.com/questions/10332789/stdlist-vs-stdvector-iteration
*/