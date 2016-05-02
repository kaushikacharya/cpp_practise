// https://www.hackerrank.com/challenges/balanced-parentheses
// May 01, 2016

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <stack>

using namespace std;

class Parentheses
{
public:
    Parentheses(){};
    ~Parentheses(){};
public:
    bool check_balance(string str)
    {
        // sanity check: str should have even number of characters
        if (str.size()%2 == 1)
        {
            return false;
        }

        stack<char> stk;
        bool flag_balanced = true;
        for (unsigned int i = 0; i != str.size(); ++i)
        {
            if (stk.empty())
            {
                bool is_next_char_opening_parentheses = is_parenthesis_opening_type(str[i]);

                if (is_next_char_opening_parentheses)
                {
                    stk.push(str[i]);
                }
                else
                {
                    flag_balanced = false;
                    break;
                }
            }
            else
            {
                char ch_stk_top = stk.top();
                // case a: str[i] closes the parentheses of ch_stk_top
                //          pop the top element in stack
                // case b: push str[i] into stack if its of an opening type
                bool flag_balance = is_next_char_balances_top_of_stack(ch_stk_top, str[i]);

                if (flag_balance)
                {
                    stk.pop();
                }
                else
                {
                    bool is_next_char_opening_parentheses = is_parenthesis_opening_type(str[i]);

                    if (is_next_char_opening_parentheses)
                    {
                        stk.push(str[i]);
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }

        if (stk.empty() && flag_balanced)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
private:
    // returns: (a) is the current char (str[i]) i.e. end_parentheses balances parentheses at top of stack?
    //          (b) Is end_parentheses belongs to opening parentheses?
    //      If (a) is false and end_parentheses is closing parentheses, then the string sequence won't have a balance of parentheses
    bool is_next_char_balances_top_of_stack(char begin_parentheses, char end_parentheses)
    {
        bool flag_balance = true;
        switch (begin_parentheses)
        {
            case '(':
               if (end_parentheses != ')')
               {
                   flag_balance = false;
               }
               break;
            case '{':
                if (end_parentheses != '}')
                {
                    flag_balance = false;
                }
                break;
            case '[':
                if (end_parentheses != ']')
                {
                    flag_balance = false;
                }
                break;
            default:
                flag_balance = false;
        }

        return flag_balance;
    }

    bool is_parenthesis_opening_type(char parentheses)
    {
        bool is_next_char_opening_parentheses;
        switch (parentheses)
        {
            case '(':
                is_next_char_opening_parentheses = true;
                break;
            case '{':
                is_next_char_opening_parentheses = true;
                break;
            case '[':
                is_next_char_opening_parentheses = true;
                break;
            default:
                is_next_char_opening_parentheses = false;
        }

        return is_next_char_opening_parentheses;
    }
};


int main(int argc, char* argv[]) {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

    /*
    string seq_str;
    getline(cin, seq_str);
    cout << seq_str << endl;
    */

    int n_test_cases;
    cin >> n_test_cases;
    // cout << "Number of test cases: " << n_test_cases << endl;
    Parentheses parentheses;

    for (unsigned int test_case_i = 0; test_case_i != n_test_cases; ++test_case_i)
    {
        string seq_str;
        // getline(cin, seq_str);
        cin >> seq_str;
        // cout << "test_case #" << test_case_i << " : " << seq_str << " size: " << seq_str.size() << endl;
        bool flag_valid = parentheses.check_balance(seq_str);
        if (flag_valid)
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }

    return 0;
}

/*  Editorial:
    Thought process in editorial is more clear than mine.
*/

/*
http://stackoverflow.com/questions/25985639/passing-text-file-to-standard-input
http://stackoverflow.com/questions/13035674/how-to-read-line-by-line-or-a-whole-text-file-at-once
http://www.cplusplus.com/reference/istream/istream/getline/
http://www.cplusplus.com/doc/tutorial/basic_io/
*/
