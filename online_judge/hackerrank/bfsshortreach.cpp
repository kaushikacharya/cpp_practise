// https://www.hackerrank.com/challenges/bfsshortreach/problem
// Dec 02, 2017

#include <bits/stdc++.h>

using namespace std;

// undirected graph
class Graph
{
public:
    Graph(int nNodes)
    : nNodes_(nNodes)
    {
        adjList_.reserve(nNodes_);
        // assign empty list for each adjacent list
        for (int node_i=0; node_i != nNodes_; ++node_i)
        {
            adjList_.push_back(vector<int>());
        }

        // assign False to visited flag
        vecVisited_.reserve(nNodes_);
        for (int node_i=0; node_i != nNodes_; ++node_i)
        {
            vecVisited_.push_back(false);
        }
    }

    void add_edge(int u, int v)
    {
        adjList_[u].push_back(v);
        adjList_[v].push_back(u);
    }

    void bfs_traverse(int s, vector<int>& vecStep)
    {
        vecStep.reserve(nNodes_);
        // -1 represents that not possible to reach from node s
        for(int node_i=0; node_i != nNodes_; ++node_i)
        {
            vecStep.push_back(-1);
        }

        queue<pair<int,int> > Q;
        Q.push(make_pair(s,0)); // pair:(node,steps from source s)

        while (!Q.empty())
        {
            pair<int,int> cur_elem = Q.front();
            int cur_node = cur_elem.first;
            int n_step = cur_elem.second;
            Q.pop();

            if (vecVisited_[cur_node])
            {
                continue;
            }

            vecVisited_[cur_node] = true;
            vecStep[cur_node] = n_step;

            for (vector<int>::iterator it = adjList_[cur_node].begin(); it != adjList_[cur_node].end(); ++it)
            {
                int next_node = *it;

                // Though we are checking for visited flag as we enter the while loop again but to improve efficiency ignoring nodes
                // which have been already visited to be put again in queue
                if (!vecVisited_[next_node])
                {
                    Q.push(make_pair(next_node, n_step+1));
                }
            }
        }
    }
private:
    vector<vector<int> > adjList_;
    int nNodes_;
    vector<bool> vecVisited_;
};

int main() {
    int q;
    cin >> q;
    int step_cost = 6; // defined in the problem
    // Iterate over each query
    for(int a0 = 0; a0 < q; a0++){
        int n;
        long m;
        cin >> n >> m;
        Graph graph(n);
        for(long edge_i = 0; edge_i < m; edge_i++){
            int u;
            int v;
            cin >> u >> v;
            // input is 1 based indexed. Whereas in graph we have done 0 based indexing
            graph.add_edge(u-1, v-1);
        }
        int s;
        cin >> s;
        vector<int> vecStep;
        graph.bfs_traverse(s-1, vecStep);

        // print output
        for (int i = 0; i != (s-1); ++i)
        {
            int dist = (vecStep[i] < 0) ? vecStep[i] : step_cost * vecStep[i];
            if (i > 0)
            {
                cout << " ";
            }
            cout << dist;
        }

        for (int i = s; i != n; ++i)
        {
            int dist = (vecStep[i] < 0) ? vecStep[i] : step_cost * vecStep[i];
            if (i > 1)
            {
                cout << " ";
            }
            cout << dist;
        }
        cout << endl;
    }
    return 0;
}

