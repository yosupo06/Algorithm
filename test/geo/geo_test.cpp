#include "gtest/gtest.h"
#include "base.h"
#include "util/ostream.h"
#include "util/random.h"
#include "geo/primitive.h"
#include "geo/intersect.h"
#include "geo/polygon.h"
#include "geo/circle.h"
#include "geo/graphiccompute.h"
#include "geo/delaunay.h"

TEST(GeoTest, CCW) {
    ASSERT_EQ(ccw(P(0, 0), P(2, 2), P(1, 1)), 0);
    ASSERT_EQ(ccw(P(0, 0), P(-2, 2), P(-1, 1)), 0);
    ASSERT_EQ(ccw(P(0, 0), P(2, -2), P(1, -1)), 0);
    ASSERT_EQ(ccw(P(0, 0), P(-2, -2), P(-1, -1)), 0);

    ASSERT_EQ(ccw(P(0, 0), P(2, 2), P(2, 2)), 0);
    ASSERT_EQ(ccw(P(0, 0), P(-2, 2), P(-2, 2)), 0);
    ASSERT_EQ(ccw(P(0, 0), P(2, -2), P(2, -2)), 0);
    ASSERT_EQ(ccw(P(0, 0), P(-2, -2), P(-2, -2)), 0);

    ASSERT_EQ(ccw(P(0, 0), P(-2, -2), P(-3, -3)), -2);
    ASSERT_EQ(ccw(P(0, 0), P(-2, -2), P(1, 1)), 2);
    ASSERT_EQ(ccw(P(0, 0), P(100, -100), P(1, 1)), 1);
    ASSERT_EQ(ccw(P(0, 0), P(-100, 100), P(1, 1)), -1);
}

TEST(GeoTest, CrossSS) {
    auto check = [](L l1, L l2, int expect) {
        P p;
        ASSERT_EQ(crossSS(l1, l2, p), expect);
        if (expect) {
            ASSERT_EQ(ccw(l1, p), 0);
            ASSERT_EQ(ccw(l2, p), 0);
        }
    };
    // 重複
    check(L(P(0, 0), P(0, 2)), L(P(0, 1), P(0, 3)), -1);
    check(L(P(0, 0), P(2, 0)), L(P(1, 0), P(3, 0)), -1);
    check(L(P(0, 0), P(2, 2)), L(P(1, 1), P(3, 3)), -1);
    check(L(P(0, 2), P(0, 0)), L(P(0, 1), P(0, 3)), -1);
    check(L(P(0, 0), P(0, 2)), L(P(0, 3), P(0, 1)), -1);
    check(L(P(0, 2), P(0, 0)), L(P(0, 3), P(0, 1)), -1);
    
    // 端点
    check(L(P(0, 2), P(0, 0)), L(P(0, 2), P(0, 3)), 1);
    check(L(P(0, 0), P(2, 0)), L(P(2, 0), P(3, 0)), 1);
    check(L(P(0, 0), P(2, 2)), L(P(2, 2), P(3, 3)), 1);

    // クロス
    check(L(P(0, 0), P(0, 2)), L(P(-1, 1), P(1, 1)), 1);
    check(L(P(0, 0), P(2, 2)), L(P(0, 2), P(2, 0)), 1);
    // クロスしない
    check(L(P(0, 0), P(2, 0)), L(P(0, 1), P(2, 1)), 0);
    check(L(P(0, 0), P(0, 2)), L(P(1, 0), P(1, 2)), 0);
    check(L(P(0, 0), P(2, 0)), L(P(1, 1), P(100, 100)), 0);
}

