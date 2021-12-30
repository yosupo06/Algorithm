---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: src/hl_lca.test.cpp
    title: src/hl_lca.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/hl_vertex_add_path_sum.test.cpp
    title: src/hl_vertex_add_path_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/hl_vertex_add_subtree_sum.test.cpp
    title: src/hl_vertex_add_subtree_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"src/tree/hl.hpp\"\n\n\nstruct HL {\n    // inside index\
    \ of HL\n    struct I {\n        int i;\n    };\n    V<int> _ord;          //\
    \ int -> I\n    V<int> _rord;         // I -> int\n    V<int> _big, _small;  //\
    \ I -> I\n    // optionals\n    V<int> dps;       // node depth(int -> int)\n\
    \    int pc = 0;       // path count(optional)\n    V<int> pid, psz;  // path\
    \ id, size (optional)\n    V<int> _out;       // ouv[i] is end of subtree(I ->\
    \ I)\n    HL() {}\n    HL(size_t n)\n        : _ord(n), _rord(n), _big(n), _small(n),\
    \ dps(n), pid(n), _out(n) {}\n    I ord(int v) const { return v == -1 ? I{-1}\
    \ : I{_ord[v]}; }\n    int rord(I i) const { return i.i == -1 ? -1 : _rord[i.i];\
    \ }\n    I par(I i) const { return I{_small[i.i] == i.i ? _big[i.i] : i.i - 1};\
    \ }\n    I subtree_out(int v) const { return I{_out[ord(v).i]}; };\n    int par(int\
    \ v) const { return rord(par(ord(v))); }\n    int lca(int a, int b) const {\n\
    \        int ai = ord(a).i;\n        int bi = ord(b).i;\n        while (ai !=\
    \ bi) {\n            if (ai > bi) swap(ai, bi);\n            if (_small[bi] <=\
    \ ai)\n                break;\n            else\n                bi = _big[bi];\n\
    \        }\n        return rord(I{ai});\n    }\n    // a\u306E\u76F4\u524D\u307E\
    \u3067b\u304B\u3089\u767B\u308B\u3001f(I, I)\u306E\u5F15\u6570\u306F\u4E21\u9589\
    \u533A\u9593\n    template <class F> void get_path(int a, int b, F f) const {\n\
    \        int ai = ord(a).i;\n        int bi = ord(b).i;\n        while (ai < bi)\
    \ {\n            if (_small[bi] <= ai)\n                f(I{ai + 1}, I{bi});\n\
    \            else\n                f(I{_small[bi]}, I{bi});\n            bi =\
    \ _big[bi];\n        }\n    }\n    int to(int a, int b) {  // a\u304B\u3089b\u306E\
    \u65B9\u5411\u30781\u79FB\u52D5\u3059\u308B\n        int ai = ord(a).i;\n    \
    \    int bi = ord(b).i;\n        assert(ai < bi);\n        while (true) {\n  \
    \          if (_small[bi] <= ai)\n                return rord(I{ai + 1});\n  \
    \          else if (_big[bi] == ai)\n                return rord(I{_small[bi]});\n\
    \            bi = _big[bi];\n        }\n        assert(false);\n    }\n    int\
    \ dist(int a, int b) const {\n        int c = lca(a, b);\n        return dps[a]\
    \ + dps[b] - 2 * dps[c];\n    }\n};\n\ntemplate <class E> struct HLExec : HL {\n\
    \    const VV<E>& g;\n    V<int> tch;\n    int id = 0;\n    HLExec(const VV<E>&\
    \ _g, int r) : HL(_g.size()), g(_g), tch(g.size(), -1) {\n        assert(dfs_sz(r,\
    \ -1) == int(g.size()));\n        dfs(r, -1);\n        init_extra();\n    }\n\
    \    void init_extra() {\n        // ord, rord, big, small\u4EE5\u5916\u3092\u4F7F\
    \u308F\u306A\u3044\u306A\u3089\u4E0D\u8981\n        int n = int(g.size());\n\n\
    \        // dps\n        dps[rord(I{0})] = 0;\n        for (int i = 1; i < n;\
    \ i++) {\n            dps[rord(I{i})] = dps[rord(par(I{i}))] + 1;\n        }\n\
    \n        // pid, psz, pc\n        int l = 0;\n        while (l < n) {\n     \
    \       int r = l + 1;\n            while (r < n && _small[r] == l) r++;\n   \
    \         psz.push_back(r - l);\n            for (int i = l; i < r; i++) {\n \
    \               pid[i] = pc;\n            }\n            l = r;\n            pc++;\n\
    \        }\n\n        // out\n        for (int i = n - 1; i >= 0; i--) {\n   \
    \         _out[i] = max(_out[i], i + 1);\n            int p = ord(par(rord(I{i}))).i;\n\
    \            if (p != -1) _out[p] = max(_out[p], _out[i]);\n        }\n    }\n\
    \    int dfs_sz(int p, int b) {\n        int sz = 1, msz = -1;\n        for (auto\
    \ e : g[p]) {\n            if (e.to == b) continue;\n            int u = dfs_sz(e.to,\
    \ p);\n            sz += u;\n            if (msz < u) tie(tch[p], msz) = make_pair(e.to,\
    \ u);\n        }\n        return sz;\n    }\n    void dfs(int p, int b) {\n  \
    \      int q = id++, bq = ord(b).i;\n        _ord[p] = q;\n        _rord[q] =\
    \ p;\n        if (b == -1 || bq != q - 1) {\n            _small[q] = q;\n    \
    \        _big[q] = bq;\n        } else {\n            _small[q] = _small[bq];\n\
    \            _big[q] = _big[bq];\n        }\n        if (tch[p] == -1) return;\n\
    \        dfs(tch[p], p);\n        for (auto e : g[p]) {\n            if (e.to\
    \ == b || e.to == tch[p]) continue;\n            dfs(e.to, p);\n        }\n  \
    \  }\n};\n\ntemplate <class E> HL get_hl(const VV<E>& g, int r) { return HLExec<E>(g,\
    \ r); }\n"
  code: "#pragma once\n\n\nstruct HL {\n    // inside index of HL\n    struct I {\n\
    \        int i;\n    };\n    V<int> _ord;          // int -> I\n    V<int> _rord;\
    \         // I -> int\n    V<int> _big, _small;  // I -> I\n    // optionals\n\
    \    V<int> dps;       // node depth(int -> int)\n    int pc = 0;       // path\
    \ count(optional)\n    V<int> pid, psz;  // path id, size (optional)\n    V<int>\
    \ _out;       // ouv[i] is end of subtree(I -> I)\n    HL() {}\n    HL(size_t\
    \ n)\n        : _ord(n), _rord(n), _big(n), _small(n), dps(n), pid(n), _out(n)\
    \ {}\n    I ord(int v) const { return v == -1 ? I{-1} : I{_ord[v]}; }\n    int\
    \ rord(I i) const { return i.i == -1 ? -1 : _rord[i.i]; }\n    I par(I i) const\
    \ { return I{_small[i.i] == i.i ? _big[i.i] : i.i - 1}; }\n    I subtree_out(int\
    \ v) const { return I{_out[ord(v).i]}; };\n    int par(int v) const { return rord(par(ord(v)));\
    \ }\n    int lca(int a, int b) const {\n        int ai = ord(a).i;\n        int\
    \ bi = ord(b).i;\n        while (ai != bi) {\n            if (ai > bi) swap(ai,\
    \ bi);\n            if (_small[bi] <= ai)\n                break;\n          \
    \  else\n                bi = _big[bi];\n        }\n        return rord(I{ai});\n\
    \    }\n    // a\u306E\u76F4\u524D\u307E\u3067b\u304B\u3089\u767B\u308B\u3001\
    f(I, I)\u306E\u5F15\u6570\u306F\u4E21\u9589\u533A\u9593\n    template <class F>\
    \ void get_path(int a, int b, F f) const {\n        int ai = ord(a).i;\n     \
    \   int bi = ord(b).i;\n        while (ai < bi) {\n            if (_small[bi]\
    \ <= ai)\n                f(I{ai + 1}, I{bi});\n            else\n           \
    \     f(I{_small[bi]}, I{bi});\n            bi = _big[bi];\n        }\n    }\n\
    \    int to(int a, int b) {  // a\u304B\u3089b\u306E\u65B9\u5411\u30781\u79FB\u52D5\
    \u3059\u308B\n        int ai = ord(a).i;\n        int bi = ord(b).i;\n       \
    \ assert(ai < bi);\n        while (true) {\n            if (_small[bi] <= ai)\n\
    \                return rord(I{ai + 1});\n            else if (_big[bi] == ai)\n\
    \                return rord(I{_small[bi]});\n            bi = _big[bi];\n   \
    \     }\n        assert(false);\n    }\n    int dist(int a, int b) const {\n \
    \       int c = lca(a, b);\n        return dps[a] + dps[b] - 2 * dps[c];\n   \
    \ }\n};\n\ntemplate <class E> struct HLExec : HL {\n    const VV<E>& g;\n    V<int>\
    \ tch;\n    int id = 0;\n    HLExec(const VV<E>& _g, int r) : HL(_g.size()), g(_g),\
    \ tch(g.size(), -1) {\n        assert(dfs_sz(r, -1) == int(g.size()));\n     \
    \   dfs(r, -1);\n        init_extra();\n    }\n    void init_extra() {\n     \
    \   // ord, rord, big, small\u4EE5\u5916\u3092\u4F7F\u308F\u306A\u3044\u306A\u3089\
    \u4E0D\u8981\n        int n = int(g.size());\n\n        // dps\n        dps[rord(I{0})]\
    \ = 0;\n        for (int i = 1; i < n; i++) {\n            dps[rord(I{i})] = dps[rord(par(I{i}))]\
    \ + 1;\n        }\n\n        // pid, psz, pc\n        int l = 0;\n        while\
    \ (l < n) {\n            int r = l + 1;\n            while (r < n && _small[r]\
    \ == l) r++;\n            psz.push_back(r - l);\n            for (int i = l; i\
    \ < r; i++) {\n                pid[i] = pc;\n            }\n            l = r;\n\
    \            pc++;\n        }\n\n        // out\n        for (int i = n - 1; i\
    \ >= 0; i--) {\n            _out[i] = max(_out[i], i + 1);\n            int p\
    \ = ord(par(rord(I{i}))).i;\n            if (p != -1) _out[p] = max(_out[p], _out[i]);\n\
    \        }\n    }\n    int dfs_sz(int p, int b) {\n        int sz = 1, msz = -1;\n\
    \        for (auto e : g[p]) {\n            if (e.to == b) continue;\n       \
    \     int u = dfs_sz(e.to, p);\n            sz += u;\n            if (msz < u)\
    \ tie(tch[p], msz) = make_pair(e.to, u);\n        }\n        return sz;\n    }\n\
    \    void dfs(int p, int b) {\n        int q = id++, bq = ord(b).i;\n        _ord[p]\
    \ = q;\n        _rord[q] = p;\n        if (b == -1 || bq != q - 1) {\n       \
    \     _small[q] = q;\n            _big[q] = bq;\n        } else {\n          \
    \  _small[q] = _small[bq];\n            _big[q] = _big[bq];\n        }\n     \
    \   if (tch[p] == -1) return;\n        dfs(tch[p], p);\n        for (auto e :\
    \ g[p]) {\n            if (e.to == b || e.to == tch[p]) continue;\n          \
    \  dfs(e.to, p);\n        }\n    }\n};\n\ntemplate <class E> HL get_hl(const VV<E>&\
    \ g, int r) { return HLExec<E>(g, r); }\n"
  dependsOn: []
  isVerificationFile: false
  path: src/tree/hl.hpp
  requiredBy: []
  timestamp: '2021-12-30 20:52:19+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - src/hl_vertex_add_path_sum.test.cpp
  - src/hl_vertex_add_subtree_sum.test.cpp
  - src/hl_lca.test.cpp
documentation_of: src/tree/hl.hpp
layout: document
redirect_from:
- /library/src/tree/hl.hpp
- /library/src/tree/hl.hpp.html
title: src/tree/hl.hpp
---
