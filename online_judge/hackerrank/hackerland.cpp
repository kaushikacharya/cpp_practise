// https://www.hackerrank.com/contests/world-codesprint-11/challenges/hackerland
// Jan 28, 2018

#include <bits/stdc++.h>

using namespace std;

class HackerLand
{
public:
    HackerLand(int n)
    : n_(n)
    {
        for (int i=0; i != n; ++i)
        {
            adjList_.push_back(vector<int>());
        }
    }
public:
    void add_edge(int x, int y)
    {
        // Adding edge x -> y
        adjList_[x].push_back(y);
        // cout << "add edge: " << x << " -> " << y << endl;
    }

    void add_node()
    {
        ++n_;
        adjList_.push_back(vector<int>());
    }

    bool path_exists(int x, int y)
    {
        // Checks if there exist a path to move from x to y
        vector<bool> vecVisited(n_, false);
        // Do a BFS traversal till either y is reached or there's no more nodes available in queue
        queue<int> Q;
        Q.push(x);

        bool isPathExist = false;
        while (!Q.empty())
        {
            int cur_elem = Q.front();
            Q.pop();
            // cout << "Front element of queue: " << cur_elem << endl;
            if (cur_elem == y)
            {
                isPathExist = true;
                break;
            }

            if (vecVisited[cur_elem])
            {
                // cout << "Already visited. Hence not inserting any adjacent element for cur_elem: " << cur_elem << endl;
                continue;
            }
            vecVisited[cur_elem] = true;

            // cout << "Pushing adjacent element for cur_elem: " << cur_elem << " :: ";
            for (vector<int>::iterator it = adjList_[cur_elem].begin(); it != adjList_[cur_elem].end(); ++it)
            {
                Q.push(*it);
                // cout << *it << " ";
            }
            // cout << endl;
        }

        return isPathExist;
    }
private:
    int n_; // number of cities
    // we are using 0 based indexing for city numbers
    vector<vector<int> > adjList_;
};

int main() {
    int n;
    int m;
    cin >> n >> m;
    HackerLand hackerLand(n);
    for(int a0 = 0; a0 < m; a0++){
        int u;
        int v;
        cin >> u >> v;
        hackerLand.add_edge(u-1, v-1);
    }
    int q;
    cin >> q;
    for(int a0 = 0; a0 < q; a0++){
        int query_type;
        int x;

        cin >> query_type;

        if (query_type == 1)
        {
            hackerLand.add_node();
            ++n;
            int d;
            cin >> x >> d;
            if (d == 0)
            {
                hackerLand.add_edge(x-1, n-1);
            }
            else
            {
                hackerLand.add_edge(n-1, x-1);
            }
        }
        else
        {
            int y;
            cin >> x >> y;
            bool isPathExist = hackerLand.path_exists(x-1, y-1);
            if (isPathExist)
            {
                cout << "Yes" << endl;
            }
            else
            {
                cout << "No" << endl;
            }
        }

    }
    return 0;
}

/**
Current status:
Time Limit exceeded for almost all of the test cases.
*/
