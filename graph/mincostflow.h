template<class C, class D, D INF, D EPS> // cap, dist (C must be integer)
struct MinCostFlow {
    int N;
    C nc; D nd;

    template<class E>
    MinCostFlow(const Graph<E> &g) {
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
    void setEnds(const Graph<E> &g, int s, int t, bool neg = false) {
        this->s = s; this->t = t;
        potRef(g, neg);
    }

    template<class E>
    C singleFlow(Graph<E> &g, C c) {
        c = min(c, nc);
        for (int v = t; v != s; v = pv[v]) {
            E &e = g[pv[v]][pe[v]];
            e.cap -= c;
            g[v][e.rev].cap += c;
        }
        nc -= c;
        if (!nc) potRef(g, false);
        return c;
    }

    V<int> visited; int vid = 114514;
    template<class E>
    C dfs(Graph<E> &g, int v, C c) {
        visited[v] = vid;
        C sm = 0;
        for (E &e: g[v]) {
            if (!e.cap || visited[e.to] == vid) continue;
            D ed = e.dist + h[v] - h[e.to];
            if (EPS < ed) continue; //eps?
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
    C multiFlow(Graph<E> &g, C c) {
        C sm = 0;
        while (true) {
            vid++;
            C res = dfs(g, s, c);
            if (!res) break;
            sm += res;
            c -= res;
        }
        potRef(g, false);
        return sm;
    }
    template<class R, class E> // R = C*T
    R maxFlow(Graph<E> &g, int s, int t, C c, bool neg = false) {
        R res = 0;
        setEnds(g, s, t, neg);
        while (c) {
            D d = nd;
            C f = multiFlow(g, c);
//            C f = singleFlow(g, c);
            if (!f) break;
            res += R(f) * d;
            c -= f;
        }
        return res;
    }

    V<D> h, dist;
    V<int> pv, pe;

    template<class E>
    void potBell(const Graph<E> &g) {
        bool update;
        dist[s] = 0;
        do {
            update = false;
            for (int v = 0; v < N; v++) {
                if (dist[v] == INF) continue;
                for (int i = 0; i < (int)g[v].size(); i++) {
                    E e = g[v][i];
                    D ed = e.dist + h[v] - h[e.to];
                    if (e.cap && dist[e.to] > dist[v] + ed) {
                        dist[e.to] = dist[v] + ed;
                        pv[e.to] = v; pe[e.to] = i;
                        update = true;
                    }
                }
            }
        } while (update);
        for (int v = 0; v < N; v++) {
            if (dist[v] >= dist[t]) continue;
            h[v] += dist[v]-dist[t];
        }
    }

    template<class E>
    void potDijk(const Graph<E> &g) {
        using P = pair<D, int>;
        queue<int> ref_v;
        priority_queue<P, vector<P>, greater<P>> que;
        que.push(P(0, s));
        dist[s] = 0;
        while (!que.empty()) {
            P p = que.top(); que.pop();
            int v = p.second;
            if (v == t) break;
            if (dist[v] < p.first) continue;
            ref_v.push(v);
            for (int i = 0; i < (int)g[v].size(); i++) {
                E e = g[v][i];
                D ed = e.dist + h[v] - h[e.to];
                if (e.cap && dist[e.to] > dist[v] + ed) {
                    dist[e.to] = dist[v] + ed;
                    pv[e.to] = v; pe[e.to] = i;
                    que.push(P(dist[e.to], e.to));
                }
            }
        }
        while (ref_v.size()) {
            int v = ref_v.front(); ref_v.pop();
            if (dist[v] >= dist[t]) continue;
            h[v] += dist[v]-dist[t];
        }        
    }

    template<class E>
    void potRef(const Graph<E> &g, bool neg) {
        fill(begin(dist), end(dist), INF);
        if (neg) {
            potBell(g);
        } else {
            potDijk(g);
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
