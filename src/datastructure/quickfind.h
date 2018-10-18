struct QuickFind {
    V<int> ig;
    VV<int> gi;
    int gc;  // group count
    QuickFind(int n = 0) {
        ig = V<int>(n);
        gi = VV<int>(n);
        for (int i = 0; i < n; i++) {
            ig[i] = i; gi[i] = {i};
        }
        gc = n;
    }
    void merge(int a, int b) {
        if (same(a, b)) return;
        gc--;
        int x = ig[a], y = ig[b];
        if (gi[x].size() < gi[y].size()) swap(x, y);
        for (int j: gi[y]) {
            ig[j] = x;
        }
        gi[x].insert(gi[x].end(), gi[y].begin(), gi[y].end());
        gi[y].clear();
    }
    bool same(int a, int b) { return ig[a] == ig[b]; }
};
