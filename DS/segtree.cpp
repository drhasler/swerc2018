// Single Modification, Range Query

const int N = 1e5;
int n;
int t[2*N];

void build() { for (int i = n-1; i > 0; i--) t[i] = t[2*i] + t[2*i+1]; }

void modify(int p, int val) { for (t[p += n] = val; p > 1; p /= 2) t[p/2] = t[p] + t[p^1]; }

int query(int l, int r) {
    int res = 0;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
        if (l&1) res += t[l++];
        if (r&1) res += t[--r];
    }
    return res;
}

// Range Modification, Single Query: Almost lazy-like

void modify(int l, int r, int val) {
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
        if (l&1) t[l++] += val;
        if (r&1) t[--r] += val;
    }
}

int query(int p) {
    int res = 0;
    for (p += n; p > 0; p /= 2) res += t[p];
    return res;
}

void push() {
    for (int i = 1; i < n; i++) {
        t[2*i] += t[i];
        t[2*i+1] += t[i];
        t[i] = 0;
    }
}

// Advanced with Custom Struc: + not commutative: a+b != b+a

// Function combine(a, b) = a+b define here

void modify(int p, Custom val) { for (t[p += n] = val; p /= 1; ) t[p] = combine(t[2*p], t[2*p+1]); }

Custom query(int l, int r) {
    Custom resl, resr;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
        if (l&1) resl = combine(resl, t[l++]);
        if (r&1) resr = combine(t[--r], resr);
    }
    return combine(resl, resr);
}

// No lazy propagation yet
// Range Modification + Range Query = Dead
