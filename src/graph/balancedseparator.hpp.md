---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/base.hpp
    title: src/base.hpp
  - icon: ':heavy_check_mark:'
    path: src/datastructure/hashmap.hpp
    title: src/datastructure/hashmap.hpp
  - icon: ':heavy_check_mark:'
    path: src/datastructure/hashset.hpp
    title: src/datastructure/hashset.hpp
  - icon: ':heavy_check_mark:'
    path: src/datastructure/simplequeue.hpp
    title: src/datastructure/simplequeue.hpp
  - icon: ':heavy_check_mark:'
    path: src/graph/primitive.hpp
    title: src/graph/primitive.hpp
  - icon: ':heavy_check_mark:'
    path: src/graph/treedecomp.hpp
    title: src/graph/treedecomp.hpp
  - icon: ':warning:'
    path: src/tree/centroid.hpp
    title: src/tree/centroid.hpp
  - icon: ':heavy_check_mark:'
    path: src/util/hash.hpp
    title: src/util/hash.hpp
  - icon: ':heavy_check_mark:'
    path: src/util/random.hpp
    title: src/util/random.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: base.hpp: line\
    \ -1: no such header\n"
  code: "#pragma once\n\n#include \"base.hpp\"\n#include \"graph/primitive.hpp\"\n\
    #include \"graph/treedecomp.hpp\"\n#include \"tree/centroid.hpp\"\n\nstruct BalancedSeparator\
    \ {\n    int num_layer;\n    VV<SimpleEdge> tr;\n    VV<int> bags;\n    V<int>\
    \ lv;\n    V<int> pos;\n    V<int> par;\n\n    // lca bag of vertex u, v\n   \
    \ int lca(int u, int v) const {\n        u = pos[u]; v = pos[v];\n        while\
    \ (u != v) {\n//            dbg(u, v, lv[u], lv[v], par[u], par[v]);\n       \
    \     if (lv[u] < lv[v]) swap(u, v);\n            u = par[u];\n        }\n   \
    \     return u;\n    }\n};\n\nBalancedSeparator balanced_separator(const TreeDecomp&\
    \ td) {\n    int n = 0;\n    for (auto bag: td.bags) {\n        for (auto v: bag)\
    \ {\n            n = max(n, v + 1);\n        }\n    }\n    BalancedSeparator bs;\n\
    \    bs.pos = V<int>(n, -1);\n\n    auto cent = get_centroid(td.tr);\n\n    auto\
    \ cdfs = [&](auto self, int p, int bk_id, int now_lv) -> int {\n        int id\
    \ = int(bs.tr.size());\n        bs.tr.push_back({});\n        bs.bags.push_back({});\n\
    \        bs.par.push_back(bk_id);\n        bs.lv.push_back(now_lv);\n        for\
    \ (auto v : td.bags[p]) {\n            if (bs.pos[v] != -1) continue;\n      \
    \      bs.pos[v] = id;\n            bs.bags[id].push_back(v);\n        }\n\n \
    \       for (int d : cent.tr[p]) {\n            int cid = self(self, d, id, now_lv\
    \ + 1);\n            bs.tr[id].push_back({cid});\n        }\n        return id;\n\
    \    };    \n    cdfs(cdfs, cent.r, -1, 0);\n    bs.num_layer = 0;\n    for (int\
    \ x: bs.lv) bs.num_layer = max(bs.num_layer, x + 1);\n\n    return bs;\n}\n"
  dependsOn:
  - src/base.hpp
  - src/graph/primitive.hpp
  - src/graph/treedecomp.hpp
  - src/datastructure/hashset.hpp
  - src/util/hash.hpp
  - src/util/random.hpp
  - src/datastructure/hashmap.hpp
  - src/datastructure/simplequeue.hpp
  - src/tree/centroid.hpp
  isVerificationFile: false
  path: src/graph/balancedseparator.hpp
  requiredBy: []
  timestamp: '2020-10-18 20:05:46+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/graph/balancedseparator.hpp
layout: document
redirect_from:
- /library/src/graph/balancedseparator.hpp
- /library/src/graph/balancedseparator.hpp.html
title: src/graph/balancedseparator.hpp
---
