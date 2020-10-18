---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: src/graph/twosat.hpp
    title: src/graph/twosat.hpp
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"src/graph/scc.hpp\"\nstruct SCC {\n    V<int> id;\n    VV<int>\
    \ groups;\n};\n\ntemplate <class E> struct SCCExec : SCC {\n    int n;\n    const\
    \ VV<E>& g;\n    int tm = 0;\n    V<bool> flag;\n    V<int> low, ord, st;\n  \
    \  void dfs(int v) {\n        low[v] = ord[v] = tm++;\n        st.push_back(v);\n\
    \        flag[v] = true;\n        for (auto e : g[v]) {\n            if (ord[e.to]\
    \ == -1) {\n                dfs(e.to);\n                low[v] = min(low[v], low[e.to]);\n\
    \            } else if (flag[e.to]) {\n                low[v] = min(low[v], ord[e.to]);\n\
    \            }\n        }\n        if (low[v] == ord[v]) {\n            V<int>\
    \ gr;\n            while (true) {\n                int u = st.back();\n      \
    \          st.pop_back();\n                gr.push_back(u);\n                if\
    \ (u == v) break;\n            }\n            for (int x : gr) flag[x] = false;\n\
    \            groups.push_back(gr);\n        }\n    }\n    SCCExec(const VV<E>&\
    \ _g)\n        : n(int(_g.size())), g(_g), flag(n), low(n), ord(n, -1) {\n   \
    \     id = V<int>(n);\n        for (int i = 0; i < n; i++) {\n            if (ord[i]\
    \ == -1) dfs(i);\n        }\n        reverse(groups.begin(), groups.end());\n\
    \        for (int i = 0; i < int(groups.size()); i++) {\n            for (int\
    \ x : groups[i]) {\n                id[x] = i;\n            }\n        }\n   \
    \ }\n};\n\ntemplate <class E> SCC get_scc(const VV<E>& g) { return SCCExec<E>(g);\
    \ }\n\ntemplate <size_t N> struct BitsetSCCExec : SCC {\n    using B = bitset<N>;\n\
    \    int n;\n    const V<B>& g;\n    const V<B>& rg;\n    V<int> vs;\n    B unvis;\n\
    \    void dfs(int v) {\n        unvis.reset(v);\n        while (true) {\n    \
    \        int d = (unvis & g[v])._Find_first();\n            if (d >= n) break;\n\
    \            dfs(d);\n        }\n        vs.push_back(v);\n    }\n\n    void rdfs(int\
    \ v, int k) {\n        unvis.reset(v);\n        id[v] = k;\n        groups[k].push_back(v);\n\
    \        while (true) {\n            int d = (unvis & rg[v])._Find_first();\n\
    \            if (d >= n) break;\n            rdfs(d, k);\n        }\n    }\n\n\
    \    BitsetSCCExec(const V<B>& _g, const V<B>& _rg)\n        : n(int(_g.size())),\
    \ g(_g), rg(_rg) {\n        unvis.set();\n        for (int i = 0; i < n; i++)\
    \ {\n            if (unvis[i]) dfs(i);\n        }\n        reverse(vs.begin(),\
    \ vs.end());\n        unvis.set();\n        id = V<int>(n);\n        int k = 0;\n\
    \        for (int i : vs) {\n            if (unvis[i]) {\n                groups.push_back({});\n\
    \                rdfs(i, k++);\n            }\n        }\n    }\n};\n\ntemplate\
    \ <size_t N>\nSCC get_bitset_scc(const V<bitset<N>>& g, const V<bitset<N>>& rg)\
    \ {\n    return BitsetSCCExec<N>(g, rg);\n}\n"
  code: "struct SCC {\n    V<int> id;\n    VV<int> groups;\n};\n\ntemplate <class\
    \ E> struct SCCExec : SCC {\n    int n;\n    const VV<E>& g;\n    int tm = 0;\n\
    \    V<bool> flag;\n    V<int> low, ord, st;\n    void dfs(int v) {\n        low[v]\
    \ = ord[v] = tm++;\n        st.push_back(v);\n        flag[v] = true;\n      \
    \  for (auto e : g[v]) {\n            if (ord[e.to] == -1) {\n               \
    \ dfs(e.to);\n                low[v] = min(low[v], low[e.to]);\n            }\
    \ else if (flag[e.to]) {\n                low[v] = min(low[v], ord[e.to]);\n \
    \           }\n        }\n        if (low[v] == ord[v]) {\n            V<int>\
    \ gr;\n            while (true) {\n                int u = st.back();\n      \
    \          st.pop_back();\n                gr.push_back(u);\n                if\
    \ (u == v) break;\n            }\n            for (int x : gr) flag[x] = false;\n\
    \            groups.push_back(gr);\n        }\n    }\n    SCCExec(const VV<E>&\
    \ _g)\n        : n(int(_g.size())), g(_g), flag(n), low(n), ord(n, -1) {\n   \
    \     id = V<int>(n);\n        for (int i = 0; i < n; i++) {\n            if (ord[i]\
    \ == -1) dfs(i);\n        }\n        reverse(groups.begin(), groups.end());\n\
    \        for (int i = 0; i < int(groups.size()); i++) {\n            for (int\
    \ x : groups[i]) {\n                id[x] = i;\n            }\n        }\n   \
    \ }\n};\n\ntemplate <class E> SCC get_scc(const VV<E>& g) { return SCCExec<E>(g);\
    \ }\n\ntemplate <size_t N> struct BitsetSCCExec : SCC {\n    using B = bitset<N>;\n\
    \    int n;\n    const V<B>& g;\n    const V<B>& rg;\n    V<int> vs;\n    B unvis;\n\
    \    void dfs(int v) {\n        unvis.reset(v);\n        while (true) {\n    \
    \        int d = (unvis & g[v])._Find_first();\n            if (d >= n) break;\n\
    \            dfs(d);\n        }\n        vs.push_back(v);\n    }\n\n    void rdfs(int\
    \ v, int k) {\n        unvis.reset(v);\n        id[v] = k;\n        groups[k].push_back(v);\n\
    \        while (true) {\n            int d = (unvis & rg[v])._Find_first();\n\
    \            if (d >= n) break;\n            rdfs(d, k);\n        }\n    }\n\n\
    \    BitsetSCCExec(const V<B>& _g, const V<B>& _rg)\n        : n(int(_g.size())),\
    \ g(_g), rg(_rg) {\n        unvis.set();\n        for (int i = 0; i < n; i++)\
    \ {\n            if (unvis[i]) dfs(i);\n        }\n        reverse(vs.begin(),\
    \ vs.end());\n        unvis.set();\n        id = V<int>(n);\n        int k = 0;\n\
    \        for (int i : vs) {\n            if (unvis[i]) {\n                groups.push_back({});\n\
    \                rdfs(i, k++);\n            }\n        }\n    }\n};\n\ntemplate\
    \ <size_t N>\nSCC get_bitset_scc(const V<bitset<N>>& g, const V<bitset<N>>& rg)\
    \ {\n    return BitsetSCCExec<N>(g, rg);\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: src/graph/scc.hpp
  requiredBy:
  - src/graph/twosat.hpp
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/graph/scc.hpp
layout: document
redirect_from:
- /library/src/graph/scc.hpp
- /library/src/graph/scc.hpp.html
title: src/graph/scc.hpp
---
