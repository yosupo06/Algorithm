/**
 * Multiset(AA Tree)
 *
 * template引数のclass Dは要素の型、class Cは比較関数
 */
template<class D, class C = less<D>>
struct AAMSet {
    struct Node;
    using NP = Node*;
    static Node last_d;
    static NP last;
    struct Node {
        NP l, r;
        int level, sz;
        D v;
        Node(): l(nullptr), r(nullptr), level(0), sz(0) {}
        Node(D vv): l(last), r(last), level(1), sz(1) {
            v = vv;
        }
        /// メモリプールをしたい時のためにnewはラッパする
        static NP make() {
            return new Node();
        }
        static NP make(D vv) {
            return new Node(vv);
        }

        inline void update() {
            sz = 1+l->sz+r->sz;
        }

        inline void push() {
        }
    } *n;

    static D at(NP n, int k) {
        if (k == n->l->sz) return n->v;
        n->push();
        if (k < n->l->sz) {
            return at(n->l, k);
        } else {
            return at(n->r, k - (n->l->sz+1));
        }
    }
    /// k番目の要素を取得
    D at(int k) {
        return at(n, k);
    }
    static int lb(NP n, D x) {
        if (n == last) return 0;
        if (C()(n->v, x)) return n->l->sz + 1 + lb(n->r, x);
        return lb(n->l, x);
    }
    /// lower_bound、ただし返り値はインデックス
    int lb(D v) {
        return lb(n, v);
    }
    static int ub(NP n, D x) {
        if (n == last) return 0;
        if (C()(x, n->v)) return ub(n->l, x);
        return n->l->sz + 1 + ub(n->r, x);
    }
    /// upper_bound、ただし返り値はインデックス
    int ub(D v) {
        return ub(n, v);
    }
    static NP insert(NP n, D x) {
        if (n == last) {
            return Node::make(x);
        }
        n->push();
        if (!C()(n->v, x)) {
            n->l = insert(n->l, x);
            n->update();
        } else {
            n->r = insert(n->r, x);
            n->update();
        }
        n = skew(n);
        n = pull(n);
        return n;
    }
    /// xをinsertする
    void insert(D x) {
        n = insert(n, lb(x), x);
    }
    static NP erase(NP n, D x) {
        assert(n != last);
        n->push();
        if (!C()(n->v, x) && !C()(x, n->v)) {
            if (n->level == 1) {
                return n->r;
            }
            auto x = at0_with_remove(n->r);
            NP nn = x.first;
            nn->push();
            nn->l = n->l;
            nn->r = x.second;
            nn->level = n->level;
            nn->update();
            return rightdown(nn);
        }
        if (C()(x, n->v)) {
            n->l = erase(n->l, x);
            n->update();
            return leftdown(n);
        } else {
            n->r = erase(n->r, x);
            n->update();
            return rightdown(n);
        }
    }
    /// xを削除する
    void erase(D x) {
        n = remove(n, lb(x));
    }

    static void tp(NP n) {
        if (n == last) return;
        n->push();
        tp(n->l);
        cout << n->v << " ";
        tp(n->r);
    }
    void tp() {
        tp(n);
        printf("\n");
    }
    static void allpush(NP n) {
        if (n == last) return;
        n->push();
        allpush(n->l);
        allpush(n->r);
    }
    void allpush() {
        allpush(n);
        return;
    }

    static NP built(int sz, D d[]) {
        if (!sz) return last;
        int md = (sz-1)/2;
        NP n = Node::make(d[md]);
        n->l = built(md, d);
        n->r = built(sz-(md+1), d+(md+1));
        n->level = n->l->level+1;
        n->update();
        return n;
    }
    AAMSet() : n(last) {}
    AAMSet(NP n) : n(n) {}
    //木の初期化はn回insertより一気に作る方が有意に速くなる事が多い
    AAMSet(int sz, D d[]) {
        n = built(sz, d);
    }


    //基本動作
    int sz() {
        return n->sz;
    }
    int size() {
        return sz();
    }
    void merge(AAMSet r) {
        n = merge(n, r.n);
    }
    AAMSet split(int k) {
        auto y = split(n, k);
        n = y.first;
        return AAMSet(y.second);
    }
    void insert(int k, D x) {
        n = insert(n, k, x);
    }
    void remove(int k) {
        n = remove(n, k);
    }

