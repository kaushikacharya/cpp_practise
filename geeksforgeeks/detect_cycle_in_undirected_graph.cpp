// http://www.geeksforgeeks.org/detect-cycle-undirected-graph/
// Date: Jan 26, 2015

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

template <typename T>
class Graph
{
public:
    Graph(){}

    void add_vertices(vector<T> vec)
    {
        nNode_ = vec.size();
        vecNode_.reserve(vec.size());
        adjList_.reserve(vec.size());
        vecVisited_.reserve(vec.size());

        for (typename vector<T>::iterator it = vec.begin(); it != vec.end(); ++it)
        {
            vecNode_.push_back(*it);
            adjList_.push_back(vector<int>());
            vecVisited_.push_back(false);
        }
    }

    void add_edge(int node_i, int node_j)
    {
        adjList_[node_i].push_back(node_j);
        adjList_[node_j].push_back(node_i);
    }

    bool isDetectCycle()
    {
        // assign false to visited flag
        for (int i=0; i != nNode_; ++i)
        {
            vecVisited_[i] = false;
        }

        bool flag_cycle_present = false;
        for (int i=0; i != nNode_; ++i)
        {
            if (vecVisited_[i])
            {
                continue; // current node has been processed earlier
            }

            // Now do a traversal over the nodes to detect presence of cycle
            stack<int> stk;
            stk.push(i);

            while (!stk.empty())
            {
                int node_i = stk.top();
                stk.pop();

                if (vecVisited_[node_i])
                {
                    flag_cycle_present = true;
                    break;
                }

                vecVisited_[node_i] = true;
                for (vector<int>::iterator adjIt = adjList_[node_i].begin(); adjIt != adjList_[node_i].end(); ++adjIt)
                {
                    int node_j = *adjIt;
                    if (!vecVisited_[node_j])
                    {
                        stk.push(node_j);
                    }
                }
            }

            if (flag_cycle_present)
            {
                // empty stk
                while (!stk.empty())
                {
                    stk.pop();
                }
                break;
            }
        }

        return flag_cycle_present;
    }
private:
    int nNode_;
    vector<T> vecNode_;
    vector<vector<int> > adjList_; // only indices are stored
    vector<bool> vecVisited_;
};

int main(int argc, char* argv[])
{
    Graph<int> graph;
    int arr[] = {0,1,2,3,4};
    vector<int> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));
    graph.add_vertices(vec);
    graph.add_edge(0,1);
    graph.add_edge(0,2);
    //graph.add_edge(1,2);
    graph.add_edge(0,3);
    graph.add_edge(3,4);
    bool flag_cycle_present = graph.isDetectCycle();
    cout << flag_cycle_present << endl;
    return 0;
}
