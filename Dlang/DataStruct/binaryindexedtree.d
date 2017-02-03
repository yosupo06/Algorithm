class BinaryIndexedTree {
    immutable int n;
    long[] seg;
    this(int i) {
        n = i;
        seg.length = i;
    }

    void add(int i, long x) {
        while (i < n) {
            seg[i] += x;
            i += (i+1) & ~i;
        }
    }

    long sum(int i) {
        long s = 0;
        for (i--; i >= 0; i = (i & (i+1)) - 1) {
            s += seg[i];            
        }
        return s;
    }

    long sum(int a, int b) {
        return sum(b) - sum(a);
    }
}

class BITRangeAdd {
    immutable int n;
    BinaryIndexedTree b0, b1;
    long[] ds;
    this(long[] d) {
        n = cast(int)d.length;
        b0 = new BinaryIndexedTree(n);
        b1 = new BinaryIndexedTree(n);
        ds.length = n+1;
        ds[0] = 0;
        for (int i = 1; i <= n; i++) {
            ds[i] = d[i-1]+ds[i-1];
        }
    }

    void add(int i, long x) {
        b0.add(i, x);
    }

    void add(int l, int r, long x) {
        b1.add(l, x);
        b1.add(r, -x);
        b0.add(l, -ds[l]*x);
        b0.add(r, ds[r]*x);
    }

    //[0, i)
    long sum(int i) {
        long d = b0.sum(i)+b1.sum(i)*ds[i];
        return d;
    }

    //[a, b)
    long sum(int a, int b) {
        long d = sum(b) - sum(a);
        return d;
    }
};