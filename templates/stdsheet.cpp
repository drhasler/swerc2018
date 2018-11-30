#include <bits/stdc++.h>

#define xx first
#define yy second
#define pb push_back
#define mp make_pair
#define ll long long

using namespace std;

int main() {
    int n; cin >> n;
    double* a = new double[n];
    for (int i=0;i<n;i++) cin >> a[i];
    reverse(a,a+n);
    { // temporary variables
        double* it = unique(a,a+n);
        n = int (it-a);
    }
    double tot = accumulate(a,a+n,0.0);
    partial_sum(a,a+n,a);
    assert(a[n-1]==tot);
    double ans = tot/n;
    delete a;
    cout.precision(16);
    cout << ans << endl; // endl to flush
    vector<int> v(4,9);
    v.assign(3,8); // re-init
    v.pb(-1); // append
    assert(v.size()==4);
    for (int i=0;i<3;i++) v[i] = i*4;
    int x = 5;
    if (lower_bound(v.begin(),v.end(),x)
     != upper_bound(v.begin(),v.end(),x))
        printf("%d in vec\n",x);
    else printf("%d not in vec\n",x);
    map<int,char> m;
    string s; cin >> s;
    random_shuffle(s.begin(),s.end());
    for (char c:s) m[x++] = c;
    {
        char bigC = 0;
        auto rit = m.rbegin();
        while (rit!=m.rend()) {
            if (rit->yy>bigC) {
                int y; tie(y,bigC) = *(rit++);
                cout << x << bigC << endl;
                m.erase(rit.base());
            } else rit++;
        }
        for (auto x:m) cout << x.yy;
    }
}
