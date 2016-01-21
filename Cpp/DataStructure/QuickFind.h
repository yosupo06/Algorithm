/**
 * QuickFind
 *
 * See_Also: http://topcoder.g.hatena.ne.jp/iwiwi/20131226/1388062106
 */
template <int N>
struct UnionFind {
    int ig[N];
    vector<int> gi[N];
    int gn;

    void init(int n = N) {
        for (int i = 0; i < n; ++i) {
            ig[i] = i;
            gi[i] = {i};
        }
        gn = n;
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

    int group_num() {
        return gn;
    }
};
