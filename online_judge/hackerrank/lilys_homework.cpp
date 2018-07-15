// https://www.hackerrank.com/challenges/lilys-homework/problem
// July 14, 2018

#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the lilysHomework function below.
int lilysHomework(vector<int> arr) {
    // It can be inferred that beautiful array will have the elements in sorted order either ascending or descending.
    // Only then the sum of absolute difference of neighboring elements will be minimal.
    // We would need to check for both ascending as well as descending order
    if (arr.size() < 2)
    {
        // There's no question of swap for single element array.
        return 0;
    }
    bool verbose = false;
    int n = arr.size();
    int n_swap_ascending_order;
    int n_swap_descending_order;

    for (int sort_i=0; sort_i < 2; ++sort_i)
    {
        vector<int> a_arr(arr); // Creating a copy of input array in which swaps will be done
        vector<int> b_arr(arr); // This would be sorted in next step
        bool flag_ascending_order = (sort_i == 0)?true:false;

        if (flag_ascending_order)
        {
            // ascending
            sort(b_arr.begin(), b_arr.end());
        }
        else
        {
            // descending
            sort(b_arr.rbegin(), b_arr.rend());
        }

        // We are using the fact that elements of the array are distinct
        unordered_map<int,int> cur_position_map;
        for (int i=0; i<n; ++i)
        {
            cur_position_map[arr[i]] = i;
        }

        // This would store the position of each element in the sorted array
        unordered_map<int,int> final_position_map;
        for (int i=0; i<n; ++i)
        {
            final_position_map[b_arr[i]] = i;
        }

        int n_swap = 0;
        // Iterate over each of the position.
        // If the element that should be there in final position isn't there then swap the element that should be there in final position with the current one at i'th position.
        // After i'th iteration, a_arr[0,...,i] elements should match with sorted array b_arr[0,...,i]
        for (int i=0; i<n; ++i)
        {
            if (a_arr[i] == b_arr[i])
            {
                continue;
            }
            // We should swap so that b_arr[i] should be placed in i'th position
            int j = cur_position_map[b_arr[i]];
            assert((a_arr[j] == b_arr[i]) && "a_arr[j] != b_arr[i]");
            // swap the elements
            swap(a_arr[i], a_arr[j]);
            ++n_swap;
            // update current position of these two elements
            cur_position_map[a_arr[i]] = i;
            cur_position_map[a_arr[j]] = j;
        }

        if (flag_ascending_order)
        {
            n_swap_ascending_order = n_swap;
            if (verbose)
            {
                cout << "swaps(in ascending order): " << n_swap << endl;
            }
        }
        else
        {
            n_swap_descending_order = n_swap;
            if (verbose)
            {
                cout << "swaps(in descending order): " << n_swap << endl;
            }
        }
    }

    return min(n_swap_ascending_order, n_swap_descending_order);
}

int lilysHomeworkOld(vector<int> arr) {

    // It can be inferred that beautiful array will have the elements in sorted order either ascending or descending.
    // Only then the sum of absolute difference of neighboring elements will be minimal.
    if (arr.size() < 2)
    {
        // There's no question of swap for single element array.
        return 0;
    }

    // Identify the elements into following 3 classes:
    // a) the elements which are in the position where its supposed to be in sorted order
    // b) Among the others there are two types:
    // i)  arr[i], arr[j] if swapped then both would be placed in their appropriate position in sorted order of array.
    //     i.e. arr[i]'s final position is j and arr[j]'s final position is i. They can be swapped without the help of any other elements.
    //     Hence number of swaps needed for this type would be number of such pairs.
    // ii) arr[i], arr[j] would need other element(s) to placed in their appropriate positions in sorted order of array.

    // We need to try both the sorted order: ascending, descending
    // e.g. [3,5,2,1]: descending order can be achieved in less number of swaps than ascending order

    bool verbose = true;
    int n = arr.size();
    vector<int> n_swap_vec;
    n_swap_vec.reserve(2);
    for (int sort_i=0; sort_i < 2; ++sort_i)
    {
        vector<int> b_arr(arr);
        if (sort_i == 0)
        {
            sort(b_arr.begin(), b_arr.end());
        }
        else
        {
            sort(b_arr.rbegin(), b_arr.rend());
        }

        if (false)
        {
            cout << "original array: ";
            for (vector<int>::iterator it=arr.begin(); it!=(arr.end()-1); ++it)
            {
                cout << *it << ",";
            }
            cout << arr.back() << endl;

            cout << "sorted array: ";
            for (vector<int>::iterator it=b_arr.begin(); it!=(b_arr.end()-1); ++it)
            {
                cout << *it << ",";
            }
            cout << b_arr.back() << endl;
        }

        // We are using the fact that elements of the array are distinct
        unordered_map<int,int> orig_position_map;
        for (int i=0; i<n; ++i)
        {
            orig_position_map[arr[i]] = i;
        }

        // This would store the position of each element in the sorted array
        unordered_map<int,int> final_position_map;
        for (int i=0; i<n; ++i)
        {
            final_position_map[b_arr[i]] = i;
        }

        // Count of elements in different types mentioned above in comments
        int n_type_1 = 0;
        int n_type_2 = 0;
        int n_type_3 = 0;

        for (int i=0; i<n; ++i)
        {
            if (arr[i] == b_arr[i])
            {
                ++n_type_1;
            }
            else
            {
                int j = final_position_map[arr[i]];

                if (final_position_map[arr[j]] == i)
                {
                    ++n_type_2;
                }
                else
                {
                    ++n_type_3;
                }
            }
        }

        assert(((n_type_1+n_type_2+n_type_3)==n) && "type assignment missed for some element(s)");
        assert((n_type_2%2 == 0) && "Type 2 count should be even");

        int n_swap = n_type_2/2;
        if (n_type_3 > 0)
        {
            n_swap += (n_type_3-1);
        }
        n_swap_vec.push_back(n_swap);
        if (verbose)
        {
            cout << "n_swap: " << n_swap << " :: n_type_1: " << n_type_1 << " : n_type_2: " << n_type_2 << " : n_type_3: " << n_type_3 << endl;
        }
    }

    return min(n_swap_vec.front(), n_swap_vec.back());
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split_string(arr_temp_temp);

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    int result = lilysHomework(arr);

    fout << result << "\n";
    // cout << result << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}

/**
Time complexity: O(n*log n) since sort is involved.
                 Swapping takes O(n)
*/
