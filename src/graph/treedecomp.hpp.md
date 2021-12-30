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
    path: src/util/hash.hpp
    title: src/util/hash.hpp
  - icon: ':heavy_check_mark:'
    path: src/util/random.hpp
    title: src/util/random.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: src/graph/balancedseparator.hpp
    title: src/graph/balancedseparator.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: src/treedecomp_width2.test.cpp
    title: src/treedecomp_width2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: base.hpp: line\
    \ -1: no such header\n"
  code: "#pragma once\n\n#include \"base.hpp\"\n#include \"graph/primitive.hpp\"\n\
    #include \"datastructure/hashset.hpp\"\n#include \"datastructure/hashmap.hpp\"\
    \n#include \"datastructure/simplequeue.hpp\"\n\nstruct TreeDecomp {\n    VV<SimpleEdge>\
    \ tr;\n    VV<int> bags;\n};\n\n\ntemplate <class E>\nTreeDecomp decomp_width2(VV<E>\
    \ _g) {\n    int n = int(_g.size());\n    assert(n);\n\n    V<HashSet<int>> g(n);\n\
    \    for (int i = 0; i < n; i++) {\n        for (auto e : _g[i]) {\n         \
    \   int j = e.to;\n            g[i].insert(j);\n        }\n    }\n\n    V<int>\
    \ deg(n);\n    V<bool> alive(n, true);\n    SimpleQueue<int> que;\n    for (int\
    \ i = 0; i < n; i++) {\n        deg[i] = int(g[i].size());\n        que.push(i);\n\
    \    }\n\n    struct Event {\n        int deg;\n        int a, b, c;\n    };\n\
    \    V<Event> events;\n\n    V<int> nears;\n    auto remove = [&](int p) {\n \
    \       assert(alive[p]);\n        alive[p] = false;\n        for (int i: nears)\
    \ {\n            assert(alive[i]);\n            g[i].erase(p);\n            deg[i]--;\n\
    \            que.push(i);\n        }\n    };\n    while (que.size()) {\n     \
    \   int p = que.front();\n        que.pop();\n        int d = deg[p];\n      \
    \  if (!alive[p] || d >= 3) continue;\n        nears = g[p].to_vec();\n      \
    \  assert(int(nears.size()) == d);\n        if (d == 0) {\n            events.push_back({0,\
    \ p, -1, -1});\n        }\n        if (d == 1) {\n            events.push_back({1,\
    \ p, nears[0], -1});\n        }\n        if (d == 2) {\n            int u = nears[0];\n\
    \            int v = nears[1];\n            events.push_back({2, p, u, v});\n\
    \            g[u].insert(v);\n            g[v].insert(u);\n            deg[u]\
    \ = int(g[u].size());\n            deg[v] = int(g[v].size());\n        }\n   \
    \     remove(p);\n    }\n\n    for (int i = 0; i < n; i++) {\n        if (alive[i])\
    \ {\n            return TreeDecomp{};\n        }\n    }\n\n    TreeDecomp td;\n\
    \    V<int> par;\n    V<int> node_pos(n, -1);\n    HashMap<pair<int, int>, int>\
    \ edge_pos;\n    reverse(events.begin(), events.end());\n    for (auto event :\
    \ events) {\n        int id = int(td.bags.size());\n        if (event.deg == 0)\
    \ {\n            td.bags.push_back({event.a});\n            par.push_back(id -\
    \ 1);\n        }\n        if (event.deg == 1) {\n            td.bags.push_back({event.a,\
    \ event.b});\n            par.push_back(node_pos[event.b]);\n        }\n     \
    \   if (event.deg == 2) {\n            td.bags.push_back({event.a, event.b, event.c});\n\
    \            par.push_back(edge_pos.get(minmax(event.b, event.c)));\n        }\n\
    \        for (int x : td.bags.back()) {\n            node_pos[x] = id;\n     \
    \   }\n        for (int x : td.bags.back()) {\n            for (int y : td.bags.back())\
    \ {\n                if (x < y) edge_pos.set({x, y}, id);\n            }\n   \
    \     }\n    }\n    int K = int(td.bags.size());\n    td.tr = VV<SimpleEdge>(K);\n\
    \    for (int i = 1; i < K; i++) {\n        td.tr[par[i]].push_back({i});\n  \
    \      td.tr[i].push_back({par[i]});\n    }\n    return td;\n}\n"
  dependsOn:
  - src/base.hpp
  - src/graph/primitive.hpp
  - src/datastructure/hashset.hpp
  - src/util/hash.hpp
  - src/util/random.hpp
  - src/datastructure/hashmap.hpp
  - src/datastructure/simplequeue.hpp
  isVerificationFile: false
  path: src/graph/treedecomp.hpp
  requiredBy:
  - src/graph/balancedseparator.hpp
  timestamp: '2021-12-30 20:52:19+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - src/treedecomp_width2.test.cpp
documentation_of: src/graph/treedecomp.hpp
layout: document
redirect_from:
- /library/src/graph/treedecomp.hpp
- /library/src/graph/treedecomp.hpp.html
title: src/graph/treedecomp.hpp
---
