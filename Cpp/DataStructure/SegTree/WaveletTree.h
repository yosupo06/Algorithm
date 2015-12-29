/**
 * 本当にWaveletTreeなのかは知らない
 *
 * 区間について
 * [l, r)でk番目の値の取得
 * [l, r)でxが何番目に大きいかの取得
 * をどちらもO(logn)で行える強力なデータ構造
 *
 * ただし一度構成したら変更不可能
 *
 * template引数のclass Dは要素の型
 * int Sは要素数が2^Sであることを示す
 */
template<class D, int S>
struct WaveletTree {
    static const int N = 1<<S;
    typedef pair<D, int> P;
    int n;
    P x[N];
    int d[S+1][N];
    int lc[S][N];

    void built(int l, int r, int dps) {
        if (dps == S) return;
        int pl = l, md = (l+r)/2, pr = md;
        for (int i = l; i < r; i++) {
            if (d[dps][i] < md) {
                d[dps+1][pl++] = d[dps][i];
            } else {
                d[dps+1][pr++] = d[dps][i];
            }
            lc[dps][i] = pl-l;
        }
        built(l, md, dps+1);
        built(md, r, dps+1);
    }

    void init(int nn = N) {
        n = nn;
        for (int i = 0; i < N; i++) {
            x[i].second = i;
        }
        sort(x, x+n);
        for (int i = 0; i < N; i++) {
            d[0][x[i].second] = i;
        }
        built(0, N, 0);
    }
    int get(int l, int r, int k, int dps, int idx) {
        assert(1 <= k && k <= r-l);
        if (dps == S) {
            return d[dps][l];
        }
        int ls = (l > idx ? lc[dps][l-1] : 0);
        int c = lc[dps][r-1] - ls;
        if (k < c) {
            return get(idx+ls, idx+ls+c, k, dps+1, idx);
        } else {
            int sz = 1<<(S-dps-1);
            return get(l+sz-ls, r+sz-(ls+c), k-c, dps+1, idx+sz);
        }
        return -1;
    }
    /// [l, r)でk番目の値を調べる
    D get(int l, int r, int k) {
        return x[get(l, r, k, 0, 0)].first;
    }
    int find(int l, int r, int x, int dps, int idx) {
        if (r <= l) return 0;
        if (dps == S) {
            return (x <= l) ? 0 : 1;
        }
        int ls = (l > idx ? lc[dps][l-1] : 0);
        int c = lc[dps][r-1] - ls;
        int sz = 1<<(S-dps-1);
        int md = idx+sz;
        if (x <= md) {
            return find(idx+ls, idx+ls+c, x, dps+1, idx);
        } else {
            return c+find(l+sz-ls, r+sz-(ls+c), x, dps+1, idx+sz);
        }
    }
    /// [l, r)でuが何番目に大きいかを調べる。ただしlower_bound
    int find(int l, int r, D u) {
        return find(l, r, lower_bound(x, x+n, P(u, -1)) - x, 0, 0);
    }
};
