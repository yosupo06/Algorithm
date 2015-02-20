/*
データ構造をマージする一般的なテクによるQuickFind
*/

template <int N>
struct UnionFind {
    int ig[N];
    vector<int> gi[N];
    int dc;
    void init(int n = N) {
        for (int i = 0; i < n; ++i) {
            ig[i] = i;
            gi[i] = {i};
        }
        dc = 0;
    }
 
    void merge(int a, int b) {
        if (same(a, b)) return;
        dc++;
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
