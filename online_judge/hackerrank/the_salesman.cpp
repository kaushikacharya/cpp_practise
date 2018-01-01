// https://www.hackerrank.com/contests/world-codesprint-12/challenges/the-salesman
// Jan 01, 2018

#include <bits/stdc++.h>

using namespace std;

int minimumTime(vector <int> x) {
    //  Return the minimum time needed to visit all the houses.
    int min_x = x[0];
    int max_x = x[0];

    for (vector<int>::iterator it = x.begin()+1; it != x.end(); ++it)
    {
        if (*it < min_x)
        {
            min_x = *it;
        }
        if(max_x < *it)
        {
            max_x = *it;
        }
    }

    // minimum time will be taken if we start from the house with minimum position and move towards the maximum position
    return max_x - min_x;
}

int main() {
    int t;
    cin >> t;
    for(int a0 = 0; a0 < t; a0++){
        int n;
        cin >> n;
        vector<int> x(n);
        for(int x_i = 0; x_i < n; x_i++){
           cin >> x[x_i];
        }
        int result = minimumTime(x);
        cout << result << endl;
    }
    return 0;
}
