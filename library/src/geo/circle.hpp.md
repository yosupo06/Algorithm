---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :warning: src/geo/circle.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#0a5d4e383899a81c6f7ba383cf1d6fea">src/geo</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/geo/circle.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct C {
    P p;
    D r;
    C(P _p = P(), D _r = D()) : p(_p), r(_r) {}
};

// need Intersect/distLP, r.sはよりl.sに近い
int crossCL(const C& c, const L& l, L& r) {
    D u = distLP(l, c.p);
    int si = sgn(u, c.r);
    if (si == 1) return 0;
    P v = project(l, c.p);
    P di = (si == 0) ? P(0, 0) : l.vec() * (sqrt(c.r * c.r - u * u) / l.abs());
    r = L(v - di, v + di);
    if (si == 0) return 1;
    return 2;
}

// need Intersect/distLP, r.sはよりl.sに近い
int crossCS(const C& c, const L& s, L& l) {
    if (!crossCL(c, s, l)) return 0;
    bool f1 = !ccw(s, l.s), f2 = !ccw(s, l.t);
    if (f1 && f2) return 2;
    if (!f1 && !f2) return 0;
    if (f1)
        l.t = l.s;
    else
        l.s = l.t;
    return 1;
}

// return number of cross point
// l, rはcから見た交点の角度、[l, r]がdに覆われている
int crossCC(const C& c, const C& d, D& l, D& r) {
    if (c.p == d.p) {
        assert(sgn(c.r - d.r));  // prohibit same circles
        return 0;
    }
    D di = (c.p - d.p).abs(), bth = (d.p - c.p).arg();
    D costh = (c.r * c.r + di * di - d.r * d.r) / (2 * c.r * di);
    int ty = min(sgn(c.r + d.r, di), sgn(di, abs(c.r - d.r)));
    if (ty == -1) return 0;
    if (ty == 0) costh = sgn(costh);
    D th = acos(costh);
    l = bth - th;
    r = bth + th;
    return ty + 1;
}

// pからcに接線を引く，交点はp1, p2
int tangent(const C& c, const P& p, P& p1, P& p2) {
    D di = (c.p - p).abs();
    int si = sgn(c.r, di);
    if (si == 1) return 0;
    D th = acos(min(D(1), c.r / di));
    D ar = (p - c.p).arg();
    p1 = c.p + P::polar(c.r, ar - th);
    p2 = c.p + P::polar(c.r, ar + th);
    if (si == 0) return 1;
    return 2;
}

//共通接線
int tangent(const C& c, const C& d, L& l, L& r, bool inter) {
    D di = (d.p - c.p).abs(), ar = (d.p - c.p).arg();
    if (sgn(di) == 0) {
        assert(sgn(c.r - d.r));  // prohibit same circles
        return 0;
    }
    D costh = c.r + (inter ? d.r : -d.r);
    int si = sgn(abs(costh), di);
    costh /= di;
    if (si == 1)
        return 0;
    else if (si == 0)
        costh = sgn(costh);
    D th = acos(costh);
    P base;
    base = P::polar(1, ar - th);
    l = L(c.p + base * c.r, d.p + base * d.r * (inter ? -1 : 1));
    base = P::polar(1, ar + th);
    r = L(c.p + base * c.r, d.p + base * d.r * (inter ? -1 : 1));
    if (si == 0) return 1;
    return 2;
}

C circum_circle(P a, P b, P c) {
    b -= a;
    c -= a;
    D s = 2 * crs(b, c);
    D x = (b - c).norm(), y = c.norm(), z = b.norm();
    D S = x + y + z;
    P r = (b * (S - 2 * y) * y + c * z * (S - 2 * z)) / (s * s);
    return C(r + a, r.abs());
}

C smallest_circle(const Pol& p, int i, array<P, 3> q, int j) {
    if (i == int(p.size())) {
        switch (j) {
            case 0:
                return C(P(0, 0), -1);
            case 1:
                return C(q[0], 0);
            case 2:
                return C((q[0] + q[1]) / D(2.0), (q[0] - q[1]).abs() / D(2.0));
            case 3:
                return circum_circle(q[0], q[1], q[2]);
        }
        assert(false);
    }
    C c = smallest_circle(p, i + 1, q, j);
    if (sgn((p[i] - c.p).abs(), c.r) == 1) {
        q[j] = p[i];
        return smallest_circle(p, i + 1, q, j + 1);
    }
    return c;
}
C smallest_circle(Pol p) {
    random_shuffle(begin(p), end(p));
    return smallest_circle(p, 0, array<P, 3>(), 0);
}

// C(P(0, 0), r)とTri((0, 0), a, b)の共有面積
D area2CT(const C& c, const P& _a, const P& _b) {
    P a = _a - c.p, b = _b - c.p;
    D r = c.r;
    if (a == b) return 0;
    auto single = [&](P x, P y, bool tri) {
        if (tri)
            return crs(x, y);
        else
            return r * r * ((y * P(x.x, -x.y)).arg());
    };
    bool ia = sgn(a.abs(), r) != 1, ib = sgn(b.abs(), r) != 1;
    if (ia && ib) return single(a, b, true);
    L l;
    if (!crossCS(C(P(0, 0), r), L(a, b), l)) return single(a, b, false);
    return single(a, l.s, ia) + single(l.s, l.t, true) + single(l.t, b, ib);
}

