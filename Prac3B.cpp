#include <lib/stdc++.h>

#define SIZE 6
#define INF 999

using namespace std;

class Graph
{
private:
    string cities[SIZE];
    int adjMat[SIZE][SIZE];

public:
    Graph()
    {
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                adjMat[i][j] = INF;
    }

    void inputGraph()
    {
        cout << "Enter city names:\n";
        for (int i = 0; i < SIZE; i++)
        {
            cout << "City-" << i + 1 << ": ";
            cin >> cities[i];
        }

        cout << "\nEnter cost (0 = no connection):\n";
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = i + 1; j < SIZE; j++)
            {
                int cost;
                cout << cities[i] << " -> " << cities[j] << ": ";
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
            cout << setw(12) << cities[i];
        cout << endl;

        for (int i = 0; i < SIZE; i++)
        {
            cout << setw(12) << cities[i];
            for (int j = 0; j < SIZE; j++)
                cout << setw(12) << adjMat[i][j];
            cout << endl;
        }
    }

    void primsMST(int start)
    {
        if (start >= SIZE)
            return;

        bool visited[SIZE] = {false};
        set<int> mstSet;

        int totalCost = 0;
        int edges = 0;

        mstSet.insert(start);
        visited[start] = true;

        cout << "\nEdges in MST:\n";

        while (edges < SIZE - 1)
        {
            int minCost = INF;
            int src = -1, dest = -1;

            for (int u : mstSet)
            {
                for (int v = 0; v < SIZE; v++)
                {
                    if (!visited[v] && adjMat[u][v] < minCost)
                    {
                        minCost = adjMat[u][v];
                        src = u;
                        dest = v;
                    }
                }
            }

            if (dest == -1) break;

            cout << cities[src] << " -> " << cities[dest]
                 << "  Cost: " << minCost << endl;

            totalCost += minCost;
            visited[dest] = true;
            mstSet.insert(dest);
            edges++;
        }

        cout << "\nMinimum Cost (MST): " << totalCost << endl;
    }
};

int main()
{
    Graph g;

    g.inputGraph();
    g.displayGraph();
    g.primsMST(0);

    return 0;
}

/*
Output:
┌──(vmsin0㉿martian)-[~/STUDY/Manual/AI]
└─$  ./a.out
Enter city names:
City-1: Miami
City-2: Seattle
City-3: Buffalo
City-4: Manhattan
City-5: NewYork
City-6: Washington

Enter cost (0 = no connection):
Miami -> Seattle: 12
Miami -> Buffalo: 8
Miami -> Manhattan: 0
Miami -> NewYork: 0
Miami -> Washington: 0
Seattle -> Buffalo: 9
Seattle -> Manhattan: 0
Seattle -> NewYork: 22
Seattle -> Washington: 11
Buffalo -> Manhattan: 0
Buffalo -> NewYork: 16
Buffalo -> Washington: 14
Manhattan -> NewYork: 15
Manhattan -> Washington: 3
NewYork -> Washington: 18

Adjacency Matrix:

                   Miami     Seattle     Buffalo   Manhattan     NewYork  Washington
       Miami         999          12           8         999         999         999
     Seattle          12         999           9         999          22          11
     Buffalo           8           9         999         999          16          14
   Manhattan         999         999         999         999          15           3
     NewYork         999          22          16          15         999          18
  Washington         999          11          14           3          18         999

Edges in MST:
Miami -> Buffalo  Cost: 8
Buffalo -> Seattle  Cost: 9
Seattle -> Washington  Cost: 11
Washington -> Manhattan  Cost: 3
Manhattan -> NewYork  Cost: 15

Minimum Cost (MST): 46

*/
