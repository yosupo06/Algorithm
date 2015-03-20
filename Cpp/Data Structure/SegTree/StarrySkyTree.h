/**
 * 遅延評価で書かれているStarry Sky Tree
 */
template <int S>
struct StarrySkyTree {
    typedef ll D;
    static const int N = 1<<S;
    static const D INF = 1LL<<55;   
    D seg[2*N], lz[2*N];
    int sz[2*N];
    StarrySkyTree() {
        for (int i = 2*N-1; i >= N; i--) {
            sz[i] = 1;
        }
        for (int i = N-1; i >= 1; i--) {
            sz[i] = sz[i*2]+sz[i*2+1];
        }
    }
    void init() {
        for (int i = 1; i < 2*N; i++) {
            seg[i] = 0;
            lz[i] = 0;
        }
    }

    void lzdata(int k, D x) {
        seg[k] += x;
        lz[k] += x;
    }
    void push(int k) {
        assert(1 <= k && k < N);
        if (lz[k]) {
            lzdata(k*2, lz[k]);
            lzdata(k*2+1, lz[k]);
            lz[k] = 0;
        }
    }
    void update(int k) {
        assert(1 <= k && k < N);
        seg[k] = max(seg[k*2], seg[k*2+1]);
    }

    /// k番目の要素にxを足す
    void add(int k, D x) {
        k += N;
        for (int i = S; i > 0; i--) {
            push(k>>i);
        }
        lzdata(k, x);
        for (int i = 1; i <= S; i++) {
            update(k>>i);
        }
    }

    /// [a, b)にそれぞれxを足す
    void add(int a, int b, D x, int k = 1) {
        if (sz[k] <= a || b <= 0) return;
        if (a <= 0 && sz[k] <= b) {
            lzdata(k, x);
            return;
        }
        push(k);
        add(a, b, x, k*2);
        add(a-sz[k]/2, b-sz[k]/2, x, k*2+1);
        update(k);
    }
    /// [a, b)の最大を求める
    D get(int a, int b, int k = 1) {
        if (sz[k] <= a || b <= 0) return -INF;
        if (a <= 0 && sz[k] <= b) return seg[k];
        push(k);
        D dl = get(a, b, k*2);
        D dr = get(a-sz[k]/2, b-sz[k]/2, k*2+1);
        return max(dl, dr);
    }
};