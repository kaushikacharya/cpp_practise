// https://www.hackerrank.com/challenges/common-child/problem
// Dec 30, 2017

#include <bits/stdc++.h>

using namespace std;

int commonChild(string s1, string s2){
    // matrix of longest child
    // Notation: row represents characters of s1 and col represents characters of s2
    // matrix[i,j]: represents the longest child created from s1[0,...,i] and s2[0,...,j]
    vector<vector<int> > matrix;
    matrix.reserve(s1.size());
    // initialize with zeros
    for (unsigned int i=0; i != s1.size(); ++i)
    {
        matrix.push_back(vector<int>(s2.size()));

        for (unsigned int j=0; j != s2.size(); ++j)
        {
            matrix[i][j] = 0;
        }
    }

    // populate first row
    unsigned int j = 0;
    // iterate over the characters of s2 till it matches the 1st character of s1
    while( (j < s2.size()) && (s1[0] != s2[j]) )
    {
        ++j;
    }
    while(j < s2.size())
    {
        matrix[0][j] = 1;
        ++j;
    }

    // populate first column
    // similar logic as above
    unsigned int i = 0;
    while ( (i < s1.size()) && (s1[i] != s2[0]) )
    {
        ++i;
    }
    while (i < s1.size())
    {
        matrix[i][0] = 1;
        ++i;
    }

    for (unsigned int i=1; i != s1.size(); ++i)
    {
        unsigned int j = 1;
        while (j < s2.size())
        {
            if (s1[i] != s2[j])
            {
                // If s1[0,...,i] and s2[0,...,j] has n common child then for the rest of s2 it will be >= n common child
                matrix[i][j] = max(matrix[i-1][j], matrix[i][j-1]);
            }
            else
            {
                // Check whether s1[i] should be mapped to s2[j]
                // For this we need to figure out if s2[j] has been already mapped to a character in s1[0,...,i-1]
                if (matrix[i-1][j-1] == matrix[i-1][j])
                {
                    // s2[j] has not been yet mapped to s1[0,....,i-1]
                    int val = matrix[i-1][j] + 1;
                    matrix[i][j] = max(matrix[i][j-1], val);
                }
                else
                {
                    matrix[i][j] = max(matrix[i-1][j], matrix[i][j-1]);
                }
            }

            ++j;
        }
    }

    // For debugging, switch on check_matrix_validity
    bool check_matrix_validity = false;
    if (check_matrix_validity)
    {
        bool is_valid = true;

        for (unsigned int i=0; i != s1.size(); ++i)
        {
            for (unsigned int j=0; j != s2.size(); ++j)
            {
                if (i > 0)
                {
                    if (matrix[i][j] < matrix[i-1][j])
                    {
                        cout << "i: " << i << " ,j: " << j << " :: matrix[i][j] < matrix[i-1][j]" << endl;
                        is_valid = false;
                        break;
                    }
                }
                if (j > 0)
                {
                    if (matrix[i][j] < matrix[i][j-1])
                    {
                        cout << "i: " << i << " ,j: " << j << " :: matrix[i][j] < matrix[i][j-1]" << endl;
                        is_valid = false;
                        break;
                    }
                }
            }
        }

        assert(is_valid && "matrix invalid");
    }

    return matrix[s1.size()-1][s2.size()-1];
}

int main() {
    string s1;
    cin >> s1;
    string s2;
    cin >> s2;
    int result = commonChild(s1, s2);
    cout << result << endl;
    return 0;
}

/***
Learning:
As mentioned in editorial, to save space we can have only two rows instead of the entire matrix.
*/
