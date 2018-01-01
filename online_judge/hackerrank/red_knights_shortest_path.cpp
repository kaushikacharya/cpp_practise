// https://www.hackerrank.com/contests/world-codesprint-12/challenges/red-knights-shortest-path
// Jan 01, 2018

#include <bits/stdc++.h>

using namespace std;

//  Print the distance along with the sequence of moves.
void printShortestPath(int n, int i_start, int j_start, int i_end, int j_end) {
     /*
     // visited matrix (initialize with false)
     vector<vector<bool> > visited_matrix;
     visited_matrix.reserve(n);
     for (int i=0; i != n; ++i)
     {
         visited_matrix.push_back(vector<bool>(n, false));
     }
     */

     // matrix with (a) path length (initialize with negative value representing the position not yet visited)
     //        and (b) previous position from which optimal path jumped to current position
     vector<vector<pair<int,int> > > path_len_matrix;
     path_len_matrix.reserve(n);
     pair<int,int> init_pair_path_len_prev_pos = make_pair(-1,-1);
     for (int i=0; i != n; ++i)
     {
         path_len_matrix.push_back(vector<pair<int,int> >(n, init_pair_path_len_prev_pos));
     }

     // tuple: <prev pos, cur pos, path length>
     // pos is a scalar value representing the 2 dimensional position in matrix
     queue<tuple<int,int,int> > Q;
     int source_pos = i_start*n + j_start;
     Q.push(make_tuple(-1,source_pos,0));

     while (!Q.empty())
     {
         tuple<int,int,int> cur_elem = Q.front();
         int prev_pos = get<0>(cur_elem);
         int cur_pos = get<1>(cur_elem);
         // convert current pos to 2 dimension
         int i_pos = cur_pos/n;
         int j_pos = cur_pos%n;
         int path_len = get<2>(cur_elem);
         Q.pop();

         // check if the current position has already been visited
         if (path_len_matrix[i_pos][j_pos].first >= 0)
         {
             continue; // already visited. Hence shortest path length already assigned
         }

         // assign path length
         path_len_matrix[i_pos][j_pos] = make_pair(path_len,prev_pos);

         if ( (i_pos == i_end) && (j_pos == j_end) )
         {
             // reached target
              break;
         }

         // push the next positions according to the priority of the order
         int next_pos;
         int i_next_pos;
         int j_next_pos;

         // UL
         if ( (i_pos > 1) && (j_pos > 0) )
         {
             i_next_pos = i_pos-2;
             j_next_pos = j_pos-1;

             if (path_len_matrix[i_next_pos][j_next_pos].first < 0)
             {
                 next_pos = i_next_pos*n + j_next_pos;
                 Q.push(make_tuple(cur_pos, next_pos, path_len+1));
             }
         }

         // UR
         if ( (i_pos > 1) && (j_pos < (n-1)) )
         {
             i_next_pos = i_pos-2;
             j_next_pos = j_pos+1;

             if (path_len_matrix[i_next_pos][j_next_pos].first < 0)
             {
                 next_pos = i_next_pos*n + j_next_pos;
                 Q.push(make_tuple(cur_pos, next_pos, path_len+1));
             }
         }

         // R
         if (j_pos < (n-2))
         {
             i_next_pos = i_pos;
             j_next_pos = j_pos+2;

             if (path_len_matrix[i_next_pos][j_next_pos].first < 0)
             {
                 next_pos = i_next_pos*n + j_next_pos;
                 Q.push(make_tuple(cur_pos, next_pos, path_len+1));
             }
         }

         // LR
         if ( (i_pos < (n-2)) && (j_pos < (n-1)) )
         {
             i_next_pos = i_pos+2;
             j_next_pos = j_pos+1;

             if (path_len_matrix[i_next_pos][j_next_pos].first < 0)
             {
                 next_pos = i_next_pos*n + j_next_pos;
                 Q.push(make_tuple(cur_pos, next_pos, path_len+1));
             }
         }

         // LL
         if ( (i_pos < (n-2)) && (j_pos > 0) )
         {
             i_next_pos = i_pos+2;
             j_next_pos = j_pos-1;

             if (path_len_matrix[i_next_pos][j_next_pos].first < 0)
             {
                 next_pos = i_next_pos*n + j_next_pos;
                 Q.push(make_tuple(cur_pos, next_pos, path_len+1));
             }
         }

         // L
         if (j_pos > 1)
         {
             i_next_pos = i_pos;
             j_next_pos = j_pos-2;

             if (path_len_matrix[i_next_pos][j_next_pos].first < 0)
             {
                 next_pos = i_next_pos*n + j_next_pos;
                 Q.push(make_tuple(cur_pos, next_pos, path_len+1));
             }
         }
     }

     // First check if target position is reachable from source position
     if (path_len_matrix[i_end][j_end].first < 0)
     {
         cout << "Impossible" << endl;
         return;
     }

     // Path length
     cout << path_len_matrix[i_end][j_end].first << endl;
     // steps
     vector<string> vecPath(path_len_matrix[i_end][j_end].first);
     int cur_pos = i_end*n + j_end;
     int i = path_len_matrix[i_end][j_end].first - 1;
     while (i >= 0)
     {
         int i_cur_pos = cur_pos/n;
         int j_cur_pos = cur_pos%n;

         int prev_pos = path_len_matrix[i_cur_pos][j_cur_pos].second;
         int i_prev_pos = prev_pos/n;
         int j_prev_pos = prev_pos%n;

         if (i_cur_pos < i_prev_pos)
         {
             if (j_cur_pos < j_prev_pos)
             {
                 vecPath[i] = "UL";
             }
             else
             {
                 vecPath[i] = "UR";
             }
         }
         else if (i_cur_pos == i_prev_pos)
         {
             if (j_cur_pos < j_prev_pos)
             {
                 vecPath[i] = "L";
             }
             else
             {
                 vecPath[i] = "R";
             }
         }
         else
         {
             if (j_cur_pos < j_prev_pos)
             {
                 vecPath[i] = "LL";
             }
             else
             {
                 vecPath[i] = "LR";
             }
         }

         cur_pos = prev_pos;
         --i;
     }

     cout << vecPath[0];
     for (unsigned int i=1; i != vecPath.size(); ++i)
     {
         cout << " " << vecPath[i];
     }
     cout << endl;
}

int main() {
    // cout << 11/4 << endl;
    // cout << 11%4 << endl;
    int n;
    cin >> n;
    int i_start;
    int j_start;
    int i_end;
    int j_end;
    cin >> i_start >> j_start >> i_end >> j_end;
    printShortestPath(n, i_start, j_start, i_end, j_end);
    return 0;
}

// http://thispointer.com/c11-stdtuple-tutorial-examples/
/* Improvement:
   Could have saved the priority strings as we have to print that as part of output.
*/
