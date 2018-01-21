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
    // reverse(s.begin(), s.end());
    // cout << s << endl;

    int cur_base_10_num = 0;
    // If there are enough leading zeros then we can start computation from the substring which contains non-zero digit
    // as contribution of all digits have '0' will be 0
    unsigned int i = (n_leading_zeros < k) ? 0 : n_leading_zeros-k+1;
    int base_power = 1; // After computing for first base 10 number it should be b^(k-1) mod m
    unsigned int j = i + k - 1;
    while (true)
    {
        cur_base_10_num += int(s[j]-'0') * base_power;
        cur_base_10_num %= m;
        if (j == i)
        {
            break;
        }
        base_power = (base_power * b) % m;
        --j;
    }
    // Now base_power = b^(k-1) mod m

    // cout << "b^(k-1): " << cur_base_10_num << endl;
    magic_num += cur_base_10_num;
    // cout << "magic_num: " << magic_num << endl;

    // If there are enough leading zeros we can stop early
    unsigned int n_trailing_zeros = 0;
    for (auto it = s.rbegin(); it != s.rend(); ++it)
    {
        if (*it == '0')
        {
            n_trailing_zeros += 1;
        }
        else
        {
            break;
        }
    }
    unsigned int upper_index = s.size() - k + 1;
    if (k <= n_trailing_zeros)
    {
        upper_index = s.size() - n_trailing_zeros;
    }
    // cout << "upper_index: " << upper_index << endl;
    ++i;
    int left_most_contribution; // s[i-1]*b^(k-1) mod m
    while (i < upper_index)
    {
        // contribution by s[i-1] in cur_base_10_num
        // As we have moved ahead we would remove the contribution by s[i-1]
        left_most_contribution = (int(s[i-1]-'0') * base_power) % m;
        // remove contribution by s[i-1]
        if (left_most_contribution <= cur_base_10_num)
        {
            cur_base_10_num -= left_most_contribution;
        }
        else
        {
            cur_base_10_num = m - left_most_contribution + cur_base_10_num;
        }

        // Now add the contribution of newly added digit in the current substring
        cur_base_10_num = (cur_base_10_num * b + int(s[i+k-1]-'0')) % m;
        magic_num += cur_base_10_num;
        // cout << "magic_num: " << magic_num << endl;
        ++i;
    }

    return magic_num;
}

int main() {
    // cout << "max(int): " << numeric_limits<int>::max() << endl;
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

