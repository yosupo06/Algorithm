struct T {
    P d[3];
    T() {}
    T(P x, P y, P z) {
        d[0] = x; d[1] = y; d[2] = z;
    }
    P& operator[](int p) {
        return d[p];
    }
    const P& operator[](int p) const {
        return d[p];
    }
    int size() const {
        return 3;
    }
};

using Pol = V<P>;

template<class C>
P cu(const C &p, int i) {
    int s = p.size();
    return p[(i%s+s)%s];
};


//0:P is out 1:P is on line 2:P is in
template<class C>
int contains(const C &pol, P p) {
    int in = -1;
    for (int i = 0; i < (int)pol.size(); i++) {
        P a=cu(pol,i)-p, b=cu(pol,i+1)-p;
        if (ccw(a, b, P(0, 0)) == 0) return 1;
        if (imag(a) > imag(b)) swap(a, b);
        if (imag(a) <= 0 && 0 < imag(b)) {
            if (cross(a, b) < 0) in *= -1;
        }
    }
    return in+1;
}
R area2(V<P> &p) {
    R u = 0;
    for (int i = 0; i < (int)p.size(); i++) {
        u += cross(cu(p, i), cu(p, i+1));
    }
    return u;
}

R area_naive(const Pol &p) {
    R u = 0;
    for (int i = 0; i < (int)p.size(); i++) {
        u += cross(cu(p, i), cu(p, i+1));
    }
    return u/2;
}

R area(const Pol &p) {
    return abs(area_naive(p));
}

/*
 -1 -> clock
 0 -> non polygon
 1 -> counter clock
 */
int iscclock(const Pol &p) {
    return sgn(area_naive(p));
}


/*
 スパゲッティソースをパクった、直線の左側の多角形を返却する   
 */
Pol convex_cut(const Pol &p, const L &l) {
    Pol q;
    for (int i = 0; i < (int)p.size(); i++) {
        P a = cu(p, i), b = cu(p, i+1);
        if (ccw(l.x, l.y, a) != -1) q.push_back(a);
        if (ccw(l.x, l.y, a)*ccw(l.x, l.y, b) < 0) {
            P p;
            crossLL(l, L(a, b), p);
            q.push_back(p);
        }
    }
    return q;
}


Pol convex(Pol p) {
    sort(begin(p), end(p), lessP);
    p.erase(unique(begin(p), end(p), near), end(p));
    if (p.size() <= 2) return p;
    Pol up;
    for (P d: p) {
        while (up.size() > 1 && ccw(up[up.size()-2], up[up.size()-1], d) == 1) up.pop_back();
        up.push_back(d);
    }
    reverse(begin(up), end(up));
    Pol down;
    for (P d: p) {
        while (down.size() > 1 && ccw(down[down.size()-2], down[down.size()-1], d) == -1) down.pop_back();
        down.push_back(d);
    }
    down.insert(begin(down), begin(up)+1, end(up)-1);
    return down;
}


//0:P is out 1:P is on line 2:P is in
int contains(const Pol &pol, const L &l) {
    vector<P> v;
    v.push_back(l.x); v.push_back(l.y);
    for (int i = 0; i < (int)pol.size(); i++) {
        P a = cu(pol, i), b = cu(pol, i+1);
        P p;
        if (crossSS(L(a, b), l, p)) {
            v.push_back(p);
        }
    }

    sort(v.begin(), v.end(), [&](const P &x, const P &y){
        return abs(l.x-x) < abs(l.x-y);
    });

    int sz = (int)v.size();
    for (int i = 0; i < sz-1; i++) {
        v.push_back((v[i]+v[i+1])/(R)2);
    }
    bool f = false;
    for (P p: v) {
        int u = contains(pol, p); 
        if (!u) return 0;
        if (u == 2) f = true;
    }
    if (f) return 2;
    return 1;
}

