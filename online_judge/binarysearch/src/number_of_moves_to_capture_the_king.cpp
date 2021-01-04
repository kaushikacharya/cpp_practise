/**
* Problem: Number of Moves to Capture the King
* URL: https://binarysearch.com/problems/Number-of-Moves-to-Capture-the-King
* Date: Jan 03, 2021
* Approach: BFS traversal
*       Start from king's position and traverse till either a knight is found or all paths are explored.
*/

#include <number_of_moves_to_capture_the_king.hpp>

int solve(vector<vector<int>>& board) {
    unsigned int n = board.size();
    vector<vector<bool>> visitMatrix(n, vector<bool>(n, false));

    queue<tuple<int, int, unsigned int>> Q; // row index, col index, moves(to reach king)

    for (int i=0; i<n; ++i){
        for (int j=0; j<n; ++j){
            if (board[i][j] == 2){
                visitMatrix[i][j] = true;
                Q.push(make_tuple(i, j, 0));
                break;
            }
        }
    }

    int n_moves = -1; // value if no solution found
    while (!Q.empty()){
        tuple<int, int, unsigned int> elem = Q.front();
        Q.pop();

        int i = get<0>(elem);
        int j = get<1>(elem);
        unsigned int n_moves_pos = get<2>(elem);

        if (board[i][j] == 1){
            // knight found
            n_moves = n_moves_pos;
            // empty queue
            while (!Q.empty()){
                Q.pop();
            }
        }
        else {
            if (i > 1){
                // Positions: two rows back
                if ((j > 0) && (!visitMatrix[i-2][j-1])) {
                    Q.push(make_tuple(i-2, j-1, n_moves_pos+1));
                    visitMatrix[i-2][j-1] = true;
                }
                if ((j < (n-1)) && (!visitMatrix[i-2][j+1])) {
                    Q.push(make_tuple(i-2, j+1, n_moves_pos+1));
                    visitMatrix[i-2][j+1] = true;
                }
            }
            if (i < (n-2)){
                // Positions: two rows forward
                if ((j > 0) && (!visitMatrix[i+2][j-1])) {
                    Q.push(make_tuple(i+2, j-1, n_moves_pos+1));
                    visitMatrix[i+2][j-1] = true;
                }
                if ((j < (n-1)) && (!visitMatrix[i+2][j+1])) {
                    Q.push(make_tuple(i+2, j+1, n_moves_pos+1));
                    visitMatrix[i+2][j+1] = true;
                }
            }

            if (j > 1){
                // Positions: two columns back
                if ((i > 0) && (!visitMatrix[i-1][j-2])){
                    Q.push(make_tuple(i-1, j-2, n_moves_pos+1));
                    visitMatrix[i-1][j-2] = true;
                }
                if ((i < (n-1)) && (!visitMatrix[i+1][j-2])){
                    Q.push(make_tuple(i+1, j-2, n_moves_pos+1));
                    visitMatrix[i+1][j-2] = true;
                }
            }
            if (j < (n-2)){
                // Positions: two columns forward
                if ((i > 0) && (!visitMatrix[i-1][j+2])){
                    Q.push(make_tuple(i-1, j+2, n_moves_pos+1));
                    visitMatrix[i-1][j+2] = true;
                }
                if ((i < (n-1)) && (!visitMatrix[i+1][j+2])){
                    Q.push(make_tuple(i+1, j+2, n_moves_pos+1));
                    visitMatrix[i+1][j+2] = true;
                }
            }
        }
    }

    return n_moves;
}

