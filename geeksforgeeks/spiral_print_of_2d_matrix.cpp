// http://www.geeksforgeeks.org/print-a-given-matrix-in-spiral-form/
// Date: Jan 23, 2015

#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class Solution
{
public:
    void spiral_print(vector<vector<T> >& vec)
    {
        if (vec.empty())
        {
            return;
        }

        int m = vec.size(); // row
        int n = vec[0].size(); // col
        int iter = 0;

        int i = 0; // index for row
        int j = 0; // index for col

        // printing 1st element
        cout << vec[i][j];

        while (iter <= (min(m,n)-1)/2)
        {
            // increasing col index
            bool flag_moved_forward = false;
            while (++j <= (n-1-iter))
            {
                flag_moved_forward = true;
                cout << " " << vec[i][j];
            }
            --j;

            // increasing row index
            bool flag_moved_downward = false;
            while (++i <= (m-1-iter))
            {
                flag_moved_downward = true;
                cout << " " << vec[i][j];
            }
            --i;

            if (flag_moved_forward && flag_moved_downward)
            {
                // decreasing col index
                while (--j >= iter)
                {
                    cout << " " << vec[i][j];
                }
                ++j;

                // decreasing row index
                while (--i > iter)
                {
                    cout << " " << vec[i][j];
                }
                ++i;
            }

            ++iter;
        }
    }
};

int main(int argc, char* argv[])
{
    int m = 3;
    int arr[3][1] = {
                      {1},
                      {5},
                      {9}
                      };
    vector<vector<int> > matrix;
    matrix.reserve(m);
    for (int row_i = 0; row_i != m; ++row_i)
    {
        vector<int> vec(arr[row_i], arr[row_i]+sizeof(arr[row_i])/sizeof(arr[row_i][0]));
        matrix.push_back(vec);
    }

    //cout << matrix[1][1] << endl;

    Solution<int> sln;
    sln.spiral_print(matrix);

    return 0;
}

/*
http://www.tutorialspoint.com/cplusplus/cpp_multi_dimensional_arrays.htm
*/
