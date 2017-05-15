struct Bridge {
    V<bool> is_root; // is root of group
    int count; // group count
    V<int> id, root; // i to group, group root
    Bridge() {}
    Bridge(int n) {
        is_root = V<bool>(n);
        id = V<int>(n);
    }
};

template<class E>
Bridge bridge(const VV<E> &g, const LowLink &lc) {
    int n = int(g.size());
    Bridge br(n);
    auto &is_root = br.is_root;
    auto &id = br.id;
    auto &root = br.root;
    auto &count = br.count;

    count = 0;
    for (int p: lc.vlis) {
        is_root[p] = (lc.low[p] == lc.ord[p]);
        if (is_root[p]) {
            id[p] = count++;
            root.push_back((lc.par[p] == -1) ? -1 : id[lc.par[p]]);
        } else {
            id[p] = id[lc.par[p]];
        }
    }

    return br;
}
template<class E>
Bridge bridge(const VV<E> &g) { return bridge(g, lowlink(g, -1)); }
