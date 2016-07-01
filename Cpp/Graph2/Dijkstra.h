/**
 * Dijkstra法により最短距離を求める
 *
 * template引数のint Vは頂点数
 * ---
 * struct Edge {
 *     int to;
 *     T dist;
 * };
 * ---
 */
template<class D, D INF>
struct Dijkstra {
    vector<D> res; //res[i] = sからiまでの最短距離
    
    template<class E>
    void exec(const Graph<E> &g, int s) {
        int V = (int)g.size();
        res.resize(V); fill_n(res.begin(), V, INF);
        using P = pair<D, int>;
        priority_queue<P, vector<P>, greater<P>> q;
        q.push(P(0, s));
        res[s] = 0;
        while (!q.empty()) {
            P p = q.top(); q.pop();
            if (res[p.second] < p.first) continue;
            for (E e: g[p.second]) {
                if (p.first+e.dist < res[e.to]) {
                    res[e.to] = p.first+e.dist;
                    q.push(P(res[e.to], e.to));
                }
            }
        }
    }
};
