// http://www.geeksforgeeks.org/greedy-algorithms-set-6-dijkstras-shortest-path-algorithm/
// Date: Feb 04, 2015

#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <vector>
#include <cassert>

using namespace std;

template <typename T, typename W>
struct Edge
{
    T tgtNode;
    W weight;
    Edge(T vertex, W wt): tgtNode(vertex), weight(wt){}
};

template <typename T, typename W>
struct Comp
{
    bool operator()(const pair<T,W>& elem1, const pair<T,W>& elem2) const
    {
        return elem1.second < elem2.second;
    }
};

template <typename T, typename W>
class Graph
{
public:
    Graph(){}

    void add_vertex(T v)
    {
        adjList_.insert(make_pair(v, vector<Edge<T,W> >()));
        visitedMap_.insert(make_pair(v,false));
    }

    void add_edge(T src, T tgt, W wt)
    {
        Edge<T,W> edge(tgt,wt);
        typename map<T, vector<Edge<T,W> > >::iterator it = adjList_.find(src);
        assert((it != adjList_.end()) && "source vertex not present");
        (*it).second.push_back(edge);
    }

    void compute_shortest_path(T src)
    {
        // TBD: map of (node,cost). Here cost represents either the final cost or the cost in priority queue
        set<pair<T,W>, Comp<T,W> > pq;
        map<T,W> node_cost_map;
        // initializing elements of priority queue
        for (typename map<T, vector<Edge<T,W> > >::iterator it = adjList_.begin(); it != adjList_.end(); ++it)
        {
            W priority = numeric_limits<W>::max();
            if ((*it).first == src)
            {
                priority = 0;
            }
            pq.insert(make_pair((*it).first,priority));
            node_cost_map.insert(make_pair((*it).first, priority));
        }

        while (!pq.empty())
        {
            pair<T,W> elem_top_priority = *(pq.begin());
            pq.erase(pq.begin());
            T node_top_priority = elem_top_priority.first;
            W cost_shortest_path_top_priority = elem_top_priority.second;
            typename map<T,bool>::iterator vIt = visitedMap_.find(node_top_priority);
            (*vIt).second = true;
            cout << node_top_priority << " : " << cost_shortest_path_top_priority << endl;

            // update the path cost of the nodes in the adjacency list of node_top_priority
            typename map<T, vector<Edge<T,W> > >::iterator it = adjList_.find(node_top_priority);
            for (typename vector<Edge<T,W> >::iterator edgeIt = (*it).second.begin(); edgeIt != (*it).second.end(); ++edgeIt)
            {
                T adj_node = (*edgeIt).tgtNode;
                W edge_weight = (*edgeIt).weight;

                // consider the adj_node only if its not visited earlier
                vIt = visitedMap_.find(adj_node);
                if (!(*vIt).second)
                {
                    typename map<T,W>::iterator cIt = node_cost_map.find(adj_node);
                    if ((cost_shortest_path_top_priority+edge_weight) < (*cIt).second)
                    {
                        // we found a path with lower cost from source node to adj_node
                        // update the cost in priority queue
                        // implementation: remove the node and then insert back with updated cost
                        //typename set<pair<T,W>, Comp<T,W> >::iterator pqIt = pq.find(make_pair(adj_node,(*cIt).second));
                        //pq.erase(pqIt);
                        pq.erase(make_pair(adj_node,(*cIt).second));
                        W updated_cost = cost_shortest_path_top_priority+edge_weight;
                        pq.insert(make_pair(adj_node,updated_cost));
                        (*cIt).second = updated_cost;
                    }
                }
            }
        }
    }
private:
    map<T, vector<Edge<T,W> > > adjList_;
    map<T, bool> visitedMap_;
};

int main(int argc, char* argv[])
{
    Graph<char,int> graph;
    // add vertices
    for (int i=0; i != 9; ++i)
    {
        graph.add_vertex('a'+i);
    }
    // add edges
    graph.add_edge('a','b',4);
    graph.add_edge('b','a',4);
    graph.add_edge('b','c',8);
    graph.add_edge('c','b',8);
    graph.add_edge('c','d',7);
    graph.add_edge('d','c',7);
    graph.add_edge('d','e',9);
    graph.add_edge('e','d',9);
    graph.add_edge('e','f',10);
    graph.add_edge('f','e',10);
    graph.add_edge('d','f',14);
    graph.add_edge('f','d',14);
    graph.add_edge('c','f',4);
    graph.add_edge('f','c',4);
    graph.add_edge('f','g',2);
    graph.add_edge('g','f',2);
    graph.add_edge('g','i',6);
    graph.add_edge('i','g',6);
    graph.add_edge('c','i',2);
    graph.add_edge('i','c',2);
    graph.add_edge('h','i',7);
    graph.add_edge('i','h',7);
    graph.add_edge('g','h',1);
    graph.add_edge('h','g',1);
    graph.add_edge('b','h',11);
    graph.add_edge('h','b',11);
    graph.add_edge('a','h',8);
    graph.add_edge('h','a',8);

    graph.compute_shortest_path('a');

    return 0;
}

/*
Note: using map for adjacency_list :: In this case its complexity is as expected but in case of BFS/DFS it will lead to
additional complexity i.e O(|V|*log(|V|) + |E|)

http://stackoverflow.com/questions/14133115/implementation-of-an-adjacency-list-graph-representation (Yuushi's answer)
 Adjacency list using map:
http://www.cplusplus.com/forum/beginner/112723/

Set based as well as Binary heap based solution:
http://stackoverflow.com/questions/9209323/easiest-way-of-using-min-priority-queue-with-key-update-in-c

http://fusharblog.com/3-ways-to-define-comparison-functions-in-cpp/
*/
