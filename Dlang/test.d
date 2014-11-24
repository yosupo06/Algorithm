import std.stdio, std.getopt, std.random, std.range, std.string, std.conv;
import std.algorithm, std.container;
import std.complex, std.math, std.datetime;
import std.ascii;

struct RBSTree(T) {
    alias Node = RBSNode*;
    __gshared RBSNode last_d = RBSNode(null, null, 0, 0);
    __gshared Node last = &last_d;
    
    static int size(in Node x) {
        assert(x !is null);
        return ((x is null) ? 0 : x.sz);
    }

    static Node update(Node x) {
        x.sz = x.l.sz + x.r.sz + 1;
        return x;
    }

    static void push(Node x) {
        if (x.rev) {
            swap(x.l, x.r);
            if (size(x.l)) x.l.rev ^= true;
            if (size(x.r)) x.r.rev ^= true;
            x.rev = false;
        }
    }

    static Node merge(Node l, Node r) {
        if (!size(l)) return r;
        if (!size(r)) return l;
        push(l); push(r);
        auto ls = l.sz, rs = r.sz;
        if (uniform(0, ls+rs, RBSNode.rnd) < ls) {
            l.r = merge(l.r, r);
            return update(l);
        } else {
            r.l = merge(l, r.l);
            return update(r);
        }
    }

    static Node[2] split(Node x, int k) {
        if (!size(x)) return [last, last];
        push(x);
        int ls = size(x.l);
        if (k <= ls) {
            auto y = split(x.l, k);
            x.l = y[1];
            y[1] = update(x);
            return y;
        } else {
            auto y = split(x.r, k-ls-1);
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
        static Xorshift rnd;
        static this() {
            rnd = Xorshift(unpredictableSeed);
        }

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
            value = _v; l = _l; _sz = sz; r = _r;
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

        void get(T[] d, int cl, int cr) {
            push(&this);
            int ls = size(l), rs = size(r);
            if (cl < ls) {
                l.get(d, cl, min(cr, ls));
                if (cr <= ls) return;
                d = d[ls-cl..$];
            }
            cl -= ls; cr -= ls;
            if (cl <= 0) {
                d[0] = value;
                d = d[1..$];
            }
            cl -= 1; cr -= 1;
            if (0 < cr) r.get(d, max(0, cl), cr);
        }

        void get(T[] d) {
            push(&this);
            if (size(l)) l.get(d[0..size(l)]);
            d[size(l)] = value;
            if (size(r)) r.get(d[size(l)+1..$]);
        }
    }


    Node mt;

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
        static RBSTree[3] x;
        split(x, [l, r]);
        assert(x[1].mt !is null);
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

int main() {
    auto t = RBSTree!int([0,1,2,3,4,5,6,7,8,9]);
    t.reverse(4, 8);
    writeln(t.getAll);
    return 0;
}