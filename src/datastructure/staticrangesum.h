#pragma once

#include "base.h"

template <class D, class I> struct StaticRangeSum {
    struct P {
        I x, y;
        D val;
    };
    int lg;
    V<I> xs, ys;

    V<int> mid;
    VV<int> bits;
    VV<D> sums;

    StaticRangeSum(V<P> ps) {
        if (!ps.size()) return;
        sort(ps.begin(), ps.end(), [&](P l, P r) { return l.x < r.x; });
        for (auto p : ps) {
            xs.push_back(p.x);
            ys.push_back(p.y);
        }
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());

        int n = int(xs.size());
        int m = int(ys.size());

        lg = 1;
        while ((1 << lg) < m) lg++;

        mid = V<int>(lg);
        bits = VV<int>(lg, V<int>(n + 1));
        sums = VV<D>(lg + 1, V<D>(n + 1));

        struct Q {
            int y;
            D val;
        };
        V<Q> v;
        for (auto p: ps) {
            int y = int(lower_bound(ys.begin(), ys.end(), p.y) - ys.begin());
            v.push_back({y, p.val});
        }
        for (int i = 0; i < n; i++) {
            Q q = v[i];
            sums[lg][i + 1] = sums[lg][i] + q.val;
        }
        for (int lv = lg - 1; lv >= 0; lv--) {
            array<V<Q>, 2> nx;
            for (int i = 0; i < n; i++) {
                Q q = v[i];
                bool f = (q.y >> lv) & 1;                
                bits[lv][i + 1] = bits[lv][i] + (f ? 0 : 1);
                nx[f].push_back(q);
            }
            mid[lv] = int(nx[0].size());
            v.clear();
            v.insert(v.end(), nx[0].begin(), nx[0].end());
            v.insert(v.end(), nx[1].begin(), nx[1].end());
            for (int i = 0; i < n; i++) {
                Q q = v[i];
                sums[lv][i + 1] = sums[lv][i] + q.val;
            }
        }
    }
    D sum(int l, int r, int u) {
        if (u == (1 << lg)) return sums[lg][r] - sums[lg][l];
        D ans = 0;
        for (int lv = lg - 1; lv >= 0; lv--) {
            bool f = (u >> lv) & 1;
            int l0 = bits[lv][l], r0 = bits[lv][r];
            if (f) {
                ans += sums[lv][r0] - sums[lv][l0];
                l = l - l0 + mid[lv];
                r = r - r0 + mid[lv];
            } else {
                l = l0;
                r = r0;
            }
        }
        return ans;
    }
    D sum(I _lx, I _ly, I _ux, I _uy) {
        assert(_lx <= _ux && _ly <= _uy);
        int lx = int(lower_bound(xs.begin(), xs.end(), _lx) - xs.begin());
        int ux = int(lower_bound(xs.begin(), xs.end(), _ux) - xs.begin());
        int ly = int(lower_bound(ys.begin(), ys.end(), _ly) - ys.begin());
        int uy = int(lower_bound(ys.begin(), ys.end(), _uy) - ys.begin());
        if (lx == ux || ly == uy) return D(0);
        return sum(lx, ux, uy) - sum(lx, ux, ly);
    }
};
