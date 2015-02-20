/*
execでresに最短距離が入る
*/
template<int V>
struct Dijkstra {
    using T = int;
    using P = pair<T, int>;
    const T INF = 1<<28;
    vector<P> g[V];
    void add(int from, int to, T dist) {
        g[from].push_back(P(dist, to));
    }
    T res[V];
    void exec(int s) {
        fill_n(res, V, INF);
        priority_queue<P, vector<P>, greater<P>> q;
        q.push(P(0, s));
        while (!q.empty()) {
            P p = q.top(); q.pop();
            if (res[p.second] < p.first) continue;
            res[p.second] = p.first;
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