TEST(GeoTest, TangentCC) {
    struct Q {
        C c1, c2;
        int expect_inner, expect_outer;
    };

    V<Q> que;

    que.push_back(Q{C(P(0, 0), 1), C(P(0, 2), 1), 1, 2});
    que.push_back(Q{C(P(0, 0), 1), C(P(0, 3), 1), 2, 2});
    que.push_back(Q{C(P(0, 0), 1), C(P(2, 0), 1), 1, 2});
    que.push_back(Q{C(P(0, 0), 1), C(P(0, 3), 1), 2, 2});
    que.push_back(Q{C(P(0, 0), 3), C(P(0, 2), 1), 0, 1});
    que.push_back(Q{C(P(0, 0), 1), C(P(0, 2), 3), 0, 1});
    que.push_back(Q{C(P(0, 2), 1), C(P(0, 0), 3), 0, 1});
    que.push_back(Q{C(P(0, 0), 1), C(P(0, 0), 2), 0, 0});
    que.push_back(Q{C(P(0, 0), 2), C(P(0, 1), 2), 0, 2});
    que.push_back(Q{C(P(0, 0), 2), C(P(1, 0), 2), 0, 2});

    for (auto q: que) {
        C c1 = q.c1, c2 = q.c2;
        int expect_inner = q.expect_inner, expect_outer = q.expect_outer;
        L l1, l2;
        ASSERT_EQ(tangent(c1, c2, l1, l2, true), expect_inner);
        if (expect_inner == 2) {
            L buf;
            ASSERT_EQ(crossCL(c1, l1, buf), 1);
            ASSERT_EQ(crossCL(c1, l2, buf), 1);
            ASSERT_EQ(crossCL(c2, l1, buf), 1);
            ASSERT_EQ(crossCL(c2, l2, buf), 1);
        } else if (expect_inner == 1) {
            ASSERT_EQ(l1.s, l1.t);
            ASSERT_EQ(l1.t, l2.s);
            ASSERT_EQ(l2.s, l2.t);
            ASSERT_EQ(sgn((l1.s - c1.p).abs(), c1.r), 0);
            ASSERT_EQ(sgn((l1.s - c2.p).abs(), c2.r), 0);
        }
        ASSERT_EQ(tangent(c1, c2, l1, l2, false), expect_outer);
        if (expect_outer == 2) {
            L buf;
            ASSERT_EQ(crossCL(c1, l1, buf), 1);
            ASSERT_EQ(crossCL(c1, l2, buf), 1);
            ASSERT_EQ(crossCL(c2, l1, buf), 1);
            ASSERT_EQ(crossCL(c2, l2, buf), 1);
        } else if (expect_outer == 1) {
            ASSERT_EQ(l1.s, l1.t);
            ASSERT_EQ(l1.t, l2.s);
            ASSERT_EQ(l2.s, l2.t);
            ASSERT_EQ(sgn((l1.s - c1.p).abs(), c1.r), 0);
            ASSERT_EQ(sgn((l1.s - c2.p).abs(), c2.r), 0);
        }
    };
}

TEST(GeoTest, Diameter) {
    auto naive = [](Pol p) {
        int n = int(p.size());
        D ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                ans = max(ans, (p[i]-p[j]).abs());
            }
        }
        return ans;
    };
    auto check = [&](Pol p) {
        auto ans = naive(p);
        auto out = diameter(p);
        ASSERT_NEAR(ans, out, 1e-9);
    };

    check(Pol{P(0, 0), P(0, 1)});
    check(Pol{P(0, 0), P(1, 0)});
    check(Pol{P(0, 0), P(1, 1)});
    check(Pol{P(0, 0), P(-1, 1)});
    check(Pol{P(0, 0), P(1, -1)});
    check(Pol{P(0, 0), P(-1, -1)});

    check(Pol{P(0, 0), P(1, 1), P(-1, 1)});
    check(Pol{P(0, 0), P(1, 1), P(-1, 1), P(-2, 0)});
}

TEST(GeoTest, crossCC) {
    C c1 = C(P(0, 0), 2), c2 = C(P(2, 0), 2);
    D l, r;
    ASSERT_EQ(crossCC(c1, c2, l, r), 2);    
    P p1 = c1.p + P::polar(c1.r, l);
    P p2 = c1.p + P::polar(c1.r, r);
    if (p2 < p1) swap(p1, p2);
    ASSERT_NEAR(p1.x, 1, 1e-5);
    ASSERT_NEAR(p1.y, -1.73205080, 1e-5);
    ASSERT_NEAR(p2.x, 1, 1e-5);
    ASSERT_NEAR(p2.y, 1.73205080, 1e-5);
}

