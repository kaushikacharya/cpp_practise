// https://www.hackerrank.com/contests/world-codesprint-12/challenges/animal-transport
// Jan 05, 2018

#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct PathNode{
    T n_delivered;
    multiset<T> destinations;
    short group_index;
};

template<typename T>
struct Animal{
    Animal(char t, T s, T d)
    : type(t), source(s), destination(d){}
    char type;
    T source;
    T destination;
};

// Order the animals first in terms of source and then in terms of destination
template<typename T>
bool cmp(const Animal<T>& a1, const Animal<T>& a2)
{
    if (a1.source < a2.source)
    {
        return true;
    }
    else if (a1.source == a2.source)
    {
        return a1.destination < a2.destination;
    }
    else
    {
        return false;
    }
}

// Return a list of length n consisting of the answers
template<typename T>
vector <T> minimumZooNumbers(T m, T n, vector <char> vecAnimalType, vector <T> vecSource, vector <T> vecDestination) {
    // Note: source, destination are 1-indexed
    vector<T> vecOutput(n,-1);
    // cout << "initialized: " << vecOutput[0] << " : " << vecOutput[n-1] << endl;

    vector<Animal<T> > vecAnimal;
    for (T i=0; i != n; ++i)
    {
        vecAnimal.push_back(Animal<T>(vecAnimalType[i], vecSource[i], vecDestination[i]));
    }

    sort(vecAnimal.begin(), vecAnimal.end(), cmp<T>);

    /*
    // For debugging purpose
    cout << "Post sorting of animals:" << endl;
    for (T i=0; i != n; ++i)
    {
        cout << vecAnimal[i].type << " : " << vecAnimal[i].source << " -> " << vecAnimal[i].destination << endl;
    }
    */


    // destinations multiset in PathNode represents the various ways that can be taken by truck to deliver the animals
    // T nDelivered = 0; // represents max number of animals delivered till now on a path where truck is currently empty
    vector<PathNode<T> > vecPath; // 1st - CE,  2nd - DM
    // The two vecPath is required because there would be two category of paths: one that currently contains group CE animals and the other contains DM
    // Truck moves from 1st to last zoo in order
    // Every position where a new animal is waiting to be picked up, we update the paths
    T i = 0;
    while (i < n)
    {
        vector<T> grp1DestinationVec; // C,E
        vector<T> grp2DestinationVec; // D,M

        // collect the animals which can be picked up from current zoo
        T curZoo = vecAnimal[i].source;
        while ( (i < n) && (vecAnimal[i].source == curZoo) )
        {
            // consider only the animals whose destination zoo is greater than source zoo
            // This check is required as there are some test cases which violate this.
            if (curZoo < vecAnimal[i].destination)
            {
                if ( (vecAnimal[i].type == 'C') || (vecAnimal[i].type == 'E') )
                {
                    grp1DestinationVec.push_back(vecAnimal[i].destination);
                }
                else
                {
                    grp2DestinationVec.push_back(vecAnimal[i].destination);
                }
            }
            ++i;
        }

        if (vecPath.empty())
        {
            vecPath.push_back(PathNode<T>());
            vecPath.push_back(PathNode<T>());

            vecPath[0].n_delivered = 0;
            vecPath[1].n_delivered = 0;
        }

        vector<T> grpCountToDeliver(2,0);
        for (unsigned short group_index=0; group_index != 2; ++ group_index)
        {
            for (auto it = vecPath[group_index].destinations.begin(); it != vecPath[group_index].destinations.end(); ++it)
            {
                T output_index = vecPath[group_index].n_delivered + grpCountToDeliver[group_index];
                if (*it <= curZoo)
                {
                    if (vecOutput[output_index] < 0)
                    {
                        vecOutput[output_index] = *it;
                    }
                    else if (*it < vecOutput[output_index])
                    {
                        vecOutput[output_index] = *it;
                    }
                    ++grpCountToDeliver[group_index];
                }
                else
                {
                    break;
                }
            }
        }

        // We take the max of n_delivered of both the PathNode. This represents the optimal path till delivery of n_delivered animals.
        // Optimal path would have carried sometimes CE group of animals and sometime DM group of animals
        T countToDeliver = max(grpCountToDeliver[0], grpCountToDeliver[1]);

        for (unsigned group_index=0; group_index != 2; ++group_index)
        {
            // min(countToDeliver, vecPath[group_index].destinations.size())
            if (countToDeliver < vecPath[group_index].destinations.size())
            {
                vecPath[group_index].destinations.erase(vecPath[group_index].destinations.begin(),
                                                    next(vecPath[group_index].destinations.begin(),countToDeliver));
            }
            else
            {
                // remove the entire destination multiset
                vecPath[group_index].destinations.clear();
            }

            vecPath[group_index].n_delivered += countToDeliver;
        }

        vecPath[0].destinations.insert(grp1DestinationVec.begin(), grp1DestinationVec.end());
        vecPath[1].destinations.insert(grp2DestinationVec.begin(), grp2DestinationVec.end());
    }

    // No more animals to be loaded
    for (unsigned group_index=0; group_index != 2; ++ group_index)
    {
        for (auto it = vecPath[group_index].destinations.begin(); it != vecPath[group_index].destinations.end(); ++it)
        {
            T output_index = vecPath[group_index].n_delivered + distance(vecPath[group_index].destinations.begin(),it);

            if (vecOutput[output_index] < 0)
            {
                vecOutput[output_index] = *it;
            }
            else if (*it < vecOutput[output_index])
            {
                vecOutput[output_index] = *it;
            }
        }
    }

    return vecOutput;
}

int main() {
    int cases;
    cin >> cases;
    for(int a0 = 0; a0 < cases; a0++){
        int m;
        int n;
        cin >> m >> n;
        vector<char> t(n);
        for(int t_i = 0; t_i < n; t_i++){
           cin >> t[t_i];
        }
        vector<int> s(n);
        for(int s_i = 0; s_i < n; s_i++){
           cin >> s[s_i];
        }
        vector<int> d(n);
        for(int d_i = 0; d_i < n; d_i++){
           cin >> d[d_i];
        }
        vector <int> result = minimumZooNumbers(m, n, t, s, d);
        for (ssize_t i = 0; i < result.size(); i++) {
            cout << result[i] << (i != result.size() - 1 ? " " : "");
        }
        cout << endl;


    }
    return 0;
}

/**
https://stackoverflow.com/questions/1033089/can-i-increment-an-iterator-by-just-adding-a-number
*/
