// Scheduling Problem
// Job: Start-End, Profit. Find max profit without overlapping job

struct Job {
    int s, e, p;

    bool operator< (Job &other) { return e < other.e; }
};

vector<Job> jobs;

int find_job(int idx) {
    int l = 0, h = idx-1;
    while (l <= h) {
        int m = (l+h)/2;
        if (jobs[m].e <= jobs[idx].s) {
            if (jobs[m+1].e <= jobs[idx].s) l = m+1;
            else return m;
        }
        else h = m-1;
    }
    return -1;
}

sort(jobs.begin(), jobs.end());
vector<int> dp(n); dp[0] = jobs[0].p;
for (int i = 1; i < n; i++) {
    int p = jobs[i].p;
    int it = find_job(i);
    if (it != -1) p += dp[it];
    dp[i] = max(dp[i-1], p);
}
// Answer is dp[n-1];
