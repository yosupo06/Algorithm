struct Ariticulation {
    V<bool> is_arit; // is Ariticulation point
    V<bool> is_div; // is Div when parent remove
    Ariticulation() {}
    Ariticulation(int n) {
        is_arit = V<bool>(n);
        is_div = V<bool>(n);
    }
};

template<class E>
Ariticulation ariticulation(const VV<E> &g, const LowLink &lc) {
    int n = int(g.size());
    Ariticulation ar(n);
    auto &is_arit = ar.is_arit;
    auto &is_div = ar.is_div;
    for (int p: lc.vlis) {
        if (lc.par[p] == -1) {
            //root
            is_arit[p] = (lc.tr[p].size() >= 2);
            for (int d: lc.tr[p]) {
                is_div[d] = true;
            }
        } else {
            is_arit[p] = false;
            for (int d: lc.tr[p]) {
                if (lc.low[d] >= lc.ord[p]) {
                    is_arit[p] = true;
                    is_div[d] = true;
                }
            }
        }
    }
    return ar;
}
template<class E>
Ariticulation ariticulation(const VV<E> &g) {
    return ariticulation(g, lowlink(g, -1));
}
