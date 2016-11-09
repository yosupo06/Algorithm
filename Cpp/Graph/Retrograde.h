/**
 * d[i] = 
 *   -1:このマスからスタートすると先手が負ける
 *    0:?
 *    1:このマスからスタートすると先手が勝つ
 */
template<class E>
void retrograde(const Graph<E> &g, const Graph<E> &rg, vector<int> &d) {
    int V = (int)g.size();
    vector<int> count(V);
    for (int i = 0; i < V; i++) {
        count[i] = (int)g[i].size();
    }
    for (int i = 0; i < V; i++) {
        if (d[i] == 1) {
            for (E e: rg[i]) {
                count[e.to]--;
            }
        }
    }
    for (int i = 0; i < V; i++) {
        if (d[i] == -1) {
            for (E e: rg[i]) {
                if (d[e.to]) continue;
                d[e.to] = 1;
                for (E f: rg[e.to]) {
                    count[f.to]--;
                }
            }
        }
    }
    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (count[i]) continue;
        q.push(i);
    }
    while (q.size()) {
        int p = q.front(); q.pop();
        if (d[p]) continue;
        d[p] = -1;
        for (E e: rg[p]) {
            if (d[e.to]) continue;
            d[e.to] = 1;
            for (E f: rg[e.to]) {
                count[f.to]--;
                if (!count[f.to]) {
                    q.push(f.to);
                }
            }
        }
    }
}
