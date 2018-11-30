// Longest Increasing Subsequence

// O(n^2)
int n;
vector<int> a, dp(n, 1);
for (int i = 0; i < n; i++) for (int j = 0; j < i; j++) if (a[j] < a[i]) dp[i] = max(dp[i], dp[j]+1);
// Answer is dp[n]

// O(nlogn)
vector<int> d, dp;
for (int i = 0; i < n; i++) {
    auto it = lower_bound(dp.begin(), dp.end(), a[i]); // upper_bound for non-decreasing subsequence
    if (it == dp.end()) dp.pb(a[i]);
    else *it = a[i];
}
// dp vector is the answer, exactly the LIS, dp.size() is the lis
