#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

const int MAX_ROUTERS = 100;

vector<pair<int, int>> graph[MAX_ROUTERS]; 

void dijkstra(int source, int numRouters) {
    vector<int> distance(numRouters, INT_MAX);
    vector<bool> visited(numRouters, false);

    distance[source] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;

        visited[u] = true;

        for (auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (!visited[v] && distance[u] != INT_MAX &&
                distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                pq.push({distance[v], v});
            }
        }
    }

    for (int i = 0; i < numRouters; ++i) {
        cout << "Shortest distance from router " << source << " to router " << i << " is: " << distance[i] << endl;
    }
}

int main() {
    int numRouters, numEdges;
    cout << "Enter the number of routers and edges: ";
    cin >> numRouters >> numEdges;

    cout << "Enter the edges (neighbor, weight) for each router:" << endl;
    for (int i = 0; i < numEdges; ++i) {
        int router, neighbor, weight;
        cin >> router >> neighbor >> weight;
        graph[router].push_back({neighbor, weight});
    }

    int sourceRouter;
    cout << "Enter the source router: ";
    cin >> sourceRouter;

    dijkstra(sourceRouter, numRouters);

    return 0;
}

