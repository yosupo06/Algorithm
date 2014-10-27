struct RBSTree(T) {
    alias Node = RBSNode*;
    __gshared RBSNode last_d = RBSNode(null, null, 0, 0);
    __gshared Node last = &last_d;
    
    static Node update(Node x) {
        x.sz = x.l.sz + x.r.sz + 1;
        return x;
    }

    static void push(Node x) {
        if (x.rev) {
            swap(x.l, x.r);
            if (x.l.sz) x.l.rev ^= true;
            if (x.r.sz) x.r.rev ^= true;
            x.rev = false;
        }
    }

    static Node merge(Node l, Node r) {
        if (!l.sz) return r;
        if (!r.sz) return l;
        push(l); push(r);
        auto ls = l.sz, rs = r.sz;
        static uint xor128(){
            __gshared uint x=123456789,y=362436069,z=521288629,w=88675123;
            uint t;
            t=(x^(x<<11));x=y;y=z;z=w; return( w=(w^(w>>19))^(t^(t>>8)) );
        }
        if (xor128() % (ls+rs) < ls) {
            l.r = merge(l.r, r);
            return update(l);
        } else {
            r.l = merge(l, r.l);
            return update(r);
        }
    }

    static Node[2] split(Node x, int k) {
        if (!x.sz) return [last, last];
        push(x);
        if (k <= x.l.sz) {
            auto y = split(x.l, k);
            x.l = y[1];
            y[1] = update(x);
            return y;
        } else {
            auto y = split(x.r, k-x.l.sz-1);
            x.r = y[0];
            y[0] = update(x);
            return y;
        }
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

    static Node built(T[] d) {
        if (d.length == 0) return last;
        int u = cast(int)d.length/2;
        return new RBSNode(built(d[0..u]), built(d[u+1..$]), d[u]);
    }

    static struct RBSNode {
        Node l, r;
        int sz;
        T value;
        bool rev;
        this(T d) {
            sz = 1; value = d;
        }

        this(Node _l, Node _r, in T _v) {
            value = _v; l = _l; r = _r;
            sz = 1 + l.sz + r.sz;
        }

        this(Node _l, Node _r, int _sz, in T _v) {
            value = _v; l = _l; sz = _sz; r = _r;
        }
        
        T get(int k) {
            if (l.sz == k) return value;
            if (k < l.sz) {
                return l.get(k);
            } else {
                return r.get(k-l.sz-1);
            }
        }

        void get(T[] d, int cl, int cr) {
            push(&this);
            if (cl < l.sz) {
                l.get(d, cl, min(cr, l.sz));
                if (cr <= l.sz) return;
                d = d[l.sz-cl..$];
            }
            cl -= l.sz; cr -= l.sz;
            if (cl <= 0) {
                d[0] = value;
                d = d[1..$];
            }
            cl -= 1; cr -= 1;
            if (0 < cr) r.get(d, max(0, cl), cr);
        }

        void get(T[] d) {
            push(&this);
            if (l.sz) l.get(d[0..l.sz]);
            d[l.sz] = value;
            if (r.sz) r.get(d[l.sz+1..$]);
        }
    }


    Node mt;

    @property int size() {
        return mt.sz;
    }

    this(Node d) {
        mt = d;
    }

    this(T[] d) {
        mt = built(d);
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

    T get(int k) {
        return mt.get(k);
    }

    T[] get(T[] res, int l, int r) {
        mt.get(res, l, r);
        return res;
    }

    T[] getAll() {
        T[] res = new T[](mt.sz);
        return get(res, 0, mt.sz);
    }
}