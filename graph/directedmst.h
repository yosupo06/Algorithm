template<class E>
struct DirectedMST {
    decltype(E::dist) cost = 0;
    V<E> mine; // min edge
    DirectedMST(const Graph<E> &g, int r) {
        int n = (int)g.size();
        mine = vector<E>(n);
        for (int i = 0; i < n; i++) {
            if (i == r) continue;
            assert((int)g[i].size());
            mine[i] = *min_element(g[i].begin(), g[i].end(),
                [](const E &l, const E &r){return l.dist < r.dist;});
            cost += mine[i].dist;
        }
        V<int> i2g(n, -1); i2g[r] = 0;
        int gc = 1;
        for (int i = 0; i < n; i++) {
            if (i2g[i] != -1) continue;
            int j = i;
            do {
                i2g[j] = gc++;
            } while (j = mine[j].to, i2g[j] == -1);
            if (i2g[j] < i2g[i]) continue;
            //roop
            int k = j;
            do {
                i2g[k] = i2g[j];
            } while(k = mine[k].to, k != j);
            gc = i2g[j]+1;
        }
        if (gc == n) return;
        Graph<E> ng(gc);
        for (int i = 0; i < n; i++) {
            if (i == r) continue;
            for (E e: g[i]) {
                if (i2g[e.to] == i2g[i]) continue;
                e.to = i2g[e.to];
                e.dist -= mine[i].dist;
                ng[i2g[i]].push_back(e);
            }
        }
        auto nme = DirectedMST(ng, 0).mine;
        vector<bool> ok(gc, false);
        for (int i = 0; i < n; i++) {
            if (i == r or ok[i2g[i]]) continue;
            for (E e: g[i]) {
                if (e.dist - mine[i].dist == nme[i2g[i]].dist) {
                    ok[i2g[i]] = true;
                    mine[i] = e;
                    cost += nme[i2g[i]].dist;
                    break;
                }
            }
        }
    }
};
