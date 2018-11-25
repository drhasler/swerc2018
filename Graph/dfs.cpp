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

// DFS Tree

vector<int> par;

void dfs(int v) {
    used[v] = true;
    for (auto u: adj[v]) if (!used[u]) {
        dfs(u);
        par[u] = v;
    }
}

// Starting time, finishing time: v is an ancestor of u <=> st[v] <= st[u] <= ft[u] <= ft[v];

int timer = 0;
vector<int> st, ft;

void dfs(int v) {
    st[v] = timer++;
    used[v] = true;
    for (auto u: adj[v]) if (!used[u]) dfs(u);
    ft[v] = timer;
}
