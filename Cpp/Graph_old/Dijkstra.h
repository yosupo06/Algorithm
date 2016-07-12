/**
 * Dijkstra法により最短距離を求める
 *
 * template引数のint Vは頂点数
 */
template<int V>
struct Dijkstra {
    using T = int; /// 辺の距離の型
    const int INF = 1<<28;
    typedef pair<T, int> P;
    vector<P> g[V];
    /// 辺のクリア
    void init() {
        for (int i = 0; i < V; i++) {
            g[i].clear();
        }
    }
    /// 辺の追加
    void add(int from, int to, T dist) {
        g[from].push_back(P(dist, to));
    }
    T res[V]; /// execを行うと、これに最短距離が入る 
    void exec(int s) {
        fill_n(res, V, INF);
        priority_queue<P, vector<P>, greater<P>> q;
        q.push(P(0, s));
        res[s] = 0;
        while (!q.empty()) {
            P p = q.top(); q.pop();
            if (res[p.second] < p.first) continue;
            for (P e: g[p.second]) {
                if (p.first+e.first < res[e.second]) {
                    res[e.second] = p.first+e.first;
                    q.push(P(p.first+e.first, e.second));
                }
            }
        }
        return;
    }
};
