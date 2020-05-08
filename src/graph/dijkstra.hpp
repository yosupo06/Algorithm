template <class D> struct MinDist {
    V<D> dist;
    V<int> from;
};

template <class D, class E>
MinDist<D> mindist(const VV<E>& g, int s, D inf = numeric_limits<D>::max()) {
    int n = (int)g.size();
    V<D> dist = V<D>(n, inf);
    V<int> from = V<int>(n);
    struct P {
        D key;
        int to;
        bool operator<(P r) const { return key > r.key; }
    };
    priority_queue<P> q;
    q.push(P{0, s});
    dist[s] = D(0);
    while (!q.empty()) {
        P p = q.top();
        q.pop();
        if (dist[p.to] < p.key) continue;
        for (E e : g[p.to]) {
            if (p.key + e.dist < dist[e.to]) {
                dist[e.to] = p.key + e.dist;
                from[e.to] = p.to;
                q.push(P{dist[e.to], e.to});
            }
        }
    }
    return MinDist<D>{dist, from};
}
