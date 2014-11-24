long size(T)(RBSNode!(T)* x) {
    return ((x is null) ? 0 : x.sz);
}

RBSNode!(T)* update(T)(RBSNode!(T)* x) {
    x.sz = x.l.size() + x.r.size() + 1;
    return x;
}

RBSNode!(T)* merge(T)(RBSNode!(T)* l, RBSNode!(T)* r) {
    if (l is null) return r;
    if (r is null) return l;
    if (uniform(0, l.size()+r.size(), RBSNode!(T).rnd) < l.sz) {
        l.r = merge(l.r, r);
        return l.update();
    } else {
        r.l = merge(l, r.l);
        return r.update();
    }
}

RBSNode!T erase(T)(RBSNode!T x, int k) {
    auto y = x.split(k);
    x = y[0].merge(split(y[1], 1)[1]);
    return x;
}

RBSNode!(T)*[2] split(T)(RBSNode!(T)* x, long k) {
    if (!k) return [null, x];
    if (k <= x.l.size()) {
        auto y = split(x.l, k);
        x.l = y[1];
        return [y[0], x.update()];
    } else {
        auto y = split(x.r, k-x.l.size()-1);
        x.r = y[0];
        return [x.update(), y[1]];
    }
}

RBSNode!(T)*[] split(T)(RBSNode!(T)* x, long[] k) {
    auto res = new RBSNode!(T)*[](k.length+1);
    foreach_reverse(i, d; k) {
        writeln(i, " ", d);
        auto y = x.split(d);
        x = y[0];
        res[i+1] = y[1];
    }
    res[0] = x;
    return res;
}

RBSNode!T insert(T)(RBSNode!T x, int k, T d) {
    auto y = x.split(k);
    return y[0].merge(new RBSNode!T(d)).merge(y[1]);
}

struct RBSNode(T) {
    static Xorshift rnd;
    static this() {
        rnd = Xorshift(unpredictableSeed);
    }

    RBSNode* l, r;
    long sz;
    T value;

    this(T d) {
        sz = 1; value = d; l = r = null;
    }

    this(T[] d) {
        sz = d.length;
        value = d[sz/2];
        if (sz/2) {
            l = new RBSNode(d[0..sz/2]);
        }
        if (sz-sz/2-1) {
            r = new RBSNode(d[sz/2+1..sz]);
        }
    }
    
    T get(long k) {
        if (l.size() == k) return value;
        if (k < l.size()) {
            return l.get(k);
        } else {
            return r.get(k-l.size()-1);
        }
    }

    void get(T[] d) {
        if (l !is null) l.get(d[0..l.size()]);
        d[l.size()] = value;
        if (r !is null) r.get(d[l.size()+1..$]);
    }

    T[] getAll() {
        auto res = new T[](sz);
        get(res);
        return res;
    }
}

class RBSTree(T) {
    RBSNode!T* mt;
    long sz;

    this(RBSNode!T* d) {
        mt = d;
        sz = mt.size;
    }

    this(T[] d) {
        mt = new RBSNode!T(d);
        sz = d.length;
    }

    RBSTree!(T) split(long k) {
        auto y = mt.split(k);
        mt = y[0];
        return new RBSTree(y[1]);
    }

    RBSTree!(T)[] split(long[] k) {
        auto res = new RBSTree[](k.length+1);
        foreach_reverse(i, d; k) {
            writeln(i, " ", d);
            res[i+1] = split(d);
        }
        res[0] = this;
        return res;
    }

    RBSTree merge(RBSTree!(T) r) {
        mt = mt.merge(r.mt);
        return this;
    }

    void insert(T)(int k, T d) {
        auto y = mt.split(k);
        mt = y[0].merge(new RBSNode!T(d)).merge(y[1]);
    }

    T[] getAll() {
        return mt.getAll();
    }
}


class DRBSTree(T) {
    RBSTree!T mt, rt;
    long sz;
    this(T[] d) {
        mt = new RBSTree!T(d);
        rt = new RBSTree!T(d.reverse);
        sz = d.length;
    }

    void reverse(int l, int r) {
        auto x = mt.split([l, r]);
        auto y = rt.split([sz-r, sz-l]);
        writeln(x[0].getAll, x[1].getAll, x[2].getAll);
        writeln(y[0].getAll, y[1].getAll, y[2].getAll);
        mt = x[0].merge(y[1]).merge(x[2]);
        rt = y[0].merge(x[1]).merge(y[2]);
    }

    T[] getAll() {
        return mt.getAll();
    }
}