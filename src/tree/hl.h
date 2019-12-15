#pragma once

#include "../base.h"

struct HL {
    // inside index of HL
    struct I {
        int i;
    };
    V<int> _ord;          // int -> I
    V<int> _rord;         // I -> int
    V<int> _big, _small;  // I -> I
    // optionals
    V<int> dps;       // node depth(int -> int)
    int pc = 0;       // path count(optional)
    V<int> pid, psz;  // path id, size (optional)
    V<int> _out;       // ouv[i] is end of subtree(I -> I)
    HL() {}
    HL(size_t n)
        : _ord(n), _rord(n), _big(n), _small(n), dps(n), pid(n), _out(n) {}
    I ord(int v) const { return v == -1 ? I{-1} : I{_ord[v]}; }
    int rord(I i) const { return i.i == -1 ? -1 : _rord[i.i]; }
    I par(I i) const { return I{_small[i.i] == i.i ? _big[i.i] : i.i - 1}; }
    I subtree_out(int v) const { return I{_out[ord(v).i]}; };
    int par(int v) const { return rord(par(ord(v))); }
    int lca(int a, int b) const {
        int ai = ord(a).i;
        int bi = ord(b).i;
        while (ai != bi) {
            if (ai > bi) swap(ai, bi);
            if (_small[bi] <= ai)
                break;
            else
                bi = _big[bi];
        }
        return rord(I{ai});
    }
    // aの直前までbから登る、f(I, I)の引数は両閉区間
    template <class F> void get_path(int a, int b, F f) const {
        int ai = ord(a).i;
        int bi = ord(b).i;
        while (ai < bi) {
            if (_small[bi] <= ai)
                f(I{ai + 1}, I{bi});
            else
                f(I{_small[bi]}, I{bi});
            bi = _big[bi];
        }
    }
    int to(int a, int b) {  // aからbの方向へ1移動する
        int ai = ord(a).i;
        int bi = ord(b).i;
        assert(ai < bi);
        while (true) {
            if (_small[bi] <= ai)
                return rord(I{ai + 1});
            else if (_big[bi] == ai)
                return rord(I{_small[bi]});
            bi = _big[bi];
        }
        assert(false);
    }
    int dist(int a, int b) const {
        int c = lca(a, b);
        return dps[a] + dps[b] - 2 * dps[c];
    }
};

template <class E> struct HLExec : HL {
    const VV<E>& g;
    V<int> tch;
    int id = 0;
    HLExec(const VV<E>& _g, int r) : HL(_g.size()), g(_g), tch(g.size(), -1) {
        assert(dfs_sz(r, -1) == int(g.size()));
        dfs(r, -1);
        init_extra();
    }
    void init_extra() {
        // ord, rord, big, small以外を使わないなら不要
        int n = int(g.size());

        // dps
        dps[rord(I{0})] = 0;
        for (int i = 1; i < n; i++) {
            dps[rord(I{i})] = dps[rord(par(I{i}))] + 1;
        }

        // pid, psz, pc
        int l = 0;
        while (l < n) {
            int r = l + 1;
            while (r < n && _small[r] == l) r++;
            psz.push_back(r - l);
            for (int i = l; i < r; i++) {
                pid[i] = pc;
            }
            l = r;
            pc++;
        }

        // out
        for (int i = n - 1; i >= 0; i--) {
            _out[i] = max(_out[i], i + 1);
            int p = ord(par(rord(I{i}))).i;
            if (p != -1) _out[p] = max(_out[p], _out[i]);
        }
    }
    int dfs_sz(int p, int b) {
        int sz = 1, msz = -1;
        for (auto e : g[p]) {
            if (e.to == b) continue;
            int u = dfs_sz(e.to, p);
            sz += u;
            if (msz < u) tie(tch[p], msz) = make_pair(e.to, u);
        }
        return sz;
    }
    void dfs(int p, int b) {
        int q = id++, bq = ord(b).i;
        _ord[p] = q;
        _rord[q] = p;
        if (b == -1 || bq != q - 1) {
            _small[q] = q;
            _big[q] = bq;
        } else {
            _small[q] = _small[bq];
            _big[q] = _big[bq];
        }
        if (tch[p] == -1) return;
        dfs(tch[p], p);
        for (auto e : g[p]) {
            if (e.to == b || e.to == tch[p]) continue;
            dfs(e.to, p);
        }
    }
};

template <class E> HL get_hl(const VV<E>& g, int r) { return HLExec<E>(g, r); }
