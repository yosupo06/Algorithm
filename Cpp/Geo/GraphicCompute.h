C circumCircle(T t) {
    P a = t.d[0], b = t.d[1], c = t.d[2];
    b -= a; c -= a;
    R s = 2*cross(b, c);
    R x = norm(b-c), y = norm(c), z = norm(b);
    R S = x+y+z;
    P r = (y*(S-2*y)*b+z*(S-2*z)*c)/(s*s);
    return C(r + a, abs(r));
}

C smallestEnclosingCircle(Pol &p, int ps, T q = T(), int qs = 0) {
    if (!ps) {
        switch (qs) {
            case 0:
                return C(P(0, 0), -1);
            case 1:
                return C(q.d[0], 0);
            case 2:
                return C((q.d[0]+q.d[1])/R(2.0), abs(q.d[0]-q.d[1])/R(2.0));
            case 3:
                return circumCircle(q);
        }
        assert(false);
    }
    C c = smallestEnclosingCircle(p, ps-1, q, qs);
    if (sgn(c.r, abs(p[ps-1]-c.p)) == 1) {
        q.d[qs] = p[ps-1];
        return smallestEnclosingCircle(p, ps-1, q, qs+1);
    }
    return c;
}

//線分アレンジメント
//l->線分 n->線分の数 p->点集合結果 g->エッジの情報
//pのサイズはlC2+2*l確保
//返り値として点集合の個数を返す
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
            if (ccw(l[i].x, l[i].y, p[j]) != 0) continue;
            v.push_back(j);
        }
        sort(v.begin(), v.end(), [&](const int &x, const int &y) 
            {return abs(p[x] - l[i].x) < abs(p[y] - l[i].x);});
        for (int j = 0; j < (int)v.size() - 1; j++) {
            g[v[j]].push_back(v[j+1]);
            g[v[j+1]].push_back(v[j]);
        }
    }

    for (int i = 0; i < pc; i++) {
        sort(g[i].begin(), g[i].end());
        g[i].erase(unique(g[i].begin(), g[i].end()), g[i].end());
    }
    return pc;
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
