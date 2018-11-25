int n;
vector<vector<int>> adj;
vector<int> d;

void bfs(int root) {
    d.assign(n, INF); d[root] = 0;
    queue<int> q; q.push(root);
    while (!q.empty()) {
        int cur = q.front(); q.pop();
        for (auto nxt: adj[cur]) if (d[nxt] == INF) {
            d[nxt] = d[cur]+1;
            q.push(nxt);
        }
    }
}
