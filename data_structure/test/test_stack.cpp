#include "..\Stack.hpp"
#include <iostream>

int main( int argc, char* argv[] )
{
	using namespace ds;

    std::size_t test_case = 0;

    switch (test_case)
    {
    case 0:
        Stack<Version::V0,std::string> stack;
        ListNode<Version::V0,std::string>* node = NULL;
        stack.push("an");

        node = stack.top();
        //stack.pop();
        bool flag = stack.isEmpty();
        //stack.pop(); //should throw exception


        stack.push("the");
        stack.pop();

        break;
    }

	return 0;
}