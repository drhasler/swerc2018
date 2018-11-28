// Usage: Vector a = {a[1],..., a[n]} with a[i] = 0
// Query 1: p, val => a[p] += val
// Query 2: p      => Output a[1]+...+a[p]

// Note: Vector must be 1-based, NOT 0-based

int n;
vector<int> fen;

void fenwick_init() { fen.assign(n, 0); }

void update(int p, int val) {
    for (int i = p; i <= n; i += i & -i) fen[i] += val;
}

int sum(int p) {
    int res = 0;
    for (int i = p; i > 0; i -= i & -i) res += fen[i];
    return ans;
}
