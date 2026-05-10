#include <bits/stdc++.h>

#define SIZE 8

using namespace std;

class Graph
{
private:
    string cities[SIZE] = {"A","B","C","D","E","F","G","H"};

    int adjMat[SIZE][SIZE] = {
        {0,1,0,1,0,0,0,0},
        {0,0,1,0,0,1,0,0},
        {0,0,0,0,1,0,1,1},
        {0,0,0,0,0,1,0,0},
        {0,1,0,0,0,1,0,0},
        {1,0,0,0,0,0,0,0},
        {0,0,0,0,1,0,0,1},
        {1,0,0,0,0,0,0,0}
    };

public:

    void displayGraph()
    {
        cout << "\nAdjacency Matrix:\n\n";
        cout << setw(6) << "";
        for (int i = 0; i < SIZE; i++)
            cout << setw(6) << cities[i];
        cout << endl;

        for (int i = 0; i < SIZE; i++)
        {
            cout << setw(6) << cities[i];
            for (int j = 0; j < SIZE; j++)
                cout << setw(6) << adjMat[i][j];
            cout << endl;
        }
    }

    void DFS(int start)
    {
        bool visited[SIZE] = {false};
        stack<int> st;

        st.push(start);

        cout << "\nDFS Traversal: ";

        while (!st.empty())
        {
            int node = st.top();
            st.pop();

            if (!visited[node])
            {
                cout << cities[node] << " ";
                visited[node] = true;

                for (int j = SIZE - 1; j >= 0; j--)
                {
                    if (adjMat[node][j] == 1 && !visited[j])
                        st.push(j);
                }
            }
        }
    }

    void BFS(int start)
    {
        bool visited[SIZE] = {false};
        queue<int> q;

        q.push(start);
        visited[start] = true;

        cout << "\nBFS Traversal: ";

        while (!q.empty())
        {
            int node = q.front();
            q.pop();

            cout << cities[node] << " ";

            for (int j = 0; j < SIZE; j++)
            {
                if (adjMat[node][j] == 1 && !visited[j])
                {
                    q.push(j);
                    visited[j] = true;
                }
            }
        }
    }
};

int main()
{
    Graph g;

    g.displayGraph();
    g.DFS(7);
    g.BFS(7);

    return 0;
}

/*
┌──(vmsin0㉿martian)-[~/STUDY/Manual/AI]
└─$  ./a.out     

Adjacency Matrix:

           A     B     C     D     E     F     G     H
     A     0     1     0     1     0     0     0     0
     B     0     0     1     0     0     1     0     0
     C     0     0     0     0     1     0     1     1
     D     0     0     0     0     0     1     0     0
     E     0     1     0     0     0     1     0     0
     F     1     0     0     0     0     0     0     0
     G     0     0     0     0     1     0     0     1
     H     1     0     0     0     0     0     0     0

DFS Traversal: H A B C E F G D 
BFS Traversal: H A B D C F E G     
*/