TEST(GeoTest, Convex) {
    auto check = [&](Pol p) {
        auto pol = convex(p);
        int m = int(pol.size());
        if (m == 1) {
            for (auto q: p) {
                ASSERT_TRUE(q == pol[0]);
            }
            return;
        }
        if (m == 2) {
            for (auto q: p) {
                ASSERT_EQ(ccw(pol[0], pol[1], q), 0);
            }
            return;
        }
        for (int i = 0; i < m; i++) {
            P a = pol[i], b = pol[(i+1)%m], c = pol[(i+2)%m];
            ASSERT_EQ(ccw(a, b, c), 1);
        }
        for (int i = 0; i < m; i++) {
            P a = pol[i], b = pol[(i+1)%m];
            for (auto q: p) {
                int buf = ccw(a, b, q);
                ASSERT_TRUE(buf == 0 || buf == 1);
            }
        }
        for (auto q: p) {
            ASSERT_TRUE(contains(pol, q) > 0);
        }
    };

    check(Pol{P(0, 0), P(0, 1)});
    check(Pol{P(0, 0), P(1, 0)});
    check(Pol{P(0, 0), P(1, 1)});
    check(Pol{P(0, 0), P(-1, 1)});
    check(Pol{P(0, 0), P(1, -1)});
    check(Pol{P(0, 0), P(-1, -1)});

    check(Pol{P(0, 0), P(1, 1), P(-1, 1)});
    check(Pol{P(0, 0), P(0, 1), P(0, 2), P(0, 3)});
    check(Pol{P(0, 0), P(0, 1), P(0, 0), P(0, 1)});
    check(Pol{P(0, 0), P(0, 2), P(2, 0), P(2, 2), P(1, 1)});
    check(Pol{P(0, 0), P(0, 2), P(2, 0), P(2, 2), P(0, 1)});
    check(Pol{P(0, 0), P(0, 2), P(2, 0), P(2, 2), P(1, 0)});
    check(Pol{P(0, 0), P(0, 2), P(2, 0), P(2, 2), P(2, 1)});
    check(Pol{P(0, 0), P(0, 2), P(2, 0), P(2, 2), P(1, 2)});
}

TEST(GeoTest, Area2) {
    ASSERT_NEAR(area2(Pol{P(0, 0), P(1, 0), P(1, 1), P(0, 1)}), 2, 1e-8);
    ASSERT_NEAR(area2(Pol{P(0, 0), P(0, 1), P(1, 1), P(1, 0)}), -2, 1e-8);
    ASSERT_NEAR(area2(Pol{}), 0, 1e-8);
}

TEST(GeoTest, Contain) {
    // AOJ GGL_3 sample
    Pol pol{P(0, 0), P(3, 1), P(2, 3), P(0, 3)};
    ASSERT_EQ(contains(pol, P(2, 1)), 2);
    ASSERT_EQ(contains(pol, P(0, 2)), 1);
    ASSERT_EQ(contains(pol, P(3, 2)), 0);

    ASSERT_EQ(contains(Pol{P(0, 2), P(0, 0), P(2, 0), P(2, 2)}, P(2, 1)), 1);
    ASSERT_EQ(contains(Pol{}, P(2, 1)), 0);
}

TEST(GeoTest, CircumCircle) {
    auto check = [&](P a, P b, P c) {
        ASSERT_NE(ccw(a, b, c) % 2, 0);
        C cir = circum_circle(a, b, c);
        ASSERT_NEAR(cir.r, (cir.p - a).abs(), 1e-8);
        ASSERT_NEAR(cir.r, (cir.p - b).abs(), 1e-8);
        ASSERT_NEAR(cir.r, (cir.p - c).abs(), 1e-8);
    };

    check(P(0, 0), P(0, 1), P(1, 0));
    check(P(0, 0), P(10, 0), P(5, 1));
    check(P(0, 0), P(10, 0), P(5, 5));
    check(P(0, 0), P(5, 10), P(-5, 10));
    check(P(4, 2), P(3, 1), P(8, -3));
}

