// https://www.hackerrank.com/challenges/organizing-containers-of-balls/problem
// July 08, 2018

#include <bits/stdc++.h>

using namespace std;

// Complete the organizingContainers function below.
string organizingContainers(vector<vector<int>> container) {
    int n = container.size();

    // each element represents corresponding containers capacity
    vector<int> container_capacity_vec(n);

    // each element represents corresponding ball types total count
    vector<int> ball_total_vec(n);

    // populate container capacities
    for (int i=0; i<n; ++i)
    {
        int container_capacity = 0;
        for (int j=0; j<n; ++j)
        {
            container_capacity += container[i][j];
        }
        container_capacity_vec[i] = container_capacity;
    }

    // populate ball types total count
    for (int j=0; j<n; ++j)
    {
        int ball_total_count = 0;
        for (int i=0; i<n; ++i)
        {
            ball_total_count += container[i][j];
        }
        ball_total_vec[j] = ball_total_count;
    }

    // Moving all balls of a particular type to one container would be possible if container capacity equals ball total count of corresponding type
    sort(container_capacity_vec.begin(), container_capacity_vec.end());
    sort(ball_total_vec.begin(), ball_total_vec.end());

    string organizing_possibility = "Possible";
    for (int i=0; i<n; ++i)
    {
        if (container_capacity_vec[i] != ball_total_vec[i])
        {
            organizing_possibility = "Impossible";
            break;
        }
    }

    return organizing_possibility;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        vector<vector<int>> container(n);
        for (int i = 0; i < n; i++) {
            container[i].resize(n);

            for (int j = 0; j < n; j++) {
                cin >> container[i][j];
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        string result = organizingContainers(container);

        fout << result << "\n";
        // cout << result << "\n";
    }

    fout.close();

    return 0;
}

/**
Run time complexity: O(n^2)
Initially was thinking of backtracking but based on the hint in discussion section realized that it need not be that complicated.
*/
