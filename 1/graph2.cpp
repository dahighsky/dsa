#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <omp.h>

using namespace std;

class Graph {
private:
    int numVertices;
    vector<vector<int>> adj;

public:
    Graph(int vertices) : numVertices(vertices), adj(vertices) {}

    void addEdge(int src, int dest) {
        adj[src].push_back(dest);
        adj[dest].push_back(src);
    }

    void viewGraph() {
        cout << "Graph:\n";
        for (int i = 0; i < numVertices; i++) {
            cout << "Vertex " << i << " -> ";
            for (int neighbor : adj[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    void bfs(int startVertex) {
        vector<bool> visited(numVertices, false);
        queue<int> q;
        visited[startVertex] = true;
        q.push(startVertex);

        while (!q.empty()) {
            int currentVertex = q.front();
            q.pop();
            cout << currentVertex << " ";

            #pragma omp parallel for
            for (int i = 0; i < adj[currentVertex].size(); i++) {
                int neighbor = adj[currentVertex][i];
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }

    void dfs(int startVertex) {
        vector<bool> visited(numVertices, false);
        stack<int> s;
        visited[startVertex] = true;
        s.push(startVertex);

        while (!s.empty()) {
            int currentVertex = s.top();
            s.pop();
            cout << currentVertex << " ";

            #pragma omp parallel for
            for (int i = 0; i < adj[currentVertex].size(); i++) {
                int neighbor = adj[currentVertex][i];
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    s.push(neighbor);
                }
            }
        }
    }
};

int main() {
    int numVertices;
    cin >> numVertices;

    Graph graph(numVertices);

    int numEdges;
    cin >> numEdges;

    for (int i = 0; i < numEdges; i++) {
        int src, dest;
        cin >> src >> dest;
        graph.addEdge(src, dest);
    }

    graph.viewGraph();

    int startVertex;
    cin >> startVertex;

    cout << "Breadth First Search (BFS): ";
    graph.bfs(startVertex);
    cout << endl;

    cout << "Depth First Search (DFS): ";
    graph.dfs(startVertex);
    cout << endl;

    return 0;
}
