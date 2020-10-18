---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"src/geo/intersect.hpp\"\n/**\n * \u5E7E\u4F55(\u885D\u7A81\
    \u5224\u5B9A)\n */\n\nP project(const L& l, const P& p) {\n    P v = l.vec();\n\
    \    return l.s + v * dot(v, p - l.s) / v.norm();\n}\n\nbool insSL(const L& s,\
    \ const L& l) {\n    int a = ccw(l, s.s), b = ccw(l, s.t);\n    return (a % 2\
    \ == 0 || b % 2 == 0 || a != b);\n}\n\nbool insSS(const L& s, const L& t) {\n\
    \    int a = ccw(s, t.s), b = ccw(s, t.t);\n    int c = ccw(t, s.s), d = ccw(t,\
    \ s.t);\n    if (a * b <= 0 && c * d <= 0) return true;\n    return false;\n}\n\
    \nD distLP(const L& l, const P& p) {\n    return abs(crs(l.vec(), p - l.s)) /\
    \ l.abs();\n}\n\nD distSP(const L& s, const P& p) {\n    P q = project(s, p);\n\
    \    if (ccw(s, q) == 0)\n        return (p - q).abs();\n    else\n        return\
    \ min((s.s - p).abs(), (s.t - p).abs());\n}\n\nD distSS(const L& s, const L& t)\
    \ {\n    if (insSS(s, t)) return 0;\n    return min(\n        {distSP(s, t.s),\
    \ distSP(s, t.t), distSP(t, s.s), distSP(t, s.t)});\n}\n\nint crossLL(const L&\
    \ l, const L& m, P& r) {\n    D cr1 = crs(l.vec(), m.vec()), cr2 = crs(l.vec(),\
    \ l.t - m.s);\n    if (sgncrs(l.vec(), m.vec()) == 0) {\n        r = l.s;\n  \
    \      if (sgncrs(l.vec(), l.t - m.s)) return 0;\n        return -1;\n    }\n\
    \    r = m.s + m.vec() * cr2 / cr1;\n    return 1;\n}\n\nint crossSS(L l, L m,\
    \ P& r) {\n    int u = crossLL(l, m, r);\n    if (u == 0) return 0;\n    if (u\
    \ == -1) {\n        r = max(min(l.s, l.t), min(m.s, m.t));\n        P q = min(max(l.s,\
    \ l.t), max(m.s, m.t));\n        return (q < r) ? 0 : (q == r ? 1 : -1);\n   \
    \ }\n    if (ccw(l, r) == 0 && ccw(m, r) == 0) return 1;\n    return 0;\n}\n"
  code: "/**\n * \u5E7E\u4F55(\u885D\u7A81\u5224\u5B9A)\n */\n\nP project(const L&\
    \ l, const P& p) {\n    P v = l.vec();\n    return l.s + v * dot(v, p - l.s) /\
    \ v.norm();\n}\n\nbool insSL(const L& s, const L& l) {\n    int a = ccw(l, s.s),\
    \ b = ccw(l, s.t);\n    return (a % 2 == 0 || b % 2 == 0 || a != b);\n}\n\nbool\
    \ insSS(const L& s, const L& t) {\n    int a = ccw(s, t.s), b = ccw(s, t.t);\n\
    \    int c = ccw(t, s.s), d = ccw(t, s.t);\n    if (a * b <= 0 && c * d <= 0)\
    \ return true;\n    return false;\n}\n\nD distLP(const L& l, const P& p) {\n \
    \   return abs(crs(l.vec(), p - l.s)) / l.abs();\n}\n\nD distSP(const L& s, const\
    \ P& p) {\n    P q = project(s, p);\n    if (ccw(s, q) == 0)\n        return (p\
    \ - q).abs();\n    else\n        return min((s.s - p).abs(), (s.t - p).abs());\n\
    }\n\nD distSS(const L& s, const L& t) {\n    if (insSS(s, t)) return 0;\n    return\
    \ min(\n        {distSP(s, t.s), distSP(s, t.t), distSP(t, s.s), distSP(t, s.t)});\n\
    }\n\nint crossLL(const L& l, const L& m, P& r) {\n    D cr1 = crs(l.vec(), m.vec()),\
    \ cr2 = crs(l.vec(), l.t - m.s);\n    if (sgncrs(l.vec(), m.vec()) == 0) {\n \
    \       r = l.s;\n        if (sgncrs(l.vec(), l.t - m.s)) return 0;\n        return\
    \ -1;\n    }\n    r = m.s + m.vec() * cr2 / cr1;\n    return 1;\n}\n\nint crossSS(L\
    \ l, L m, P& r) {\n    int u = crossLL(l, m, r);\n    if (u == 0) return 0;\n\
    \    if (u == -1) {\n        r = max(min(l.s, l.t), min(m.s, m.t));\n        P\
    \ q = min(max(l.s, l.t), max(m.s, m.t));\n        return (q < r) ? 0 : (q == r\
    \ ? 1 : -1);\n    }\n    if (ccw(l, r) == 0 && ccw(m, r) == 0) return 1;\n   \
    \ return 0;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: src/geo/intersect.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/geo/intersect.hpp
layout: document
redirect_from:
- /library/src/geo/intersect.hpp
- /library/src/geo/intersect.hpp.html
title: src/geo/intersect.hpp
---