    //AA木の基本動作であるskew/split splitは名前が紛らわしいためpullに変更してある
    static NP skew(NP n) {
        if (n->level == n->l->level) {
            NP L = n->l;
            n->push(); L->push();
            n->l = L->r;
            L->r = n;
            n->update(); L->update();
            return L;
        }
        return n;
    }
    static NP pull(NP n) {
        if (n->level == n->r->level && n->r->level == n->r->r->level) {
            NP R = n->r;
            n->push(); R->push();
            n->r = R->l;
            R->l = n;
            R->level++;
            n->update(); R->update();
            return R;
        }
        return n;
    }

    static NP leftdown(NP n) {
        assert(n->l->level < n->level);
        if (n->l->level == n->level-1) return n;
        n->level--;
        if (n->r->level == n->level) {
            n = pull(n);
        } else {
            n->r->level--;
            n->r = skew(n->r);
            n->r->r = skew(n->r->r);
            n = pull(n);
            n->r = pull(n->r);
        }
        return n;
    }
    static NP rightdown(NP n) {
        assert(n->r->level <= n->level);
        if (n->r->level >= n->level-1) return n;
        n->level--;
        n = skew(n);
        n->r = skew(n->r);
        n = pull(n);
        return n;
    }
    static NP superleftdown(NP n) {
        if (n->l->level == n->level-1) return n;
        if (n->level != n->r->level && n->r->level != n->r->r->level) {
            n->level--;
            return superleftdown(n);
        }
        n = leftdown(n);
        n->l = superleftdown(n->l);
        n = leftdown(n);
        return n;
    }
    static NP superrightdown(NP n) {
        if (n->r->level >= n->level-1) return n;
        n = rightdown(n);
        n->r = superrightdown(n->r);
        n = rightdown(n);
        return n;
    }

    static NP insert(NP n, int k, D x) {
        if (n == last) {
            assert(k == 0);
            return Node::make(x);
        }
        n->push();
        if (k <= n->l->sz) {
            n->l = insert(n->l, k, x);
            n->update();
        } else {
            n->r = insert(n->r, k - (n->l->sz+1), x);
            n->update();
        }
        n = skew(n);
        n = pull(n);
        return n;
    }
    //pair<0番目の要素,0番目の要素を削除した木>
    static pair<NP, NP> at0_with_remove(NP n) {
        n->push();
        if (n->l == last) {
            return {n, n->r};
        }
        auto x = at0_with_remove(n->l);
        n->l = x.second;
        n->update();
        x.second = leftdown(n);
        return x;
    }
    static NP remove(NP n, int k) {
        assert(n != last);
        n->push();
        if (k == n->l->sz) {
            if (n->level == 1) {
                return n->r;
            }
            auto x = at0_with_remove(n->r);
            NP nn = x.first;
            nn->push();
            nn->l = n->l;
            nn->r = x.second;
            nn->level = n->level;
            nn->update();
            return rightdown(nn);
        }
        if (k < n->l->sz) {
            n->l = remove(n->l, k);
            n->update();
            return leftdown(n);
        } else {
            n->r = remove(n->r, k - (n->l->sz+1));
            n->update();
            return rightdown(n);
        }
    }
    static NP merge(NP l, NP r) {
        if (l == last) return r;
        if (r == last) return l;
        if (l->level == r->level) {
            auto x = at0_with_remove(r);
            NP n = x.first;
            n->push();
            n->r = x.second;
            n->l = l;
            n->level = l->level+1;
            n->update();
            return rightdown(n);
        }
        NP n;
        l->push(); r->push();
        if (l->level > r->level) {
            l->push();
            l->r = merge(l->r, r);
            l->update();
            n = l;
        } else {
            r->push();
            r->l = merge(l, r->l);
            r->update();
            n = r;
        }
        n = skew(n);
        n = pull(n);
        return n;
    }
    static pair<NP, NP> split(NP n, int k) {
        if (n == last) return {last, last};
        n->push();
        if (k <= n->l->sz) {
            auto y = split(n->l, k);
            n->l = y.second;
            n->update();
            n = superleftdown(n);
            y.second = n;
            return y;
        } else {
            auto y = split(n->r, k- (n->l->sz+1));
            n->r = y.first;
            n->update();
            n = superrightdown(n);
            y.first = n;
            return y;
        }
    }
};
template<class D, class C>
typename AAMSet<D, C>::Node AAMSet<D, C>::last_d = AAMSet<D, C>::Node();
template<class D, class C>
typename AAMSet<D, C>::NP AAMSet<D, C>::last = &AAMSet<D, C>::last_d;
