using Pol = V<P>;

D area2(const Pol& pol) {
    D u = 0;
    if (!pol.size()) return u;
    P a = pol.back();
    for (auto b : pol) u += crs(a, b), a = b;
    return u;
}

// (1:left) | (2: right) is inside between v[i] ~ v[i + 1]
V<pair<P, int>> insPolL(Pol pol, L l) {
    using Pi = pair<P, int>;
    V<Pi> v;
    P a, b = pol.back();
    for (auto now: pol) {
        a = b; b = now;
        P p;
        if (crossLL({a, b}, l, p) != 1) continue;
        int sa = ccw(l, a) % 2, sb = ccw(l, b) % 2;
        if (sa > sb) swap(sa, sb);
        if (sa != 1 && sb == 1) v.push_back({p, 1});
        if (sa == -1 && sb != -1) v.push_back({p, 2});
    }
    sort(v.begin(), v.end(), [&](Pi x, Pi y){
        return dot(l.vec(), x.first - l.s) < dot(l.vec(), y.first - l.s);
    });
    int m = int(v.size());
    V<Pi> res;
    for (int i = 0; i < m; i++) {
        if (i) v[i].second ^= v[i - 1].second;
        if (!res.empty() && res.back().first == v[i].first) res.pop_back();
        res.push_back(v[i]);
    }
    return res;
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
