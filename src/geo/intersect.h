/**
 * 幾何(衝突判定)
 */

P project(const L& l, const P& p) {
    P v = l.vec();
    return l.s + v * dot(v, p - l.s) / v.norm();
}

bool insSL(const L& s, const L& l) {
    int a = ccw(l, s.s), b = ccw(l, s.t);
    return (a % 2 == 0 || b % 2 == 0 || a != b);
}

bool insSS(const L& s, const L& t) {
    int a = ccw(s, t.s), b = ccw(s, t.t);
    int c = ccw(t, s.s), d = ccw(t, s.t);
    if (a * b <= 0 && c * d <= 0) return true;
    return false;
}

D distLP(const L& l, const P& p) {
    return abs(crs(l.vec(), p - l.s)) / l.abs();
}

D distSP(const L& s, const P& p) {
    P q = project(s, p);
    if (ccw(s, q) == 0)
        return (p - q).abs();
    else
        return min((s.s - p).abs(), (s.t - p).abs());
}

D distSS(const L& s, const L& t) {
    if (insSS(s, t)) return 0;
    return min(
        {distSP(s, t.s), distSP(s, t.t), distSP(t, s.s), distSP(t, s.t)});
}

int crossLL(const L& l, const L& m, P& r) {
    D cr1 = crs(l.vec(), m.vec()), cr2 = crs(l.vec(), l.t - m.s);
    if (sgncrs(l.vec(), m.vec()) == 0) {
        r = l.s;
        if (sgncrs(l.vec(), l.t - m.s)) return 0;
        return -1;
    }
    r = m.s + m.vec() * cr2 / cr1;
    return 1;
}

int crossSS(L l, L m, P& r) {
    int u = crossLL(l, m, r);
    if (u == 0) return 0;
    if (u == -1) {
        r = max(min(l.s, l.t), min(m.s, m.t));
        P q = min(max(l.s, l.t), max(m.s, m.t));
        return (q < r) ? 0 : (q == r ? 1 : -1);
    }
    if (ccw(l, r) == 0 && ccw(m, r) == 0) return 1;
    return 0;
}
