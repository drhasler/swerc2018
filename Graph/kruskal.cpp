struct Edge {
    int u, v, w;
    bool operator< (Edge const &other) { return w < other.w; }
};

int n;
vector<Edge> edges;

int total_weight = 0;
vector<Edge> tree; // Answer here

void kruskal() {
    dsu_init();
    sort(edges.begin(), edges.end());
    for (auto e: edges) {
        if (root(e.u) != root(e.v)) {
            total_weight += e.w;
            tree.pb(e);
            merge(e.u, e.v);
        }
    }
}
