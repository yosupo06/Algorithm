---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"src/tree/alltree.hpp\"\ntemplate <class N, class E> struct\
    \ AllTree {\n    int n;\n    const VV<E>& g;\n    V<N> sm;\n    VV<N> dp;  //\
    \ tree\n    void dfs1(int p, int b) {\n        sm[p] = N();\n        for (auto\
    \ e : g[p]) {\n            int d = e.to;\n            if (d == b) continue;\n\
    \            dfs1(d, p);\n            sm[p] = sm[p] + sm[d].to_subs(p, e);\n \
    \       }\n        sm[p] = sm[p].join(p);\n    }\n    void dfs2(int p, int b,\
    \ N top) {\n        int deg = int(g[p].size());\n        dp[p] = V<N>(deg + 1);\n\
    \        dp[p][0] = N();\n        for (int i = 0; i < deg; i++) {\n          \
    \  int d = g[p][i].to;\n            dp[p][i + 1] =\n                dp[p][i] +\
    \ (d == b ? top : sm[d]).to_subs(p, g[p][i]);\n        }\n        N rnode = N();\n\
    \        dp[p].back() = dp[p].back().join(p);\n        for (int i = deg - 1; i\
    \ >= 0; i--) {\n            dp[p][i] = (dp[p][i] + rnode).join(p);\n         \
    \   int d = g[p][i].to;\n            if (d != b) dfs2(d, p, dp[p][i]);\n     \
    \       rnode = rnode + (d == b ? top : sm[d]).to_subs(p, g[p][i]);\n        }\n\
    \    }\n    AllTree(const VV<E>& _g) : n(int(_g.size())), g(_g), sm(n), dp(n)\
    \ {\n        dfs1(0, -1);\n        dfs2(0, -1, N());\n    }\n};\n\ntemplate <class\
    \ N, class E> VV<N> get_all_tree(const VV<E>& g) {\n    return AllTree<N, E>(g).dp;\n\
    }\n\nstruct Node {\n    // Educational DP Contest V - Subtree\n    Mint sm = Mint(1);\n\
    \    template <class E> Node to_subs(int, const E&) const {\n        // tree ->\
    \ subtrees\n        return {sm + 1};\n    }\n    Node operator+(const Node& r)\
    \ const {\n        // subtrees + subtrees\n        return {sm * r.sm};\n    }\n\
    \    Node join(int) const {\n        // subtrees -> tree\n        return *this;\n\
    \    }\n};\n\nstruct Node {\n    // Diameter of Tree\n    int rad = 0, dia = 0;\
    \         // radius(tree), diameter\n    array<int, 2> rd = {{0, 0}};  // radiuses(subtrees)\n\
    \    template <class E> Node to_subs(int, const E& e) const {\n        // tree\
    \ -> subtrees\n        return {-1, dia, {rad + e.dist, 0}};\n    }\n    Node operator+(const\
    \ Node& r) const {\n        // subtrees + subtrees\n        array<int, 4> v =\
    \ {rd[0], rd[1], r.rd[0], r.rd[1]};\n        sort(v.begin(), v.end(), greater<>());\n\
    \        return {-1, max(dia, r.dia), {v[0], v[1]}};\n    }\n    Node join(int)\
    \ const {\n        // subtrees -> tree\n        return {rd[0], max(dia, rd[0]\
    \ + rd[1]), {}};\n    }\n};\n"
  code: "template <class N, class E> struct AllTree {\n    int n;\n    const VV<E>&\
    \ g;\n    V<N> sm;\n    VV<N> dp;  // tree\n    void dfs1(int p, int b) {\n  \
    \      sm[p] = N();\n        for (auto e : g[p]) {\n            int d = e.to;\n\
    \            if (d == b) continue;\n            dfs1(d, p);\n            sm[p]\
    \ = sm[p] + sm[d].to_subs(p, e);\n        }\n        sm[p] = sm[p].join(p);\n\
    \    }\n    void dfs2(int p, int b, N top) {\n        int deg = int(g[p].size());\n\
    \        dp[p] = V<N>(deg + 1);\n        dp[p][0] = N();\n        for (int i =\
    \ 0; i < deg; i++) {\n            int d = g[p][i].to;\n            dp[p][i + 1]\
    \ =\n                dp[p][i] + (d == b ? top : sm[d]).to_subs(p, g[p][i]);\n\
    \        }\n        N rnode = N();\n        dp[p].back() = dp[p].back().join(p);\n\
    \        for (int i = deg - 1; i >= 0; i--) {\n            dp[p][i] = (dp[p][i]\
    \ + rnode).join(p);\n            int d = g[p][i].to;\n            if (d != b)\
    \ dfs2(d, p, dp[p][i]);\n            rnode = rnode + (d == b ? top : sm[d]).to_subs(p,\
    \ g[p][i]);\n        }\n    }\n    AllTree(const VV<E>& _g) : n(int(_g.size())),\
    \ g(_g), sm(n), dp(n) {\n        dfs1(0, -1);\n        dfs2(0, -1, N());\n   \
    \ }\n};\n\ntemplate <class N, class E> VV<N> get_all_tree(const VV<E>& g) {\n\
    \    return AllTree<N, E>(g).dp;\n}\n\nstruct Node {\n    // Educational DP Contest\
    \ V - Subtree\n    Mint sm = Mint(1);\n    template <class E> Node to_subs(int,\
    \ const E&) const {\n        // tree -> subtrees\n        return {sm + 1};\n \
    \   }\n    Node operator+(const Node& r) const {\n        // subtrees + subtrees\n\
    \        return {sm * r.sm};\n    }\n    Node join(int) const {\n        // subtrees\
    \ -> tree\n        return *this;\n    }\n};\n\nstruct Node {\n    // Diameter\
    \ of Tree\n    int rad = 0, dia = 0;         // radius(tree), diameter\n    array<int,\
    \ 2> rd = {{0, 0}};  // radiuses(subtrees)\n    template <class E> Node to_subs(int,\
    \ const E& e) const {\n        // tree -> subtrees\n        return {-1, dia, {rad\
    \ + e.dist, 0}};\n    }\n    Node operator+(const Node& r) const {\n        //\
    \ subtrees + subtrees\n        array<int, 4> v = {rd[0], rd[1], r.rd[0], r.rd[1]};\n\
    \        sort(v.begin(), v.end(), greater<>());\n        return {-1, max(dia,\
    \ r.dia), {v[0], v[1]}};\n    }\n    Node join(int) const {\n        // subtrees\
    \ -> tree\n        return {rd[0], max(dia, rd[0] + rd[1]), {}};\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: src/tree/alltree.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/tree/alltree.hpp
layout: document
redirect_from:
- /library/src/tree/alltree.hpp
- /library/src/tree/alltree.hpp.html
title: src/tree/alltree.hpp
---
