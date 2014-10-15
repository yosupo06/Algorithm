bool insLL(const L &l, const L &m) {
    if (abs(cross(l.y-l.x, m.y-m.x)) > EPS) return true;
    if (abs(cross(l.y-l.x, m.y-l.x)) < EPS) return true;
    return false;
}

bool insLS(const L &l, const L &s) {
    double a = cross(l.y-l.x, s.x-l.x);
    double b = cross(l.y-l.x, s.y-l.x);
    if ((a<EPS&&-EPS<b)||(b<EPS&&-EPS<a)) return true;
    return false;
}

bool insSP(const L &s, P p) {
    return abs(s.x-p)+abs(s.y-p)+abs(s.y-s.x) < EPS;
}

bool insSS(const L &s, const L &t) {
    int a = ccw(s.x,s.y,t.x), b = ccw(s.x,s.y,t.y);
    int c = ccw(t.x,t.y,s.x), d = ccw(t.x,t.y,s.y);
    if (a*b <= 0 && c*d <= 0) return true;
    return false;
}

bool insPP(P p, P q) {
    return (abs(p-q) < EPS);
}

double distLP(const L &l, const P &p) {
    return cross(l.y-l.x, p-l.x)/abs(l.y-l.x);
}

P crossP(const L &l, const L &m) {
    double A = cross(l.y-l.x, m.y-m.x);
    double B = cross(l.y-l.x, l.y-m.x);
    if (abs(A) < EPS && abs(B) < EPS) return m.x;
    return m.x+B/A*(m.y-m.x);
}

L shortenA(const L &l, double ab) {
    L ll = l;
    P p = l.y-l.x;
    p /= abs(p);
    ll.x = l.x+p*ab;
    ll.y = l.y-p*ab;
    return ll;
}

L shortenR(const L &l, double rel) {
    L ll = l;
    P p = l.y-l.x;
    ll.x = l.x+p*rel;
    ll.y = l.y-p*rel;
    return ll;
}
