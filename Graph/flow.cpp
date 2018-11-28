int n;
vector<vector<int>> adj, capacity;

int source, sink;
vector<int> par;

int bfs() {
    par.assign(n, -1); par[source] = 2;
    queue<pair<int, int>> q; q.push({source, INF});
    while (!q.empty()) {
        int cur = q.front().first, flow = q.front().second; q.pop();
        for (auto nxt: adj[cur]) {
            if (par[nxt] == -1 && capacity[cur][nxt]) {
                par[nxt] = cur;
                int new_flow = min(flow, capacity[cur][nxt]);
                if (nxt == t) return new_flow;
                q.push({nxt, new_flow});
            }
        }
    }
    return 0;
}

int maxflow() {
    int flow = 0, new_flow;
    while (new_flow = bfs()) {
        flow += new_flow;
        int cur = sink;
        while (cur != source) {
            int prev = par[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }
    return flow;
}
