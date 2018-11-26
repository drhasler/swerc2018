int n;
vector<vector<int>> w; // w[i][j] = 0 if i = j, w[i][j] = wij if there is an edge from i->j with weight wij, w[i][j] = INF if there are no edges

void floyd_warshall() {
    for (int k = 0; k < n; k++) for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if (d[i][k] < INF && d[k][j] < INF) {
        d[i][j] = min(d[i][j], d[i][k]+d[k][j]);
    }
    for (int i = 0; i < n; i++) if (d[i][i] < 0) { // Found negative cycle}
}
