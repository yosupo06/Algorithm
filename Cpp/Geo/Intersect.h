bool insLS(const L &l, const L &s) {
    int a = ccw(l.x, l.y, s.x);
    int b = ccw(l.x, l.y, s.y);
    if (a == 1 && b == 1) return false;
    if (a == -1 && b == -1) return false;
    return true;
}

bool insSS(const L &s, const L &t) {
    int a = ccw(s.x,s.y,t.x), b = ccw(s.x,s.y,t.y);
    int c = ccw(t.x,t.y,s.x), d = ccw(t.x,t.y,s.y);
    if (a*b <= 0 && c*d <= 0) return true;
    return false;
}

int crossLL(const L &l, const L &m, P &r) {
    L mm = L(m.x - l.x, m.y - l.x);
    mm.x *= polar<R>(1.0, -arg(vec(l)));
    mm.y *= polar<R>(1.0, -arg(vec(l)));
    if (sgn(vec(mm).imag()) == 0) {
        r = l.x;
        if (sgn(mm.x.imag()) == 0) return -1;
        return 0;
    }
    r = mm.x - vec(mm) * (mm.x.imag() / vec(mm).imag());
    r *= polar<R>(1.0, arg(vec(l)));
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


//線分と点の最小距離
R distSP(const L &s, const P &p) {
    P s2 = vec(s)*P(0, 1);
    if (ccw(s.x, s.x+s2, p) == 1) return abs(s.x-p);
    if (ccw(s.y, s.y+s2, p) == -1) return abs(s.y-p);
    return min(min(abs(s.x-p), abs(s.y-p)), distLP(s, p));
}

//線分と線分の最小距離
R distSS(const L &s, const L &t) {
    if (insSS(s, t)) return 0;
    return min(min(distSP(s, t.x), distSP(s, t.y)),
               min(distSP(t, s.x), distSP(t, s.y)));
}

//線分アレンジメント
//l->線分 n->線分の数 p->点集合結果 g->アレ
//pのサイズはlC2+2*l確保
int arrange(L l[], int n, P p[], vector<int> g[]) {
    int pc = 0;
    for (int i = 0; i < n; i++) {
        p[pc] = l[i].x; pc++;
        p[pc] = l[i].y; pc++;
        for (int j = i+1; j < n; j++) {
            int u = crossSS(l[i], l[j], p[pc]);
            if (u == 0) continue;
            pc++;
        }
    }
    sort(p, p+pc, lessP);
    pc = unique(p, p+pc, near) - p;
    for (int i = 0; i < n; i++) {
        vector<int> v;
        for (int j = 0; j < pc; j++) {
            if (ccw(l[i].x, l[i].y, v[j]) != 0) continue;
            v.push_back(j);
        }
        sort(v.begin(), v.end(), [&](const int &x, const int &y) 
            {return abs(p[x] - l[i].x) < abs(p[y] - l[i].x);});
        for (int j = 0; j < (int)v.size() - 1; j++) {
            g[v[j]].push_back(v[j+1]);
            g[v[j+1]].push_back(v[j]);
        }
    }
    return pc;
}