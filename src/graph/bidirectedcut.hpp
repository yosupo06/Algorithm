template<class D, D INF>
struct BidirectedCut {
    D sum = INF;
    template<class E>
    BidirectedCut(VV<E> g) {
        int n = (int)g.size();
        int m_a = -1, m_b = -1;
        V<D> dist_base(n, 0);
        for (int m = n; m > 1; m--) {
            int a, b;
            auto dist = dist_base;
            for (int i = 0; i < m; i++) {
                a = b; b = max_element(begin(dist), end(dist)) - begin(dist);
                if (i == m-1) sum = min(sum, dist[b]);
                dist[b] = -INF;
                for (E &e: g[b]) {
                    if (e.to == m_b) e.to = m_a;
                    if (dist[e.to] == -INF) continue;
                    dist[e.to] += e.dist;
                }
            }
            //merge a, b
            m_a = a; m_b = b;
            g[a].insert(end(g[a]), begin(g[b]), end(g[b]));
            g[b].clear();
            dist_base[b] = -INF;
        }
    }
};
