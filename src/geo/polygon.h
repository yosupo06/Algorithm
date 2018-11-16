using Pol = V<P>;

D area2(const Pol& pol) {
    D u = 0;
    if (!pol.size()) return u;
    P a = pol.back();
    for (auto b : pol) u += crs(a, b), a = b;
    return u;
}

// 0: outside, 1: on line, 2: inside
int contains(const Pol& pol, P p) {
    if (!pol.size()) return 0;
    int in = -1;
    P _a, _b = pol.back();
    for (auto now : pol) {
        _a = _b;
        _b = now;
        P a = _a, b = _b;
        if (ccw(a, b, p) == 0) return 1;
        if (a.y > b.y) swap(a, b);
        if (!(a.y <= p.y && p.y < b.y)) continue;
        if (sgn(a.y, p.y) ? (crs(a - p, b - p) > 0) : (a.x > p.x)) in *= -1;
    }
    return in + 1;
}

// 0:P is out 1:P is on line 2:P is in
int contains(const Pol& pol, const L& l) {
    V<P> v = {l.s, l.t};
    P a, b = pol.back();
    for (auto now : pol) {
        a = b;
        b = now;
        P p;
        if (crossSS(L(a, b), l, p)) v.push_back(p);
    }
    sort(v.begin(), v.end(), [&](const P& x, const P& y) {
        return (l.s - x).rabs() < (l.s - y).rabs();
    });
    bool f = false;
    for (int i = 0; i < int(v.size()) - 1; i++) {
        P p = (v[i] + v[i + 1]) / D(2);
        int u = contains(pol, p);
        if (!u) return 0;
        if (u == 2) f = true;
    }
    if (f) return 2;
    return 1;
}

// p must be sorted and uniqued!
Pol convex_down(const V<P>& ps) {
    assert(ps.size() >= 2);
    Pol dw;
    for (P d : ps) {
        size_t n;
        while ((n = dw.size()) > 1) {
            // if (ccw(dw[n - 2], dw[n - 1], d) != -1) break; // line上も取る
            if (ccw(dw[n - 2], dw[n - 1], d) == 1) break;
            dw.pop_back();
        }
        dw.push_back(d);
    }
    return dw;
}

Pol convex(V<P> ps) {
    sort(ps.begin(), ps.end());
    ps.erase(unique(ps.begin(), ps.end()), ps.end());
    if (ps.size() <= 1) return ps;
    Pol dw = convex_down(ps);
    reverse(ps.begin(), ps.end());
    Pol up = convex_down(ps);
    dw.insert(dw.begin(), up.begin() + 1, up.end() - 1);
    return dw;
}

// スパゲッティソースをパクった、直線の左側の多角形を返却する
Pol convex_cut(const Pol& po, const L& l) {
    if (!po.size()) return Pol{};
    Pol q;
    P a, b = po.back();
    for (auto now : po) {
        a = b;
        b = now;
        if ((ccw(l, a) % 2) * (ccw(l, b) % 2) < 0) {
            P buf;
            crossLL(l, L(a, b), buf);
            q.push_back(buf);
        }
        if (ccw(l, b) != -1) q.push_back(b);
    }
    return q;
}

// pol must be convex
D diameter(const Pol& p) {
    int n = int(p.size());
    if (n == 2) return (p[1] - p[0]).abs();
    int x = 0, y = 0;
    for (int i = 1; i < n; i++) {
        if (p[i] < p[x]) x = i;
        if (p[y] < p[i]) y = i;
    }
    D ans = 0;
    int sx = x, sy = y;
    /*
    do {
        ...
    } while (sx != x || sy != y);
    で1周する
    */
    while (sx != y || sy != x) {
        ans = max(ans, (p[x] - p[y]).abs());
        int nx = (x + 1 < n) ? x + 1 : 0, ny = (y + 1 < n) ? y + 1 : 0;
        if (crs(p[nx] - p[x], p[ny] - p[y]) < 0)
            x = nx;
        else
            y = ny;
    }
    return ans;
}

///// ここからOLD

// // -1: cw, 0: line, 1: ccw
// int is_ccw(const Pol &p) {
//     return sgn(area2_noabs(p));
// }

// D area2(V<P> &p) {
//     D u = 0;
//     for (int i = 0; i < (int)p.size(); i++) {
//         u += cross(cu(p, i), cu(p, i+1));
//     }
//     return u;
// }

// D area_naive(const Pol &p) {
//     D u = 0;
//     for (int i = 0; i < (int)p.size(); i++) {
//         u += cross(cu(p, i), cu(p, i+1));
//     }
//     return u/2;
// }

// D area(const Pol &p) {
//     return abs(area_naive(p));
// }

// int contains(const Pol& pol, const L& l) {
//     int n = int(pol.size());
//     vector<P> v = {l.s, l.t};
//     for (int i = 0; i < n; i++) {
//         P a = pol[i], b = pol[(i + 1) % n];
//         P p;
//         if (crossSS(L(a, b), l, p)) {
//             v.push_back(p);
//         }
//     }

//     sort(v.begin(), v.end(), [&](const P& x, const P& y) {
//         return (l.s - x).abs() < (l.s - y).abs();
//     });

//     int sz = int(v.size());
//     for (int i = 0; i < sz - 1; i++) {
//         v.push_back((v[i] + v[i + 1]) / D(2));
//     }
//     bool f = false;
//     for (P p: v) {
//         int u = contains(pol, p);
//         if (!u) return 0;
//         if (u == 2) f = true;
//     }
//     if (f) return 2;
//     return 1;
// }
