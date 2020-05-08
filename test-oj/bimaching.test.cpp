#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"

#include "base.hpp"
#include "util/fast_io.hpp"
#include "graph/bimaching.hpp"

int main() {
    Scanner sc(stdin);
    Printer pr(stdout);
    int l, r, m;
    sc.read(l, r, m);
    V<pair<int, int>> edges(m);
    for (int i = 0; i < m; i++) {
        sc.read(edges[i].first, edges[i].second);
    }
    BipartiteMaching bm(l, r, edges);
    V<pair<int, int>> ans;
    for (int i = 0; i < l; i++) {
        if (bm.lmt[i] != -1) {
            ans.push_back({i, bm.lmt[i]});
        }
    }
    pr.writeln(ans.size());
    for (auto p : ans) {
        pr.writeln(p.first, p.second);
    }
    return 0;
}
