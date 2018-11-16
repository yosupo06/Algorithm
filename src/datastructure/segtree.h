
template<class D, class L, class OPDD, class OPDL, class OPLL>
struct SegTree {
    D e_d;
    L e_l;
    OPDD opdd;
    OPDL opdl;
    OPLL opll;
    int sz, lg; //(2^lgに拡張後の)サイズ, lg
    V<D> d;
    V<L> lz;

    SegTree(V<D> first, D _e_d, L _e_l, OPDD _opdd, OPDL _opdl, OPLL _opll) : e_d(_e_d), e_l(_e_l), opdd(_opdd), opdl(_opdl), opll(_opll) {
        int n = int(first.size());
        lg = 1;
        while ((1<<lg) < n) lg++;
        sz = 1<<lg;
        d = V<D>(2*sz, e_d);
        lz = V<L>(2*sz, e_l);
        for (int i = 0; i < n; i++) d[sz + i] = first[i];
        for (int i = sz-1; i >= 0; i--) {
            update(i);
        }
    }

    void all_add(int k, L x) {
        d[k] = opdl(d[k], x);
        lz[k] = opll(lz[k], x);
    }
    void push(int k) {
        all_add(2*k, lz[k]); all_add(2*k+1, lz[k]);
        lz[k] = e_l;
    }
    void update(int k) { d[k] = opdd(d[2*k], d[2*k+1]); }

    D sum(int a, int b, int l, int r, int k) {
        if (b <= l || r <= a) return e_d;
        if (a <= l && r <= b) return d[k];
        push(k);
        int mid = (l + r) / 2;
        return op_dd(sum(a, b, l, mid, 2*k), sum(a, b, mid, r, 2*k+1));
    }
    D sum(int a, int b) { return sum(a, b, 0, sz, 1); }

    void add(int a, int b, L x, int l, int r, int k) {
        if (b <= l || r <= a) return;
        if (a <= l && r <= b) {
            all_add(k, x);
            return;
        }
        push(k);
        int mid = (l + r) / 2;
        add(a, b, x, l, mid, 2*k); add(a, b, x, mid, r, 2*k+1);
        update(k);
    }
    void add(int a, int b, L x) { add(a, b, x, 0, sz, 1); }

};

template<class D, class L, class OPDD, class OPDL, class OPLL>
SegTree<D, L, OPDD, OPDL, OPLL> get_seg(V<D> first, D e_d, L e_l, OPDD opdd, OPDL opdl, OPLL opll) {
    return SegTree<D, L, OPDD, OPDL, OPLL>(first, e_d, e_l, opdd, opdl, opll);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    auto seg = SegTree<int, int, my_min, add, add>(V<int>(n, 0), (1<<30) - 1000, 0);
    for (int i = 0; i < q; i++) {
        int ty, x, y;
        cin >> ty >> x >> y; y++;
        if (ty == 0) {
            int z;
            cin >> z;
            seg.add(x, y, z);
        } else {
            cout << seg.sum(x, y) << endl;
        }
    }
    return 0;
}