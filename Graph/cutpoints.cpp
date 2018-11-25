int n;
vector<vector<int>> adj;
vector<bool> used;
vector<int> tin, fup;
int timer;

vector<int> cutpoints; // Answers here

void dfs(int v, int p = -1) {
    used[v] = true;
    tin[v] = fup[v] = timer++;
    int children = 0;
    for (auto u: adj[v]) if (u != p) {
        if (used[u]) fup[v] = min(fup[v], tin[u]);
        else {
            dfs(u, v);
            fup[v] = min(fup[v], fup[u]);
            if (fup[v] >= tin[v] && p != -1) cutpoints.pb(v);
            children += 1;
        }
    }
    if (p == -1 && children > 1) cutpoints.pb(v);
}

void find_cutpoints() {
    timer = 0;
    used.assign(n, false);
    tin.assign(n, -1); fup.assign(n, -1);
    for (int i = 0; i < n; i++) if (!used[i]) dfs(i);
}
