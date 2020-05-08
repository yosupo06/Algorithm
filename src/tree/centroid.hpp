#pragma once

struct Centroid {
    int r;
    VV<int> tr;
    V<int> par;
};

template <class E> struct CentroidExec : Centroid {
    int n;
    const VV<E>& g;
    V<bool> used;

    using P = pair<int, int>;
    V<P> info;  //(child max, child)

    int dfs(int p, int b) {
        int sz = 1;
        info[p] = P(0, -1);
        for (E e : g[p]) {
            int d = e.to;
            if (d == b || used[d]) continue;
            int csz = dfs(d, p);
            sz += csz;
            info[p] = max(info[p], P(csz, d));
        }
        return sz;
    }
    int init(int p, int b) {
        int sz = dfs(p, -1);
        while (info[p].first > sz / 2) p = info[p].second;
        par[p] = b;
        used[p] = true;
        for (E e : g[p]) {
            int d = e.to;
            if (used[d]) continue;
            tr[p].push_back(init(d, p));
        }
        return p;
    }
    CentroidExec(const VV<E>& _g) : n(int(_g.size())), g(_g), used(n), info(n) {
        tr = VV<int>(n);
        par = V<int>(n);
        r = init(0, -1);
    }
};

template <class E> Centroid get_centroid(const VV<E>& g) {
    return CentroidExec<E>(g);
}
