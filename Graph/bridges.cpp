int n;
vector<vector<int>> adj;
vector<bool> used;
vector<int> tin, fup;
int timer;

vector<pair<int, int>> bridges; // Answer here

void dfs(int v, int p = -1) {
    used[v] = true;
    tin[v] = fup[v] = timer++;
    for (int u: adj[v]) if (u != p) {
        if (used[u]) fup[v] = min(fup[v], tin[u]);
        else {
            dfs(u, v);
            fup[v] = min(fup[v], fup[u]);
            if (fup[v] > tin[v]) bridges.pb({v, u});
        }
    }
}

void find_bridges() {
    timer = 0;
    used.assign(n, false);
    tin.assign(n, -1); fup.assign(n, -1);
    for (int i = 0; i < n; i++) if (!used[i]) dfs(i);
}
