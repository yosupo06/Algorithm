namespace AA {
    template<class N>
    struct AABase {
        using NP = N*;
        NP l, r;
        int level, sz;
        AABase() : l(nullptr), r(nullptr), level(0), sz(0) {}
        AABase(NP last) : l(last), r(last), level(1), sz(1) {}
        virtual void push() = 0;
        virtual NP update() = 0;
    };

    template<class N>
    N* built(int sz, N n[]) {
        if (!sz) return N::last;
        int md = (sz-1)/2;
        N* nn = n+md;
        nn->l = built(md, n);
        nn->r = built(sz-(md+1), n+(md+1));
        nn->level = nn->l->level+1;
        nn->update();
        return nn;
    }

    template<class N>
    N* at(N* n, int k) {
        if (k == n->l->sz) return n;
        n->push();
        if (k < n->l->sz) {
            return at(n->l, k);
        } else {
            return at(n->r, k - (n->l->sz+1));
        }
    }
    //AA木の基本動作であるskew/split splitは名前が紛らわしいためpullに変更してある
    template<class N>
    N* skew(N* n) {
        if (n->level == n->l->level) {
            N* L = n->l;
            n->push(); L->push();
            n->l = L->r;
            L->r = n;
            n->update(); L->update();
            return L;
        }
        return n;
    }

    template<class N>
    N* pull(N* n) {
        if (n->level == n->r->level && n->r->level == n->r->r->level) {
            N* R = n->r;
            n->push(); R->push();
            n->r = R->l;
            R->l = n;
            R->level++;
            n->update(); R->update();
            return R;
        }
        return n;
    }

    template<class N>
    N* leftdown(N* n) {
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

    template<class N>
    N* rightdown(N* n) {
        assert(n->r->level <= n->level);
        if (n->r->level >= n->level-1) return n;
        n->level--;
        n = skew(n);
        n->r = skew(n->r);
        n = pull(n);
        return n;
    }

    template<class N>
    N* superleftdown(N* n) {
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

    template<class N>
    N* superrightdown(N* n) {
        if (n->r->level >= n->level-1) return n;
        n = rightdown(n);
        n->r = superrightdown(n->r);
        n = rightdown(n);
        return n;
    }
    template<class N>
    N* insert(N* n, int k, N* x) {
        if (n == N::last) {
            assert(k == 0);
            return x;
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
    template<class N>
    pair<N*, N*> at0_with_remove(N* n) {
        n->push();
        if (n->l == N::last) {
            return {n, n->r};
        }
        auto x = at0_with_remove(n->l);
        n->l = x.second;
        n->update();
        x.second = leftdown(n);
        return x;
    }

    template<class N>
    N* remove(N* n, int k) {
        assert(n != N::last);
        n->push();
        if (k == n->l->sz) {
            if (n->level == 1) {
                return n->r;
            }
            auto x = at0_with_remove(n->r);
            N* nn = x.first;
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

    template<class N>
    N* merge(N* l, N* r) {
        if (l == N::last) return r;
        if (r == N::last) return l;
        if (l->level == r->level) {
            auto x = at0_with_remove(r);
            N* n = x.first;
            n->push();
            n->r = x.second;
            n->l = l;
            n->level = l->level+1;
            n->update();
            return rightdown(n);
        }
        N* n;
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

    template<class N>
    pair<N*, N*> split(N* n, int k) {
        if (n == N::last) return {N::last, N::last};
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
}
