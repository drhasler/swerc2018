int n;
vector<vector<pair<int, int>>> adj; // adj[i] is the vector of edges: edge = (to, len)
// Alternatively: vector<vector<int>> adj, w; // adj for adj vertices, w[i][j] = wij
vector<int> d;

// On average: O(m), worst case = O(nm)
void spfa(int root) { 
    d.assign(n, INF); d[root] = 0;
    queue<int> q; q.push(root);
    vector<bool> inqueue(n, false); inqueue[root] = true;
    while (!q.empty()) {
        int cur = q.front(); q.pop(); inqueue[cur] = false;
        for (auto p: adj[cur]) {
            int nxt = p.first, len = p.second;
            if (d[nxt] > d[cur]+len) {
                d[nxt] = d[cur]+len;
                if (!inqueue[nxt]) {
                    q.push(nxt);
                    inqueue[nxt] = true;
                }
            }
        }
    }
}
