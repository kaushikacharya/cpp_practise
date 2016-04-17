#include <algorithm>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <functional>

template<typename T>
T compute_median_sum_modulus(std::vector<T>& inputVec, T modulus);

template<typename T>
void textReader(const char* textFile, std::vector<T>& inputVec);

void tokenize(std::string& line,std::vector<std::string>& lineSplit);

int main(int argc, char* argv[])
{
	std::size_t test_case = 2;

	switch (test_case)
	{
	case 0:
		{
			//testing priority queue
			std::priority_queue<int,std::vector<int>,std::less<int> > pq1;
			std::priority_queue<int,std::vector<int>,std::greater<int> > pq2;

			pq1.push(1);
			pq1.push(7);
			pq1.push(3);

			pq2.push(8);
			pq2.push(1);
			pq2.push(3);

			std::cout << "top(pq1): " << pq1.top() << std::endl;
			std::cout << "top(pq2): " << pq2.top() << std::endl;

			pq2.push(pq1.top());
			pq1.pop();

			std::cout << "(after)top(pq1): " << pq1.top() << std::endl;
			std::cout << "(after)top(pq2): " << pq2.top() << std::endl;

			std::cout << "7 % 10 = " << 7 % 10 << std::endl;
			std::cout << "(12+8) % 10 = " << (12+8) % 10 << std::endl;
			std::cout << "(13+8) % 10 = " << (13+8) % 10 << std::endl;

			int gh = 0;
		}
		break;
	case 1:
		{
			std::vector<int> inputVec;
			inputVec.reserve(10000);
			textReader("D:/cpp_practise/test_cases/Median.txt",inputVec);
			int modulus = 10000;
			int median_sum_modulus = compute_median_sum_modulus(inputVec, modulus);
			std::cout << "sum of these 10000 medians, modulo 10000: " << median_sum_modulus << std::endl;
			int gh = 0;
		}
		break;
	case 2:
		{
			//https://class.coursera.org/algo-003/forum/thread?thread_id=669#post-3237
			std::vector<int> inputVec;
			inputVec.reserve(5000);
			textReader("D:/cpp_practise/test_cases/median_sum/mmtest2.txt",inputVec);
			int modulus = 10000;
			int median_sum_modulus = compute_median_sum_modulus(inputVec, modulus);
			std::cout << "sum of these 5000 medians, modulo 10000: " << median_sum_modulus << std::endl;
			int gh = 0;
		}
		break;
	}

	return 0;
}

template<typename T>
void textReader(const char* textFile, std::vector<T>& inputVec)
{
	std::ifstream textFileStream;
	textFileStream.open(textFile);
	assert(textFileStream.is_open() && "invalid input text file");

	int countLine = 0;
	while (!textFileStream.eof())
	{
		std::string line;
		std::getline(textFileStream,line);
		if (!line.empty())
		{
			std::vector<std::string> lineSplit;
			tokenize(line,lineSplit);
			if (!lineSplit.empty())
			{
				//Note: atoi converts empty string to 0
				assert((lineSplit.size()==1) && "only 1 int expected");
				inputVec.push_back(std::atoi(lineSplit[0].c_str()));
			}
		}
		++countLine;
	}

	textFileStream.close();
}

//TBD: input paramter: delimiters
void tokenize(std::string& line,std::vector<std::string>& lineSplit)
{
	if (line == "")
	{
		return;
	}
	std::string::size_type start = 0;
	std::string::size_type end = 0;
	while(end < line.npos)
	{
		start = line.find_first_not_of(" ",end);
		end   = line.find_first_of(" ",start);
		if (start == end)
		{
			break;
		}
		lineSplit.push_back(line.substr(start,(end-start)));
	}
}

template<typename T>
T compute_median_sum_modulus(std::vector<T>& inputVec, T modulus)
{
	std::priority_queue<int,std::vector<int>,std::less<int> > pqLow;
	std::priority_queue<int,std::vector<int>,std::greater<int> > pqHigh;

	int mod_sum_medians = 0;
	//we would treat the numbers as stream of numbers
	for (std::vector<int>::iterator it = inputVec.begin(); it != inputVec.end(); ++it)
	{
		int elem = *it;

		if (pqLow.empty() && pqHigh.empty())
		{
			pqLow.push(elem);
		}
		else
		{
			//after the first element from the stream, pqLow will always be non-empty
			int topLowPQ = pqLow.top();

			if (topLowPQ < elem)
			{
				pqHigh.push(elem);
			}
			else
			{
				pqLow.push(elem);
			}
		}

		//check if difference in size between the two priority queue is > 1
		//then we need to balance the size
		if (pqLow.size() > (1+pqHigh.size()))
		{
			int topLowPQ = pqLow.top();
			pqLow.pop();
			pqHigh.push(topLowPQ);
		}
		else if (pqHigh.size() > (1+pqLow.size()))
		{
			int topHighPQ = pqHigh.top();
			pqHigh.pop();
			pqLow.push(topHighPQ);
		}

		//Now get the current median
		int median;
		if (pqLow.size() == pqHigh.size())
		{
			//even number of elements have been read from stream till now
			median = pqLow.top();
		}
		else if (pqLow.size() < pqHigh.size())
		{
			median = pqHigh.top();
		}
		else
		{
			median = pqLow.top();
		}

		mod_sum_medians = (mod_sum_medians + median) % modulus;
		int pk = 0;
	}

	return mod_sum_medians;
}