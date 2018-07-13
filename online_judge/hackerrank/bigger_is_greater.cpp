// https://www.hackerrank.com/challenges/bigger-is-greater/problem
// July 12, 2018

#include <bits/stdc++.h>

using namespace std;

// Complete the biggerIsGreater function below.
string biggerIsGreater(string w) {
    string output = "no answer";
    if (w.size() == 1)
    {
        return output;
    }

    // iterate from right to left until we fail to find the suffix which fails to be the biggest suffix from those characters
    // i.e. w[i+1,...,end] is in lexicographically non-increasing order. w[i,...,end] fails to be in non-increasing order.
    int i = w.size()-2;
    while (i >= 0)
    {
        if (w[i] < w[i+1])
        {
            break;
        }
        else
        {
            --i;
        }
    }

    if (i < 0)
    {
        // w is the lexicographically biggest possible string for the characters of w
        return output;
    }

    // w[i,i+1,..w.size()-1] needs to be swapped so that w becomes the next string of input w in lexicographical order
    // Prefix w[0,...,i-1] need not be changed to get the next string bigger than original input.

    // First find the character in w[i+1,...,w.size()-1] which is smallest among the ones greater than w[i]
    int j = w.size()-1;
    while (j > i)
    {
        if (w[j] > w[i])
        {
            break;
        }
        else
        {
            --j;
        }
    }

    // Swap w[i] with that character
    swap(w[i], w[j]);

    // Then reverse w[i+1,...,w.size()-1]
    reverse(w.begin()+i+1, w.end());

    return w;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int T;
    cin >> T;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int T_itr = 0; T_itr < T; T_itr++) {
        string w;
        getline(cin, w);

        string result = biggerIsGreater(w);

        fout << result << "\n";
        // cout << result << "\n";
    }

    fout.close();

    return 0;
}

/*
Time complexity: O(n)
*/