TEST(GeoTest, SmallestCircle) {
    auto allin = [&](const V<P> &ps, C c) {
        for (auto p: ps) {
            if (sgn((c.p - p).abs(), c.r) == 1) return false;
        }
        return true;
    };
    auto naive = [&](const V<P> &ps) {
        int n = int(ps.size());
        C c = C(P(0, 0), 100000);
        auto ref = [&](C d) {
            if (!allin(ps, d)) return;
            if (d.r < c.r) c = d;
        };
        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                ref(C((ps[i] + ps[j]) / 2, (ps[i] - ps[j]).abs() / 2));
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                for (int k = j+1; k < n; k++) {
                    ref(circum_circle(ps[i], ps[j], ps[k]));
                }
            }
        }
        return c;
    };
    auto check = [&](const V<P> &ps) {
        C c1 = smallest_circle(ps);
        C c2 = naive(ps);
        ASSERT_TRUE(c1.p == c2.p);
        ASSERT_NEAR(c1.r, c2.r, 1e-6);
    };
    check(V<P>{P(0, 0), P(1, 0), P(0, 1)});
    check(V<P>{P(0, 0), P(1, 0), P(0, 1), P(1, 1)});
    check(V<P>{P(0, 0), P(10, 0), P(5, 1)});
    check(V<P>{P(0, 0), P(10, 0), P(5, -1)});
    check(V<P>{P(0, 0), P(10, 0), P(5, 1), P(5, -1)});
    check(V<P>{P(0, 0), P(2, 0), P(0, 2), P(2, 2), P(1, 1)});
    check(V<P>{P(0, 0), P(3, 5), P(9, 15)});
    check(V<P>{P(0, 0), P(1, 8)});
}

TEST(GeoTest, Delaunay) {
    auto check = [&](const V<P> &ps) {
        int n = int(ps.size());
        auto g = delaunay(ps);
        for (int i = 0; i < n; i++) {
            if (g[i].back() == n) g[i].pop_back();
            for (int j: g[i]) {
                for (int k = 0; k < n; k++) {
                    for (int l = 0; l < n; l++) {
                        if (ccw(ps[i], ps[j], ps[k]) != 1) continue;
                        if (ccw(ps[i], ps[j], ps[l]) != -1) continue;
                        auto c = circum_circle(ps[i], ps[j], ps[k]);
                        ASSERT_NE(sgn((ps[l]-c.p).abs(), c.r), -1);
                    }
                }
            }
        }
    };
    check(V<P>{P(0, 0), P(1, 0), P(0, 1)});
    check(V<P>{P(0, 0), P(1, 0), P(0, 1), P(1, 1)});
    check(V<P>{P(0, 0), P(10, 0), P(5, 1)});
    check(V<P>{P(0, 0), P(10, 0), P(5, -1)});
    check(V<P>{P(0, 0), P(10, 0), P(5, 1), P(5, -1)});
    check(V<P>{P(0, 0), P(2, 0), P(0, 2), P(2, 2), P(1, 1)});
    check(V<P>{P(0, 0), P(3, 5), P(9, 15)});
    check(V<P>{P(0, 0), P(1, 8)});
    check(V<P>{P(-10, 9), P(10, -5), P(0, 7)});
    check(V<P>{P(-10, 9), P(0, 7), P(10, -5)});
    check(V<P>{P(-4, 6), P(-2, 3), P(1, -6), P(9, -3)});
    check(V<P>{P(0, 0), P(0, 1)});
    check(V<P>{P(0, 0), P(0, 1), P(0, 2)});
    check(V<P>{P(6, 8), P(-10, -10), P(-3, -1), P(-3, 0)});
    for (int ph = 0; ph < 1000; ph++) {
        auto n = rand_int(2, 15);
        V<P> ps(n);
        for (int i = 0; i < n; i++) {
            D x = rand_int(-100, 100);
            D y = rand_int(-100, 100);
            ps[i] = P(x, y);
        }
        sort(begin(ps), end(ps));
        ps.erase(unique(begin(ps), end(ps)), end(ps));
        random_shuffle(begin(ps), end(ps));
        if (ps.size() == 1) continue;
        check(ps);
    }
}

