---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"src/geo/delaunay.hpp\"\n\n// \u4ECAp\u304C\u4E00\u76F4\u7DDA\
    \u4E0A\u306E\u6642\u306F\u7D76\u5BFE\u306B\u4F7F\u308F\u306A\u3044\u3067\u4E0B\
    \u3055\u3044\n// \u6319\u52D5\u304C\u30E4\u30D0\u3059\u304E\u3066\uFF0C\u307B\u307C\
    100%\u305D\u306E\u5834\u3067\u30D0\u30B0\u3063\u3066\u3057\u307E\u3044\u307E\u3059\
    \u3002\nVV<int> delaunay(const V<P>& p) {\n    int n = int(p.size());\n    assert(n\
    \ > 1);\n    VV<int> mp(n + 2, V<int>(n + 2, -1));\n    int special = 0;\n   \
    \ for (int i = 1; i < n; i++)\n        if (p[i] < p[special]) special = i;\n \
    \   using Pi = pair<int, int>;\n    stack<Pi> st;\n    auto set_tr = [&](int i,\
    \ int j, int k) {\n        mp[i][j] = k;\n        mp[j][k] = i;\n        mp[k][i]\
    \ = j;\n        st.push(Pi(i, j));\n    };\n    set_tr(special, n, n + 1);\n \
    \   st.pop();\n    for (int l = 0; l < n; l++) {\n        if (l == special) continue;\n\
    \        int i = n, j = n + 1, k = mp[i][j];\n        do {\n            assert(k\
    \ != -1);\n            auto succ = [&](int x, int y) {\n                assert(!(x\
    \ == n && y == n + 1));\n                assert(!(x == n + 1 && y == n));\n  \
    \              if (x == n || y == n + 1) return p[l] < p[min(x, y)];\n       \
    \         if (x == n + 1 || y == n) return p[min(x, y)] < p[l];\n            \
    \    return ccw(p[x], p[y], p[l]) == 1;\n            };\n            if (succ(i,\
    \ k))\n                j = k;\n            else if (succ(k, j))\n            \
    \    i = k;\n            else\n                break;\n            k = mp[i][j];\n\
    \        } while (true);\n        auto on_line = [&](int x, int y, int z) {\n\
    \            if (max(x, y) >= n || ccw(p[x], p[y], p[l]) == 1) return false;\n\
    \            int w = mp[y][x];\n            mp[x][y] = mp[y][x] = -1;\n      \
    \      set_tr(x, w, l);\n            set_tr(w, y, l);\n            set_tr(y, z,\
    \ l);\n            set_tr(z, x, l);\n            return true;\n        };\n  \
    \      if (!on_line(i, j, k) && !on_line(j, k, i) && !on_line(k, i, j)) {\n  \
    \          set_tr(i, j, l);\n            set_tr(j, k, l);\n            set_tr(k,\
    \ i, l);\n        }\n        while (st.empty() == false) {\n            int u,\
    \ v;\n            tie(u, v) = st.top();\n            st.pop();\n            int\
    \ w = mp[u][v], x = mp[v][u];\n            assert(w == l);\n            if (w\
    \ < 0 || x < 0 || max(w, x) >= n) continue;\n            if (max(u, v) < n) {\n\
    \                P a = p[u] - p[x], b = p[v] - p[x], c = p[w] - p[x];\n      \
    \          D z = 0;\n                z += a.norm() * crs(b, c);\n            \
    \    z += b.norm() * crs(c, a);\n                z += c.norm() * crs(a, b);\n\
    \                if (z <= 0) continue;\n            } else {\n               \
    \ if (u < n && ccw(p[x], p[w], p[u]) != 1) continue;\n                if (v <\
    \ n && ccw(p[w], p[x], p[v]) != 1) continue;\n            }\n            mp[u][v]\
    \ = mp[v][u] = -1;\n            set_tr(u, x, l);\n            set_tr(x, v, l);\n\
    \        }\n    }\n\n    set_tr(special, n + 1, n);  // for traverse\n    VV<int>\
    \ g(n);\n    for (int i = 0; i < n; i++) {\n        int s = 0;\n        for (int\
    \ j = 0; j < n; j++) {\n            if (mp[s][i] < mp[j][i]) s = j;\n        }\n\
    \        int j = s;\n        bool unbounded = false;\n        do {\n         \
    \   if (j < n)\n                g[i].push_back(j);\n            else\n       \
    \         unbounded = true;\n            j = mp[i][j];\n        } while (j !=\
    \ s);\n        if (unbounded) g[i].push_back(n);\n    }\n    return g;\n}\n"
  code: "\n// \u4ECAp\u304C\u4E00\u76F4\u7DDA\u4E0A\u306E\u6642\u306F\u7D76\u5BFE\u306B\
    \u4F7F\u308F\u306A\u3044\u3067\u4E0B\u3055\u3044\n// \u6319\u52D5\u304C\u30E4\u30D0\
    \u3059\u304E\u3066\uFF0C\u307B\u307C100%\u305D\u306E\u5834\u3067\u30D0\u30B0\u3063\
    \u3066\u3057\u307E\u3044\u307E\u3059\u3002\nVV<int> delaunay(const V<P>& p) {\n\
    \    int n = int(p.size());\n    assert(n > 1);\n    VV<int> mp(n + 2, V<int>(n\
    \ + 2, -1));\n    int special = 0;\n    for (int i = 1; i < n; i++)\n        if\
    \ (p[i] < p[special]) special = i;\n    using Pi = pair<int, int>;\n    stack<Pi>\
    \ st;\n    auto set_tr = [&](int i, int j, int k) {\n        mp[i][j] = k;\n \
    \       mp[j][k] = i;\n        mp[k][i] = j;\n        st.push(Pi(i, j));\n   \
    \ };\n    set_tr(special, n, n + 1);\n    st.pop();\n    for (int l = 0; l < n;\
    \ l++) {\n        if (l == special) continue;\n        int i = n, j = n + 1, k\
    \ = mp[i][j];\n        do {\n            assert(k != -1);\n            auto succ\
    \ = [&](int x, int y) {\n                assert(!(x == n && y == n + 1));\n  \
    \              assert(!(x == n + 1 && y == n));\n                if (x == n ||\
    \ y == n + 1) return p[l] < p[min(x, y)];\n                if (x == n + 1 || y\
    \ == n) return p[min(x, y)] < p[l];\n                return ccw(p[x], p[y], p[l])\
    \ == 1;\n            };\n            if (succ(i, k))\n                j = k;\n\
    \            else if (succ(k, j))\n                i = k;\n            else\n\
    \                break;\n            k = mp[i][j];\n        } while (true);\n\
    \        auto on_line = [&](int x, int y, int z) {\n            if (max(x, y)\
    \ >= n || ccw(p[x], p[y], p[l]) == 1) return false;\n            int w = mp[y][x];\n\
    \            mp[x][y] = mp[y][x] = -1;\n            set_tr(x, w, l);\n       \
    \     set_tr(w, y, l);\n            set_tr(y, z, l);\n            set_tr(z, x,\
    \ l);\n            return true;\n        };\n        if (!on_line(i, j, k) &&\
    \ !on_line(j, k, i) && !on_line(k, i, j)) {\n            set_tr(i, j, l);\n  \
    \          set_tr(j, k, l);\n            set_tr(k, i, l);\n        }\n       \
    \ while (st.empty() == false) {\n            int u, v;\n            tie(u, v)\
    \ = st.top();\n            st.pop();\n            int w = mp[u][v], x = mp[v][u];\n\
    \            assert(w == l);\n            if (w < 0 || x < 0 || max(w, x) >= n)\
    \ continue;\n            if (max(u, v) < n) {\n                P a = p[u] - p[x],\
    \ b = p[v] - p[x], c = p[w] - p[x];\n                D z = 0;\n              \
    \  z += a.norm() * crs(b, c);\n                z += b.norm() * crs(c, a);\n  \
    \              z += c.norm() * crs(a, b);\n                if (z <= 0) continue;\n\
    \            } else {\n                if (u < n && ccw(p[x], p[w], p[u]) != 1)\
    \ continue;\n                if (v < n && ccw(p[w], p[x], p[v]) != 1) continue;\n\
    \            }\n            mp[u][v] = mp[v][u] = -1;\n            set_tr(u, x,\
    \ l);\n            set_tr(x, v, l);\n        }\n    }\n\n    set_tr(special, n\
    \ + 1, n);  // for traverse\n    VV<int> g(n);\n    for (int i = 0; i < n; i++)\
    \ {\n        int s = 0;\n        for (int j = 0; j < n; j++) {\n            if\
    \ (mp[s][i] < mp[j][i]) s = j;\n        }\n        int j = s;\n        bool unbounded\
    \ = false;\n        do {\n            if (j < n)\n                g[i].push_back(j);\n\
    \            else\n                unbounded = true;\n            j = mp[i][j];\n\
    \        } while (j != s);\n        if (unbounded) g[i].push_back(n);\n    }\n\
    \    return g;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: src/geo/delaunay.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/geo/delaunay.hpp
layout: document
redirect_from:
- /library/src/geo/delaunay.hpp
- /library/src/geo/delaunay.hpp.html
title: src/geo/delaunay.hpp
---
