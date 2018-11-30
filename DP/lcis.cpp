// Longest Common Increasing Sequence

vector<int> a, b;
int m = a.size(), n = b.size();
vector<int> dp(n, 0), par(n);
for (int i = 0; i < m; i++) {
    int cur = 0, last = -1;
    for (int j = 0; j < n ; j++) {
        if (a[i] == b[j]) if (cur+1 > dp[j]) {
            dp[j] = max(dp[j], cur+1);
            par[j] = last; // Backtracking
        }
        if (a[i] > b[j]) if (dp[j] > cur) {
            cur = max(cur, dp[j]);
            last = j; // Backtracking
        }
    }
}

// Printing
int best_length = 0, best_idx;    
for (int i = 0; i < n; i++) if (dp[i] > best_length) {
    best_length = dp[i];
    best_idx = i;
}

vector<int> lcis;
int idx = best_idx;
while (idx != -1) {
    lcis.pb(b[idx]);
    idx = par[idx];
}
