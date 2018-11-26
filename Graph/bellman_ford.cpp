struct Edge {
    int u, v, cost;
};

int n;
vector<Edge> edges;
vector<int> d, p;

void bellman_ford(int root) {
    d.assign(n, INF); d[root] = 0;
    p.assign(n, -1);
    for (int i = 1; i <= n; i++) {
        bool change = false;
        for (auto e: edges) {
            int u = e.u, v = e.v, cost = e.cost;
            if (d[u] < INF && d[v] > d[u]+cost) {
                d[v] = d[u]+cost;
                p[v] = u;
                change = true;
            }
        }
        if (!change && i < n-1) break; // Not really needed
        if (i == n-1 && change) {
            // Negative cycle accessible from root
        }
    }
}

void restore_path(int src, int dst) {
    bellman_ford(src);
    if (d[dst] == INF) return vector<int>(); // No path
    vector<int> path;
    for (int v = dst; v != -1; v = p[v]) path.pb(v);
    reverse(path.begin(), path.end());
    return path;
}
