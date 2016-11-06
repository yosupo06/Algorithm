/**
 * 関節点の検出
 */
struct Ariticulation {
    vector<bool> isArit; // is Ariticulation point
    vector<bool> isDiv; // is Div when parent remove
    template<class E>
    Ariticulation(const Graph<E> &g, const LowLink &lc) {
        int V = (int)g.size();
        isArit.resize(V); isDiv.resize(V);
        for (int p: lc.vlis) {
            if (lc.par[p] == -1) {
                //root
                isArit[p] = (lc.tr[p].size() >= 2);
                for (int d: lc.tr[p]) {
                    isDiv[d] = true;
                }
            } else {
                isArit[p] = false;
                for (int d: lc.tr[p]) {
                    if (lc.low[d] >= lc.ord[p]) {
                        isArit[p] = true;
                        isDiv[d] = true;
                    }
                }
            }
        }
    }
};
