template<int S>
struct WaveletTree {
    static const int N = 1<<S;
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
    //idxは0~N-1の順列じゃないともうガバガバですよ
    void init(int idx[]) {
        copy_n(idx, N, d[0]);
        sort(idx, idx+N);
        for (int i = 0; i < N; i++) {
            assert(idx[i] == i);
        }
        built(0, N, 0);
    }

    //[l, r)でk番目の数を調べる
    int get(int l, int r, int k, int dps = 0, int idx = 0) {
        assert(1 <= k && k <= r-l);
        if (dps == S) {
            return d[dps][l];
        }
        int ls = (l > idx ? lc[dps][l-1] : 0);
        int c = lc[dps][r-1] - ls;
        if (k <= c) {
            return get(idx+ls, idx+ls+c, k, dps+1, idx);
        } else {
            int sz = 1<<(S-dps-1);
            return get(l+sz-ls, r+sz-(ls+c), k-c, dps+1, idx+sz);
        }
        return -1;
    }
    //[l, r)でxが何番目に大きいかを調べる。ただしlower_bound
    int find(int l, int r, int x, int dps = 0, int idx = 0) {
        if (r <= l) return 1;
        if (dps == S) {
            return (x <= l) ? 1 : 2;
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
};