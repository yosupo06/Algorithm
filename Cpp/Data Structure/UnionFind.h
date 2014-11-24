template <int N>
struct UnionFind {
    int ig[N];
    vector<int> gi[N];
    void init() {
        for (int i = 0; i < N; ++i) {
            ig[i] = i;
            gi[i] = {i};
        }
    }
 
    void merge(int a, int b) {
        if (same(a, b)) return;
        int x = ig[a], y = ig[b];
        if (gi[x].size() < gi[y].size()) swap(x, y);
        for (int j: gi[y]) {
            ig[j] = x;
        }
        gi[x].insert(gi[x].end(), gi[y].begin(), gi[y].end());
        gi[y].clear();
    }
 
    bool same(int a, int b) {
        return ig[a] == ig[b];
    }
};
