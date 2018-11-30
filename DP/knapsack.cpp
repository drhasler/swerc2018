// 0-1 Knapsack
// n items, each has value and weight, find max value such sum of weight <= capacity C

int n;
vector<int> val, w;
int dp[n+1][C+1]; // Answer = dp[n][C]

for (int i = 0; i <= n; i++) for (int c = 0; c <= C; c++) {
    if (i == 0 || c == 0) dp[i][c] = 0;
    else if (w[i-1] <= c) dp[i][c] = max(val[i-1]+dp[i-1][c-w[i-1]], dp[i-1][c]); 
    else dp[i][c] = dp[i-1][c];
}

// Printing Knapsack
int res = dp[n][C], c = C;
vector<int> idx; // Index of the items
for (int i = n; i > 0 && res > 0; i--) {
    if (res == dp[i-1][c]) continue;
    idx.pb(i-1);
    res -= val[i-1];
    c -= w[i-1];
}
