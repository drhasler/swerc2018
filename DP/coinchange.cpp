// Coin change
// Money = M, n values of coins

vector<int> coin;
int dp[M+1][n];
for (int m = 1; m <= M; m++) for (int i = 0; i < n; i++) {
    if (m == 0) dp[m][i] = 1;
    else dp[m][i] = (coin[i] <= m ? dp[m-coin[i]][i] : 0) + (i >= 1 ? dp[m][i-1] : 0);
}
// Answer is dp[M][n-1];