// p, cの共有面積
D area2CPol(const C& c, const Pol& po) {
    D sm = 0;
    P a, b = po.back();
    for (auto p : po) {
        a = b;
        b = p;
        sm += area2CT(c, a, b);
    }
    return sm;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/geo/circle.hpp"
struct C {
    P p;
    D r;
    C(P _p = P(), D _r = D()) : p(_p), r(_r) {}
};

// need Intersect/distLP, r.sはよりl.sに近い
int crossCL(const C& c, const L& l, L& r) {
    D u = distLP(l, c.p);
    int si = sgn(u, c.r);
    if (si == 1) return 0;
    P v = project(l, c.p);
    P di = (si == 0) ? P(0, 0) : l.vec() * (sqrt(c.r * c.r - u * u) / l.abs());
    r = L(v - di, v + di);
    if (si == 0) return 1;
    return 2;
}

// need Intersect/distLP, r.sはよりl.sに近い
int crossCS(const C& c, const L& s, L& l) {
    if (!crossCL(c, s, l)) return 0;
    bool f1 = !ccw(s, l.s), f2 = !ccw(s, l.t);
    if (f1 && f2) return 2;
    if (!f1 && !f2) return 0;
    if (f1)
        l.t = l.s;
    else
        l.s = l.t;
    return 1;
}

// return number of cross point
// l, rはcから見た交点の角度、[l, r]がdに覆われている
int crossCC(const C& c, const C& d, D& l, D& r) {
    if (c.p == d.p) {
        assert(sgn(c.r - d.r));  // prohibit same circles
        return 0;
    }
    D di = (c.p - d.p).abs(), bth = (d.p - c.p).arg();
    D costh = (c.r * c.r + di * di - d.r * d.r) / (2 * c.r * di);
    int ty = min(sgn(c.r + d.r, di), sgn(di, abs(c.r - d.r)));
    if (ty == -1) return 0;
    if (ty == 0) costh = sgn(costh);
    D th = acos(costh);
    l = bth - th;
    r = bth + th;
    return ty + 1;
}

// pからcに接線を引く，交点はp1, p2
int tangent(const C& c, const P& p, P& p1, P& p2) {
    D di = (c.p - p).abs();
    int si = sgn(c.r, di);
    if (si == 1) return 0;
    D th = acos(min(D(1), c.r / di));
    D ar = (p - c.p).arg();
    p1 = c.p + P::polar(c.r, ar - th);
    p2 = c.p + P::polar(c.r, ar + th);
    if (si == 0) return 1;
    return 2;
}

//共通接線
int tangent(const C& c, const C& d, L& l, L& r, bool inter) {
    D di = (d.p - c.p).abs(), ar = (d.p - c.p).arg();
    if (sgn(di) == 0) {
        assert(sgn(c.r - d.r));  // prohibit same circles
        return 0;
    }
    D costh = c.r + (inter ? d.r : -d.r);
    int si = sgn(abs(costh), di);
    costh /= di;
    if (si == 1)
        return 0;
    else if (si == 0)
        costh = sgn(costh);
    D th = acos(costh);
    P base;
    base = P::polar(1, ar - th);
    l = L(c.p + base * c.r, d.p + base * d.r * (inter ? -1 : 1));
    base = P::polar(1, ar + th);
    r = L(c.p + base * c.r, d.p + base * d.r * (inter ? -1 : 1));
    if (si == 0) return 1;
    return 2;
}

C circum_circle(P a, P b, P c) {
    b -= a;
    c -= a;
    D s = 2 * crs(b, c);
    D x = (b - c).norm(), y = c.norm(), z = b.norm();
    D S = x + y + z;
    P r = (b * (S - 2 * y) * y + c * z * (S - 2 * z)) / (s * s);
    return C(r + a, r.abs());
}

C smallest_circle(const Pol& p, int i, array<P, 3> q, int j) {
    if (i == int(p.size())) {
        switch (j) {
            case 0:
                return C(P(0, 0), -1);
            case 1:
                return C(q[0], 0);
            case 2:
                return C((q[0] + q[1]) / D(2.0), (q[0] - q[1]).abs() / D(2.0));
            case 3:
                return circum_circle(q[0], q[1], q[2]);
        }
        assert(false);
    }
    C c = smallest_circle(p, i + 1, q, j);
    if (sgn((p[i] - c.p).abs(), c.r) == 1) {
        q[j] = p[i];
        return smallest_circle(p, i + 1, q, j + 1);
    }
    return c;
}
C smallest_circle(Pol p) {
    random_shuffle(begin(p), end(p));
    return smallest_circle(p, 0, array<P, 3>(), 0);
}

// C(P(0, 0), r)とTri((0, 0), a, b)の共有面積
D area2CT(const C& c, const P& _a, const P& _b) {
    P a = _a - c.p, b = _b - c.p;
    D r = c.r;
    if (a == b) return 0;
    auto single = [&](P x, P y, bool tri) {
        if (tri)
            return crs(x, y);
        else
            return r * r * ((y * P(x.x, -x.y)).arg());
    };
    bool ia = sgn(a.abs(), r) != 1, ib = sgn(b.abs(), r) != 1;
    if (ia && ib) return single(a, b, true);
    L l;
    if (!crossCS(C(P(0, 0), r), L(a, b), l)) return single(a, b, false);
    return single(a, l.s, ia) + single(l.s, l.t, true) + single(l.t, b, ib);
}

// p, cの共有面積
D area2CPol(const C& c, const Pol& po) {
    D sm = 0;
    P a, b = po.back();
    for (auto p : po) {
        a = b;
        b = p;
        sm += area2CT(c, a, b);
    }
    return sm;
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

