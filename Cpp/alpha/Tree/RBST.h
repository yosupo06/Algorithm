namespace RBST {
    uint xor128(){
        static uint x=123456789,y=362436069,z=521288629,w=88675123;
        uint t;
        t=(x^(x<<11));x=y;y=z;z=w; return( w=(w^(w>>19))^(t^(t>>8)) );
    }
    template<class N>
    static N* merge(N* l, N* r) {
        if (!l->sz) return r;
        if (!r->sz) return l; 
        l->push(); r->push();
        if ((int)(xor128() % (l->sz + r->sz)) < l->sz) {
            l->r = merge(l->r, r);
            return l->update();
        } else {
            r->l = merge(l, r->l);
            return r->update();
        }
    }
    template<class N>
    static pair<N*, N*> split(N* x, int k) {
        if (!x->sz) return {N::last, N::last};
        x->push();
        if (k <= x->l->sz) {
            auto y = split(x->l, k);
            x->l = y.second;
            y.second = x->update();
            return y;
        } else {
            auto y = split(x->r, k- x->l->sz -1);
            x->r = y.first;
            y.first = x->update();
            return y;
        }
    }
    template<class N>
    N* insert(N* n, int k, N* x) {
        auto u = split(n, k);
        return merge(merge(u.first, x), u.second);
    }
    template<class N>
    N* remove(N* n, int k) {
        auto u = split(n, k);
        return merge(u.first, split(u.second, 1).second);
    }
}
