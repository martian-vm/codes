#include <bits/stdc++.h>

#define SIZE 6
#define INF 999

using namespace std;

struct Edge {
    int u, v, weight;
};

class Graph
{
	private:
		string nodes[SIZE];
		int adjMat[SIZE][SIZE];

		int parent[SIZE];

		int find(int i)
		{
		    if (parent[i] == i) return i;
		    return parent[i] = find(parent[i]);
		}

		void unionSet(int u, int v)
		{
		    int rootU = find(u);
		    int rootV = find(v);
		    parent[rootV] = rootU;
		}

	public:
		Graph()
		{
		    for (int i = 0; i < SIZE; i++) {
		        for (int j = 0; j < SIZE; j++)
		            adjMat[i][j] = INF;
		        parent[i] = i;
		    }
		}

		void inputGraph()
		{
		    cout << "Enter node names:\n";
		    for (int i = 0; i < SIZE; i++) {
		        cout << "Node-" << i + 1 << ": ";
		        cin >> nodes[i];
		    }

		    cout << "\nEnter cost (0 = no connection):\n";
		    for (int i = 0; i < SIZE; i++) {
		        for (int j = i + 1; j < SIZE; j++) {
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

		void displayGraph()
		{
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

		void kruskalsMST()
		{
		    vector<Edge> edges;

		    for (int i = 0; i < SIZE; i++) {
		        for (int j = i + 1; j < SIZE; j++) {
		            if (adjMat[i][j] != INF)
		                edges.push_back({i, j, adjMat[i][j]});
		        }
		    }

		    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
		        return a.weight < b.weight;
		    });

		    int totalCost = 0;
		    int edgeCount = 0;

		    cout << "\nEdges in MST (Kruskal):\n";

		    for (auto &e : edges) {
		        int u = find(e.u);
		        int v = find(e.v);

		        if (u != v) {
		            cout << nodes[e.u] << " -> " << nodes[e.v] << "  Cost: " << e.weight << endl;

		            totalCost += e.weight;
		            unionSet(u, v);
		            edgeCount++;

		            if (edgeCount == SIZE - 1)
		                break;
		        }
		    }

		    cout << "\nMinimum Cost (MST): " << totalCost << endl;
		}
};

int main()
{
    Graph g;

    g.inputGraph();
    g.displayGraph();
    g.kruskalsMST();

    return 0;
}


/*
┌──(vmsin0㉿martian)-[~/STUDY/Manual/AI]
└─$  g++ Prac3C.cpp && ./a.out
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
           A         999           4           4         999         999         999
           B           4         999           2         999         999         999
           C           4           2         999           3           2           4
           D         999         999           3         999         999           3
           E         999         999           2         999         999           3
           F         999         999           4           3           3         999

Edges in MST (Kruskal):
B -> C  Cost: 2
C -> E  Cost: 2
C -> D  Cost: 3
D -> F  Cost: 3
A -> B  Cost: 4

Minimum Cost (MST): 14

*/
