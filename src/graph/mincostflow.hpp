/*
struct E {
    int to, rev, cap, dist;
};
VV<E> g;
auto add_edge = [&](int from, int to, int cap, int dist) {
    g[from].push_back(E{to, int(g[to].size()), cap, dist});
    g[to].push_back(E{from, int(g[from].size())-1, 0, -dist});
};

auto res = min_cost_flow<int, int>(g, s, t, false);
res.max_flow(TEN(9));

// cap_flow : 最大流量
// flow : 最小費用
*/

template<class C, class D, class E>
struct MinCostFlow {
    static constexpr D INF = numeric_limits<D>::max();
    int n;
    VV<E> g;
    int s, t;
    C nc, cap_flow = 0;
    D nd, flow = 0;

    V<D> dual;
    V<int> pv, pe;

    MinCostFlow(VV<E> _g, int _s, int _t, bool neg)
        : n(int(_g.size())), g(_g), s(_s), t(_t) {
        assert(s != t);
        dual = V<D>(n);
        pv = pe = V<int>(n);
        if (neg) {
            V<D> dist(n, D(INF));
            dist[s] = 0;
            for (int ph = 0; ph < n; ph++) {
                bool update = false;
                for (int i = 0; i < n; i++) {
                    if (dist[i] == INF) continue;
                    for (auto e: g[i]) {
                        if (!e.cap) continue;
                        if (dist[i] + e.dist < dist[e.to]) {
                            dist[e.to] = dist[i] + e.dist;
                            update = true;
                        }
                    }
                }
                if (!update) break;
            }
            for (int v = 0; v < n; v++) {
                dual[v] += dist[v];
            }
        }
        dual_ref();
    }

    C single_flow(C c) {
        if (nd == INF) return nc;
        c = min(c, nc);
        for (int v = t; v != s; v = pv[v]) {
            E& e = g[pv[v]][pe[v]];
            e.cap -= c;
            g[v][e.rev].cap += c;
        }
        cap_flow += c;
        flow += nd * c;
        nc -= c;
        if (!nc) dual_ref();
        return c;
    }

    void max_flow(C c) {
        while (c) {
            C f = single_flow(c);
            if (!f) break;
            c -= f;
        }
    }

    void dual_ref() {
        V<D> dist(g.size(), D(INF));
        pv = pe = V<int>(n, -1);
        struct Q {
            D key;
            int to;
            bool operator<(Q r) const { return key > r.key; }
        };
        priority_queue<Q> que;
        dist[s] = 0;
        que.push(Q{D(0), s});
        V<char> vis(n);
        while (!que.empty()) {
            int v = que.top().to; que.pop();
            if (v == t) break;
            if (vis[v]) continue;
            vis[v] = true;
            for (int i = 0; i < int(g[v].size()); i++) {
                E e = g[v][i];
                if (vis[e.to] || !e.cap) continue;
                D cost = dist[v] + e.dist + dual[v] - dual[e.to];
                if (dist[e.to] > cost) {
                    dist[e.to] = cost;
                    pv[e.to] = v; pe[e.to] = i;
                    que.push(Q{dist[e.to], e.to});
                }
            }
        }
        if (dist[t] == INF) {
            nd = INF; nc = 0;
            return;
        }
        for (int v = 0; v < n; v++) {
            if (!vis[v]) continue;
            dual[v] += dist[v] - dist[t];
        }
        nd = dual[t] - dual[s];
        nc = numeric_limits<C>::max();
        for (int v = t; v != s; v = pv[v]) {
            nc = min(nc, g[pv[v]][pe[v]].cap);
        }
    }
};

template<class C, class D, class E>
MinCostFlow<C, D, E> get_mcf(const VV<E>& g, int s, int t, bool neg = false) {
    return MinCostFlow<C, D, E>(g, s, t, neg);
}
