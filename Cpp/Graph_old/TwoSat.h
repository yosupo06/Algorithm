/**
 * TwoSat
 */
template<int V>
struct TwoSat {
    SCC<2*V> scc;
    void init() {
        scc.init();
    }
    // (x_a == apos) v (x_b == bpos)
    void add(int a, bool apos, int b, bool bpos) {
        scc.add(a+(apos?V:0), b+(bpos?0:V));
        scc.add(b+(bpos?V:0), a+(apos?0:V));
    }
    bool res[V];
    bool exec() {
        scc.exec(2*V);
        for (int i = 0; i < V; i++) {
            if (scc.res[i] == scc.res[i+V]) return false;
            res[i] = scc.res[i] > scc.res[i+V];
        }
        return true;
    }
};
