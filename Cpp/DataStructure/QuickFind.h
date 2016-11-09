struct UnionFind {
    vector<int> ig;
    vector<vector<int>> gi;
    int gn;
    UnionFind(int N) {
        ig.resize(N); gi.resize(N);
        for (int i = 0; i < N; i++) {
            ig[i] = i; gi[i] = {i};
        }
        gn = N;
    }
    void merge(int a, int b) {
        if (same(a, b)) return;
        gn--;
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
