// http://www.geeksforgeeks.org/write-a-c-program-to-print-all-permutations-of-a-given-string/
// June 21, 2016

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution
{
public:
    vector<string> compute_all_permutations(string str)
    {
        vector<string> vecPermutation;

        if (str.empty())
        {
            return vecPermutation;
        }
        else if (str.size() == 1)
        {
            vecPermutation.push_back(str);
            return vecPermutation;
        }

        for (int i=0; i != str.size(); ++i)
        {
            string sub_str = str.substr(0,i);
            sub_str += str.substr(i+1);

            vector<string> vecPermutationSubString = compute_all_permutations(sub_str);

            for (vector<string>::iterator it = vecPermutationSubString.begin(); it != vecPermutationSubString.end(); ++it)
            {
                string permutation_sub_str = *it;
                vecPermutation.push_back(str[i]+permutation_sub_str);
            }
        }

        return vecPermutation;
    }
};

int main(int argc, char* argv[])
{
    string str = "CACB";
    sort(str.begin(), str.end());
    cout << "str(post sort): " << str << endl;
    Solution sln;
    vector<string> vec_permutation = sln.compute_all_permutations(str);
    cout << "permutation: " << endl;
    for (vector<string>::iterator it = vec_permutation.begin(); it != vec_permutation.end(); ++it)
    {
        cout << *it << endl;
    }
    return 0;
}

/**
* We compute all permutations of the string in lexicographic order.
* Here we allow duplicates if multiple instance of any char is present in the string.
*
* Alternate approach of using swap instead of create sub_str:
*   http://www.geeksforgeeks.org/write-a-c-program-to-print-all-permutations-of-a-given-string/
*/
