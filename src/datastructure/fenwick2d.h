#pragma once

#include "base.h"
#include "datastructure/fenwick.h"

template <class D, class I> struct Fenwick2D {
    using P = pair<I, I>;
    V<P> points;
    VV<I> ys;
    V<Fenwick<D>> fws;
    int lg, sz;
    Fenwick2D(V<P> _points) : points(_points) {
        sort(points.begin(), points.end());
        points.erase(unique(points.begin(), points.end()), points.end());
        int n = int(points.size());
        lg = 1;
        while ((1 << lg) < n) lg++;
        sz = 1 << lg;
        ys = VV<I>(2 * sz);
        for (int i = 0; i < n; i++) ys[sz + i].push_back(points[i].second);
        for (int i = sz - 1; i >= 1; i--) {
            ys[i] = V<I>(ys[2 * i].size() + ys[2 * i + 1].size());
            merge(ys[2 * i].begin(), ys[2 * i].end(), ys[2 * i + 1].begin(),
                  ys[2 * i + 1].end(), ys[i].begin());
        }
        fws = V<Fenwick<D>>(2 * sz);
        for (int i = 1; i < 2 * sz; i++) {
            fws[i] = Fenwick<D>(int(ys[i].size()));
        }
    }

    void add(P p, D x) {
        int k =
            int(lower_bound(points.begin(), points.end(), p) - points.begin());
        k += sz;
        while (k) {
            int yid = int(lower_bound(ys[k].begin(), ys[k].end(), p.second) -
                          ys[k].begin());
            fws[k].add(yid, x);
            k >>= 1;
        }
    }

    D sum(int a, int b, I lw, I up, int l, int r, int k) {
        if (b <= l || r <= a) return D(0);
        if (a <= l && r <= b) {
            int lid = int(lower_bound(ys[k].begin(), ys[k].end(), lw) -
                          ys[k].begin());
            int uid = int(lower_bound(ys[k].begin(), ys[k].end(), up) -
                          ys[k].begin());
            return fws[k].sum(lid, uid);
        }
        int mid = (l + r) / 2;
        return sum(a, b, lw, up, l, mid, 2 * k) +
               sum(a, b, lw, up, mid, r, 2 * k + 1);
    }

    D sum(P lw, P up) {
        int a = int(lower_bound(points.begin(), points.end(), lw.first,
                                [&](P p, I x) { return p.first < x; }) -
                    points.begin());
        int b = int(lower_bound(points.begin(), points.end(), up.first,
                                [&](P p, I x) { return p.first < x; }) -
                    points.begin());
        return sum(a, b, lw.second, up.second, 0, sz, 1);
    }
};
