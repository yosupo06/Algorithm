/*
二つあるが基本的にMinCostFlowをそのまま置き換えられる
どちらも定数倍改善がされたPrimal-dual法 負辺は未対応
改善率はたかだか2,3倍なので当てにしないこと
*/

template<int V>
struct MinCostFlowOptimize {
    using T = int;
    using P = pair<T, int>;
    const T INF = 1<<27;
    struct Edge {
        int to, rev;
        int cap;
        T cost;
    };
    vector<Edge> g[V];
    void add(int from, int to, int cap, T cost) {
        g[from].push_back(Edge{to, (int)g[to].size(), cap, cost});
        g[to].push_back(Edge{from, (int)g[from].size()-1, 0, (T)(-cost)});
    }

    T h[V], dist[V];
    bool used[V];
    Edge *prev[V];
    T exec(int s, int t, int f) {
        T res = 0;
        fill_n(h, V, 0);
        while (f > 0) {
            fill_n(dist, V, INF);
            fill_n(used, V, false);
            dist[s] = 0;
            priority_queue<P, vector<P>, greater<P>> que;
            que.push(P(0, s));
            while (!que.empty()) {
                P p = que.top(); que.pop();
                int v = p.second;
                if (v == t) break;
                if (used[v]) continue;
                used[v] = true;
                int hv = h[v], distv = dist[v];                
                for (Edge &e: g[v]) {
                    if (!e.cap) continue;
                    T ee = e.cost-hv+h[e.to];
                    if (dist[e.to] > distv+ee) {
                        dist[e.to] = distv+ee;
                        prev[e.to] = &e;
                        que.push(P(dist[e.to], e.to));
                    }
                }
            }
            if (dist[t] == INF) {
                return -1;
            }
            for (int v = 0; v < V; v++) {
                if (dist[v] >= dist[t]) continue;
                h[v] += dist[t]-dist[v];
            }
            T d = f;
            for (int v = t; v != s; v = g[v][prev[v]->rev].to) {
                d = min(d, prev[v]->cap);
            }
            f -= d;
            res += d * (h[s]-h[t]);
            for (int v = t; v != s; v = g[v][prev[v]->rev].to) {
                prev[v]->cap -= d;
                g[v][prev[v]->rev].cap += d;
            }
        }
        return res;
    }
};

template<int V>
struct MinCostFlowOptimize {
    using T = int;
    using P = pair<T, int>;
    const T INF = 1<<27;
    int c = 0;
    struct Edge {
        int to, rev;
        short cap, size;
        T cost;
    };
    vector<Edge> g[V];
    void add(int from, int to, short cap, T cost) {
        g[from].push_back(Edge{to, (int)g[to].size(), cap, cap, cost});
        g[to].push_back(Edge{from, (int)g[from].size()-1, 0, cap, (T)(-cost)});
    }

    T h[V], dist[V], rdist[V];
    bool used[V], rused[V];
    Edge *prev[V], *rprev[V];
    T exec(int s, int t, short f) {
        T res = 0;
        fill_n(h, V, 0);
        RadixHeap q, rq;
        int C = 2;
        while (true) {
            int tp;
            fill_n(dist, V, INF);
            dist[s] = 0;
            fill_n(used, V, false);
            q.clear();
            q.push(0, s);
            int c = 0;
            while (!q.empty()) {
                P p = q.pop();
                int v = p.second;
                if (used[v]) continue;
                used[v] = true;
                tp = v;
                if (v == t) break;
                c++;
                if (c == C) break;
                int hv = h[v], distv = dist[v];
                for (Edge &e: g[v]) {
                    if (!e.cap) continue;
                    T ee = e.cost-hv+h[e.to];
                    if (dist[e.to] > distv+ee) {
                        dist[e.to] = distv+ee;
                        prev[e.to] = &e;
                        q.push(dist[e.to], e.to);
                    }
                }
            }
            for (int v = 0; v < V; v++) {
                if (dist[v] >= dist[tp]) continue;
                h[v] += dist[tp]-dist[v];
            }
            tp = -1;
            fill_n(rdist, V, INF);
            rdist[t] = 0;
            fill_n(rused, V, false);
            rq.clear();
            rq.push(0, t);
            c = 0;
            while (!rq.empty()) {
                P p = rq.pop();
                int v = p.second;
                if (rused[v]) continue;
                rused[v] = true;
                if (used[v]) {
                    tp = v;
                    break;
                }
                c++;
                if (c == C) break;
                int hv = h[v], rdistv = rdist[v];
                for (Edge &e: g[v]) {
                    if (e.size == e.cap) continue;
                    T ee = -e.cost-h[e.to]+hv;
                    if (rdist[e.to] > rdistv+ee) {
                        rdist[e.to] = rdistv+ee;
                        rprev[e.to] = &e;
                        rq.push(rdist[e.to], e.to);
                    }
                }
            }
            if (tp == -1) {
                if (C == V) return -1;
                C = min(2*C, V);
                continue;
            }
            for (int v = 0; v < V; v++) {
                if (rdist[v] >= rdist[tp]) continue;
                h[v] -= rdist[tp]-rdist[v];
            }
            auto d = f;
            for (int v = tp; v != s; v = g[v][prev[v]->rev].to) {
                d = min(d, prev[v]->cap);
            }
            for (int v = tp; v != t; v = g[v][rprev[v]->rev].to) {
                d = min(d, g[v][rprev[v]->rev].cap);
            }
            f -= d;
            res += d * (h[s]-h[t]);
            for (int v = tp; v != s; v = g[v][prev[v]->rev].to) {
                prev[v]->cap -= d;
                g[v][prev[v]->rev].cap += d;
            }
            for (int v = tp; v != t; v = g[v][rprev[v]->rev].to) {
                rprev[v]->cap += d;
                g[v][rprev[v]->rev].cap -= d;
            }
            if (!f) break;
        }
        return res;
    }
};