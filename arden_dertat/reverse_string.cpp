#include "..\data_structure\Stack.hpp"
#include "..\file_reader\TextReader.hpp"
#include <iostream>
//problem source: http://www.ardendertat.com/2011/10/31/programming-interview-questions-12-reverse-words-in-a-string/
//TBD: Arden Dertat has suggested a better solution. Try that. 

int main( int argc, char* argv[] )
{
    using namespace ds;

    std::size_t test_case = 0;
    std::string line;

    switch (test_case)
    {
    case 0:
        line = " This  Austrian chapter introduces one mechanism"; //extra spaces introduced
        break;
    }

    typedef std::vector<std::string> strVector;
    strVector strVec;
    TextReader::tokenize(line,strVec);
    Stack<Version::V0,std::string> stack;

    for (strVector::iterator it = strVec.begin(); it != strVec.end(); ++it)
    {
        stack.push(*it);
    }

    std::cout << "reverse string:" << std::endl;
    while(!stack.isEmpty())
    {
        ListNode<Version::V0,std::string>* node = stack.pop();
        std::cout << node->item() << " ";
    }

    return 0;
}