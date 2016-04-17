// http://poj.org/problem?id=1915
#include <cstdio>
#include <vector>
#include <queue>
#include <list>
#include <limits>
//#include <ctime>

#define PRE_COMPUTE_JUMP 0

template<typename T>
class Position
{
public:
	Position(T row, T col);
	~Position();
public:
	void add_jump_pos(T pos);
	std::vector<T> jumpPos();
private:
	T row_;
	T col_;
	std::vector<T> vecJumpPos_;
};

template<typename T>
class Board
{
public:
	Board(T N);
	~Board();
public:
	T compute_distance(T beginPos, T endPos);
	void getJumpPos(T pos,std::vector<T>& vecJumpPos);
private:
	void compute_possible_moves();
private:
	T N_;
	T nPos_;
	std::vector<Position<T> > vecPos_;
};

// --------------------------------------
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
	vecJumpPos_.push_back(pos);
}
template<typename T>
std::vector<T> Position<T>::jumpPos()
{
	return vecJumpPos_;
}

// --------------------------------------
template<typename T>
Board<T>::Board(T N)
: N_(N)
{
	nPos_ = N_*N_;
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
void Board<T>::getJumpPos(T pos,std::vector<T>& vecJumpPos)
{
	T row_i = pos/N_;
	T col_i = pos%N_;
	//vecJumpPos.reserve(8); //max 8 moves possible

	if (row_i > 0)
	{
		if (col_i > 1)
		{
			// pos = [row_i-1,col_i-2]
			vecJumpPos.push_back( (row_i-1)*N_ + (col_i-2) );
		}
		if (col_i+2 < N_)
		{
			// pos = [row_i-1,col_i+2]
			vecJumpPos.push_back( (row_i-1)*N_ + (col_i+2) );
		}

		if (row_i > 1)
		{
			if (col_i > 0)
			{
				// pos = [row_i-2,col_i-1]
				vecJumpPos.push_back( (row_i-2)*N_ + (col_i-1) );
			}
			if (col_i+1 < N_)
			{
				// pos = [row_i-2,col_i+1]
				vecJumpPos.push_back( (row_i-2)*N_ + (col_i+1) );
			}
		}
	}

	if (row_i+1 < N_)
	{
		if (col_i > 1)
		{
			// pos = [row_i+1,col_i-2]
			vecJumpPos.push_back( (row_i+1)*N_ + (col_i-2) );
		}
		if (col_i+2 < N_)
		{
			// pos = [row_i+1,col_i+2]
			vecJumpPos.push_back( (row_i+1)*N_ + (col_i+2) );
		}

		if (row_i+2 < N_)
		{
			if (col_i > 0)
			{
				// pos = [row_i+2,col_i-1]
				vecJumpPos.push_back( (row_i+2)*N_ + (col_i-1) );
			}
			if (col_i+1 < N_)
			{
				// pos = [row_i+2,col_i+1]
				vecJumpPos.push_back( (row_i+2)*N_ + (col_i+1) );
			}
		}
	}
}

template<typename T>
void Board<T>::compute_possible_moves()
{
	vecPos_.reserve(N_*N_);

	for (T row_i = 0; row_i < N_; ++row_i)
	{
		for (T col_i = 0; col_i < N_; ++col_i)
		{
			Position<T> position(row_i,col_i);

			if (row_i > 0)
			{
				if (col_i > 1)
				{
					// pos = [row_i-1,col_i-2]
					position.add_jump_pos( (row_i-1)*N_ + (col_i-2) );
				}
				if (col_i+2 < N_)
				{
					// pos = [row_i-1,col_i+2]
					position.add_jump_pos( (row_i-1)*N_ + (col_i+2) );
				}

				if (row_i > 1)
				{
					if (col_i > 0)
					{
						// pos = [row_i-2,col_i-1]
						position.add_jump_pos( (row_i-2)*N_ + (col_i-1) );
					}
					if (col_i+1 < N_)
					{
						// pos = [row_i-2,col_i+1]
						position.add_jump_pos( (row_i-2)*N_ + (col_i+1) );
					}
				}
			}

			if (row_i+1 < N_)
			{
				if (col_i > 1)
				{
					// pos = [row_i+1,col_i-2]
					position.add_jump_pos( (row_i+1)*N_ + (col_i-2) );
				}
				if (col_i+2 < N_)
				{
					// pos = [row_i+1,col_i+2]
					position.add_jump_pos( (row_i+1)*N_ + (col_i+2) );
				}

				if (row_i+2 < N_)
				{
					if (col_i > 0)
					{
						// pos = [row_i+2,col_i-1]
						position.add_jump_pos( (row_i+2)*N_ + (col_i-1) );
					}
					if (col_i+1 < N_)
					{
						// pos = [row_i+2,col_i+1]
						position.add_jump_pos( (row_i+2)*N_ + (col_i+1) );
					}
				}
			}

			vecPos_.push_back(position);
			int gh = 0;
		}
	}
}


template<typename T>
T Board<T>::compute_distance(T beginPos, T endPos)
{
	if (beginPos == endPos)
	{
		return 0;
	}

	std::vector<bool> vecVisited;
	std::vector<T> vecDist;

	vecVisited.reserve(nPos_);
	vecDist.reserve(nPos_);

	// initialization
	for (T i = 0; i < nPos_; ++i)
	{
		vecVisited.push_back(false);
		vecDist.push_back(std::numeric_limits<T>::max());
	}

	// bfs traversal till we reach endPos
	std::queue<T> queuePos; //,std::list<T> as container of queue
	vecVisited[beginPos] = true;
	vecDist[beginPos] = 0;
	queuePos.push(beginPos);
	
	bool foundEndPos = false;
	unsigned int count = 0;
	std::vector<T> vecJumpPos;
	vecJumpPos.reserve(8); //max 8 moves possible

	while (!queuePos.empty() && !foundEndPos)
	{
		T curPos = queuePos.front();
		queuePos.pop();

		//++count;
		
		// check if we have reached endPos
		/*
		if (curPos == endPos)
		{
			break;
		}
		*/
		// std::vector<T> vecJumpPos;
		
		if (PRE_COMPUTE_JUMP)
		{
			vecJumpPos = vecPos_[curPos].jumpPos();
		}
		else
		{
			getJumpPos(curPos,vecJumpPos);
		}

		for (std::vector<T>::iterator it = vecJumpPos.begin(); it != vecJumpPos.end(); ++it)
		{
			if (!vecVisited[(*it)])
			{
				vecVisited[(*it)] = true;
				vecDist[(*it)] = vecDist[curPos] + 1;
				// check if we have reached endPos
				if ((*it) == endPos)
				{
					foundEndPos = true;
					break;
				}
				queuePos.push(*it);
			}
		}

		vecJumpPos.clear();

	}

	//printf("\ncount: %d\n",count);

	return vecDist[endPos];
}
// --------------------------------------
int main(int argc, char* argv[])
{
	unsigned int nCase;
	scanf("%d",&nCase);

	//clock_t totalTime = clock();
	for (unsigned int case_i = 0; case_i < nCase; ++case_i)
	{
		unsigned int edgeLen;
		scanf("%d",&edgeLen);
		unsigned int startRow, startCol;
		scanf("%d",&startRow);
		scanf("%d",&startCol);
		unsigned int endRow, endCol;
		scanf("%d",&endRow);
		scanf("%d",&endCol);

		Board<unsigned int> board(edgeLen);
		unsigned int startPos = startRow*edgeLen + startCol;
		unsigned int endPos = endRow*edgeLen + endCol;
		printf("%d\n",board.compute_distance(startPos,endPos));
		int gh = 0;
	}

	//totalTime = clock() - totalTime;
	//printf("\ntotal time: click: %d :: time(in sec):%f\n",totalTime,((float)totalTime)/CLOCKS_PER_SEC);
	return 0;
}

/*
http://poj.org/showmessage?message_id=162038
QUEUE with the STL is not good, a lot faster with a list.  //N.B. This isn't correct.

http://stackoverflow.com/questions/1262808/which-stl-container-should-i-use-for-a-fifo  gmannickg's answer (explanation in detail)
std::queue is only an adapter. It provides the safe interface, but uses a different container on the inside. 
You can choose this underlying container, and this allows a good deal of flexibility.

http://www.cs.bu.edu/teaching/c/queue/array/types.html
Queue - Array implementation
http://online-judge.uva.es/board/viewtopic.php?f=22&t=76036  Brian's suggestion
*/