// http://www.geeksforgeeks.org/counting-inversions/
// Date: Dec 25, 2014

#include <iostream>
#include <vector>

using namespace std;

class Solution
{
    // recursive solution
    public:
        int countInv(vector<int>& vec, int p, int q)
        {
            // count inversions of vec[p,...,q]
            if (p == q)
            {
                return 0;
            }

            int mid = (p + q)/2;

            int val_left_inv = countInv(vec, p, mid);
            int val_right_inv = countInv(vec, mid+1, q);
            int val_cross_inv = mergeInv(vec, p, mid, q);

            return val_left_inv + val_right_inv + val_cross_inv;
        }
    private:
        int mergeInv(vector<int>& vec, int p, int mid, int q)
        {
            // count cross inverse of vec[p,...,mid] and vec[mid+1,...,q]
            int i = p;
            int j = mid+1;

            vector<int> sortedVec;
            sortedVec.reserve(q-p+1);

            int count_inversion = 0;
            while ((i <= mid) && (j <= q))
            {
                if (vec[j] < vec[i])
                {
                    sortedVec.push_back(vec[j]);
                    count_inversion += mid-i+1;
                    ++j;
                }
                else
                {
                    sortedVec.push_back(vec[i]);
                    ++i;
                }
            }

            while (i <= mid)
            {
                sortedVec.push_back(vec[i]);
                ++i;
            }
            while (j <= q)
            {
                sortedVec.push_back(vec[j]);
                ++j;
            }

            // now vec[p,...,q] should be replaced by sorted elements
            for (int i=p; i <= q; ++i)
            {
                vec[i] = sortedVec[i-p];
            }

            return count_inversion;
        }
};

int main(int argc, char* argv[])
{
    int arr[] = {2, 4, 1, 3, 5};
    vector<int> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));

    Solution sln;
    int count_inv = sln.countInv(vec, 0, vec.size()-1);
    cout << "inv count: " << count_inv << endl;

    cout << "sorted vec" << endl;
    for (vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin())
        {
            cout << ",";
        }
        cout << *it;
    }
}

/*
Boundary case that needs to be handled: empty vec
*/
