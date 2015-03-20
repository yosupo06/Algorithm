/*
execでresに最短距離が入る
*/
template<int V>
struct Dijkstra {
    typedef R T;
    typedef pair<T, int> P;
    const R INF = 1e9;
    vector<P> g[V];
    void init() {
        for (int i = 0; i < V; i++) {
            g[i].clear();
        }
    }
    void add(int from, int to, T dist) {
        g[from].push_back(P(dist, to));
    }
    T res[V];
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
                    q.push(P(e.first+p.first, e.second));
                }
            }
        }
        return;
    }
};


