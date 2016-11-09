template<class D, D INF>
struct Dijkstra {
    vector<D> res; //res[i] = sからiまでの最短距離
    
    template<class E>
    Dijkstra(const Graph<E> &g, int s) {
        int V = (int)g.size();
        res = vector<D>(V, INF);
        
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
