#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> goal = {
    {1,2,3},
    {4,5,6},
    {7,8,0}
};

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

struct Node {
    vector<vector<int>> mat;
    int x, y;
    int g, h;
    Node* parent;

    int f() const {
        return g + h;
    }
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->f() > b->f();
    }
};

string serialize(vector<vector<int>>& mat) {
    string s;
    for (auto& row : mat)
        for (int x : row)
            s += to_string(x);
    return s;
}

int calculateH(vector<vector<int>>& mat) {
    int h = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (mat[i][j] != 0) {
                int val = mat[i][j] - 1;
                int goalX = val / 3;
                int goalY = val % 3;
                h += abs(i - goalX) + abs(j - goalY);
            }
        }
    }
    return h;
}

void printPath(Node* node) {
    if (!node) return;
    
    printPath(node->parent);

    for (auto& row : node->mat) {
        for (int x : row) cout << x << " ";
        cout << "\n";
    }
    cout << "--------\n";
}

void solve(vector<vector<int>> start, int x, int y) {

    priority_queue<Node*, vector<Node*>, Compare> pq;
    unordered_set<string> visited;

    Node* root = new Node{start, x, y, 0, calculateH(start), nullptr};
    pq.push(root);

    while (!pq.empty()) {
        Node* curr = pq.top();
        pq.pop();

        string key = serialize(curr->mat);
        if (visited.count(key)) continue;
        visited.insert(key);

        if (curr->h == 0) {
            cout << "Solution found!\n";
            printPath(curr);
            return;
        }

        for (int d = 0; d < 4; d++) {
            int nx = curr->x + dx[d];
            int ny = curr->y + dy[d];

            if (nx >= 0 && ny >= 0 && nx < 3 && ny < 3) {
                vector<vector<int>> newMat = curr->mat;
                swap(newMat[curr->x][curr->y], newMat[nx][ny]);

                string newKey = serialize(newMat);
                if (!visited.count(newKey)) {
                    Node* child = new Node{
                        newMat,
                        nx, ny,
                        curr->g + 1,
                        calculateH(newMat),
                        curr
                    };
                    pq.push(child);
                }
            }
        }
    }

    cout << "No solution exists\n";
}

int main() {
    vector<vector<int>> start = {
        {1,2,3},
        {4,0,5},
        {6,7,8}
    };

    int x = 1, y = 1;

    solve(start, x, y);

    return 0;
}


/*
┌──(vmsin0㉿martian)-[~/STUDY/Manual/AI]
└─$  g++ Prac2.cpp && ./a.out
Solution found!
1 2 3 
4 0 5 
6 7 8 
--------
1 2 3 
4 5 0 
6 7 8 
--------
1 2 3 
4 5 8 
6 7 0 
--------
1 2 3 
4 5 8 
6 0 7 
--------
1 2 3 
4 5 8 
0 6 7 
--------
1 2 3 
0 5 8 
4 6 7 
--------
1 2 3 
5 0 8 
4 6 7 
--------
1 2 3 
5 6 8 
4 0 7 
--------
1 2 3 
5 6 8 
4 7 0 
--------
1 2 3 
5 6 0 
4 7 8 
--------
1 2 3 
5 0 6 
4 7 8 
--------
1 2 3 
0 5 6 
4 7 8 
--------
1 2 3 
4 5 6 
0 7 8 
--------
1 2 3 
4 5 6 
7 0 8 
--------
1 2 3 
4 5 6 
7 8 0 
--------

*/
