// http://www.spoj.com/problems/ELIS/
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <stack>

const bool READ_FROM_FILE = false;

// elements of graph: indices of the list instead of the elements of the list.
template<typename T>
class Graph
{
public:
    Graph(T n)
        : n_(n)
    {
        vecNode_.reserve(n_);
        for (T i = 0; i != n_; ++i)
        {
            vecNode_.push_back(i);
            outAdjList_.push_back(std::vector<T>());
            inAdjList_.push_back(std::vector<T>());
        }
    }
public:
    // nodeA -> nodeB
    void add_edge(T nodeA, T nodeB)
    {
        outAdjList_[nodeA].push_back(nodeB);
        inAdjList_[nodeB].push_back(nodeA);
    }
    std::vector<T> out_edge_nodes(T node)
    {
        return outAdjList_[node];
    }
    std::vector<T> in_edge_nodes(T node)
    {
        return inAdjList_[node];
    }
private:
    T n_;
    std::vector<T> vecNode_;
    std::vector<std::vector<T> > outAdjList_;
    std::vector<std::vector<T> > inAdjList_;
};

// T1 - data type for index
// T2 - data type of elements of the list
template<typename T1, typename T2>
class LIS
{
public:
    LIS(T1 n)
        : n_(n)
        , graphOfIndex_(n_)
    {
        seq_.reserve(n_);
        vecTopologicalSortedIndex_.reserve(n_);
        vecExplored_.reserve(n_);
        vecSubSeqLength_.reserve(n_);
    }
public:
    void read_input_sequence(std::ifstream& pFile)
    {
        T2 elem;
        for(T1 elem_i = 0; elem_i != n_; ++elem_i)
        {
            if (READ_FROM_FILE)
            {
                pFile >> elem;
            }
            else
            {
                std::cin >> elem;
            }
            seq_.push_back(elem);
        }
    }
    T1 compute_longest_increasing_subsequence();
private:
    void build_graph()
    {
        for(T1 j=1; j != n_; ++j)
        {
            for(T1 i = 0; i != j; ++i)
            {
                if (seq_[i] < seq_[j])
                {
                    graphOfIndex_.add_edge(i,j);
                }
            }
        }
    }
    void sort_topologically()
    {
        vecExplored_.clear();
        vecTopologicalSortedIndex_.clear();
        for (T1 i = 0; i != n_; ++i)
        {
            vecExplored_.push_back(false);
            vecTopologicalSortedIndex_.push_back(n_); //dummy assignment
        }

        curLabel_ = n_;
        for (T1 i = 0; i != n_; ++i)
        {
            dfs_recursive(i);
        }

        /*
        std::stack<T1> stack;
        stack.push(0); // any of the graph nodes can be assigned
        T1 curLabel = n_;

        while (!stack.empty())
        {
            T1 elem = stack.top();
            stack.pop();
            
            if (vecExplored[elem])
            {
                continue;
            }
            vecExplored[elem] = true;
            assert((curLabel > 0) && "Error in topological sort process");
            vecTopologicalSortedIndex_[--curLabel] = elem;
            std::vector<T1> outEdgeNodes = graphOfIndex_.out_edge_nodes(elem);
            
            for (typename std::vector<T1>::iterator outIt = outEdgeNodes.begin(); outIt != outEdgeNodes.end(); ++outIt)
            {
                if (!vecExplored[*outIt])
                {
                    stack.push(*outIt);
                }
            }
        }
        */
    }
    void dfs_recursive(T1 elem)
    {
        if (vecExplored_[elem])
        {
            return;        
        }
        std::vector<T1> outEdgeNodes = graphOfIndex_.out_edge_nodes(elem);
        for (typename std::vector<T1>::iterator outIt = outEdgeNodes.begin(); outIt != outEdgeNodes.end(); ++outIt)
        {
            dfs_recursive(*outIt);
        }
        vecExplored_[elem] = true;
        assert((curLabel_ > 0) && "Error in topological sort process");
        vecTopologicalSortedIndex_[--curLabel_] = elem;
    }
private:
    T1 n_;
    std::vector<T2> seq_; //input sequence
    Graph<T1> graphOfIndex_;
    std::vector<T1> vecTopologicalSortedIndex_;
    std::vector<bool> vecExplored_;
    T1 curLabel_;
    std::vector<T1> vecSubSeqLength_;
};

template<typename T1, typename T2>
T1 LIS<T1,T2>::compute_longest_increasing_subsequence()
{
    build_graph();
    sort_topologically();
    
    // each index will have atleast its own element in the largest increasing subsequence till it
    for (T1 i = 0; i != n_; ++i)
    {
        vecSubSeqLength_.push_back(1);
    }

    // now apply dynamic programming
    T1 maxSubSeq = 0;
    for (typename std::vector<T1>::iterator it = vecTopologicalSortedIndex_.begin(); it != vecTopologicalSortedIndex_.end(); ++it)
    {
        T1 maxSubSeqInEdge = 0;
        std::vector<T1> inEdgeNodes = graphOfIndex_.in_edge_nodes(*it);
        for (typename std::vector<T1>::iterator inIt = inEdgeNodes.begin(); inIt != inEdgeNodes.end(); ++inIt)
        {
            maxSubSeqInEdge = std::max(vecSubSeqLength_[*inIt],maxSubSeqInEdge);
        }
        vecSubSeqLength_[*it] = maxSubSeqInEdge + 1;
        maxSubSeq = std::max(vecSubSeqLength_[*it],maxSubSeq);
    }

    return maxSubSeq;
}

int main(int argc, char* argv[])
{
    std::ifstream pFile;
    if (READ_FROM_FILE)
    {
        pFile.open("D:/cpp_practise/online_judge/spoj/11110_ELIS_easy_longest_increasing_subsequence_input.txt",std::ios::in);
        assert(pFile.is_open() && "input file not opened");
    }

    unsigned int nSeq;
    if (READ_FROM_FILE)
    {
        pFile >> nSeq;
    }
    else
    {
        std::cin >> nSeq;
    }

    LIS<unsigned int, int> lis(nSeq);
    lis.read_input_sequence(pFile);
    std::cout << lis.compute_longest_increasing_subsequence() << std::endl;

    if (READ_FROM_FILE)
    {
        pFile.close();
    }
    return 0;
}
/*
Dynamic Programming based implementation.
Time complexity: O(n^2)

O(n*log(n)) solution described here:
http://stackoverflow.com/questions/2631726/how-to-determine-the-longest-increasing-subsequence-using-dynamic-programming
http://codeforces.com/blog/entry/8761

Dynamic programming tutorial:
http://www.topcoder.com/tc?d1=tutorials&d2=dynProg&module=Static
*/