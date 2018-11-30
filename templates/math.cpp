#include <bits/stdc++.h>

using namespace std;

int gcd(int a,int b,int& x,int& y) {
    if (!a) {
        x = 0; y = 1;
        return b;
    }
    int x1,y1;
    int g = gcd(b%a,a,x1,y1);
    x = y1 - (b/a)*x1;
    y = x1;
    return g;
}

vector<int> pr;

#define pb push_back
vector<int> factors(int x) {
    vector<int> v;
    for (int p:pr) {
        while (x%p==0) {
            v.pb(p);
            x/=p;
        }
    }
    if (x > 1) v.pb(x);
    return v;
}

const int bigS = 1000;
bool sieve[bigS];
bool good(int x) { return 1; }

const int MOD=1e9+7;
#define ll long long
ll modpow(ll x,int p) {
    ll ans = 1;
    while (p) {
        if (p&1) ans = ans*x%MOD;
        x = x*x%MOD;
        p/=2;
    }
    return ans;
}

int main() {
    // GCD
    int a,b,x=1,y=1; cin >> a >> b;
    int g = gcd(a,b,x,y);
    assert(g==a*x+b*y);
    
    // primes
    int Nmax = 1000;
    for (int i=2;i<=sqrt(Nmax);i++) {
        for (int p:pr) if (i%p==0) goto nxtp;
        pr.pb(i);
nxtp:;
    }
    vector<int> f4 = factors(444);
    // sieve
    for (int s=2;s<bigS;s++) {
        if (!sieve[s] && good(s)) {
            // do something
            for (int ss=2*s;ss<bigS;ss+=s)
                sieve[ss] = 1;
        }
    }
    // MODs 1e5+3 1e7+19 1e9+7
    // mod inverse
    cin >> n;
    assert(n*modpow(n,MOD-2)%MOD==1);
}
