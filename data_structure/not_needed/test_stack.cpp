#include "Stack.hpp"
#include <iostream>

int main( int argc, char* argv[] )
{
	using namespace ds;
	Stack stack;

	stack.push("an");
#if 0
	std::string str = stack.pop();
	bool flag = stack.isEmpty();
	str = stack.pop(); //should throw exception
#endif

    stack.push("the");
    std::string str = stack.pop();

	return 0;
}