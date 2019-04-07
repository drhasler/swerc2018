using namespace std;

// finds occurences of S in T
vector<int> RK(string const& s, string const& t) {
    const int p = 31; 
    const int m = 1e9 + 9;
    int S = s.size(), T = t.size();

    vector<long long> p_pow(max(S, T)); 
    p_pow[0] = 1; 
    for (int i = 1; i < (int)p_pow.size(); i++) 
        p_pow[i] = (p_pow[i-1] * p) % m;

    vector<long long> h(T + 1, 0); 
    for (int i = 0; i < T; i++)
        h[i+1] = (h[i] + (t[i] - 'a' + 1) * p_pow[i]) % m; 
    long long h_s = 0; 
    for (int i = 0; i < S; i++) 
        h_s = (h_s + (s[i] - 'a' + 1) * p_pow[i]) % m; 

    vector<int> occurences;
    for (int i = 0; i + S - 1 < T; i++) { 
        long long cur_h = (h[i+S] + m - h[i]) % m; 
        if (cur_h == h_s * p_pow[i] % m)
            occurences.push_back(i);
    }
    return occurences;
}

// longest prefix in suffixes of s[0..i]
int* prefix(const string& s) {
    int n = s.size();
    int* P = new int[n];
    P[0] = 0;
    for (int i=1;i<n;i++) {
        int j=P[i-1];
        while (j>0 && s[i]!=s[j]) j = P[j-1];
        if (s[i]==s[j]) j++;
        P[i] = j;
    }
    return P;
}


// longest prefix of s starting at i
int* Zfun(const string& s) {
    int n = s.size();
    int* Z = new int[n];
    for (int i=1,l=0,r=0;i<n;i++) {
        if (i<=r) Z[i] = min(r-i+1,Z[i-l]);
        while (i+Z[i]<n && s[i+Z[i]]==s[Z[i]]) Z[i]++;
        if (i+Z[i]-1 > r)
        { l=i; r=i+Z[i]-1; }
    }
    return Z;
}


// p[i] = starting position of ith string after sort
int* suffix_arr(const string& s) { // ending with small char: $
    int n = s.size();
    const int cmax = 256;
    int* cnt = new int[max(n,cmax)];
    int* c = new int[n];
    int* p = new int[n];
    for (int i=0;i<n;i++) cnt[s[i]]++; // classes sizes
    partial_sum(cnt,cnt+cmax,cnt);
    for (int i=0;i<n;i++) p[--cnt[s[i]]] = i; // partial ordering
    int bigc = 0;
    c[p[0]] = bigc;
    for (int i=1;i<n;i++) {
        if (s[p[i]] != s[p[i-1]]) bigc++; // need new class
        c[p[i]] = bigc; // class of word starting at i
    }
    int* cn = new int[n]; // new class distribution
    int* pn = new int[n]; // previous idx of ith term in partial
    for (int len=1;n>len;len*=2) { // concat
        for (int i=0;i<n;i++) {
            pn[i] = p[i] - len;
            if (pn[i]<0) pn[i] += n;
        }
        fill(cnt,cnt+bigc+1,0);
        for (int i=0;i<n;i++) cnt[c[pn[i]]]++; // classes sizes
        partial_sum(cnt,cnt+bigc+1,cnt);
        // iterate backwards to keep ordering
        for (int i=n-1;i>=0;i--) p[--cnt[c[pn[i]]]] = pn[i]; // partial ordering
        bigc = 0;
        cn[p[0]] = bigc;
        for (int i=1;i<n;i++) {
            if (c[p[i]]!=c[p[i-1]] || c[(p[i]+len)%n]!=c[(p[i-1]+len)%n])
                bigc++; // new class
            cn[p[i]] = bigc;
        }
        swap(c,cn);
    }
    return p;
}

// application: longest prefix starting at i
int* LCP(const string& s,int* p) {
    int n = s.size();
    int* rk = new int[n];
    int* lcp = new int[n];
    for (int i=0;i<n;i++) rk[p[i]] = i;
    int k = 0;
    for (int i=0;i<n;i++) {
        if (rk[i]==n-1) { lcp[rk[i]]=k=0; continue; }
        int j = p[rk[i]+1];
        while (i+k<n && j+k<n && s[i+k]==s[j+k]) k++;
        lcp[rk[i]] = k;
        if (k) k--;
    }
    return lcp;
}

