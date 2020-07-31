/***
* https://binarysearch.io/problems/Pascal's-Triangle
* July 31, 2020
***/

#include <bits/stdc++.h>

using namespace std;

class Solution {
  public:
      vector<int> solve(int n) {
        // initialize with zeros
        vector<int> arr(n+1, 0);

        // final output = n'th row of the triangle.
        // It becomes easier to manage if we populate the first non-zero element of a row at a position
        //   which is left of the position of first non-zero element of previous row.
        arr[n] = 1;

        // iterate over each step of the Pascal's triangle
        for (int i=1; i != (n+1); ++i){
            // starting position of the first non-zero element of the current row.
            int j = n-i;
            // cout << "j: " << j << endl;

            while (j < n){
                arr[j] += arr[j+1];
                ++j;
                // cout << "j: " << j << endl;
            }
        }

        return arr;
      }
};

int main(int argc, char ** argv)
{
    Solution sln;

    int n = 3;
    vector<int> result = sln.solve(n);

    cout << result[0];
    for (unsigned int i=1; i != result.size(); ++i)
    {
        cout << "," << result[i];
    }
    cout << endl;

}

/**
* Time Complexity: O(n^2)
* Space Complexity: O(n)
**/
