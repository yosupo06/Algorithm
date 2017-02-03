class Mat2 {
    import std.bitmanip : BitArray;
    int n, m;
    BitArray[] d;
    this(int _n, int _m) {
        n = _n; m = _m;
        d.length = n;
        foreach (ref e; d) {
            e.length = m;
        }
    }
    this(Mat2 mt) {
        this(mt.n, 0);
        foreach (i; 0..n) {
            d[i] = mt[i].dup;
        }
    }
    ref BitArray opIndex(size_t i) { return d[i]; }
    bool det()
    in { assert(n == m); }
    body {
        import std.algorithm : swap;
        auto mt = new Mat2(this);
        foreach (i; 0..n) {
            foreach (j; i+1..n) {
                if (mt[j][i]) {
                    swap(mt[i], mt[j]);
                    break;
                }
            }
            if (!mt[i][i]) return false;
            foreach (j; i+1..n) {
                if (mt[j][i]) {
                    mt[j] ^= mt[i];
                }
            }
        }
        return true;
    }
}
