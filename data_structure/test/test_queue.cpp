#include "..\Queue.hpp"
#include <string>
#include <iostream>

int main( int argc, char* argv[] )
{
	using namespace ds;
	std::size_t test_case = 0;

	switch (test_case)
	{
	case 0:
		Queue<Version::V0,std::string> queue;
		queue.push_back("kaushik");
		queue.push_back("is");
		//queue.pop_front();
		std::cout << "back: " << queue.back() << " : front: " << queue.front() << std::endl;
		break;
	}
	
	return 0;
}