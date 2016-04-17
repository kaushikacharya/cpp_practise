// http://www.geeksforgeeks.org/find-paths-given-source-destination/
// Date: Jan 31, 2015

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// directed graph
template <typename T>
class Graph
{
public:
    Graph(){}

    void add_vertices(vector<T>& vecNode)
    {
        nNode_ = vecNode.size();
        vecNode_ = vecNode_;
        adjList_.reserve(nNode_);

        for (int i=0; i != nNode_; ++i)
        {
            adjList_.push_back(vector<int>());
        }
    }

    void add_edge(int node_i, int node_j)
    {
        adjList_[node_i].push_back(node_j);
    }
public:
    // we will do a DFS traversal
    void find_paths(int source_index, int target_index)
    {
        typedef vector<vector<int> > VecOfVec;
        stack<pair<int, VecOfVec> > stk;
        VecOfVec vecPath;
        vector<int> path;
        path.push_back(source_index);
        vecPath.push_back(path);
        stk.push(make_pair(source_index, vecPath));

        while (!stk.empty())
        {
            pair<int, VecOfVec> elem = stk.top();
            stk.pop();
            int node_index = elem.first;

            if (node_index == target_index)
            {
                VecOfVec vecPath = elem.second;
                for (VecOfVec::iterator pathIt = vecPath.begin(); pathIt != vecPath.end(); ++pathIt)
                {
                    vector<int> path = *pathIt;
                    // print the path
                    for (vector<int>::iterator it = path.begin(); it != path.end(); ++it)
                    {
                        if (it != path.begin())
                        {
                            cout << ",";
                        }
                        cout << *it;
                    }
                    cout << endl;
                }
            }
            else
            {
                for (vector<int>::iterator it = adjList_[node_index].begin(); it != adjList_[node_index].end(); ++it)
                {
                    int adj_node_index = *it;
                    VecOfVec vecPath = elem.second;

                    for (VecOfVec::iterator pathIt = vecPath.begin(); pathIt != vecPath.end(); ++pathIt)
                    {
                        (*pathIt).push_back(adj_node_index);
                        //vector<int>& path = *pathIt;
                        //path.push_back(adj_node_index);
                    }

                    stk.push(make_pair(adj_node_index, vecPath));
                }
            }
        }
    }
private:
    int nNode_;
    vector<T> vecNode_;
    vector<vector<int> > adjList_; // stores indices of the nodes
};

int main(int argc, char* argv[])
{
    char arr[] = {'a', 'b', 'c', 'd'};
    vector<char> vecNode(arr, arr+sizeof(arr)/sizeof(arr[0]));
    Graph<char> graph;
    graph.add_vertices(vecNode);
    graph.add_edge(0,1);
    graph.add_edge(0,2);
    graph.add_edge(1,2);
    graph.add_edge(1,3);
    graph.add_edge(2,3);

    graph.find_paths(0,3);

    return 0;
}
