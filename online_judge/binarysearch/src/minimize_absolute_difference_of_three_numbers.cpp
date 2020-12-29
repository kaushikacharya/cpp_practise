/**
* Problem: Minimize Absolute Difference of Three Numbers
* URL: https://binarysearch.com/problems/Minimize-Absolute-Difference-of-Three-Numbers
* Date: Dec 29, 2020
*
* Time Complexity: O(n*log n) where n is length of biggest vector.
* Space Complexity: O(n)
*
* Approach:
* First sort the vectors.
* Compute minimum absolute difference of each element of vector b with elements of vector a and c.
*   Keep pointer for the elements in vector a and c which were closest to an element of vector b.
*   Use this pointer while computing minimum absolute difference for the next element of vector b.
*/

#include <minimize_absolute_difference_of_three_numbers.hpp>

using namespace std;

int solve(vector<int>& a, vector<int>& b, vector<int>& c) {
    // First sort the input vector
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    sort(c.begin(), c.end());

    int min_abs_diff = INT_MAX;

    // index of vectors a, c which are closest to the current element of vector b
    unsigned int a_i = 0;
    unsigned int c_i = 0;

    for (vector<int>::iterator it = b.begin(); it != b.end(); ++it){
        int cur_abs_diff_a = compute_min_abs_diff(*it, a, a_i);
        int cur_abs_diff_c = compute_min_abs_diff(*it, c, c_i);
        int cur_abs_diff = cur_abs_diff_a + cur_abs_diff_c;

        min_abs_diff = min(min_abs_diff,cur_abs_diff);
    }

    return min_abs_diff;
}

int compute_min_abs_diff(int elem, vector<int>& vec, unsigned int& i){
    // Compute min absolute difference of elem with elements of sorted vector vec.
    // elem represents an element from a sorted vector whose previous element(if exists) was closest to vec[i]
    // Also we update index i to which elem is closest to.
    int cur_abs_diff = 0;

    if ((elem <= vec[i]) || (i == (vec.size()-1))){
        // case a:
        //      case i: i=0 i.e. 0'th element of vec
        //      case ii: previous elem of sorted vector to which elem belongs to was found to be closest to vec[i].
        //               Hence as current elem <= vec[i], it is closest to vec[i]
        // case b: No further element available in vec.
        cur_abs_diff += abs(elem - vec[i]);
    } else {
        // Check if elem is closest to any vec[j] where j > i.
        //  If yes, then update i to j.
        unsigned int j = i + 1;
        while ((j < vec.size()) && (elem >= vec[j])){
            i = j;
            j += 1;
        }

        if (i == (vec.size()-1)){
            cur_abs_diff += abs(elem - vec[i]);
        } else {
            assert((i < (vec.size()-1)) && "i should be < than (vec.size()-1)");
            // Identify which element of vector vec is the current element elem closest to: i or i+1?
            int abs_diff_1 = abs(elem - vec[i]);
            int abs_diff_2 = abs(elem - vec[i+1]);

            if (abs_diff_1 < abs_diff_2){
                cur_abs_diff += abs_diff_1;
            } else {
                // update i to the element index to which current elem of vector b is closest to
                i += 1;
                cur_abs_diff += abs_diff_2;
            }
        }
    }

    return cur_abs_diff;
}
