struct C {
    P p;
    R r;
    C() {}
    C(P p, R r) : p(p), r(r) {}
};

int crossSC(const L&l, const C &c) {
    R mi = distSP(l, c.p);
    if (sgn(c.r, mi) == 1) return 0;
    if (sgn(c.r, mi) == 0) return 1;
    int u = 0;
    if (sgn(c.r, abs(l.x-c.p)) != -1) u++;
    if (sgn(c.r, abs(l.y-c.p)) != -1) u++;
    return u;
}

//need Intersect/distLP
int crossLC(const L &l, const C &c, L &r) {
    R u = distLP(l, c.p);
    int si = sgn(u - c.r);
    if (si == 1) return 0;
    P v = (l.y-l.x) / abs(l) * P(0, -1); //lに直行する単位ベクトル
    v *= u;
    if (ccw(l.x, l.y, c.p) < 0) v *= -1;
    //vは円の中心からlへと向かう方向のベクトル
    if (si == 0) {
        r.x = r.y = c.p + v;
        return 1;
    }
    r.x = c.p+v+polar<R>(sqrt(c.r*c.r - u*u), arg(vec(l)));
    r.y = c.p+v-polar<R>(sqrt(c.r*c.r - u*u), arg(vec(l)));
    return 2;
}

//return number of cross point
//l, rはcから見た交点の角度、[l, r]がdに覆われている
int crossCC(const C &c, const C &d, R &l, R &r) {
    if (near(c.p, d.p) && !sgn(c.r, d.r)) {
        l = 0; r = 2*PI;
        return -1;
    }
    R di = abs(c.p - d.p);
    if (sgn(c.r+d.r, di) == 1) return 0;
    if (sgn(di, abs(c.r-d.r)) == 1) return 0;
    R bth = arg(d.p - c.p);
    R th = sacos((c.r*c.r + di*di - d.r*d.r) / (2*c.r*di));
    l = bth-th;
    r = bth+th;
    if (sgn(th) == 0) return 1;
    return 2;
}

//共通内接線
int commonInternalTangent(const C &c, const C &d, L &l, L &r) {
    R di = abs(c.p - d.p);
    if (sgn(di, c.r + d.r) == 1) return 0;
    R th = sacos((c.r+d.r) / di);
    l.x = c.p + polar(c.r, arg(d.p-c.p)-th);
    l.y = l.x + polar<R>(1, arg(d.p-c.p)-th + PI/2);
    r.x = c.p + polar(c.r, arg(d.p-c.p)+th);
    r.y = r.x + polar<R>(1, arg(d.p-c.p)+th - PI/2);
    if (sgn(di, c.r+d.r) == 0) return 1;
    return 2;
}

//共通外接線
int commonExternalTangent(const C &c, const C &d, L &l, L &r) {
    R di = abs(c.p - d.p);
    if (sgn(di, abs(c.r - d.r)) == 1) return 0;
    if (sgn(di) == 0) {
        l = L(c.p + P(c.r, 0), c.p + P(c.r, 1));
        r = L(c.p + P(c.r, 0), c.p + P(c.r, -1));
        return -1;
    }
    R th = sacos((c.r-d.r) / di);
    l.x = c.p + polar(c.r, arg(d.p-c.p)-th);
    l.y = l.x + polar<R>(1, arg(d.p-c.p)-th + PI/2);
    r.x = c.p + polar(c.r, arg(d.p-c.p)+th);
    r.y = r.x + polar<R>(1, arg(d.p-c.p)+th - PI/2);
    if (sgn(di, abs(c.r - d.r)) == 0) return 1;
    return 2;
}

//扇型ライブラリ
struct Sec {
    C c;
    R l, r;
    Sec() {}
    Sec(C c, R l, R r) : c(c), l(l), r(r) {}
};


bool crossSecP(const Sec &s, const P &p) {
    P pp = p - s.c.p;
    if (sgn(s.c.r, abs(pp)) == 1) return false;
    if (sgn(abs(pp)) == 0) return true;
    return inR(s.l, s.r, arg(pp)) > 0;
}
