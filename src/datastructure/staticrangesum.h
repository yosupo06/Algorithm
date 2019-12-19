#pragma once

#include "base.h"

template <class D, class I> struct StaticRangeSum {
    struct P {
        I x, y;
        D val;
    };
    int sz;
    V<I> xs, ys;
    VV<int> yls, yrs;
    VV<D> sums;
    StaticRangeSum(V<P> ps) {
        assert(ps.size());
        for (auto p : ps) xs.push_back(p.x);
        for (auto p : ps) ys.push_back(p.y);
        sort(xs.begin(), xs.end());
        sort(ys.begin(), ys.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());

        int n = int(xs.size());
        int lg = 1;
        while ((1 << lg) < n) lg++;
        sz = 1 << lg;

        struct Q {
            I y;
            D val;
            int f;
        };
        VV<Q> buf(2 * sz);
        sort(ps.begin(), ps.end(),
             [&](P l, P r) { return tie(l.x, l.y) < tie(r.x, r.y); });
        int id = sz;
        for (auto p : ps) {
            if (xs[id - sz] != p.x) id++;
            if (buf[id].size() && buf[id].back().y == p.y) {
                buf[id].back().val += p.val;
            } else {
                buf[id].push_back({p.y, p.val, 0});
            }
        }

        yls = yrs = VV<int>(2 * sz);
        sums = VV<D>(2 * sz);
        for (int i = sz; i < 2 * sz; i++) {
            int m = int(buf[i].size());
            sums[i] = V<D>(m + 1);
            for (int j = 0; j < m; j++) {
                sums[i][j + 1] = sums[i][j] + buf[i][j].val;
            }
        }
        for (int i = sz - 1; i >= 1; i--) {
            auto& lb = buf[2 * i];
            auto& rb = buf[2 * i + 1];
            for (auto& p : lb) p.f = 1;
            for (auto& p : rb) p.f = 2;
            V<Q> nbuf(lb.size() + rb.size());
            merge(lb.begin(), lb.end(), rb.begin(), rb.end(), nbuf.begin(),
                  [&](Q l, Q r) { return l.y < r.y; });
            lb = rb = V<Q>();
            for (auto p : nbuf) {
                if (buf[i].size() && buf[i].back().y == p.y) {
                    buf[i].back().val += p.val;
                    buf[i].back().f |= p.f;
                    continue;
                }
                buf[i].push_back(p);
            }
            int m = int(buf[i].size());
            yls[i] = yrs[i] = V<int>(m + 1);
            sums[i] = V<D>(m + 1);
            for (int j = 0; j < m; j++) {
                yls[i][j + 1] = yls[i][j] + (buf[i][j].f & 1);
                yrs[i][j + 1] = yrs[i][j] + ((buf[i][j].f >> 1) & 1);
                sums[i][j + 1] = sums[i][j] + buf[i][j].val;
            }
        }
    }

    D sum(I _lx, I _ly, I _ux, I _uy) {
        assert(_lx <= _ux && _ly <= _uy);
        int lx = int(lower_bound(xs.begin(), xs.end(), _lx) - xs.begin());
        int ux = int(lower_bound(xs.begin(), xs.end(), _ux) - xs.begin());
        int ly = int(lower_bound(ys.begin(), ys.end(), _ly) - ys.begin());
        int uy = int(lower_bound(ys.begin(), ys.end(), _uy) - ys.begin());
        if (lx == ux || ly == uy) return D(0);
        int l = 0, r = sz, k = 1;
        while (true) {
            if (lx == l && ux == r) return sums[k][uy] - sums[k][ly];
            int md = (l + r) / 2;
            if (ux <= md) {
                ly = yls[k][ly];
                uy = yls[k][uy];
                r = md;
                k = 2 * k;
                continue;
            }
            if (md <= lx) {
                ly = yrs[k][ly];
                uy = yrs[k][uy];
                l = md;
                k = 2 * k + 1;
                continue;
            }
            D ans = 0;
            {
                int nk = 2 * k, nl = l, nr = md;
                int nly = yls[k][ly], nuy = yls[k][uy];
                while (true) {
                    if (lx == nl) {
                        ans += sums[nk][nuy] - sums[nk][nly];
                        break;
                    }
                    int nmd = (nl + nr) / 2;
                    if (lx < nmd) {
                        ans += sums[2 * nk + 1][yrs[nk][nuy]] -
                               sums[2 * nk + 1][yrs[nk][nly]];
                        nly = yls[nk][nly];
                        nuy = yls[nk][nuy];
                        nr = nmd;
                        nk = 2 * nk;
                    } else {
                        nly = yrs[nk][nly];
                        nuy = yrs[nk][nuy];
                        nl = nmd;
                        nk = 2 * nk + 1;
                    }
                }
            }
            {
                int nk = 2 * k + 1, nl = md, nr = r;
                int nly = yrs[k][ly], nuy = yrs[k][uy];
                while (true) {
                    if (ux == nr) {
                        ans += sums[nk][nuy] - sums[nk][nly];
                        break;
                    }
                    int nmd = (nl + nr) / 2;
                    if (nmd < ux) {
                        ans += sums[2 * nk][yls[nk][nuy]] -
                               sums[2 * nk][yls[nk][nly]];
                        nly = yrs[nk][nly];
                        nuy = yrs[nk][nuy];
                        nl = nmd;
                        nk = 2 * nk + 1;
                    } else {
                        nly = yls[nk][nly];
                        nuy = yls[nk][nuy];
                        nr = nmd;
                        nk = 2 * nk;
                    }
                }
            }
            return ans;
        }
    }
};
