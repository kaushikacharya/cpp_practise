// https://www.hackerrank.com/contests/world-codesprint-11/challenges/numeric-string
// Jan 20, 2018

#include <bits/stdc++.h>

using namespace std;

int getMagicNumber(string s, int k, int b, int m){
    int magic_num = 0;

    // compute leading zeros (This can reduce the computation)
    unsigned int n_leading_zeros = 0;
    for (auto it=s.begin(); it != s.end(); ++it)
    {
        if (*it != '0')
        {
            break;
        }
        else
        {
            ++n_leading_zeros;
        }
    }

    // cout << "n_leading_zeros: " << n_leading_zeros << endl;
    // reverse the string
    reverse(s.begin(), s.end());
    // cout << s << endl;

    int cur_base_10_num = 0;
    unsigned int i = 0;
    int base_power = 1; // After computing for first base 10 number it should reach to b^(k-1)
    while (i < k)
    {
        if (i > 0)
        {
           base_power *= b;
        }
        cur_base_10_num += base_power * int(s[i]-'0');
        ++i;
    }
    // Now base_power = b^(k-1)
    // cout << "b^(k-1): " << cur_base_10_num << endl;
    magic_num += cur_base_10_num % m;
    // cout << "magic_num: " << magic_num << endl;

    // If there are enough leading zeros we can stop early
    unsigned int upper_index = s.size();
    if (k <= n_leading_zeros)
    {
        upper_index = s.size() - n_leading_zeros + k - 1;
    }
    // cout << "upper_index: " << upper_index << endl;
    while (i < upper_index)
    {
        cur_base_10_num = (cur_base_10_num - int(s[i-k]-'0'))/b + int(s[i]-'0')*base_power;
        magic_num += cur_base_10_num % m;
        // cout << "magic_num: " << magic_num << endl;
        ++i;
    }

    return magic_num;
}

int main() {
    cout << "max(int): " << numeric_limits<int>::max() << endl;
    string s;
    cin >> s;
    int k;
    int b;
    int m;
    cin >> k >> b >> m;
    int result = getMagicNumber(s, k, b, m);
    cout << result << endl;
    return 0;
}

/**
Status: Wrong answer for several test cases.
        This is because b^(k-1) can go beyond the limits of any data type.
*/
