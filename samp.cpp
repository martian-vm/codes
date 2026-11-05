#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

bool isSafe(vector<int>& board, int row, int col) {
    for (int i = 0; i < row; i++) { //previous row checking
        if (board[i] == col ||  // same column checking  
            abs(board[i] - col) == abs(i - row))        //cl1-cl2 , r1-r2
            return false;
    }
    return true;
}

bool solve(int row, int n, vector<int>& board, int fixedRow) {
    if (row == n)
        return true;

    if (row == fixedRow)
        return solve(row + 1, n, board, fixedRow);

    for (int col = 0; col < n; col++)
     {
        if (isSafe(board, row, col)) 
            {
            board[row] = col;

            if (solve(row + 1, n, board, fixedRow))
                return true;

            board[row] = -1;
        }
    }
    return false;
}

int main() {
    int n, r, c;

    cout << "Enter size of chessboard: ";
    cin >> n;

    cout << "Enter first queen row and column: ";
    cin >> r >> c;

    if (n <= 0 || r < 1 || r > n || c < 1 || c > n) {
        cout << "Invalid input";
        return 0;
    }

    vector<int> board(n, -1);
    board[r - 1] = c - 1;

    if (solve(0, n, board, r - 1)) {
        cout << "\nN-Queens Matrix:\n";

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i] == j)  
                    cout << "Q ";
                else
                    cout << ". ";
            }
            cout << endl;
        }
    }
    else {
        cout << "No solution exists";
    }

    return 0;
}