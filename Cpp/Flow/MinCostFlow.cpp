template<int V>
struct MinCostFlow {
    using T = int;
    using P = pair<T, int>;
    const T INF = 1<<28;
    struct Edge {
        int to, rev;
        int cap;
        T cost;
    };
    vector<Edge> g[V];
    T h[V], dist[V];
    int pv[V], pe[V];
    void add(int from, int to, int cap, T cost) {
        g[from].push_back(Edge{to, (int)g[to].size(), cap, cost});
        g[to].push_back(Edge{from, (int)g[from].size()-1, 0, -cost});
    }

    T exec(int s, int t, int f, bool bell = false) {
        T res = 0;
        fill_n(h, V, 0);
        while (f > 0) {
            fill_n(dist, V, INF);
            dist[s] = 0;
            if (bell) {
                bell = false;
                bool update;
                do {
                    update = false;
                    for (int v = 0; v < V; v++) {
                        if (dist[v] == INF) continue;
                        for (int i = 0; i < g[v].size(); i++) {
                            Edge &e = g[v][i];
                            if (e.cap > 0 && dist[e.to] > dist[v] + e.cost) {
                                dist[e.to] = dist[v] + e.cost;
                                pv[e.to] = v;
                                pe[e.to] = i;
                                update = true;
                            }
                        }
                    }
                } while (update);
            } else {
                priority_queue<P, vector<P>, greater<P>> que;
                que.push(P(0, s));
                while (!que.empty()) {
                    P p = que.top(); que.pop();
                    int v = p.second;
                    if (dist[v] < p.first) continue;
                    for (int i = 0; i < g[v].size(); i++) {
                        Edge &e = g[v][i];
                        if (e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
                            dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
                            pv[e.to] = v;
                            pe[e.to] = i;
                            que.push(P(dist[e.to], e.to));
                        }
                    }
                }
            }
            if (dist[t] == INF) {
                return -1;
            }
            for (int v = 0; v < V; v++) {
                h[v] += dist[v];
            }

            T d = f;
            for (int v = t; v != s; v = pv[v]) {
                d = min(d, g[pv[v]][pe[v]].cap);
            }
            f -= d;
            res += d * h[t];
            for (int v = t; v != s; v = pv[v]) {
                Edge &e = g[pv[v]][pe[v]];
                e.cap -= d;
                g[v][e.rev].cap += d;
            }
        }
        return res;
    }
};
