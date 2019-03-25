
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
