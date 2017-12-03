// https://www.hackerearth.com/practice/algorithms/greedy/basics-of-greedy-algorithms/practice-problems/algorithm/problem-17-f8bc297f/description/
// Dec 02, 2017

#include<bits/stdc++.h>
using namespace std;

int Maximize (vector<int> work, int W, int N) {
   // Write your code here
   // sort the vector of fixed work for the workers
   sort(work.begin(), work.end());

   // iterate from largest to smallest
   // At each position we check how many workers can be alloted extra work so that all these workers would have the work equal to current position
   // We iterate till its possible to have number of with equal work greater than the max number of equal work till now
   int i = work.size() - 1; // Stores current position
   int n_max_equal_work = 0; // Maximum number of workers who can have equal work

   while (i >= n_max_equal_work)
   {
       int cur_work = work[i];
       int n_cur_equal_work = 1;

       // Move i to the first instance of cur_work
       // Also make n_cur_equal_work equal to the number of workers having already fixed work equal to cur_work
       while (i > 0)
       {
           if (work[i-1] == work[i])
           {
               ++n_cur_equal_work;
               --i;
           }
           else
           {
               break;
           }
       }

       // Now compute how many workers having work < cur_work can be assigned work to make them equal to cur_work
       if (i > 0)
       {
           int balance_work = W;
           int j = i-1;

           while (j >= 0)
           {
               int diff_work = work[i] - work[j];

               if (diff_work <= balance_work)
               {
                   ++n_cur_equal_work;
                   balance_work -= diff_work;
                   --j;
               }
               else
               {
                   break;
               }
           }
       }

       // Update max number of equal work if the number of equal work at current position is greater than max number of equal work.
       if (n_max_equal_work < n_cur_equal_work)
       {
           n_max_equal_work = n_cur_equal_work;
       }

       --i; // move to lower position
   }

   return n_max_equal_work;
}

int main() {

    // cout << numeric_limits<int>::max() << endl;

    ios::sync_with_stdio(0);
    cin.tie(0);
    int N;
    cin >> N;
    int W;
    cin >> W;

    vector<int> work(N);
    for(int i_work=0; i_work<N; i_work++)
    {
    	cin >> work[i_work];
    }

    int out_;
    out_ = Maximize(work, W, N);
    cout << out_;

    return 0;
}
