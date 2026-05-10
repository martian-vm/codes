#include <iostream>
#include <vector>
using namespace std;

void solve(int row, int n, vector<int>& board, vector<bool>& col, vector<bool>& diag1, 
           vector<bool>& diag2, vector<vector<int>>& solutions) {

    if (row == n) {
        solutions.push_back(board);
        return;
    }

    for (int c = 0; c < n; c++) {
        if (!col[c] && !diag1[row - c + n - 1] && !diag2[row + c]) {

            board[row] = c;
            col[c] = true;
            diag1[row - c + n - 1] = true;
            diag2[row + c] = true;

            solve(row + 1, n, board, col, diag1, diag2, solutions);

            board[row] = -1;
            col[c] = false;
            diag1[row - c + n - 1] = false;
            diag2[row + c] = false;
        }
    }
}

int main() {
    int n = 4;

    vector<int> board(n, -1);
    vector<vector<int>> solutions;

    vector<bool> col(n, false);
    vector<bool> diag1(2 * n - 1, false);
    vector<bool> diag2(2 * n - 1, false);

    solve(0, n, board, col, diag1, diag2, solutions);

    cout << "Solutions:\n";
    for (auto sol : solutions) {
        for (int i = 0; i < n; i++)
            cout << sol[i] << " ";
        cout << endl;
    }

    return 0;
}