TEST(GeoTest, InsAreaPolC) {
    // AOJ CGL_7_H sample
    {
        C c = C(P(0, 0), 5);
        Pol po = Pol{P(1, 1), P(4, 1), P(5, 5)};
        ASSERT_NEAR(area2CPol(c, po), 2 * 4.639858417607, 1e-6);
    }
    {
        C c = C(P(1, 1), 5);
        Pol po = Pol{P(2, 2), P(5, 2), P(6, 6)};
        ASSERT_NEAR(area2CPol(c, po), 2 * 4.639858417607, 1e-6);
    }
    {
        C c = C(P(0, 0), 5);
        Pol po = Pol{P(0, 0), P(-3, -6), P(1, -3), P(5, -4)};
        ASSERT_NEAR(area2CPol(c, po), 2 * 11.787686807576, 1e-6);
    }
    {        
        C c = C(P(0, 0), 5);
        Pol po = Pol{P(0, -2), P(-5, 3), P(0, -7)};
        ASSERT_NEAR(area2CPol(c, po), 2 * 11.3253235476, 1e-6);
    }
}

TEST(GeoTest, distSS) {
    // AOJ CGL_2_D sample
    {
        L l1 = L(P(0, 0), P(1, 0));
        L l2 = L(P(0, 1), P(1, 1));
        ASSERT_NEAR(distSS(l1, l2), 1, 1e-6);
    }
    {
        L l1 = L(P(0, 0), P(1, 0));
        L l2 = L(P(2, 1), P(1, 2));
        ASSERT_NEAR(distSS(l1, l2), 1.4142135624, 1e-6);
    }
    {
        L l1 = L(P(-1, 0), P(1, 0));
        L l2 = L(P(0, 1), P(0, -1));
        ASSERT_NEAR(distSS(l1, l2), 0, 1e-6);
    }
}

TEST(GeoTest, crossCL) {
    {
        C c = C(P(0, 0), 5);
        L l = L(P(5, 5), P(1, 1));
        L r;
        ASSERT_EQ(crossCL(c, l, r), 2);
        D x = 3.535533905932;
        ASSERT_NEAR((r.s - P(x, x)).abs(), 0, 1e-6);
        ASSERT_NEAR((r.t - P(-x, -x)).abs(), 0, 1e-6);
    }
}

TEST(GeoTest, HalfPlaneIntersec) {
    auto eq_vl = [&](V<L> a, V<L> b) {
        if (a.size() != b.size()) return false;
        if (!a.size()) return true;
        int n = int(a.size());
        for (int i = 0; i < n; i++) {
            bool f = true;
            for (int j = 0; j < n; j++) {
                if (a[j].s != b[j].s) f = false;
                if (a[j].t != b[j].t) f = false;
            }
            if (f) return true;
            rotate(a.begin(), a.begin()+1, a.end());
        }
        return false;
    };
    {
        V<L> lines;
        lines.push_back(L{P(0, 1), P(1, 1)});
        lines.push_back(L{P(1, 1), P(1, 0)});
        lines.push_back(L{P(1, 0), P(0, 0)});
        lines.push_back(L{P(0, 0), P(0, 1)});
        ASSERT_PRED2(eq_vl, halfplane_intersects(lines), V<L>{});
    }
    {
        V<L> lines;
        lines.push_back(L{P(2, 0), P(0, 0)});
        lines.push_back(L{P(0, 0), P(1, 2)});
        lines.push_back(L{P(1, 2), P(2, 0)});
        ASSERT_PRED2(eq_vl, halfplane_intersects(lines), V<L>{});
    }
}
