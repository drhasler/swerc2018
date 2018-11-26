// <O(n), O(logn)>
int n;
vector<vector<int>> adj;
vector<bool> used;
vector<int> height, first, euler;

void dfs(int v, int h = 1) {
    used[v] = true;
    height[v] = h;
    first[v] = euler.size();
    euler.pb(v);
    for (auto u: adj[v]) if (!used[u]) {
        dfs(u, h+1);
        euler.pb(v);
    }
}

const int M = 1e5; // Euler size
int m;
int t[2*M];

void build() {
    for (int i = 0; i < m; i++) t[m+i] = euler[i];
    for (int i = m-1; i > 0; i--) t[i] = (height[t[2*i]] < height[t[2*i+1]] ? t[2*i] : t[2*i+1]);
}

int query(int l, int r) {
    int res = 2*M;
    for (l += m, r += m; l < r; l /= 2, r /= 2) {
        if (l&1) {
            res = (height[res] < height[t[l]] ? res : t[l]);
            l += 1;
        }
        if (r&1) {
            r -= 1;
            res = (height[res] < height[t[r]] ? res : t[r]);
        }
    }
    return res;
}

void lca_init(int root = 0) {
    used.assign(n, false);
    height.resize(n); first.resize(n); euler.reserve(2*n);
    dfs(root);
    m = euler.size();
    build();
}

int lca(int u, int v) {
    int l = first[u], r = first[v]; if (l > r) swap(l, r);
    return query(l, r);
}
