#include <iostream>
#include <vector>
using namespace std;

bool isSafe(vector<int>& board, int row, int col, int n) {
    for (int i = 0; i < row; i++) {
        if (board[i] == col) return false;
        if (abs(board[i] - col) == abs(i - row)) return false;
    }
    return true;
}

void solve(int row, int n, vector<int>& board, vector<vector<int>>& solutions) {
    if (row == n) {
        solutions.push_back(board);
        return;
    }

    for (int col = 0; col < n; col++) {
        if (isSafe(board, row, col, n)) {
            board[row] = col;
            solve(row + 1, n, board, solutions);
            board[row] = -1;
        }
    }
}

int main() {
    int n = 4;
    vector<int> board(n, -1);
    vector<vector<int>> solutions;

    solve(0, n, board, solutions);

    cout << "Solutions:\n";
    for (auto sol : solutions) {
        for (int i = 0; i < n; i++)
            cout << sol[i] << " ";
        cout << endl;
    }

    return 0;
}
