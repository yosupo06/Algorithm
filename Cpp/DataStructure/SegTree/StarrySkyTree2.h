/**
 * 遅延評価で書かれている?
 * Node方式なので複雑な処理が書きやすい
 */
template <int S>
struct StarrySkyTree {
    typedef ll D;
    static const int N = 1<<S;
    static const D INF = 1LL<<54;   
    struct No {
        int sz;
        D d, r, ma;
        D l, r, ma;
        D d, ld, rd;
    } n[2*N];

    StarrySkyTree() {
        for (int i = 2*N-1; i >= N; i--) {
            n[i].sz = 1;
        }
        for (int i = N-1; i >= 1; i--) {
            n[i].sz = n[i*2].sz+n[i*2+1].sz;
        }
    }

    void init() {
        for (int i = 1; i < 2*N; i++) {
            n[i].d = n[i].ld = n[i].rd = 0;
            n[i].l = 1; n[i].r = 1; n[i].ma = 1;
        }
        for (int i = N-1; i >= 1; i--) {
            n[i] = merge(n[i*2], n[i*2+1]);
        }
    }

    No merge(No l, No r) {
        if (l.sz == 0) return r;
        if (r.sz == 0) return l;
        No n;
        n.sz = l.sz+r.sz;
        n.l = l.l;
        if (l.l == l.sz && l.rd < r.ld) {
            n.l = l.l + r.l;
        }
        n.r = r.r;
        if (r.r == r.sz && l.rd < r.ld) {
            n.r = r.r + l.r;
        }
        n.ma = max(l.ma, r.ma);
        if (l.rd < r.ld) {
            n.ma = max(n.ma, l.r + r.l);
        } 

        n.ld = l.ld;
        n.rd = r.rd;
        return n;
    }


    void set(int k, D x) {
        k += N;
        n[k].d = n[k].ld = n[k].rd = x;
        for (int i = 1; i <= S; i++) {
            n[k>>i] = merge(n[(k>>i)*2], n[(k>>i)*2+1]);
        }
    }

    /// [a, b)の最大を求める
    No get(int a, int b, int k = 1) {
        if (n[k].sz <= a || b <= 0) {
            No u;
            u.sz = 0;
            return u;
        }
        if (a <= 0 && n[k].sz <= b) return n[k];
        No dl = get(a, b, k*2);
        No dr = get(a-n[k].sz/2, b-n[k].sz/2, k*2+1);
        return merge(dl, dr);
    }
};
