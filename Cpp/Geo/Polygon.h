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

P cu(const T &t, int i) {
    return t[(i%3+3)%3];
}

typedef vector<P> Pol;

P cu(const Pol &p, int i) { 
    int s = p.size();
    return p[(i%s+s)%s];
};


//0:P is out 1:P is on line 2:P is in
int contains(const T &pol, P p) {
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

//0:P is out 1:P is on line 2:P is in
int contains(const Pol &pol, P p) {
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
    sort(p.begin(), p.end());
    if (p.size() <= 2) return p;
    Pol up;
    for (P d: p) {
        while (up.size() > 1 && ccw(up[up.size()-2], up[up.size()-1], d) == 1) up.pop_back();
        up.push_back(d);
    }
    reverse(up.begin(), up.end());
    Pol down;
    for (P d: p) {
        while (down.size() > 1 && ccw(down[down.size()-2], down[down.size()-1], d) == -1) down.pop_back();
        down.push_back(d);
    }
    down.insert(down.begin(), up.begin()+1, up.end()-1);
    return down;
}


//0:P is out 1:P is on line 2:P is in
//高速化の余地があり
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


/*
 双対グラフを作成
 pol, rgの要素は2*n-4個確保しておくこと
 gはめちゃくちゃに破壊される
 もし連結でないグラフ、しかも内包があるグラフに行うとrgは0が複数混入する
 0は、その連結成分だけに注目したときの外側の意味。本当に外側か判定したいなら
 contains等を使用すること
 */
int dualGraph(P p[], vector<int> g[], int n,
    Pol pol[], vector<int> rg[]) {
    map<pair<int, int>, int> mp;
    for (int i = 0; i < n; i++) {
        sort(g[i].begin(), g[i].end());
        assert(unique(g[i].begin(), g[i].end()) == g[i].end());
        sort(g[i].begin(), g[i].end(), [&](int l, int r){
            return arg(p[l]-p[i]) > arg(p[r]-p[i]);
        });
        for (int j = 0; j < (int)g[i].size(); j++) {
            mp[make_pair(i, g[i][j])] = j;
        }
    }

    vector<vector<int>> idx(n), rev(n);
    for (int i = 0; i < n; i++) {
        idx[i] = vector<int>(g[i].size(), -1);
        rev[i].resize(g[i].size());
        for (int j = 0; j < (int)g[i].size(); j++) {
            rev[i][j] = mp[make_pair(g[i][j], i)];
        }
    }

    int idc = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (int)g[i].size(); j++) {
            if (idx[i][j] != -1) continue;
            Pol po;
            int ii = i, jj = j;
            while (idx[ii][jj] != -2) {
                po.push_back(p[ii]);
                idx[ii][jj] = -2;
                int ni = g[ii][jj];
                int nj = (rev[ii][jj]+1) % g[ni].size();
                ii = ni; jj = nj;
            }
            int id;
            if (iscclock(po) != 1) {
                id = 0;
            } else {
                id = idc;
                pol[idc] = po;
                idc++;
            }
            while (idx[ii][jj] == -2) {
                idx[ii][jj] = id;
                int ni = g[ii][jj];
                int nj = (rev[ii][jj]+1) % g[ni].size();
                ii = ni; jj = nj;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (int)g[i].size(); j++) {
            if (idx[i][j] != 0) continue;
            int id = 0;
            for (int k = 1; k < idc; k++) {
                if (contains(pol[k], p[i]) == 2) {
                    id = k;
                }
            }
            if (id == 0) continue;
            int ii = i, jj = j;
            while (idx[ii][jj] == 0) {
                idx[ii][jj] = id;
                int ni = g[ii][jj];
                int nj = (rev[ii][jj]+1) % g[ni].size();
                ii = ni; jj = nj;
            }            
        }
    }

    for (int i = 0; i < idc; i++) {
        rg[i].clear();
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (int)g[i].size(); j++) {
            if (idx[i][j] < 0) continue;
            rg[idx[i][j]].push_back(idx[g[i][j]][rev[i][j]]);
        }
    }

    for (int i = 0; i < n; i++) {
        sort(rg[i].begin(), rg[i].end());
        rg[i].erase(unique(rg[i].begin(), rg[i].end()), rg[i].end());
    }

    return idc;
}

