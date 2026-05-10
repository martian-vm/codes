#include <bits/stdc++.h>

#define SIZE 6
#define INF 999

using namespace std;

class Graph {
private:
    int adjMat[SIZE][SIZE];
    string nodes[SIZE];

public:
    Graph() {
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                adjMat[i][j] = INF;
    }

    void inputGraph() {
        cout << "Enter node names:\n";
        for (int i = 0; i < SIZE; i++) {
            cout << "Node-" << i + 1 << ": ";
            cin >> nodes[i];
        }

        cout << "\nEnter cost (0 = no connection):\n";
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (i == j) {
                    adjMat[i][j] = 0;
                    continue;
                }
                if (i < j) {
                    int cost;
                    cout << nodes[i] << " -> " << nodes[j] << ": ";
                    cin >> cost;
                    if (cost == 0)
                        adjMat[i][j] = adjMat[j][i] = INF;
                    else
                        adjMat[i][j] = adjMat[j][i] = cost;
                }
            }
        }
    }

    void displayGraph() {
        cout << "\nAdjacency Matrix:\n\n";
        cout << setw(12) << "";
        for (int i = 0; i < SIZE; i++)
            cout << setw(12) << nodes[i];
        cout << endl;

        for (int i = 0; i < SIZE; i++) {
            cout << setw(12) << nodes[i];
            for (int j = 0; j < SIZE; j++)
                cout << setw(12) << adjMat[i][j];
            cout << endl;
        }
    }

    void dijkstra(int src) {
        int dist[SIZE];     // Shortest distance from source
        bool visited[SIZE]; // Visited nodes
        int prev[SIZE];     // Previous node in the path

        for (int i = 0; i < SIZE; i++) {
            dist[i] = INF;
            visited[i] = false;
            prev[i] = -1;
        }

        dist[src] = 0;

        for (int count = 0; count < SIZE; count++) {
            // Find unvisited node with minimum distance
            int u = -1;
            int minDist = INF;
            for (int i = 0; i < SIZE; i++) {
                if (!visited[i] && dist[i] < minDist) {
                    minDist = dist[i];
                    u = i;
                }
            }

            if (u == -1) break; // All reachable nodes processed

            visited[u] = true;

            // Update distances of neighbors
            for (int v = 0; v < SIZE; v++) {
                if (!visited[v] && adjMat[u][v] != INF) {
                    int newDist = dist[u] + adjMat[u][v];
                    if (newDist < dist[v]) {
                        dist[v] = newDist;
                        prev[v] = u;
                    }
                }
            }
        }

        // Display shortest paths
        cout << "\nShortest distances from " << nodes[src] << ":\n";
        for (int i = 0; i < SIZE; i++) {
            cout << nodes[src] << " -> " << nodes[i] << " = ";
            if (dist[i] == INF)
                cout << "INF";
            else
                cout << dist[i];
            cout << "    Path: ";

            // Print path
            if (dist[i] != INF) {
                vector<int> path;
                for (int at = i; at != -1; at = prev[at])
                    path.insert(path.begin(), at);

                for (size_t j = 0; j < path.size(); j++) {
                    cout << nodes[path[j]];
                    if (j != path.size() - 1) cout << " -> ";
                }
            }
            cout << endl;
        }
    }
};

int main() {
    Graph g;
    g.inputGraph();
    g.displayGraph();

    int src;
    cout << "\nEnter source node index (0 to " << SIZE-1 << "): ";
    cin >> src;

    g.dijkstra(src);

    return 0;
}

/*
┌──(vmsin0㉿martian)-[~/STUDY/Manual/AI]
└─$  g++ Prac3A.cpp && ./a.out
Enter node names:
Node-1: A
Node-2: B
Node-3: C
Node-4: D
Node-5: E
Node-6: F

Enter cost (0 = no connection):
A -> B: 4
A -> C: 4
A -> D: 0
A -> E: 0
A -> F: 0
B -> C: 2
B -> D: 0
B -> E: 0
B -> F: 0
C -> D: 3
C -> E: 2
C -> F: 4
D -> E: 0
D -> F: 3
E -> F: 3

Adjacency Matrix:

                       A           B           C           D           E           F
           A           0           4           4         999         999         999
           B           4           0           2         999         999         999
           C           4           2           0           3           2           4
           D         999         999           3           0         999           3
           E         999         999           2         999           0           3
           F         999         999           4           3           3           0

Enter source node index (0 to 5): 0

Shortest distances from A:
A -> A = 0    Path: A
A -> B = 4    Path: A -> B
A -> C = 4    Path: A -> C
A -> D = 7    Path: A -> C -> D
A -> E = 6    Path: A -> C -> E
A -> F = 8    Path: A -> C -> F

*/
