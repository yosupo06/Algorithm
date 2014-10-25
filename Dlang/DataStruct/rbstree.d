class RBSTree(T) {
    alias Node = RBSNode*;
    static int size(in Node x) {
        return ((x is null) ? 0 : x.sz);
    }

    static Node update(Node x) {
        x.sz = size(x.l) + size(x.r) + 1;
        return x;
    }

    static Node merge(Node l, Node r) {
        Node res;
        Node *root = &res;
        int ls, rs;
        while (true) {
            if (l is null) {
                *root = r;
                break;
            }
            if (r is null) {
                *root = l;
                break;
            }
            ls = l.sz, rs = r.sz;
            if (uniform(0, ls+rs, RBSNode.rnd) < ls) {
                l.sz += rs;
                *root = l;
                root = &l.r;
                l = l.r;
            } else {
                r.sz += ls;
                *root = r;
                root = &r.l;
                r = r.l;
            }
        }
        return res;
    }

    static Node[2] split(Node x, int k) {
        Node[2] res;
        Node*[2] root = [&res[0], &res[1]];
        while (k) {
            auto ls = size(x.l);
            if (k <= ls) { 
                x.sz -= k;
                *root[1] = x;
                root[1] = &x.l;
                x = x.l;
            } else {
                x.sz = k;
                *root[0] = x;
                root[0] = &x.r;
                x = x.r; k -= ls+1;                
            }
        }
        *root[0] = null;
        *root[1] = x;
        return res;
    }

    static Node erase(Node x, int k) {
        auto y = split(x, k);
        x = merge(y[0], split(y[1], 1)[1]);
        return x;
    }

    static Node insert(Node x, int k, T d) {    
        auto y = split(x, k);
        return merge(merge(y[0], new RBSNode(d)), y[1]);
    }

    static struct RBSNode {
        static Xorshift rnd;
        static this() {
            rnd = Xorshift(unpredictableSeed);
        }

        Node l, r;
        int sz;
        T value;

        this(T d) {
            sz = 1; value = d;
        }

        this(T[] d) {
            sz = cast(int)d.length;
            value = d[sz/2];
            if (sz/2) {
                l = new RBSNode(d[0..sz/2]);
            }
            if (sz-sz/2-1) {
                r = new RBSNode(d[sz/2+1..sz]);
            }
        }
        
        T get(int k) {
            if (size(l) == k) return value;
            if (k < size(l)) {
                return l.get(k);
            } else {
                return r.get(k-size(l)-1);
            }
        }

        void get(T[] d) {
            if (l !is null) l.get(d[0..size(l)]);
            d[size(l)] = value;
            if (r !is null) r.get(d[size(l)+1..$]);
        }

        T[] getAll() {
            auto res = new T[](sz);
            get(res);
            return res;
        }
    }


    Node mt;
    int sz;

    this(Node d) {
        mt = d;
        sz = size(mt);
    }

    this(T[] d) {
        mt = new RBSNode(d);
        sz = cast(int)d.length;
    }

    RBSTree split(int k) {
        auto y = split(mt, k);
        mt = y[0];
        sz = size(mt);
        return new RBSTree(y[1]);
    }

    RBSTree[] split(in int[] k) {
        auto res = new RBSTree[](k.length+1);
        foreach_reverse(i, d; k) {
            res[i+1] = split(d);
        }
        res[0] = this;
        return res;
    }

    RBSTree merge(RBSTree r) {
        mt = merge(mt, r.mt);
        sz = size(mt);
        return this;
    }

    void insert(int k, T d) {
        auto y = split(mt, k);
        mt = merge(merge(y[0], new RBSNode(d)), y[1]);
        sz++;
    }

    T get(int k) {
        return mt.get(k);
    }

    T[] getAll() {
        return mt.getAll();
    }
}


class DRBSTree(T) {
    RBSTree!T mt, rt;
    int sz;
    this() {}
    this(RBSTree!T m, RBSTree!T r) {
        assert(m.sz == r.sz);
        mt = m; rt = r;
        sz = m.sz;
    }

    this(T[] d) {
        mt = new RBSTree!T(d);
        rt = new RBSTree!T(d.dup.reverse);
        sz = cast(int)d.length;
    }

    DRBSTree merge(DRBSTree r) {
        mt = mt.merge(r.mt);
        rt = r.rt.merge(rt);
        sz = mt.sz;
        return this;
    }

    DRBSTree[] split(in int[] k) {
        int n = cast(int)k.length;
        auto res = new DRBSTree[](n+1);
        foreach (int i; 0..n+1) {
            res[i] = new DRBSTree();
        }
        foreach_reverse (int i; 0..n) {
            res[i+1].mt = mt.split(k[i]);
            res[n-1-i].rt = rt.split(sz-k[n-1-i]);
        }
        res[0].mt = mt;
        res[n].rt = rt;
        res[0].sz = k[0];
        foreach (int i; 1..n) {
            res[i].sz = k[i]-k[i-1];
        }
        res[n].sz = sz-k[n-1];
        return res;
    }

    void reverse(int l, int r) {
        auto x = mt.split([l, r]);
        auto y = rt.split([sz-r, sz-l]);
        mt = x[0].merge(y[1]).merge(x[2]);
        rt = y[0].merge(x[1]).merge(y[2]);
    }

    T get(int k) {
        return mt.get(k);
    }

    T[][2] getAll() {
        T[][2] res;
        res[0] = mt.getAll;
        res[1] = rt.getAll;
        return res;
    }
}
