int n;
vector<vector<int>> adj;
vector<bool> used;

vector<int> ans; // Answer here

void dfs(int v) {
    used[v] = true;
    for (auto u: adj[v]) if (!used[u]) dfs(u);
    ans.pb(v)
}

void toposort() {
    used.assign(n, false);
    for (int i = 0; i < n; i++) if (!used[i]) dfs(i);
    reverse(ans.begin(), ans.end());
}
