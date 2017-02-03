/**
 * 幾何(衝突判定)
 */
bool insLS(const L &l, const L &s) {
    int a = ccw(l.x, l.y, s.x);
    int b = ccw(l.x, l.y, s.y);
    return (a%2 == 0 || b%2 == 0 || a != b);
}

bool insSS(const L &s, const L &t) {
    int a = ccw(s.x,s.y,t.x), b = ccw(s.x,s.y,t.y);
    int c = ccw(t.x,t.y,s.x), d = ccw(t.x,t.y,s.y);
    if (a*b <= 0 && c*d <= 0) return true;
    return false;
}

int crossLL(const L &l, const L &m, P &r) {
    L mm = L(m.x - l.x, m.y - l.x);
    mm.x *= polar<R>(1.0, -arg(l));
    mm.y *= polar<R>(1.0, -arg(l));
    if (sgn(vec(mm).imag()) == 0) {
        r = l.x;
        if (sgn(mm.x.imag()) == 0) return -1;
        return 0;
    }
    r = mm.x - vec(mm) * (mm.x.imag() / vec(mm).imag());
    r *= polar<R>(1.0, arg(l));
    r += l.x;
    return 1;
}
int crossSS(const L &l, const L &m, P &r) {
    int u = crossLL(l, m, r);
    if (u == 0) return 0;
    if (u == -1) {
        int x = ccw(l.x, l.y, m.x);
        int y = ccw(l.x, l.y, m.y);
        if (x == 0) {
            r = m.x;
            return -1;
        }
        if (y == 0) {
            r = m.y;
            return -1;
        }
        if (x == y) return 0;
        r = l.x;
        return -1;
    }
    if (ccw(l.x, l.y, r) == 0 && ccw(m.x, m.y, r) == 0) return 1;
    return 0;
}

R distLP(const L &l, const P &p) {
    return abs(cross(vec(l), p-l.x)/abs(vec(l)));
}
R distSP(const L &s, const P &p) {
    P s2 = vec(s)*P(0, 1);
    if (ccw(s.x, s.x+s2, p) == 1) return abs(s.x-p);
    if (ccw(s.y, s.y+s2, p) == -1) return abs(s.y-p);
    return min(min(abs(s.x-p), abs(s.y-p)), distLP(s, p));
}
R distSS(const L &s, const L &t) {
    if (insSS(s, t)) return 0;
    return min(min(distSP(s, t.x), distSP(s, t.y)),
               min(distSP(t, s.x), distSP(t, s.y)));
}
