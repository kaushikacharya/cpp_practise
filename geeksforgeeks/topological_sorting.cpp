// http://www.geeksforgeeks.org/topological-sorting/
// Date: Jan 30, 2015

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// directed acyclic graph
template <typename T>
class Graph
{
public:
    Graph(){}

    void add_vertices(vector<T>& vecNode)
    {
        nNode_ = vecNode.size();
        vecNode_ = vecNode;

        for (int i=0; i != nNode_; ++i)
        {
            vecVisited_.push_back(false);
            adjList_.push_back(vector<int>());
        }
    }

    void add_edge(int node_i, int node_j)
    {
        adjList_[node_i].push_back(node_j);
    }

    vector<T> sort_topological()
    {
        for (int node_i = 0; node_i != nNode_; ++node_i)
        {
            if (!vecVisited_[node_i])
            {
                dfs_traversal(node_i);
            }
        }

        vector<T> vec_topo_sort;
        vec_topo_sort.reserve(nNode_);

        while (!stk_.empty())
        {
            int node_i = stk_.top();
            stk_.pop();
            vec_topo_sort.push_back(vecNode_[node_i]);
        }

        return vec_topo_sort;
    }
private:
    void dfs_traversal(int node_i)
    {
        vecVisited_[node_i] = true;

        for (vector<int>::iterator it = adjList_[node_i].begin(); it != adjList_[node_i].end(); ++it)
        {
            int node_j = *it;
            if (!vecVisited_[node_j])
            {
                dfs_traversal(node_j);
            }
        }
        stk_.push(node_i);
    }
private:
    int nNode_;
    vector<T> vecNode_;
    vector<vector<int> > adjList_; // only indices are stored
    vector<bool> vecVisited_;
    stack<int> stk_;
};

int main(int argc, char* argv[])
{
    char arr[] = {'d', 'b', 'c', 'a'};
    vector<char> vecNode(arr, arr+sizeof(arr)/sizeof(arr[0]));
    Graph<char> graph;
    graph.add_vertices(vecNode);
    graph.add_edge(0,1);
    graph.add_edge(0,2);
    graph.add_edge(1,2);
    graph.add_edge(1,3);
    graph.add_edge(2,3);

    vector<char> vecTopoSortNode = graph.sort_topological();
    for (vector<char>::iterator it = vecTopoSortNode.begin(); it != vecTopoSortNode.end(); ++it)
    {
        cout << *it << " ";
    }

    return 0;
}
