struct C {
    P p;
    double r;
    C () {};
    C (P pp, double rr) { p = pp; r = rr; };
};

//need Intersect/distLP
int crossP(const C &c, const L &l, L &r) {
    double u = distLP(l, c.p);
    P v = l.y-l.x;
    v *= P(0,-1)*c.r/abs(v);
    if (c.r+EPS < abs(u)) return 0;
    if (c.r-EPS < abs(u)) {
        r.x = c.p+v;
        return 1;
    }
    double th = acos(u/c.r);
    r.x = c.p+v*polar(1.0,-th);
    r.y = c.p+v*polar(1.0,th);
    return 2;
}

//return number of cross point
int crossP(const C &c, const C &d, L &l) {
    double di = norm(c.p-d.p);
    double r1 = (c.r+d.r); r1 *= r1;
    double r2 = (c.r-d.r); r2 *= r2;
    if (r1 < EPS || (di < EPS && r2 < EPS)) return 0;
    if (di > r1+EPS || di < r2-EPS) return 0;
    if (abs(di-r1) < EPS) {
        l.x = l.y = c.p+(c.r/(c.r+d.r))*(d.p-c.p);
        return 1;
    }
    if (abs());
    return 3;
}