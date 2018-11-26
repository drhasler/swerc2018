int n
vector<vector<pair<int, int>>> adj; // adj[i] is the vector of edges: edge = (to, len)
vector<int> d, p; // d for distance, p for parent - Backtrack

// set implementation: O(mlogm)
void dijkstra(int root) {
    d.assign(n, INF); d[root] = 0;
    p.assign(n, -1);

    set<pair<int, int>> q; q.insert({d[root], root});
    while (!q.empty()) {
        int cur = q.begin().second; q.erase(q.begin());
        for (auto edge: adj[cur]) {
            int nxt = edge.first, len = edge.second;
            if (d[nxt] > d[cur]+len) {
                q.erase({d[to], to});
                d[nxt] = d[cur]+len;
                p[nxt] = cur;
                q.insert({d[nxt], nxt});
            }
        }
    }
}

// priority_queue implementation: A little bit faster than set due to constant: O(mlogn)
void dijkstra(int root) {
    d.assign(n, INF); d[root] = 0;
    p.assign(n, -1);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q; q.push({d[root], root});
    while (!q.empty()) {
        int cur = q.top().second, d_v = q.top().first; q.pop();
        if (d_v != d[v]) continue; // Ignore old outdated pair due to duplicates (with set we can erase so no duplicate)
        // Alternatively, could use an used vector to check: if (!used[v]) continue; used[v] = true;
        for (auto edge: adj[cur]) {
            int nxt = edge.first, len = edge.second;
            if (d[nxt] > d[cur]+len) {
                d[nxt] = d[cur]+len;
                p[nxt] = cur;
                q.push({d[nxt], nxt});
            }
        }
    }
}

vector<int> restore_path(int src, int dst) {
    dijkstra(src);
    if (d[dst] == INF) return vector<int>(); // No path
    vector<int> path;
    for (int v = dst; v != -1; v = p[v]) path.pb(v);
    reverse(path.begin(), path.end());
    return path;
}
