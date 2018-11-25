int n;
vector<vector<int>> g, gr;
vector<bool> used;
vector<int> order, component;
vector<vector<int>> components; // Answer here: All connected componnents

void dfs1(int v) {
    used[v] = true;
    for (auto u: g[v]) if (!used[u]) dfs1(u);
    order.pb(v);
}

void dfs2(int v) {
    used[v] = true;
    component.pb(v);
    for (auto u: adj[v]) if (!used[u]) dfs2(u);
}

void scc() {
    used.assign(n, false);
    for (int i = 0; i < n; i++) if (!used[i]) dfs1(i);
    used.assign(n, false);
    for (int i = 0; i < n; i++) {
        int v = order[n-1-i];
        if (!used[v]) {
            dfs2(v);
            components.pb(component);
            component.clear();
        }
    }
}
