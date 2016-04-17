// http://www.geeksforgeeks.org/backttracking-set-5-m-coloring-problem/
// Date: Feb 25, 2015

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// undirected graph
class Graph
{
public:
    Graph(int nNode)
    : nNode_(nNode)
    {
        adjList_.reserve(nNode_);
        for (int i=0; i != nNode_; ++i)
        {
            adjList_.push_back(vector<int>());
        }
    }
public:
    void add_edge(int node_i, int node_j)
    {
        adjList_[node_i].push_back(node_j);
        adjList_[node_j].push_back(node_i);
    }
    vector<int> adj_nodes(int node_i)
    {
        return adjList_[node_i];
    }
    int size()
    {
        return adjList_.size();
    }
private:
    vector<vector<int> > adjList_;
    int nNode_;
};

// Backtracking
class Solution
{
public:
    Solution(Graph g, int m)
    : graph_(g)
    , nColor_(m)
    {
        vecVisited_.reserve(graph_.size());
        vecNodeColor_.reserve(graph_.size());
        vecParentNode_.reserve(graph_.size());

        for (int i=0; i != graph_.size(); ++i)
        {
            vecVisited_.push_back(false);
            vecNodeColor_.push_back(nColor_); // dummy assignment to initialize
            vecParentNode_.push_back(-1); // dummy assignment to initialize
        }
    }
    bool graph_coloring(int start_node_index=0)
    {
        stack<int> stk;
        stk.push(start_node_index);

        while (!stk.empty())
        {
            int node_i = stk.top();
            stk.pop();

            if (vecVisited_[node_i])
            {
                continue;
            }
            // TBD: a) assign color to node_i
            //      b) check if node_i gets color different from its neighbors
            bool flag_color_assigned = assign_color_to_node(node_i);

            if (!flag_color_assigned)
            {
                // backtrack
                int parent_node_index = vecParentNode_[node_i];
                if (parent_node_index == -1)
                {
                    break; // exhausted all trials
                }
                vecVisited_[parent_node_index] = false;
                stk.push(parent_node_index);
                continue;
            }

            vecVisited_[node_i] = true;

            vector<int> vec_adj_nodes = graph_.adj_nodes(node_i);
            for (vector<int>::iterator it = vec_adj_nodes.begin(); it != vec_adj_nodes.end(); ++it)
            {
                int node_j = *it;
                if (vecVisited_[node_j])
                {
                    continue;
                }
                vecParentNode_[node_j] = node_i;
                stk.push(node_j);
            }
        }

        if (stk.empty())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    void print_color_assigned_to_nodes()
    {
        for (int i = 0; i != graph_.size(); ++i)
        {
            cout << "node # " << i << " : color # " << vecNodeColor_[i] << endl;
        }
    }
private:
    bool assign_color_to_node(int node_i)
    {
        vector<bool> vec_color_availability(nColor_, true);
        vector<int> vec_adj_nodes = graph_.adj_nodes(node_i);

        for (vector<int>::iterator it = vec_adj_nodes.begin(); it != vec_adj_nodes.end(); ++it)
        {
            int node_j = *it;
            if (vecVisited_[node_j])
            {
                vec_color_availability[vecNodeColor_[node_j]] = false;
            }
        }

        // Logic:
        // We have initialized color index for each node as nColor_ i.e. out of color range
        // Case #1: We have reached this node in forward pass. Then we start checking from index 0 onwards.
        // Case #2: In backward pass (i.e. due to backtrack) we should start checking from the next index
        //          to what its aleady assigned. Reason: We had already checked the color indices prior to
        //          the current one in forward pass.
        bool flag = false;
        int color_index_available = (vecNodeColor_[node_i] == nColor_) ? 0 : (vecNodeColor_[node_i]+1);
        while (color_index_available < nColor_)
        {
            if (vec_color_availability[color_index_available])
            {
                flag = true;
                vecNodeColor_[node_i] = color_index_available;
                break;
            }
            ++color_index_available;
        }

        return flag;
    }
private:
    vector<bool> vecVisited_;
    vector<int> vecNodeColor_; // color indices: [0,1,...,(m-1)]
    vector<int> vecParentNode_; // parent is wrt the path through which we reach a particular node
    Graph graph_;
    int nColor_;
};

int main(int argc, char* argv[])
{
    /*
    Graph g(5);
    g.add_edge(0,1);
    g.add_edge(0,4);
    g.add_edge(1,2);
    g.add_edge(1,3);
    g.add_edge(2,3);
    */

    // bi-partite graph
    Graph g(4);
    g.add_edge(0,1);
    g.add_edge(0,3);
    g.add_edge(1,2);
    g.add_edge(2,3);

    int nColor = 2;
    Solution sln(g,nColor);
    bool flag_coloring = sln.graph_coloring();
    if (flag_coloring)
    {
        sln.print_color_assigned_to_nodes();
    }
    else
    {
        cout << "coloring failed" << endl;
    }

    return 0;
}

/*
Bipartitedness of a graph can be check using 2-color
http://www.geeksforgeeks.org/bipartite-graph/

http://en.wikipedia.org/wiki/Graph_coloring
*/
