/**
 * 永続化されている、範囲add、範囲sum、区間コピーが可能なRBST
 * 
 * GCは実装されていない
 *
 * Verify: ARC グラフではない
 */
struct STree {
    using D = ll;
    struct Node;
 
    using NP = const Node*;
    static Node last_d;
    static NP last;
    struct Node {
        NP l, r;
        int sz;
        D v, sm, lz;
        Node() : l(nullptr), r(nullptr), sz(0) {}
        Node(D vv) :l(last), r(last), sz(1) {
            v = vv;
            sm = 0;
            lz = 0;
        }
        static Node* make(NP x) {
            pool[pc] = *x;
            pc++;
            return &pool[pc-1];
        }
        static Node* make(D v) {
            pool[pc] = Node(v);
            pc++;
            return &pool[pc-1];
        }
        void push() {
            auto nl = make(l);
            auto nr = make(r);
            if (nl->sz) {
                nl->lzdata(lz);
            }
            if (nr->sz) {
                nr->lzdata(lz);
            }
            lz = 0;
            l = nl;
            r = nr;
        }
        /// pushはconstに関わらず呼んで良い
        void push() const {
            const_cast<Node*>(this)->push();
        }
        void update() {
            sz = 1+l->sz+r->sz;
            sm = v;
            if (l->sz) {
                sm += l->sm;
            }
            if (r->sz) {
                sm += r->sm;
            }
        }
        void lzdata(D x) {
            v += x;
            sm += sz*x;
            lz += x;
        }
    };
    NP n;

    //200,000,000とは200MBの意
    static const int PLS = 200000000 / sizeof(Node);
    static int pc;
    static Node pool[PLS];

    static void get(NP n, D d[]) {
        if (!n->sz) return;
        n->push();
        get(n->l, d);
        d[n->l->sz] = n->v;
        get(n->r, d + (n->l->sz+1));
    }
    void get(D d[]) {
        get(n, d);
    }

    void add(int l, int r, D x) {
        auto a = split(n, l);
        auto b = split(a.second, r-l);
        auto u = Node::make(b.first);
        u->lzdata(x);
        n = merge(merge(a.first, u), b.second);
    }
    D sum(int l, int r) {
        auto a = split(n, l);
        auto b = split(a.second, r-l);
        auto u = b.first;
        return u->sm;
    }

    static NP built(int l, int r, D d[]) {
        if (l == r) return last;
        int md = (l+r)/2;
        auto x = Node::make(d[md]);
        x->l = built(l, md, d);
        x->r = built(md+1, r, d);
        x->update();
        return x;
    }
 
    STree() : n(last) {}
    STree(NP n) : n(n) {}
    STree(int sz, D d[]) {
        n = built(0, sz, d);
    }

    int sz() {
        return n->sz;
    }     
    static uint xor128(){
        static uint x=123456789,y=362436069,z=521288629,w=88675123;
        uint t;
        t=(x^(x<<11));x=y;y=z;z=w; return( w=(w^(w>>19))^(t^(t>>8)) );
    }
    static NP merge(NP l, NP r) {
        if (!l->sz) return r;
        if (!r->sz) return l;
        l->push(); r->push();
        auto nl = Node::make(l);
        auto nr = Node::make(r);
        if ((int)(xor128() % (nl->sz + nr->sz)) < nl->sz) {
            nl->r = merge(nl->r, nr);
            nl->update();
            return nl;
        } else {
            nr->l = merge(nl, nr->l);
            nr->update();
            return nr;
        }
    }
    STree merge(STree r) {
        return STree(merge(n, r.n));
    }
    static pair<NP, NP> split(NP x, int k) {
        if (!x->sz) return {last, last};
        x->push();
        auto nx = Node::make(x);
        if (k <= nx->l->sz) {
            auto y = split(nx->l, k);
            nx->l = y.second;
            nx->update();
            y.second = nx;
            return y;
        } else {
            auto y = split(x->r, k- x->l->sz -1);
            nx->r = y.first;
            nx->update();
            y.first = nx;
            return y;
        }
    }
    pair<STree, STree> split(int k) {
        auto u = split(n, k);
        return pair<STree, STree>(STree(u.first), STree(u.second));
    }
};
STree::Node STree::last_d = STree::Node();
STree::NP STree::last = &last_d;
STree::Node STree::pool[STree::PLS];
int STree::pc = 0;
 