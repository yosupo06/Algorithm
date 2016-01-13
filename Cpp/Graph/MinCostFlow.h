/**
 * Primal-Dual法による最小費用流
 * 辺の容量は整数でないと解けないことに注意
 */
template<int V>
struct MinCostFlow {
    using C = double;
    const C EPS = 1e-10;
    using T = double; /// 辺のコストの型
    const T INF = 1e10;
    using P = pair<T, int>;
    struct Edge {
        int to, rev;
        C cap;
        T cost;
    };
    vector<Edge> g[V];
    T h[V], dist[V];
    int pv[V], pe[V];
    void init() {
        for (int i = 0; i < V; i++) {
            g[i].clear();
        }
    }
    /// 辺の追加
    void add(int from, int to, C cap, T cost) {
        g[from].push_back(Edge{to, (int)g[to].size(), cap, cost});
        g[to].push_back(Edge{from, (int)g[from].size()-1, 0, -cost});
    }
    /**
     * 最小費用流を計算する
     *
     * bellに関わらず、負閉路が存在する場合はこのプログラムでは解けないことに注意
     *
     * Params:
     *   s = 始点
     *   t = 終点
     *   f = 流す量
     *   bell = 負のコストの辺が存在するかどうか
     */
    T exec(int s, int t, C f, bool bell = false) {
        T res = 0;
        fill_n(h, V, 0);
        while (f > EPS) {
            fill_n(dist, V, INF);
            dist[s] = 0;
            if (bell) {
                bell = false;
                bool update;
                do {
                    update = false;
                    for (int v = 0; v < V; v++) {
                        if (dist[v] == INF) continue;
                        for (int i = 0; i < (int)g[v].size(); i++) {
                            Edge &e = g[v][i];
                            if (e.cap > EPS && dist[e.to] > dist[v] + e.cost) {
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
                    for (int i = 0; i < (int)g[v].size(); i++) {
                        Edge &e = g[v][i];
                        if (e.cap > EPS && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
                            dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
                            pv[e.to] = v;
                            pe[e.to] = i;
                            que.push(P(dist[e.to], e.to));
                        }
                    }
                }
            }
            if (dist[t] == INF) {
                return INF;
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
