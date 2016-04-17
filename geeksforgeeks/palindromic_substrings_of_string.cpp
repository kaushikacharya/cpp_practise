// http://www.geeksforgeeks.org/find-number-distinct-palindromic-sub-strings-given-string/
// Date: Feb 20, 2015

#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution
{
public:
    vector<string> get_palindromic_substrings(string str)
    {
        unordered_set<string> palindrome_set;
        vector<string> vecPalindrome;

        if (str.empty())
        {
            return vecPalindrome;
        }
        if (str.size() == 1)
        {
            vecPalindrome.push_back(str);
            return vecPalindrome;
        }

        // Now iterate over the positions(j) from left to right and mark the position i
        // such that str[i,...,j] is a palindrome
        vector<bool> prevVec(str.size(), false);
        // every char in the string is a palindrome in itself
        prevVec[0] = true;
        palindrome_set.insert(str.substr(0,1));

        for (int j=1; j != str.size(); ++j)
        {
            vector<bool> curVec(str.size(), false);
            int p = j;
            curVec[j] = true;

            for (int i = j-1; i >= 0; --i)
            {
                if (str[i] == str[j])
                {
                    if ((prevVec[i+1]) || (i == j-1))
                    {
                        // case #1: str[(i+1),....,(j-1)] is palindrome. This has been checked in previous iteration.
                        //          Using this str[i,.....,j] also becomes palindrome
                        // case #2: str[(j-1),j] is palindrome
                        curVec[i] = true;
                        p = i;
                    }
                }
            }

            // str[p,.....,j] is the palindrome
            string palindrome = str.substr(p, j-p+1);
            palindrome_set.insert(palindrome);

            prevVec = curVec;
        }

        for (unordered_set<string>::iterator it = palindrome_set.begin(); it != palindrome_set.end(); ++it)
        {
            vecPalindrome.push_back(*it);
        }

        return vecPalindrome;
    }
};

int main(int argc, char* argv[])
{
    string str = "geek";
    Solution sln;

    vector<string> vec_palindrome = sln.get_palindromic_substrings(str);
    for(vector<string>::iterator it = vec_palindrome.begin(); it != vec_palindrome.end(); ++it)
    {
        cout << *it << endl;
    }

    return 0;
}
