/**
 * 橋の検出
 */
struct Bridge {
    int gc;
    vector<int> ig; // i to group
    vector<int> gpar; // group par
    vector<bool> isRoot; // is root of group

    template<class E>
    Bridge(const Graph<E> &g, int r, const LowLink &lc) {
        int V = (int)g.size();
        ig.resize(V); isRoot.resize(V);
        gc = 0;
        for (int p: lc.vlis) {
            isRoot[p] = (lc.low[p] == lc.ord[p]);
            if (isRoot[p]) {
                ig[p] = gc++;
                gpar.push_back((p == r) ? -1 : ig[lc.par[p]]);
            } else {
                ig[p] = ig[lc.par[p]];
            }
        }
    }
};
