// https://www.hackerearth.com/practice/algorithms/string-algorithm/basics-of-string-manipulation/practice-problems/algorithm/find-the-substrings/
// Nov 29th 2017

#include<bits/stdc++.h>

using namespace std;

unsigned long long get_number_of_substrings(string str)
{
    // n_substr_all_chars: number of substrings which contains all the characters: 'a','b','c'
    unsigned long long n_substr_all_chars = 0;

    if (str.empty())
    {
        return 0;
    }
    vector<queue<unsigned long> > vecQ;
    // create vector of empty queue for the characters: 'a','b','c'
    unsigned int n_unique_chars = 3;
    for (unsigned int i=0; i != n_unique_chars; ++i)
    {
        vecQ.push_back(queue<unsigned long>());
    }

    // iterate over the characters of the given string and populate corresponding queues
    for (unsigned long i=0; i != str.length(); ++i)
    {
        char ch = str[i];
        vecQ[ch-'a'].push(i);
    }

    // First check if we have found atleast one instance of all the characters 'a','b','c'
    unsigned long cur_max_top = 0;
    bool flag = true;
    for (unsigned int i=0; i != n_unique_chars; ++i)
    {
        if (vecQ[i].empty())
        {
            flag = false;
            break;
        }
        if (cur_max_top < vecQ[i].front())
        {
            cur_max_top = vecQ[i].front();
        }
    }

    // Keep moving the start position of substring till substring satisfying the constraint mentioned in problem is satisfied
    unsigned long i = 0;
    while (flag)
    {
        char ch = str[i];
        // add number of substrings with starting position as i
        // indices of substrings: [i,...,cur_max_top], [i,...,cur_max_top+1], ..., [i,...,str.length()-1]
        n_substr_all_chars += str.length() - cur_max_top;
        // pop the current top i.e. i from the queue corresponding to the character ch
        vecQ[ch-'a'].pop();

        if (vecQ[ch-'a'].empty())
        {
            // There's no more character ch after position i
            break;
        }

        if (cur_max_top < vecQ[ch-'a'].front())
        {
            cur_max_top = vecQ[ch-'a'].front();
        }

        ++i;
    }

    unsigned long long total_substr = str.length()*(str.length()+1)/2;
    // n_substr: number of substrings with atleast one of character: 'a','b','c' missing
    unsigned long long n_substr = total_substr - n_substr_all_chars;
    return n_substr;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    bool flag_input_stream = true;

    if (flag_input_stream)
    {
        unsigned int T;
        cin >> T;

        unsigned long long n_substr;
        string str;
        for (unsigned int test_case_i=0; test_case_i != T; ++test_case_i)
        {
            cin >> str;
            n_substr = get_number_of_substrings(str);
            cout << n_substr << endl;
        }
    }
    else
    {
        // cout << numeric_limits<long long>::max() << endl;
        // cout << "b-a: " << 'b' - 'a' << endl;
        unsigned long long n_substr = get_number_of_substrings("babac");
        cout << "Number of substrings: " << n_substr << endl;
        //ababa  abc  babac
    }

    return 0;
}

/**
Discussion related to ios::sync_with_stdio:
    https://stackoverflow.com/questions/31162367/significance-of-ios-basesync-with-stdiofalse-cin-tienull
    http://codeforces.com/blog/entry/6251

https://stackoverflow.com/questions/5381882/are-there-types-bigger-than-long-long-int-in-c
*/

