// https://www.hackerrank.com/contests/world-codesprint-12/challenges/breaking-sticks/problem
// Jan 02, 2018

#include <bits/stdc++.h>

using namespace std;

// recursive function
long compute_max_moves(long n, unordered_map<long,long> map_max_moves)
{
    unordered_map<long,long>::iterator it = map_max_moves.find(n);
    if (it != map_max_moves.end())
    {
        return (*it).second;
    }

    if (n == 1)
    {
        return (long)1;
    }

    long max_moves = 1+n; // For n>1, one combination is making n parts with length = 1 of stick

    // Compute the moves for each pair of i,j such that i*j = n
    // Here i <= j. Hence i will go upto sqrt(n)
    long i = 2; // i*j = n
    while (i < n)
    {
        if (n%i != 0)
        {
            // move to next i as i is not a divisor of n
            ++i;
            continue;
        }

        long j = n/i;
        if (j < i)
        {
            // we have crossed sqrt(n) for i
            break;
        }

        // For the i,j pair there are two combinations:
        // a) i parts of stick with length=j
        // b) j parts of stick with length=i

        // (a)
        max_moves = max(max_moves, 1+i*compute_max_moves(j, map_max_moves));

        // (b)
        max_moves = max(max_moves, 1+j*compute_max_moves(i, map_max_moves));

        ++i;
    }

    // update the map
    map_max_moves[n] = max_moves;

    return max_moves;
}

vector<long> compute_factors(long n)
{
    vector<long> vecFactor;

    // Compute the moves for each pair of i,j such that i*j = n
    // Here i <= j. Hence i will go upto sqrt(n)
    long i = 1;
    while (i <= n)
    {
        if (n%i != 0)
        {
            // move to next i as i is not a divisor of n
            ++i;
            continue;
        }

        long j = n/i;
        if (j < i)
        {
            // we have crossed sqrt(n) for i
            break;
        }

        vecFactor.push_back(i);
        if (i != j)
        {
            // To avoid inserting same factor twice
            // case: (a) i = sqrt(n)  (b) n = 1
            vecFactor.push_back(j);
        }

        ++i;
    }

    sort(vecFactor.begin(), vecFactor.end());
    return vecFactor;
}

// non-recursive function to compute max number of moves for each of the factors for the given number
// This will ultimately lead to computing max number of moves for the given number.
void compute_max_moves(vector<long> vecFactor, unordered_map<long,long>& map_max_moves)
{
    // assumption: vecFactor is sorted in ascending order
    // map_max_moves: For the key max number of moves have been already computed
    unordered_map<long,long> map_moves; // iteratively keep increasing number of moves till its max possible

    // initialize moves
    for (vector<long>::iterator it = vecFactor.begin(); it != vecFactor.end(); ++it)
    {
        // First check if we have already computed max number of moves for the given factor while computing max number of moves for a number in previous iteration.
        unordered_map<long,long>::iterator mIt = map_max_moves.find(*it);
        if (mIt != map_max_moves.end())
        {
            map_moves[*it] = mIt->second;
            continue;
        }

        if (*it == 1)
        {
            map_moves[*it] = 1;
        }
        else
        {
            map_moves[*it] = *it + 1;
        }
    }

    assert((vecFactor.front()==1) && "lowest factor of each number will be 1");

    for (unsigned long i=1; i != vecFactor.size(); ++i)
    {
        // Lower factors i.e. before vecFactor[i] already have achieved max number of moves
        unordered_map<long,long>::iterator mIt = map_max_moves.find(vecFactor[i]);
        if (mIt != map_max_moves.end())
        {
            // already max number of moves stored for vecFactor[i]
            continue;
        }
        for (unsigned long j=0; j != i; ++j)
        {
            if (vecFactor[i]%vecFactor[j] != 0)
            {
                // vecFactor[j] is not a divisor of vecFactor[i]
                continue;
            }
            long divisor = vecFactor[i]/vecFactor[j];
            if (divisor < 2)
            {
                // none of the other factors are going to be divisor of vecFactor[i]
                break;
            }
            map_moves[vecFactor[i]] = max(map_moves[vecFactor[i]], 1+divisor*map_moves[vecFactor[j]]);
        }
    }

    // Now update map_max_moves
    for (unordered_map<long,long>::iterator it = map_moves.begin(); it != map_moves.end(); ++it)
    {
        map_max_moves[it->first] = it->second;
    }

}

long longestSequence(vector <long> a) {
    //  Return the length of the longest possible sequence of moves.
    unordered_map<long,long> map_max_moves; // value represents the max number of moves for the given key
    map_max_moves[1] = 1;

    long longest_seq = 0;

    // Get the list of factors of ai in sorted order

    // Initialize max moves as n+1 for n if n > 1

    // Move from left: e.g. For ai=48, pick 2 and keep updating max moves
    // Factors of 48: 1,2,3,4,6,8,12,16,24,48
    // When we choose start as 2, then 4,6,8,12,24,28 can be split as block of 2
    // choosing 2 means we already found max moves of 2

    // Next we need to handle for rest of the ai's
    // Challenge: For the factors of 48 we are done with max moves. So when the next a1 comes we shouldn't repeat for the factors if they have been done in earlier ai's

    bool use_recursive_func = false;
    cout << "number of sticks: " << a.size() << endl;
    for (vector<long>::iterator it = a.begin(); it != a.end(); ++it)
    {
        cout << *it << ",";
    }
    sort(a.begin(), a.end());
    for (vector<long>::iterator it = a.begin(); it != a.end(); ++it)
    {
        cout << "stick length: " << *it << endl;
        if (use_recursive_func)
        {
            longest_seq += compute_max_moves(*it, map_max_moves);
        }
        else
        {
            vector<long> vecFactor = compute_factors(*it);
            cout << "size(factors): " << vecFactor.size() << endl;
            compute_max_moves(vecFactor, map_max_moves);
            // cout << "size(factors): " << vecFactor.size() << " : map_max_moves:size() : " << map_max_moves.size() << endl;
            unordered_map<long,long>::iterator mIt = map_max_moves.find(*it);
            assert((mIt != map_max_moves.end()) && "ai missing in map_max_moves");
            longest_seq += mIt->second;
        }
    }

    return longest_seq;
}

int main() {
    int n;
    cin >> n;
    vector<long> a(n);
    for(int a_i = 0; a_i < n; a_i++){
       cin >> a[a_i];
       cout << a[a_i] << endl;
    }
    long result = longestSequence(a);
    cout << result << endl;
    return 0;
}

/***
Current Status:
    Timeout error

* https://www.geeksforgeeks.org/unordered_map-in-stl-and-its-applications/
*/
