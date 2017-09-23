template<class C, class D, class E>
struct MinCostFlow {
    static const D INF = numeric_limits<D>::max();
    VV<E> g;
    int s, t;
    C nc, cap_flow;
    D nd, flow;

    V<D> dual;
    V<int> pv, pe;

    MinCostFlow(VV<E> g, int s, int t, bool neg) : g(g), s(s), t(t), cap_flow(0), flow(0) {
        assert(s != t);       
        dual = V<D>(g.size());
        pv = V<int>(g.size());
        pe = V<int>(g.size());
        dual_ref(neg);
    }



    C single_flow(C c) {
        if (nd == INF) return nc;
        c = min(c, nc);
        for (int v = t; v != s; v = pv[v]) {
            E &e = g[pv[v]][pe[v]];
            e.cap -= c;
            g[v][e.rev].cap += c;
        }
        cap_flow += c;
        flow += c * nd;
        nc -= c;
        if (!nc) dual_ref(false);
        return c;
    }
    void max_flow(C c) {
        while (c) {
            C f = single_flow(c);
            if (!f) break;
            c -= f;
        }
    }
        
    void dual_ref(bool neg) {
        V<D> dist(g.size(), INF);
        fill(begin(pv), end(pv), -1);
        fill(begin(pe), end(pe), -1);
        
        using P = pair<D, int>;
        queue<int> ref_v;
        priority_queue<P, vector<P>, greater<P>> que1;
        queue<P> que2;
        auto empty = [&] {
            return (!neg) ? que1.empty() : que2.empty();
        };
        auto push = [&](P p) {
            (!neg) ? que1.push(p) : que2.push(p);
        };
        auto pop = [&]() {
            P p = (!neg) ? que1.top() : que2.front();
            (!neg) ? que1.pop() : que2.pop();
            return p;
        };
        push(P(0, s));
        dist[s] = 0;
        while (!empty()) {
            P p = pop();
            int v = p.second;
            if (dist[v] < p.first) continue;
            if (!neg) {
                if (v == t) break;
                ref_v.push(v);
            }
            for (int i = 0; i < int(g[v].size()); i++) {
                E e = g[v][i];
                D ed = e.dist + dual[v] - dual[e.to];
                if (e.cap && dist[e.to] > dist[v] + ed) {
                    dist[e.to] = dist[v] + ed;
                    pv[e.to] = v; pe[e.to] = i;
                    push(P(dist[e.to], e.to));
                }
            }
        }
        if (dist[t] == INF) {
            nd = INF;
            nc = 0;
            return;
        }
        if (!neg) {
            while (ref_v.size()) {
                int v = ref_v.front(); ref_v.pop();
                if (dist[v] >= dist[t]) continue;
                dual[v] += dist[v]-dist[t];
            }
        } else {
            for (int v = 0; v < int(g.size()); v++) {
                dual[v] += dist[v];
            }
        }
        nd = dual[t]-dual[s];
        assert(0 <= nd);
        nc = numeric_limits<C>::max();
        for (int v = t; v != s; v = pv[v]) {
            nc = min(nc, g[pv[v]][pe[v]].cap);
        }
    }
};

template<class C, class D, class E>
auto min_cost_flow(VV<E> g, int s, int t, bool neg = false) {
    return MinCostFlow<C, D, E>(g, s, t, neg);
}

/*
template<class C, class D> // cap, dist (C must be integer)
struct MinCostFlow {
    int N;
    C nc; D nd;
    D INF, EPS;
    V<D> h, dist;

    template<class E>
    MinCostFlow(const VV<E> &g, D INF, D EPS) : INF(INF), EPS(EPS) {
        N = int(g.size());
        h = V<D>(N);
        dist = V<D>(N);
        pv = V<int>(N); pe = V<int>(N);
        visited = V<int>(N);
        fill(begin(h), end(h), 0);
        nc = nd = 0;
    }

    int s, t;
    template<class E>
    void set_ends(const VV<E> &g, int s, int t, bool neg = false) {
        this->s = s; this->t = t;
        pot_ref(g, neg);
    }
    template<class E>
    C single_flow(VV<E> &g, C c) {
        c = min(c, nc);
        for (int v = t; v != s; v = pv[v]) {
            E &e = g[pv[v]][pe[v]];
            e.cap -= c;
            g[v][e.rev].cap += c;
        }
        nc -= c;
        if (!nc) pot_ref(g, false);
        return c;
    }

    V<int> visited; int vid = 114514;
    template<class E>
    C dfs(VV<E> &g, int v, C c) {
        visited[v] = vid;
        C sm = 0;
        for (E &e: g[v]) {
            D ed = e.dist + h[v] - h[e.to];
            if (!e.cap || visited[e.to] == vid) continue;
            if (EPS < ed) continue;
            C u;
            if (e.to == t) {
                u = min(c, e.cap);
            } else {
                u = dfs(g, e.to, min(e.cap, c-sm));
            }
            sm += u;
            e.cap -= u;
            g[e.to][e.rev].cap += u;
            if (c-sm <= 0) break;
        }
        return sm;
    }
    template<class E>
    C multi_flow(VV<E> &g, C c) {
        C sm = 0;
        while (true) {
            vid++;
            C res = dfs(g, s, c);
            if (!res) break;
            sm += res;
            c -= res;
        }
        pot_ref(g, false);
        return sm;
    }
    template<class R, class E> // R = C*T
    R max_flow(VV<E> &g, int s, int t, C c, bool neg = false) {
        R res = 0;
        set_ends(g, s, t, neg);
        while (c) {
            D d = nd;
            C f = multi_flow(g, c);
//            C f = single_flow(g, c);
            if (!f) break;
            res += R(f) * d;
            c -= f;
        }
        return res;
    }

    V<int> pv, pe;
    template<class E>
    void pot_ref(const VV<E> &g, bool neg) {
        fill(begin(dist), end(dist), INF);
        using P = pair<D, int>;
        queue<int> ref_v;
        priority_queue<P, vector<P>, greater<P>> que1;
        queue<P> que2;
        auto empty = [&] {
            return (!neg) ? que1.empty() : que2.empty();
        };
        auto push = [&](P p) {
            (!neg) ? que1.push(p) : que2.push(p);
        };
        auto pop = [&]() {
            P p = (!neg) ? que1.top() : que2.front();
            (!neg) ? que1.pop() : que2.pop();
            return p;
        };
        push(P(0, s));
        dist[s] = 0;
        while (!empty()) {
            P p = pop();
            int v = p.second;
            if (dist[v] < p.first) continue;
            if (!neg) {
                if (v == t) break;
                ref_v.push(v);
            }
            for (int i = 0; i < (int)g[v].size(); i++) {
                E e = g[v][i];
                D ed = e.dist + h[v] - h[e.to];
                if (e.cap && dist[e.to] > dist[v] + ed) {
                    dist[e.to] = dist[v] + ed;
                    pv[e.to] = v; pe[e.to] = i;
                    push(P(dist[e.to], e.to));
                }
            }
        }
        if (!neg) {
            while (ref_v.size()) {
                int v = ref_v.front(); ref_v.pop();
                if (dist[v] >= dist[t]) continue;
                h[v] += dist[v]-dist[t];
            }
        } else {
            for (int v = 0; v < N; v++) {
                h[v] += dist[v];
            }
        }
        if (dist[t] == INF) {
            nd = INF;
            nc = 0;
            return;
        }
        nd = h[t]-h[s];
        nc = INF;
        for (int v = t; v != s; v = pv[v]) {
            nc = min(nc, g[pv[v]][pe[v]].cap);
        }
    }
};
*/