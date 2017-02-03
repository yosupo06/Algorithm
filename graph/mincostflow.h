/**
 * Edge Sample
 * ---
 * auto addEdge = [&](int from, int to, int cap, int dist) {
 *     g[from].push_back(Edge{to, cap, dist, (int)g[to].size()});
 *     g[to].push_back(Edge{from, 0, -dist, (int)g[from].size()-1});
 * };
 * ---
 */
template<class C, class D, C EPS, D INF> // cap, dist
struct MinCostFlow {
    int V;
    C nc; D nd;

    template<class E>
    MinCostFlow(const Graph<E> &g) {
        V = (int)g.size();
        h.resize(V); dist.resize(V);
        pv.resize(V); pe.resize(V);
        fill_n(h.begin(), V, 0);
        nc = nd = 0;
    } 

    int s, t;
    template<class E>
    void setEnds(const Graph<E> &g, int s, int t, bool neg = false) {
        this->s = s; this->t = t;
        potRef(g, neg);
    }

    template<class R, class E>
    R singleFlow(Graph<E> &g, C c) {
        c = min(c, nc);
        for (int v = t; v != s; v = pv[v]) {
            E &e = g[pv[v]][pe[v]];
            e.cap -= c;
            g[v][e.rev].cap += c;
        }
        R res = (R)c*nd;
        nc -= c;
        if (nc <= EPS) potRef(g, false);
        return res;
    }

    template<class R, class E> // R = C*T
    R maxFlow(Graph<E> &g, int s, int t, C c, bool neg = false) {
        R res = 0;
        setEnds(g, s, t, neg);
        while (c > EPS) {
            if (nc <= EPS) {
                break;
            }
            C f = min(c, nc);
            res += singleFlow<R>(g, f);
            c -= f;
        }
        return res;
    }

    vector<D> h, dist;
    vector<int> pv, pe;

    template<class E>
    void potBell(const Graph<E> &g) {
        fill_n(dist.begin(), V, INF);
        bool update;
        dist[s] = 0;
        do {
            update = false;
            for (int v = 0; v < V; v++) {
                if (dist[v] == INF) continue;
                for (int i = 0; i < (int)g[v].size(); i++) {
                    E e = g[v][i];
                    if (e.cap > EPS && dist[e.to] > dist[v] + e.dist + h[v] - h[e.to]) {
                        dist[e.to] = dist[v] + e.dist + h[v] - h[e.to];
                        pv[e.to] = v; pe[e.to] = i;
                        update = true;
                    }
                }
            }
        } while (update);
    }

    template<class E>
    void potDijk(const Graph<E> &g) {
        fill_n(dist.begin(), V, INF);
        using P = pair<D, int>;
        priority_queue<P, vector<P>, greater<P>> que;
        que.push(P(0, s));
        dist[s] = 0;
        while (!que.empty()) {
            P p = que.top(); que.pop();
            int v = p.second;
            if (dist[v] < p.first) continue;
            for (int i = 0; i < (int)g[v].size(); i++) {
                E e = g[v][i];
                if (e.cap > EPS && dist[e.to] > dist[v] + e.dist + h[v] - h[e.to]) {
                    dist[e.to] = dist[v] + e.dist + h[v] - h[e.to];
                    pv[e.to] = v; pe[e.to] = i;
                    que.push(P(dist[e.to], e.to));
                }
            }
        }
    }

    template<class E>
    void potRef(const Graph<E> &g, bool neg) {
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
        for (int v = 0; v < V; v++) {
            h[v] += dist[v];
        }
        nd = h[t];
        nc = INF;
        for (int v = t; v != s; v = pv[v]) {
            nc = min(nc, g[pv[v]][pe[v]].cap);
        }
    }
};
