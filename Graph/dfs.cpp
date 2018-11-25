int n;
vector<vector<int>> adj;
vector<bool> used;

// Simple version

void dfs(int v) {
    used[v] = true;
    for (auto u: adj[v]) if (!used[u]) dfs(u);
}

// Advanced version
// 3 states: Black/White/Grey instead of 2 states True/False

void dfs(int v) {
    color[v] = gray;
    for (auto u: adj[v]) if (color[u] == white) dfs(u);
    color[v] = black;
}
