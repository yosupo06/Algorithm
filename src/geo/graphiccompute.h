/*
return arg(l) < arg(r)
arg(-1, 0) = PI, arg(0, 0) = arg(1, 0) = 0
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
            for (int j = i + 1; j < n; j++) {
                P p;
                if (crossSS(l[i], l[j], p) != 1) continue;
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
                if (!ccw(l[i].s, l[i].t, ps[j])) v.push_back(j);
            }
            sort(v.begin(), v.end(), [&](int x, int y) {
                return (ps[x] - l[i].s).rabs() < (ps[y] - l[i].s).rabs();
            });
            for (int j = 0; j < int(v.size()) - 1; j++) {
                g[v[j]].push_back(v[j + 1]);
                g[v[j + 1]].push_back(v[j]);
            }
        }

        for (int i = 0; i < m; i++) {
            sort(g[i].begin(), g[i].end());
            g[i].erase(unique(g[i].begin(), g[i].end()), g[i].end());
        }
    }
};

struct DualGraph {
    V<Pol> pols;
    VV<int> g;
    V<int> tr;

    DualGraph(V<P> ps, VV<int> pg) {
        // prohibit self-loop, multi edge
        int n = int(ps.size());
        using Pi = pair<int, int>;
        map<Pi, int> mp;
        for (int i = 0; i < n; i++) {
            if (pg[i].empty()) continue;
            sort(pg[i].begin(), pg[i].end(), [&](int l, int r) {
                return (ps[l] - ps[i]).arg() < (ps[r] - ps[i]).arg();
            });
            int a, b = pg[i].back();
            for (int now : pg[i]) {
                a = b;
                b = now;
                mp[{b, i}] = a;
            }
        }

        map<Pi, int> vis;
        int m = 0;
        for (int i = 0; i < n; i++) {
            for (int j : pg[i]) {
                if (vis.count({i, j})) continue;
                int id = m++;
                pols.push_back({});
                Pi pi = {i, j};
                while (!vis.count(pi)) {
                    vis[pi] = id;
                    pols.back().push_back(ps[pi.first]);
                    pi = {pi.second, mp[pi]};
                }
            }
        }

        g = VV<int>(m);
        for (int i = 0; i < n; i++) {
            for (int j : pg[i]) {
                g[vis[{i, j}]].push_back(vis[{j, i}]);
            }
        }
    }
    V<int> scan(V<P> que, D eps) {
        int n = int(pols.size()), m = int(que.size());
        tr = V<int>(n);
        iota(tr.begin(), tr.end(), 0);
        struct S {
            P s, t;
            int id;
            D get_y(D x) const {
                if (!sgn(s.x, t.x)) return s.y;
                return (s.y * (t.x - x) + t.y * (x - s.x)) / (t.x - s.x);
            }
            bool operator<(const S& r) const {
                D x = (max(s.x, r.s.x) + min(t.x, r.t.x)) / 2;
                return get_y(x) < r.get_y(x);
            }
        };
        struct Q {
            D x;
            int ty;
            S l;
        };
        V<Q> ev;
        for (int i = 0; i < int(que.size()); i++) {
            auto p = que[i];
            ev.push_back({p.x, 0, {p, p, n + i}});
        }
        for (int ph = 0; ph < n; ph++) {
            auto v = pols[ph];
            P a, b = v.back();
            for (auto now : v) {
                a = b;
                b = now;
                if (sgn(b.x, a.x) == -1) {
                    ev.push_back({b.x, 2, {b, a, ph}});
                    ev.push_back({a.x, 1, {b, a, ph}});
                }
            }
            if (area2(v) <= eps) {
                P mi = *min_element(v.begin(), v.end());
                tr[ph] = -1;
                ev.push_back({mi.x, 0, {mi, mi, ph}});
            }
        }
        sort(ev.begin(), ev.end(), [&](Q a, Q b) {
            if (sgn(a.x, b.x)) return sgn(a.x, b.x) == -1;
            return a.ty < b.ty;
        });
        V<int> res(m);
        set<S> st;
        for (auto e : ev) {
            if (e.ty == 0) {
                // get
                auto it = st.lower_bound(e.l);
                int u = (it == st.end() ? -1 : tr[it->id]);
                if (e.l.id < n)
                    tr[e.l.id] = u;
                else
                    res[e.l.id - n] = u;
            } else {
                if (e.ty == 1)
                    st.erase(e.l);
                else
                    st.insert(e.l);
            }
        }
        return res;
    }
};
