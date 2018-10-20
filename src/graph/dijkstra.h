template <class D> struct Dijkstra {
    V<D> dist;
    V<int> from;
};

template <class D, class E> struct DijkstraExec : Dijkstra<D> {
    using Dijkstra<D>::dist;
    using Dijkstra<D>::from;
    DijkstraExec(const VV<E>& g, int s, D inf = numeric_limits<D>::max()) {
        int n = (int)g.size();
        dist = V<D>(n, inf);
        from = V<int>(n);
        using P = pair<D, int>;
        priority_queue<P, vector<P>, greater<P>> q;
        q.push(P(0, s));
        dist[s] = D(0);
        while (!q.empty()) {
            P p = q.top();
            q.pop();
            if (dist[p.second] < p.first) continue;
            for (E e : g[p.second]) {
                if (p.first + e.dist < dist[e.to]) {
                    dist[e.to] = p.first + e.dist;
                    from[e.to] = p.second;
                    q.push(P(dist[e.to], e.to));
                }
            }
        }
    }
};
template <class D, class E>
Dijkstra<D> get_dijkstra(const VV<E>& g,
                         int s,
                         D inf = numeric_limits<D>::max()) {
    return DijkstraExec<D, E>(g, s, inf);
}