---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"src/graph/maxflow.hpp\"\n/*\nstruct E {\n    int to, rev,\
    \ cap;\n};\nVV<E> g;\nauto add_edge = [&](int from, int to, int cap) {\n    g[from].push_back(E{to,\
    \ int(g[to].size()), cap});\n    g[to].push_back(E{from, int(g[from].size())-1,\
    \ 0});\n};\n*/\n\ntemplate<class C>\nstruct MaxFlow {\n    C flow;\n    V<char>\
    \ dual;  // false: S-side true: T-side\n};\n\ntemplate<class C, class E>\nstruct\
    \ MFExec {\n    static constexpr C INF = numeric_limits<C>::max();\n    C eps;\n\
    \    VV<E>& g;\n    int s, t;\n    V<int> level, iter;\n\n    C dfs(int v, C f)\
    \ {\n        if (v == t) return f;\n        C res = 0;\n        for (int& i =\
    \ iter[v]; i < int(g[v].size()); i++) {\n            E& e = g[v][i];\n       \
    \     if (e.cap <= eps || level[v] >= level[e.to]) continue;\n            C d\
    \ = dfs(e.to, min(f, e.cap));\n            e.cap -= d;\n            g[e.to][e.rev].cap\
    \ += d;\n            res += d;\n            f -= d;\n            if (f == 0) break;\n\
    \        }\n        return res;\n    }\n\n    MaxFlow<C> info;\n    MFExec(VV<E>&\
    \ _g, int _s, int _t, C _eps)\n        : eps(_eps), g(_g), s(_s), t(_t) {\n  \
    \      int N = int(g.size());\n\n        C& flow = (info.flow = 0);\n        while\
    \ (true) {\n            queue<int> que;\n            level = V<int>(N, -1);\n\
    \            level[s] = 0;\n            que.push(s);\n            while (!que.empty())\
    \ {\n                int v = que.front(); que.pop();\n                for (E e:\
    \ g[v]) {\n                    if (e.cap <= eps || level[e.to] >= 0) continue;\n\
    \                    level[e.to] = level[v] + 1;\n                    que.push(e.to);\n\
    \                }\n            }\n            if (level[t] == -1) break;\n  \
    \          iter = V<int>(N, 0);\n            while (true) {\n                C\
    \ f = dfs(s, INF);\n                if (!f) break;\n                flow += f;\n\
    \            }\n        }\n        for (int i = 0; i < N; i++) info.dual.push_back(level[i]\
    \ == -1);\n    }\n};\n\ntemplate<class C, class E>\nMaxFlow<C> get_mf(VV<E>& g,\
    \ int s, int t, C eps) {\n    return MFExec<C, E>(g, s, t, eps).info;\n}\n"
  code: "/*\nstruct E {\n    int to, rev, cap;\n};\nVV<E> g;\nauto add_edge = [&](int\
    \ from, int to, int cap) {\n    g[from].push_back(E{to, int(g[to].size()), cap});\n\
    \    g[to].push_back(E{from, int(g[from].size())-1, 0});\n};\n*/\n\ntemplate<class\
    \ C>\nstruct MaxFlow {\n    C flow;\n    V<char> dual;  // false: S-side true:\
    \ T-side\n};\n\ntemplate<class C, class E>\nstruct MFExec {\n    static constexpr\
    \ C INF = numeric_limits<C>::max();\n    C eps;\n    VV<E>& g;\n    int s, t;\n\
    \    V<int> level, iter;\n\n    C dfs(int v, C f) {\n        if (v == t) return\
    \ f;\n        C res = 0;\n        for (int& i = iter[v]; i < int(g[v].size());\
    \ i++) {\n            E& e = g[v][i];\n            if (e.cap <= eps || level[v]\
    \ >= level[e.to]) continue;\n            C d = dfs(e.to, min(f, e.cap));\n   \
    \         e.cap -= d;\n            g[e.to][e.rev].cap += d;\n            res +=\
    \ d;\n            f -= d;\n            if (f == 0) break;\n        }\n       \
    \ return res;\n    }\n\n    MaxFlow<C> info;\n    MFExec(VV<E>& _g, int _s, int\
    \ _t, C _eps)\n        : eps(_eps), g(_g), s(_s), t(_t) {\n        int N = int(g.size());\n\
    \n        C& flow = (info.flow = 0);\n        while (true) {\n            queue<int>\
    \ que;\n            level = V<int>(N, -1);\n            level[s] = 0;\n      \
    \      que.push(s);\n            while (!que.empty()) {\n                int v\
    \ = que.front(); que.pop();\n                for (E e: g[v]) {\n             \
    \       if (e.cap <= eps || level[e.to] >= 0) continue;\n                    level[e.to]\
    \ = level[v] + 1;\n                    que.push(e.to);\n                }\n  \
    \          }\n            if (level[t] == -1) break;\n            iter = V<int>(N,\
    \ 0);\n            while (true) {\n                C f = dfs(s, INF);\n      \
    \          if (!f) break;\n                flow += f;\n            }\n       \
    \ }\n        for (int i = 0; i < N; i++) info.dual.push_back(level[i] == -1);\n\
    \    }\n};\n\ntemplate<class C, class E>\nMaxFlow<C> get_mf(VV<E>& g, int s, int\
    \ t, C eps) {\n    return MFExec<C, E>(g, s, t, eps).info;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: src/graph/maxflow.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/graph/maxflow.hpp
layout: document
redirect_from:
- /library/src/graph/maxflow.hpp
- /library/src/graph/maxflow.hpp.html
title: src/graph/maxflow.hpp
---
