#include <bits/stdc++.h>

using namespace std;

const int N = 1<<18; // 2.6e5
const int K = 18;
int T[2*N];
int dp[1<<K],cost[K];

int quer(int l,int r) { // inclusive l, exclusive r
    l += N;
    r += N;
    int res = 0;
    while (l<r) {
        if (l&1) res += T[l++];
        if (r&1) res += T[--r];
        l/=2; r/=2;
    }
    return res;
}

#define xx first
#define yy second
#define pb push_back
#define pii pair<int,int>
vector<pii> Q,I;
int main() {
    int n; cin >> n >> m;
    vector<int> idx;
    for (int i=0;i<n;i++) {
        int l,r; cin >> l >> r;
        r++;
        idx.pb(l);
        idx.pb(r);
        Q.pb({l,r});
    }
    for (int i=0;i<n;i++) {
        int x,v; cin >> x >> v;
        idx.pb(x);
        I.pb({x,v});
    }
    sort(idx.begin(),idx.end());
    idx.erase(unique(idx.begin(),idx.end()),idx.end());
    map<int,int> midx;
    int cidx = 0;
    for (int x:idx) midx[x] = cidx++;
    for (pii a:I) T[midx[a.xx]] = a.yy;
    for (int i=N-1;i>0;i--) T[i] = T[2*i]+T[2*i+1];

    // bitset dp
    for (int k=0;k<K;k++) {
        for (int s=0;s<(1<<k);s++) {
            if (dp[s|(1<<k)] < dp[s]+cost[k])
                dp[s|(1<<k)] = dp[s]+cost[k];
        }
    }
    __builtin_clz(n); // number of leading 0 bits
    __builtin_ctz(n); // number of trailing 0 bits
    __builtin_popcount(n); // number of 1 bits
}
