#include <bits/stdc++.h>
using namespace std;

#define V 9

int minKey(int key[], bool djSet[])
{
    int min = INT_MAX, min_index;
    for (int i = 0; i < V; i++)
    {
        if (!djSet[i] && key[i] < min)
        {
            min = key[i];
            min_index = i;
        }
    }
    return min_index;
}

void printDJ(int key[])
{
    cout << "Vertex \t Distance from Source" << endl;
    for (int i = 0; i < V; i++)
    {
        cout << i << " \t\t" << key[i] << endl;
    }
}

void djMST(int graph[V][V], int src)
{
    int key[V];
    bool djSet[V];

    for (int i = 0; i < V; i++)
    {
        key[i] = INT_MAX;
        djSet[i] = false;
    }

    key[src] = 0;

    for (int count = 0; count < V; count++)
    {
        int u = minKey(key, djSet);
        djSet[u] = true;

        for (int v = 0; v < V; v++)
        {
            if (!djSet[v] && graph[u][v] && key[u] + graph[u][v] < key[v])
            {
                key[v] = key[u] + graph[u][v];
            }
        }
    }

    printDJ(key);
}

int main()
{

    int graph[V][V] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
                       {4, 0, 8, 0, 0, 0, 0, 11, 0},
                       {0, 8, 0, 7, 0, 4, 0, 0, 2},
                       {0, 0, 7, 0, 9, 14, 0, 0, 0},
                       {0, 0, 0, 9, 0, 10, 0, 0, 0},
                       {0, 0, 4, 14, 10, 0, 2, 0, 0},
                       {0, 0, 0, 0, 0, 2, 0, 1, 6},
                       {8, 11, 0, 0, 0, 0, 1, 0, 7},
                       {0, 0, 2, 0, 0, 0, 6, 7, 0}};

    // Function call
    djMST(graph, 5);

    return 0;
}