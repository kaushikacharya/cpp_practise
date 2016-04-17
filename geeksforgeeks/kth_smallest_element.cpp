// http://www.geeksforgeeks.org/kth-smallestlargest-element-unsorted-array/
// Date: Dec 25, 2014'

#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

template<typename T>
class Solution
{
public:
    // k is 1-indexed
    T kth_smallest_element(vector<T>& vec, int k)
    {
        if (vec.size() == 1)
        {
            return vec[0];
        }

        srand(time(NULL));
        return kth_element(vec, 0, vec.size()-1, k-1);
    }
private:
    // here k is 0-indexed
    // Note: k is in absolute term, not relative to p
    T kth_element(vector<T>& vec, int p, int q, int k)
    {
        // find k th element in vec[p,...,q]
        if (p == q)
        {
            return vec[p];
        }

        int rand_index = rand() % (q-p+1) + p;
        // swapping pivot element with vec[p] so that 1st element of vec[p,...,q] is considered as pivot in partition function
        swap(vec[p], vec[rand_index]);
        // Note: pos_pivot is in absolute term i.e. index wrt [0,---,vec.size()-1]
        int pos_pivot = partition(vec, p, q);

        if (k == pos_pivot)
        {
            return vec[k];
        }
        else if (k < pos_pivot)
        {
            return kth_element(vec, p, pos_pivot-1, k);
        }
        else
        {
            return kth_element(vec, pos_pivot+1, q, k);
        }
    }

    int partition(vector<T>& vec, int p, int q)
    {
        // partition the vector: vec[p,...,q] wrt pivot
        // vec[p] is the pivot element
        // output: pivot's position
        int i = p;
        int j = p+1;

        while (j <= q)
        {
            if (vec[j] < vec[p])
            {
                ++i;
                swap(vec[i], vec[j]);
            }
            ++j;
        }

        // placing the pivot in its approproate position
        swap(vec[p], vec[i]);

        return i;
    }
};

int main(int argc, char* argv[])
{
    int arr[] = {7, 10, 4, 3, 20, 15};
    vector<int> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));
    int k = 6;

    Solution<int> sln;
    int kth_elem = sln.kth_smallest_element(vec, k);

    cout << "kth elem: " << kth_elem << endl;

    cout << "elements: ";
    for (vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin())
        {
            cout << ",";
        }
        cout << *it;
    }

    return 0;
}

/*
method: partition algorithm of quicksort
time complexity: avg O(n)
                worst O(n^2)

Roughgarden's week 3 lecture in part 1 (Randomized selection)
              week 2 lectire in part 1 (partition around a pivot)
*/
