struct QuickFind {
    V<int> id;
    VV<int> groups;
    int gc;  // group count
    QuickFind(int n = 0) {
        id = V<int>(n);
        groups = VV<int>(n);
        for (int i = 0; i < n; i++) {
            id[i] = i;
            groups[i] = {i};
        }
        gc = n;
    }
    void merge(int a, int b) {
        if (same(a, b)) return;
        gc--;
        int x = id[a], y = id[b];
        if (groups[x].size() < groups[y].size()) swap(x, y);
        for (int j : groups[y]) {
            id[j] = x;
            groups[x].push_back(j);
        }
        groups[y].clear();
    }
    bool same(int a, int b) { return id[a] == id[b]; }
};
