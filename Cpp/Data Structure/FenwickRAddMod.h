template <int SIZE, ll MD>
struct FenwickRAddMod {
    FenwickTreeMod<SIZE, MD> b0, b1;
    ll ds[SIZE+1];
    void init(const ll d[]) {
        b0.init();
        b1.init();
        ds[0] = 0;
        for (int i = 1; i <= SIZE; i++) {
            ds[i] = (d[i-1]+ds[i-1])%MD;
        }
    }

    void add(int i, ll x) {
        b0.add(i, x);
    }

    void add(int l, int r, ll x) {
        b1.add(l, x);
        b1.add(r, -x);
        b0.add(l, -ds[l]*x);
        b0.add(r, ds[r]*x);
    }

    //[0, i)
    ll sum(int i) {
        ll d = b0.sum(i)+b1.sum(i)*ds[i];
        return (d % MD + MD) % MD;
    }

    //[a, b)
    ll sum(int a, int b) {
        ll d = sum(b) - sum(a);
        return (d % MD + MD) % MD;
    }
};