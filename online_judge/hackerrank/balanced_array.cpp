// https://www.hackerrank.com/contests/world-codesprint-11/challenges/balanced-array
// Jan 20, 2018

#include <bits/stdc++.h>

using namespace std;

int solve(vector<int> a){
    // Complete this function
    int smallest_balancing_elem = 0;

    unsigned int n = a.size();
    unsigned int n_by_2 = n/2;
    unsigned int i = 0;

    while (i < n_by_2)
    {
        smallest_balancing_elem += a[i];
        smallest_balancing_elem -= a[i+n_by_2];
        ++i;
    }

    if (smallest_balancing_elem < 0)
    {
        smallest_balancing_elem *= -1;
    }

    return smallest_balancing_elem;
}

int main() {
    // cout << "int(max): " << numeric_limits<int>::max() << endl;
    int n;
    cin >> n;
    vector<int> a(n);
    for(int a_i = 0; a_i < n; a_i++){
       cin >> a[a_i];
    }
    int result = solve(a);
    cout << result << endl;
    return 0;
}
