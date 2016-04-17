#include "..\data_structure\Stack.hpp"
#include <iostream>
#include <string>
//problem statement: http://www.ardendertat.com/2011/11/08/programming-interview-questions-14-check-balanced-parentheses/

short parentheses_id(char c);
bool parentheses_balance_check(const std::string& str);

int main( int argc, char* argv[] )
{
    std::size_t test_case = 2;
    std::string str;

    switch (test_case)
    {
    case 0:
        str = "{[]}";
        break;
    case 1:
        str = "{[}";
        break;
	case 2:
		str = "{()[]}"; //balanced but non-symmetric string
		break;
    }

    bool flag = parentheses_balance_check(str);
    std::cout << "parentheses balanced: ";
    if (flag)
    {
        std::cout << "true" << std::endl;
    } 
    else
    {
        std::cout << "false" << std::endl;
    }

    return 0;
}

short parentheses_id(char c)
{
    short parenthesesId;

    switch (c)
    {
    case '(':
        parenthesesId = -1;
        break;
    case ')':
        parenthesesId = +1;
        break;
    case '[':
        parenthesesId = -2;
        break;
    case ']':
        parenthesesId = +2;
        break;
    case '{':
        parenthesesId = -3;
        break;
    case '}':
        parenthesesId = +3;
        break;
    default:
        parenthesesId = 0;
    }

    return parenthesesId;
}

bool parentheses_balance_check(const std::string& str)
{
    using namespace ds;

    bool flag(true);
    Stack<Version::V0,char> pStack;

    for (std::string::const_iterator it = str.begin(); it != str.end(); ++it)
    {
        char ch = *it;
        short id = parentheses_id(ch);

        if (id < 0)
        {
            //opening parentheses
            pStack.push(ch);
        }
        else if (id > 0)
        {
            //closing parentheses
            if (pStack.isEmpty())
            {
                flag = false;
                break;
            } 
            else
            {
                ListNode<Version::V0,char>* topNode = pStack.top();
                short topId = parentheses_id(topNode->item());

                if (id != -1*topId)
                {
                    flag = false;
                    break;
                }

                pStack.pop();
            }
        } 
        else
        {
            //non-parentheses
        }
    }

    if (!pStack.isEmpty())
    {
        //there's at least one opening parentheses without its corresponding closing parentheses
        flag = false;
    }

    return flag;
}