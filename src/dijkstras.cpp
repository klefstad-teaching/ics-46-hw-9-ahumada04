#include "dijkstras.h"
vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int numVertices = G.size();
    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);

    distances[source] = 0;
    previous.assign(numVertices, UNDEFINED);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> minHeap;
    minHeap.push({0, source});

    while (!minHeap.empty()) {
        int u = minHeap.top().second;
        minHeap.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (const Edge& edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;

            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({distances[v], v});
            }
        }
    }

    return distances;
}


vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    if (distances[destination] == INF) {
        return path;
    }

    for (int at = destination; at != UNDEFINED; at = previous[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total) {
    for (int node : v) {
        cout << node << " ";
    }
    cout << endl;
    cout << "Total cost is " << total << endl;;
}