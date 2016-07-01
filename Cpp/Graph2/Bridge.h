/**
 * 橋の検出
 */
struct Bridge {
    int gc;
    vector<int> ig; // i to group
    vector<int> gpar; // group par

    template<class E>
    void exec(const Graph<E> &g, int r) {
        int V = (int)g.size();
        LowLink lc(g, r);
        ig.resize(V);
        gc = 0;
        for (int p: lc.vlis) {
            if (lc.low[p] == lc.ord[p]) {
                ig[p] = gc++;
                gpar.push_back((p == r) ? -1 : ig[lc.par[p]]);
            } else {
                ig[p] = ig[lc.par[p]];
            }
        }
    }
};
