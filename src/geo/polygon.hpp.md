---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"src/geo/polygon.hpp\"\nusing Pol = V<P>;\n\nD area2(const\
    \ Pol& pol) {\n    D u = 0;\n    if (!pol.size()) return u;\n    P a = pol.back();\n\
    \    for (auto b : pol) u += crs(a, b), a = b;\n    return u;\n}\n\n// (1:left)\
    \ | (2: right) is inside between v[i] ~ v[i + 1]\nV<pair<P, int>> insPolL(Pol\
    \ pol, L l) {\n    using Pi = pair<P, int>;\n    V<Pi> v;\n    P a, b = pol.back();\n\
    \    for (auto now: pol) {\n        a = b; b = now;\n        P p;\n        if\
    \ (crossLL({a, b}, l, p) != 1) continue;\n        int sa = ccw(l, a) % 2, sb =\
    \ ccw(l, b) % 2;\n        if (sa > sb) swap(sa, sb);\n        if (sa != 1 && sb\
    \ == 1) v.push_back({p, 1});\n        if (sa == -1 && sb != -1) v.push_back({p,\
    \ 2});\n    }\n    sort(v.begin(), v.end(), [&](Pi x, Pi y){\n        return dot(l.vec(),\
    \ x.first - l.s) < dot(l.vec(), y.first - l.s);\n    });\n    int m = int(v.size());\n\
    \    V<Pi> res;\n    for (int i = 0; i < m; i++) {\n        if (i) v[i].second\
    \ ^= v[i - 1].second;\n        if (!res.empty() && res.back().first == v[i].first)\
    \ res.pop_back();\n        res.push_back(v[i]);\n    }\n    return res;\n}\n\n\
    // 0: outside, 1: on line, 2: inside\nint contains(const Pol& pol, P p) {\n  \
    \  if (!pol.size()) return 0;\n    int in = -1;\n    P _a, _b = pol.back();\n\
    \    for (auto now : pol) {\n        _a = _b;\n        _b = now;\n        P a\
    \ = _a, b = _b;\n        if (ccw(a, b, p) == 0) return 1;\n        if (a.y > b.y)\
    \ swap(a, b);\n        if (!(a.y <= p.y && p.y < b.y)) continue;\n        if (sgn(a.y,\
    \ p.y) ? (crs(a - p, b - p) > 0) : (a.x > p.x)) in *= -1;\n    }\n    return in\
    \ + 1;\n}\n\n// p must be sorted and uniqued!\nPol convex_down(const V<P>& ps)\
    \ {\n    assert(ps.size() >= 2);\n    Pol dw;\n    for (P d : ps) {\n        size_t\
    \ n;\n        while ((n = dw.size()) > 1) {\n            // if (ccw(dw[n - 2],\
    \ dw[n - 1], d) != -1) break; // line\u4E0A\u3082\u53D6\u308B\n            if\
    \ (ccw(dw[n - 2], dw[n - 1], d) == 1) break;\n            dw.pop_back();\n   \
    \     }\n        dw.push_back(d);\n    }\n    return dw;\n}\n\nPol convex(V<P>\
    \ ps) {\n    sort(ps.begin(), ps.end());\n    ps.erase(unique(ps.begin(), ps.end()),\
    \ ps.end());\n    if (ps.size() <= 1) return ps;\n    Pol dw = convex_down(ps);\n\
    \    reverse(ps.begin(), ps.end());\n    Pol up = convex_down(ps);\n    dw.insert(dw.begin(),\
    \ up.begin() + 1, up.end() - 1);\n    return dw;\n}\n\nPol convex_cut(const Pol&\
    \ po, const L& l) {\n    if (!po.size()) return Pol{};\n    Pol q;\n    P a, b\
    \ = po.back();\n    for (auto now : po) {\n        a = b;\n        b = now;\n\
    \        if ((ccw(l, a) % 2) * (ccw(l, b) % 2) < 0) {\n            P buf;\n  \
    \          crossLL(l, L(a, b), buf);\n            q.push_back(buf);\n        }\n\
    \        if (ccw(l, b) != -1) q.push_back(b);\n    }\n    return q;\n}\n\n// pol\
    \ must be convex\nD diameter(const Pol& p) {\n    int n = int(p.size());\n   \
    \ if (n == 2) return (p[1] - p[0]).abs();\n    int x = 0, y = 0;\n    for (int\
    \ i = 1; i < n; i++) {\n        if (p[i] < p[x]) x = i;\n        if (p[y] < p[i])\
    \ y = i;\n    }\n    D ans = 0;\n    int sx = x, sy = y;\n    /*\n    do {\n \
    \       ...\n    } while (sx != x || sy != y);\n    \u30671\u5468\u3059\u308B\n\
    \    */\n    while (sx != y || sy != x) {\n        ans = max(ans, (p[x] - p[y]).abs());\n\
    \        int nx = (x + 1 < n) ? x + 1 : 0, ny = (y + 1 < n) ? y + 1 : 0;\n   \
    \     if (crs(p[nx] - p[x], p[ny] - p[y]) < 0)\n            x = nx;\n        else\n\
    \            y = ny;\n    }\n    return ans;\n}\n"
  code: "using Pol = V<P>;\n\nD area2(const Pol& pol) {\n    D u = 0;\n    if (!pol.size())\
    \ return u;\n    P a = pol.back();\n    for (auto b : pol) u += crs(a, b), a =\
    \ b;\n    return u;\n}\n\n// (1:left) | (2: right) is inside between v[i] ~ v[i\
    \ + 1]\nV<pair<P, int>> insPolL(Pol pol, L l) {\n    using Pi = pair<P, int>;\n\
    \    V<Pi> v;\n    P a, b = pol.back();\n    for (auto now: pol) {\n        a\
    \ = b; b = now;\n        P p;\n        if (crossLL({a, b}, l, p) != 1) continue;\n\
    \        int sa = ccw(l, a) % 2, sb = ccw(l, b) % 2;\n        if (sa > sb) swap(sa,\
    \ sb);\n        if (sa != 1 && sb == 1) v.push_back({p, 1});\n        if (sa ==\
    \ -1 && sb != -1) v.push_back({p, 2});\n    }\n    sort(v.begin(), v.end(), [&](Pi\
    \ x, Pi y){\n        return dot(l.vec(), x.first - l.s) < dot(l.vec(), y.first\
    \ - l.s);\n    });\n    int m = int(v.size());\n    V<Pi> res;\n    for (int i\
    \ = 0; i < m; i++) {\n        if (i) v[i].second ^= v[i - 1].second;\n       \
    \ if (!res.empty() && res.back().first == v[i].first) res.pop_back();\n      \
    \  res.push_back(v[i]);\n    }\n    return res;\n}\n\n// 0: outside, 1: on line,\
    \ 2: inside\nint contains(const Pol& pol, P p) {\n    if (!pol.size()) return\
    \ 0;\n    int in = -1;\n    P _a, _b = pol.back();\n    for (auto now : pol) {\n\
    \        _a = _b;\n        _b = now;\n        P a = _a, b = _b;\n        if (ccw(a,\
    \ b, p) == 0) return 1;\n        if (a.y > b.y) swap(a, b);\n        if (!(a.y\
    \ <= p.y && p.y < b.y)) continue;\n        if (sgn(a.y, p.y) ? (crs(a - p, b -\
    \ p) > 0) : (a.x > p.x)) in *= -1;\n    }\n    return in + 1;\n}\n\n// p must\
    \ be sorted and uniqued!\nPol convex_down(const V<P>& ps) {\n    assert(ps.size()\
    \ >= 2);\n    Pol dw;\n    for (P d : ps) {\n        size_t n;\n        while\
    \ ((n = dw.size()) > 1) {\n            // if (ccw(dw[n - 2], dw[n - 1], d) !=\
    \ -1) break; // line\u4E0A\u3082\u53D6\u308B\n            if (ccw(dw[n - 2], dw[n\
    \ - 1], d) == 1) break;\n            dw.pop_back();\n        }\n        dw.push_back(d);\n\
    \    }\n    return dw;\n}\n\nPol convex(V<P> ps) {\n    sort(ps.begin(), ps.end());\n\
    \    ps.erase(unique(ps.begin(), ps.end()), ps.end());\n    if (ps.size() <= 1)\
    \ return ps;\n    Pol dw = convex_down(ps);\n    reverse(ps.begin(), ps.end());\n\
    \    Pol up = convex_down(ps);\n    dw.insert(dw.begin(), up.begin() + 1, up.end()\
    \ - 1);\n    return dw;\n}\n\nPol convex_cut(const Pol& po, const L& l) {\n  \
    \  if (!po.size()) return Pol{};\n    Pol q;\n    P a, b = po.back();\n    for\
    \ (auto now : po) {\n        a = b;\n        b = now;\n        if ((ccw(l, a)\
    \ % 2) * (ccw(l, b) % 2) < 0) {\n            P buf;\n            crossLL(l, L(a,\
    \ b), buf);\n            q.push_back(buf);\n        }\n        if (ccw(l, b) !=\
    \ -1) q.push_back(b);\n    }\n    return q;\n}\n\n// pol must be convex\nD diameter(const\
    \ Pol& p) {\n    int n = int(p.size());\n    if (n == 2) return (p[1] - p[0]).abs();\n\
    \    int x = 0, y = 0;\n    for (int i = 1; i < n; i++) {\n        if (p[i] <\
    \ p[x]) x = i;\n        if (p[y] < p[i]) y = i;\n    }\n    D ans = 0;\n    int\
    \ sx = x, sy = y;\n    /*\n    do {\n        ...\n    } while (sx != x || sy !=\
    \ y);\n    \u30671\u5468\u3059\u308B\n    */\n    while (sx != y || sy != x) {\n\
    \        ans = max(ans, (p[x] - p[y]).abs());\n        int nx = (x + 1 < n) ?\
    \ x + 1 : 0, ny = (y + 1 < n) ? y + 1 : 0;\n        if (crs(p[nx] - p[x], p[ny]\
    \ - p[y]) < 0)\n            x = nx;\n        else\n            y = ny;\n    }\n\
    \    return ans;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: src/geo/polygon.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/geo/polygon.hpp
layout: document
redirect_from:
- /library/src/geo/polygon.hpp
- /library/src/geo/polygon.hpp.html
title: src/geo/polygon.hpp
---
