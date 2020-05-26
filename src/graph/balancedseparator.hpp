#pragma once

#include "base.hpp"
#include "graph/primitive.hpp"
#include "graph/treedecomp.hpp"
#include "tree/centroid.hpp"

struct BalancedSeparator {
    int num_layer;
    VV<SimpleEdge> tr;
    VV<int> bags;
    V<int> lv;
    V<int> pos;
    V<int> par;

    // lca bag of vertex u, v
    int lca(int u, int v) const {
        u = pos[u]; v = pos[v];
        while (u != v) {
//            dbg(u, v, lv[u], lv[v], par[u], par[v]);
            if (lv[u] < lv[v]) swap(u, v);
            u = par[u];
        }
        return u;
    }
};

BalancedSeparator balanced_separator(const TreeDecomp& td) {
    int n = 0;
    for (auto bag: td.bags) {
        for (auto v: bag) {
            n = max(n, v + 1);
        }
    }
    BalancedSeparator bs;
    bs.pos = V<int>(n, -1);

    auto cent = get_centroid(td.tr);

    auto cdfs = [&](auto self, int p, int bk_id, int now_lv) -> int {
        int id = int(bs.tr.size());
        bs.tr.push_back({});
        bs.bags.push_back({});
        bs.par.push_back(bk_id);
        bs.lv.push_back(now_lv);
        for (auto v : td.bags[p]) {
            if (bs.pos[v] != -1) continue;
            bs.pos[v] = id;
            bs.bags[id].push_back(v);
        }

        for (int d : cent.tr[p]) {
            int cid = self(self, d, id, now_lv + 1);
            bs.tr[id].push_back({cid});
        }
        return id;
    };    
    cdfs(cdfs, cent.r, -1, 0);
    bs.num_layer = 0;
    for (int x: bs.lv) bs.num_layer = max(bs.num_layer, x + 1);

    return bs;
}
