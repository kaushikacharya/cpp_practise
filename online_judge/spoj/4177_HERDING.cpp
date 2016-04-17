#include <cstdio>
#include <vector>
#include <cstring>
#include <cassert>
#include <cstdlib> // malloc

#define READ_FROM_FILE 0
typedef unsigned int DType;

template<typename T>
class City
{
public:
	City(T row, T col);
	~City();
public:
	void add_next_pos(T nextPos);
	T traverse();
private:
	void traverse(T nextPos);
private:
	T row_;
	T col_;
	std::vector<bool> vecVisited_;
	std::vector<T> vecNextPos_;
	T countVisited_;
};
//---
template<typename T>
City<T>::City(T row, T col)
: row_(row)
, col_(col)
, countVisited_(0)
{
	T nSquare = row*col;
	vecVisited_.reserve(nSquare);
	vecNextPos_.reserve(nSquare);

	for (T square_i=0; square_i != nSquare; ++square_i)
	{
		vecVisited_.push_back(false);
	}
}
template<typename T>
City<T>::~City()
{}
template<typename T>
void City<T>::add_next_pos(T nextPos)
{
	vecNextPos_.push_back(nextPos);
}
template<typename T>
T City<T>::traverse()
{
	T nSquare = row_*col_;
	T countTrap = 0;
	T startPos = 0;
	while (countVisited_ < nSquare)
	{
		++countTrap;
		//get the next startPos
		while (vecVisited_[startPos])
		{
			++startPos;
		}
		traverse(startPos);
	}
	return countTrap;
}
template<typename T>
void City<T>::traverse(T nextPos)
{
	while (!vecVisited_[nextPos])
	{
		vecVisited_[nextPos] = true;
		++countVisited_;
		nextPos = vecNextPos_[nextPos];
	}
}
//---
void read_input_process(DType row, DType col, FILE* pFile)
{
	City<unsigned long> city(row,col);
	unsigned long nextPos;

	for (DType row_i = 0; row_i != row; ++row_i)
	{
		//char* str = (char *)malloc(col+1);
		char* str = new char[col+2];
		if (READ_FROM_FILE)
		{
			fgets(str,col+2,pFile);
			str = strtok(str,"\n");
		} 
		else
		{
			gets(str);
		}

		for (DType col_i=0; col_i != col; ++col_i)
		{
			switch (str[col_i])
			{
			case 'E':
				nextPos = row_i*col + col_i + 1;
				break;
			case 'W':
				nextPos = row_i*col + col_i - 1;
				break;
			case 'N':
				nextPos = (row_i-1)*col + col_i;
				break;
			case 'S':
				nextPos = (row_i+1)*col + col_i;
				break;
			default:
				assert(false && "wrong dir");
				break;
			}
			city.add_next_pos(nextPos);
		}

		delete[] str;
		//free(str);
		int gh = 0;
	}

	printf("%lu\n",city.traverse());
}

int main(int argc, char* argv[])
{
	FILE* pFile = 0;
	DType row,col;
	char ch;

	if (READ_FROM_FILE)
	{
		pFile = fopen("d:/cpp_practise/online_judge/spoj/4177_HERDING_input.txt","r");
		fscanf(pFile,"%u",&row);
		fscanf(pFile,"%u",&col);
		fscanf(pFile,"%c",&ch); //read '\n'
	} 
	else
	{
		scanf("%u",&row);
		scanf("%u",&col);
		scanf("%c",&ch);
	}
	read_input_process(row,col,pFile);
	return 0;
}

/*
http://www.embedded.com/design/embedded/4008868/Deterministic-dynamic-memory-allocation--fragmentation-in-C--C-

http://stackoverflow.com/questions/7131619/heap-corruption-detected-where-can-i-delete-dynamic-memory
John's answer
*/