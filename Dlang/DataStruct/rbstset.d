struct RBSTree(T) {
    alias Node = RBSNode*;
    __gshared RBSNode last_d = RBSNode(null, null, 0, 0);
    __gshared Node last = &last_d;
    

    static int lb(Node t, in T d) {
        if (!t.sz) return 0;
        if (t.value < d) return t.l.sz + 1 + lb(t.r, d);
        return lb(t.l, d);
    }
    int lb(T d) {
        return lb(mt, d);
    }
    static int ub(Node t, in T d) {
        if (!t.sz) return 0;
        if (d < t.value) return ub(t.l, d);
        return t.l.sz + 1 + ub(t.r, d);
    }
    int ub(T d) {
        return ub(mt, d);
    }
    static Node built(in T[] d) {
        if (d.length == 0) return last;
        int u = cast(int)(d.length)/2;
        return new RBSNode(built(d[0..u]), built(d[u+1..$]), d[u]);
    }

    this(Node d) {
        mt = d;
    }

    this(in T[] dd) {
        auto d = dd.dup.sort;
        mt = built(d);
    }

    static struct RBSNode {
        Node l, r;
        int sz;
        T value;
        bool rev;
        this(in T d) {
            sz = 1; value = d;
        }

        this(Node _l, Node _r, in T _v) {
            value = _v; l = _l; r = _r;
            sz = 1 + l.sz + r.sz;
        }

        this(Node _l, Node _r, int _sz, in T _v) {
            value = _v; l = _l; sz = _sz; r = _r;
        }
        void update() {
            sz = l.sz + r.sz + 1;
        }
        void push() {
            if (rev) {
                swap(l, r);
                l.rev ^= true;
                r.rev ^= true;
                rev = false;
            }
        }
    }

    Node mt;
    @property int size() {
        return mt.sz;
    }    
    static Node merge(Node l, Node r) {
        if (!l.sz) return r;
        if (!r.sz) return l;
        l.push; r.push;
        auto ls = l.sz, rs = r.sz;
        static uint xor128(){
            __gshared uint x=123456789,y=362436069,z=521288629,w=88675123;
            uint t;
            t=(x^(x<<11));x=y;y=z;z=w; return( w=(w^(w>>19))^(t^(t>>8)) );
        }
        if (xor128() % (ls+rs) < ls) {
            l.r = merge(l.r, r);
            l.update;
            return l;
        } else {
            r.l = merge(l, r.l);
            r.update;
            return r;
        }
    }

    static Node[2] split(Node x, int k) {
        if (!x.sz) return [last, last];
        x.push;
        if (k <= x.l.sz) {
            auto y = split(x.l, k);
            x.l = y[1];
            x.update;
            y[1] = x;
            return y;
        } else {
            auto y = split(x.r, k-x.l.sz-1);
            x.r = y[0];
            x.update;
            y[0] = x;
            return y;
        }
    }

    static Node remove(Node x, int k) {
        auto y = split(x, k);
        x = merge(y[0], split(y[1], 1)[1]);
        return x;
    }

    static Node insert(Node x, int k, T d) {
        auto y = split(x, k);
        return merge(merge(y[0], new RBSNode(d)), y[1]);
    }

    RBSTree split(in int k) {
        auto y = split(mt, k);
        mt = y[0];
        return RBSTree(y[1]);
    }

    void split(RBSTree[] res, in int[] k) {
        foreach_reverse(i, d; k) {
            res[i+1] = split(d);
        }
        res[0] = this;
    }

    RBSTree merge(RBSTree r) {
        mt = merge(mt, r.mt);
        return this;
    }

    void reverse(int l, int r) {
        __gshared RBSTree[3] x;
        split(x, [l, r]);
        x[1].mt.rev ^= true;
        mt = x[0].merge(x[1]).merge(x[2]).mt;
    }

    void insert(int k, T d) {
        auto y = split(mt, k);
        mt = merge(merge(y[0], new RBSNode(d)), y[1]);
    }
}