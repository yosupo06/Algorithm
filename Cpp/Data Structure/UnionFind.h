/**
 * データ構造をマージする一般的なテクによるUnionFindです。QuickFindと呼ばれているらしい？
 *
 * template引数のint Nは頂点の最大数
 *
 * See_Also: http://topcoder.g.hatena.ne.jp/iwiwi/20131226/1388062106
 */
template <int N>
struct UnionFind {
    int ig[N];
    vector<int> gi[N];
    int gn;
    /// UnionFindを頂点数nで初期化する
    void init(int n = N) {
        for (int i = 0; i < n; ++i) {
            ig[i] = i;
            gi[i] = {i};
        }
        gn = n;
    }

    /// 頂点aと頂点bをマージ
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
    /// 頂点aと頂点bが同じグループに所属してるかを調べる
    bool same(int a, int b) {
        return ig[a] == ig[b];
    }
    /// グループの数
    int group_num() {
        return gn;
    }
};