// Ukkonens suffix tree, credits to freopen
const int N=1e6,INF=1e9;
string a; // max size of a is N/2 - 2
int t[N][26],l[N],r[N],p[N],s[N],tv,tp,ts,la;

void ukkadd (int c) {
    suff:;
    if (r[tv]<tp) {
        if (t[tv][c]==-1) { t[tv][c]=ts;  l[ts]=la;
            p[ts++]=tv;  tv=s[tv];  tp=r[tv]+1;  goto suff; }
        tv=t[tv][c]; tp=l[tv];
    }
    if (tp==-1 || c==a[tp]-'a') tp++; else {
        l[ts+1]=la; p[ts+1]=ts;
        l[ts]=l[tv]; r[ts]=tp-1; p[ts]=p[tv]; t[ts][c]=ts+1; t[ts][a[tp]-'a']=tv;
        l[tv]=tp; p[tv]=ts; t[p[ts]][a[l[ts]]-'a']=ts; ts+=2;
        tv=s[p[ts-2]]; tp=l[ts-2];
        while (tp<=r[ts-2]) { tv=t[tv][a[tp]-'a']; tp+=r[tv]-l[tv]+1;}
        if (tp==r[ts-2]+1) s[ts-2]=tv;  else s[ts-2]=ts; 
        tp=r[tv]-(tp-r[ts-2])+2;  goto suff;
    }
}

void build() {
    ts=2; tv=0; tp=0;
    fill(r,r+N,(int)a.size()-1);
    s[0]=1;
    l[0]=-1; r[0]=-1;
    l[1]=-1; r[1]=-1;
    memset (t, -1, sizeof t);
    fill(t[1],t[1]+26,0);
    for (la=0; la<(int)a.size(); ++la) ukkadd (a[la]-'a');
}


// suffix automaton

const int abc = 26;
const int N = 100005;
int SAcnt,last;

struct SAnode {
    int len,link;
    int nxt[abc]; // or map
    // add flag cloned to avoid multiple counts
    // add invlink vector to store the tree
} SA[2*N];

void sa_init() {
    SA[0].len = 0;
    SA[0].link = -1;
    SAcnt = 1;
    last = 0;
}

void sa_extend(char c) {
    c -= 'a';
    int cur = SAcnt++; 
    SA[cur].len = SA[last].len + 1;
    fill(SA[cur].nxt,SA[cur].nxt+abc,0);
    int p = last;
    // finding first collision with par class
    while (p != -1 && !SA[p].nxt[c]) {
        SA[p].nxt[c] = cur;
        p = SA[p].link;
    }
    if (p == -1) {
        SA[cur].link = 0;
    } else {
        int q = SA[p].nxt[c];
        if (SA[p].len + 1 == SA[q].len) { // 
            SA[cur].link = q;
        } else {
            int clone = SAcnt++;
            SA[clone].len = SA[p].len + 1;
            copy(SA[q].nxt,SA[q].nxt+abc,SA[clone].nxt);
            SA[clone].link = SA[q].link;
            while (p != -1 && SA[p].nxt[c]==q) {
                SA[p].nxt[c] = clone;
                p = SA[p].link;
            }
            SA[q].link = SA[cur].link = clone;
        }
    }
    last = cur;
}

string lcs (const string& s,const string& t) {
    sa_init();
    for (char c:s) sa_extend(c);
    int v=0,l=0,bigl=0,bigi=0;
    for (int i=0;i<t.size();i++) {
        char c = t[i]-'a';
        while (v && !SA[v].nxt[c]) {
            v = SA[v].link;
            l = SA[v].len;
        }
        if (SA[v].nxt[c]) {
            v = SA[v].nxt[c];
            l++;
        }
        if (l > bigl) {
            bigl = l;
            bigi = i;
        }
    }
    return t.substr(bigi-bigl+1,bigl);
}

