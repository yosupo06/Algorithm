/*
argで2つの点をロバストに比較する, 整数点などで誤差を回避したい時に
arg(-1, 0) = PI, arg(0, 0) = arg(1, 0) = 0として扱う
*/
int argcmp(P l, P r) {
    auto psgn = [&](P p) {
        if (int u = sgn(p.y)) return u;
        if (sgn(p.x) == -1) return 2;
        return 0;
    };
    int lsgn = psgn(l), rsgn = psgn(r);
    if (lsgn < rsgn) return -1;
    if (lsgn > rsgn) return 1;
    return sgncrs(r, l);
}

V<L> halfplane_intersects(V<L> lines) {
    sort(lines.begin(), lines.end(), [&](const L& a, const L& b) {
        if (int u = argcmp(a.vec(), b.vec())) return u == -1;
        return sgncrs(a.vec(), b.s - a.s) < 0;
    });
    lines.erase(unique(lines.begin(), lines.end(),
                       [&](const L& a, const L& b) {
                           return argcmp(a.vec(), b.vec()) == 0;
                       }),
                lines.end());

    deque<L> st;
    for (auto l : lines) {
        bool err = false;
        auto is_need = [&](L a, L b, L c) {
            D ab_dw = crs(a.vec(), b.vec()), ab_up = crs(a.vec(), a.t - b.s);
            D bc_dw = crs(b.vec(), c.vec()), bc_up = crs(c.t - b.s, c.vec());
            if (ab_dw <= 0 || bc_dw <= 0) return true;
            bool f = bc_up * ab_dw > bc_dw * ab_up;
            if (!f && crs(a.vec(), c.vec()) < 0) err = true;
            return f;
        };
        while (st.size() >= 2 && !is_need(l, st[0], st[1])) st.pop_front();
        while (st.size() >= 2 &&
               !is_need(st[st.size() - 2], st[st.size() - 1], l))
            st.pop_back();
        if (st.size() < 2 || is_need(st.back(), l, st.front())) st.push_back(l);
        if (err) return {};
    }
    if (st.size() == 2 && !sgncrs(st[0].vec(), st[1].vec()) &&
        sgncrs(st[0].vec(), st[1].s - st[0].s) <= 0)
        return {};

    return V<L>(st.begin(), st.end());
}

struct Arrange {
    V<P> ps;
    VV<int> g;
    Arrange(const V<L>& l) {
        int n = int(l.size());
        for (int i = 0; i < n; i++) {
            ps.push_back(l[i].s);
            ps.push_back(l[i].t);
            for (int j = i+1; j < n; j++) {
                P p;
                int u = crossSS(l[i], l[j], p);
                if (u == 0) continue;
                ps.push_back(p);
            }
        }
        sort(ps.begin(), ps.end());
        ps.erase(unique(ps.begin(), ps.end()), ps.end());
        int m = int(ps.size());
        g = VV<int>(m);
        for (int i = 0; i < n; i++) {
            V<int> v;
            for (int j = 0; j < m; j++) {
                if (ccw(l[i].s, l[i].t, ps[j]) != 0) continue;
                v.push_back(j);
            }
            sort(v.begin(), v.end(), [&](int x, int y) {
                return (ps[x] - l[i].s).abs() < (ps[y] - l[i].s).abs();
            });
            for (int j = 0; j < int(v.size()) - 1; j++) {
                g[v[j]].push_back(v[j+1]);
                g[v[j+1]].push_back(v[j]);
            }
        }

        for (int i = 0; i < m; i++) {
            sort(g[i].begin(), g[i].end());
            g[i].erase(unique(g[i].begin(), g[i].end()), g[i].end());
        }
    }
};

/*
双対グラフを返す，psは点の位置，gはグラフ
polsよりgのほうがサイズが1大きい，これは外側の連結成分を指す
連結ではないグラフを入れるときは注意
*/
struct DualGraph {
    V<Pol> pols;
    VV<int> g;
};
DualGraph dualGraph(V<P> ps, VV<int> g) {
    assert(ps.size() == g.size());
    int n = int(ps.size());
    using Pi = pair<int, int>;
    map<Pi, int> mp;
    for (int i = 0; i < n; i++) {
        sort(begin(g[i]), end(g[i]));
        assert(unique(begin(g[i]), end(g[i])) == end(g[i]));
        sort(begin(g[i]), end(g[i]), [&](int l, int r) {
            return (ps[l] - ps[i]).arg() > (ps[r] - ps[i]).arg();
        });
        for (int j = 0; j < int(g[i].size()); j++) {
            mp[Pi(i, g[i][j])] = j;
        }
    }

    VV<int> vis(n), rev(n);
    for (int i = 0; i < n; i++) {
        vis[i] = V<int>(g[i].size(), -3);
        for (int d : g[i]) {
            rev[i].push_back(mp[Pi(d, i)]);
        }
    }

    V<Pol> pols;
    int idc = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < int(g[i].size()); j++) {
            if (vis[i][j] != -3) continue;
            Pol pol;
            int p = i, idx = j;
            while (vis[p][idx] != -2) {
                pol.push_back(ps[p]);
                vis[p][idx] = -2;
                int np = g[p][idx];
                int nidx = rev[p][idx] + 1;
                if (nidx == int(g[np].size())) nidx = 0;

                p = np;
                idx = nidx;
            }
            int id = -1;
            if (sgn(area2(pol)) == 1) {
                id = idc;
                pols.push_back(pol);
                idc++;
            }
            while (vis[p][idx] == -2) {
                vis[p][idx] = id;
                int np = g[p][idx];
                int nidx = rev[p][idx] + 1;
                if (nidx == int(g[np].size())) nidx = 0;

                p = np;
                idx = nidx;
            }
        }
    }
    VV<int> g2(idc + 1);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < int(g[i].size()); j++) {
            int x = vis[i][j], y = vis[g[i][j]][rev[i][j]];
            if (x == -1) x = idc;
            if (y == -1) y = idc;
            g2[x].push_back(y);
        }
    }
    for (int i = 0; i <= idc; i++) {
        sort(begin(g2[i]), end(g2[i]));
        g2[i].erase(unique(begin(g2[i]), end(g2[i])), end(g2[i]));
    }

    return DualGraph{pols, g2};
}

// 今pが一直線上の時は絶対に使わないで下さい
// 挙動がヤバすぎて，ほぼ100%その場でバグってしまいます。
VV<int> delaunay(const V<P>& p) {
    int n = int(p.size());
    assert(n > 1);
    VV<int> mp(n + 2, V<int>(n + 2, -1));
    int special = 0;
    for (int i = 1; i < n; i++)
        if (p[i] < p[special]) special = i;
    using Pi = pair<int, int>;
    stack<Pi> st;
    auto set_tr = [&](int i, int j, int k) {
        mp[i][j] = k;
        mp[j][k] = i;
        mp[k][i] = j;
        st.push(Pi(i, j));
    };
    set_tr(special, n, n + 1);
    st.pop();
    for (int l = 0; l < n; l++) {
        if (l == special) continue;
        int i = n, j = n + 1, k = mp[i][j];
        do {
            assert(k != -1);
            auto succ = [&](int x, int y) {
                assert(!(x == n && y == n + 1));
                assert(!(x == n + 1 && y == n));
                if (x == n || y == n + 1) return p[l] < p[min(x, y)];
                if (x == n + 1 || y == n) return p[min(x, y)] < p[l];
                return ccw(p[x], p[y], p[l]) == 1;
            };
            if (succ(i, k))
                j = k;
            else if (succ(k, j))
                i = k;
            else
                break;
            k = mp[i][j];
        } while (true);
        auto on_line = [&](int x, int y, int z) {
            if (max(x, y) >= n || ccw(p[x], p[y], p[l]) == 1) return false;
            int w = mp[y][x];
            mp[x][y] = mp[y][x] = -1;
            set_tr(x, w, l);
            set_tr(w, y, l);
            set_tr(y, z, l);
            set_tr(z, x, l);
            return true;
        };
        if (!on_line(i, j, k) && !on_line(j, k, i) && !on_line(k, i, j)) {
            set_tr(i, j, l);
            set_tr(j, k, l);
            set_tr(k, i, l);
        }
        while (st.empty() == false) {
            int u, v;
            tie(u, v) = st.top();
            st.pop();
            int w = mp[u][v], x = mp[v][u];
            assert(w == l);
            if (w < 0 || x < 0 || max(w, x) >= n) continue;
            if (max(u, v) < n) {
                P a = p[u] - p[x], b = p[v] - p[x], c = p[w] - p[x];
                D z = 0;
                z += a.norm() * crs(b, c);
                z += b.norm() * crs(c, a);
                z += c.norm() * crs(a, b);
                if (z <= 0) continue;
            } else {
                if (u < n && ccw(p[x], p[w], p[u]) != 1) continue;
                if (v < n && ccw(p[w], p[x], p[v]) != 1) continue;
            }
            mp[u][v] = mp[v][u] = -1;
            set_tr(u, x, l);
            set_tr(x, v, l);
        }
    }

    set_tr(special, n + 1, n);  // for traverse
    VV<int> g(n);
    for (int i = 0; i < n; i++) {
        int s = 0;
        for (int j = 0; j < n; j++) {
            if (mp[s][i] < mp[j][i]) s = j;
        }
        int j = s;
        bool unbounded = false;
        do {
            if (j < n)
                g[i].push_back(j);
            else
                unbounded = true;
            j = mp[i][j];
        } while (j != s);
        if (unbounded) g[i].push_back(n);
    }
    return g;
}
