---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"src/geo/circle.hpp\"\nstruct C {\n    P p;\n    D r;\n \
    \   C(P _p = P(), D _r = D()) : p(_p), r(_r) {}\n};\n\n// need Intersect/distLP,\
    \ r.s\u306F\u3088\u308Al.s\u306B\u8FD1\u3044\nint crossCL(const C& c, const L&\
    \ l, L& r) {\n    D u = distLP(l, c.p);\n    int si = sgn(u, c.r);\n    if (si\
    \ == 1) return 0;\n    P v = project(l, c.p);\n    P di = (si == 0) ? P(0, 0)\
    \ : l.vec() * (sqrt(c.r * c.r - u * u) / l.abs());\n    r = L(v - di, v + di);\n\
    \    if (si == 0) return 1;\n    return 2;\n}\n\n// need Intersect/distLP, r.s\u306F\
    \u3088\u308Al.s\u306B\u8FD1\u3044\nint crossCS(const C& c, const L& s, L& l) {\n\
    \    if (!crossCL(c, s, l)) return 0;\n    bool f1 = !ccw(s, l.s), f2 = !ccw(s,\
    \ l.t);\n    if (f1 && f2) return 2;\n    if (!f1 && !f2) return 0;\n    if (f1)\n\
    \        l.t = l.s;\n    else\n        l.s = l.t;\n    return 1;\n}\n\n// return\
    \ number of cross point\n// l, r\u306Fc\u304B\u3089\u898B\u305F\u4EA4\u70B9\u306E\
    \u89D2\u5EA6\u3001[l, r]\u304Cd\u306B\u8986\u308F\u308C\u3066\u3044\u308B\nint\
    \ crossCC(const C& c, const C& d, D& l, D& r) {\n    if (c.p == d.p) {\n     \
    \   assert(sgn(c.r - d.r));  // prohibit same circles\n        return 0;\n   \
    \ }\n    D di = (c.p - d.p).abs(), bth = (d.p - c.p).arg();\n    D costh = (c.r\
    \ * c.r + di * di - d.r * d.r) / (2 * c.r * di);\n    int ty = min(sgn(c.r + d.r,\
    \ di), sgn(di, abs(c.r - d.r)));\n    if (ty == -1) return 0;\n    if (ty == 0)\
    \ costh = sgn(costh);\n    D th = acos(costh);\n    l = bth - th;\n    r = bth\
    \ + th;\n    return ty + 1;\n}\n\n// p\u304B\u3089c\u306B\u63A5\u7DDA\u3092\u5F15\
    \u304F\uFF0C\u4EA4\u70B9\u306Fp1, p2\nint tangent(const C& c, const P& p, P& p1,\
    \ P& p2) {\n    D di = (c.p - p).abs();\n    int si = sgn(c.r, di);\n    if (si\
    \ == 1) return 0;\n    D th = acos(min(D(1), c.r / di));\n    D ar = (p - c.p).arg();\n\
    \    p1 = c.p + P::polar(c.r, ar - th);\n    p2 = c.p + P::polar(c.r, ar + th);\n\
    \    if (si == 0) return 1;\n    return 2;\n}\n\n//\u5171\u901A\u63A5\u7DDA\n\
    int tangent(const C& c, const C& d, L& l, L& r, bool inter) {\n    D di = (d.p\
    \ - c.p).abs(), ar = (d.p - c.p).arg();\n    if (sgn(di) == 0) {\n        assert(sgn(c.r\
    \ - d.r));  // prohibit same circles\n        return 0;\n    }\n    D costh =\
    \ c.r + (inter ? d.r : -d.r);\n    int si = sgn(abs(costh), di);\n    costh /=\
    \ di;\n    if (si == 1)\n        return 0;\n    else if (si == 0)\n        costh\
    \ = sgn(costh);\n    D th = acos(costh);\n    P base;\n    base = P::polar(1,\
    \ ar - th);\n    l = L(c.p + base * c.r, d.p + base * d.r * (inter ? -1 : 1));\n\
    \    base = P::polar(1, ar + th);\n    r = L(c.p + base * c.r, d.p + base * d.r\
    \ * (inter ? -1 : 1));\n    if (si == 0) return 1;\n    return 2;\n}\n\nC circum_circle(P\
    \ a, P b, P c) {\n    b -= a;\n    c -= a;\n    D s = 2 * crs(b, c);\n    D x\
    \ = (b - c).norm(), y = c.norm(), z = b.norm();\n    D S = x + y + z;\n    P r\
    \ = (b * (S - 2 * y) * y + c * z * (S - 2 * z)) / (s * s);\n    return C(r + a,\
    \ r.abs());\n}\n\nC smallest_circle(const Pol& p, int i, array<P, 3> q, int j)\
    \ {\n    if (i == int(p.size())) {\n        switch (j) {\n            case 0:\n\
    \                return C(P(0, 0), -1);\n            case 1:\n               \
    \ return C(q[0], 0);\n            case 2:\n                return C((q[0] + q[1])\
    \ / D(2.0), (q[0] - q[1]).abs() / D(2.0));\n            case 3:\n            \
    \    return circum_circle(q[0], q[1], q[2]);\n        }\n        assert(false);\n\
    \    }\n    C c = smallest_circle(p, i + 1, q, j);\n    if (sgn((p[i] - c.p).abs(),\
    \ c.r) == 1) {\n        q[j] = p[i];\n        return smallest_circle(p, i + 1,\
    \ q, j + 1);\n    }\n    return c;\n}\nC smallest_circle(Pol p) {\n    random_shuffle(begin(p),\
    \ end(p));\n    return smallest_circle(p, 0, array<P, 3>(), 0);\n}\n\n// C(P(0,\
    \ 0), r)\u3068Tri((0, 0), a, b)\u306E\u5171\u6709\u9762\u7A4D\nD area2CT(const\
    \ C& c, const P& _a, const P& _b) {\n    P a = _a - c.p, b = _b - c.p;\n    D\
    \ r = c.r;\n    if (a == b) return 0;\n    auto single = [&](P x, P y, bool tri)\
    \ {\n        if (tri)\n            return crs(x, y);\n        else\n         \
    \   return r * r * ((y * P(x.x, -x.y)).arg());\n    };\n    bool ia = sgn(a.abs(),\
    \ r) != 1, ib = sgn(b.abs(), r) != 1;\n    if (ia && ib) return single(a, b, true);\n\
    \    L l;\n    if (!crossCS(C(P(0, 0), r), L(a, b), l)) return single(a, b, false);\n\
    \    return single(a, l.s, ia) + single(l.s, l.t, true) + single(l.t, b, ib);\n\
    }\n\n// p, c\u306E\u5171\u6709\u9762\u7A4D\nD area2CPol(const C& c, const Pol&\
    \ po) {\n    D sm = 0;\n    P a, b = po.back();\n    for (auto p : po) {\n   \
    \     a = b;\n        b = p;\n        sm += area2CT(c, a, b);\n    }\n    return\
    \ sm;\n}\n"
  code: "struct C {\n    P p;\n    D r;\n    C(P _p = P(), D _r = D()) : p(_p), r(_r)\
    \ {}\n};\n\n// need Intersect/distLP, r.s\u306F\u3088\u308Al.s\u306B\u8FD1\u3044\
    \nint crossCL(const C& c, const L& l, L& r) {\n    D u = distLP(l, c.p);\n   \
    \ int si = sgn(u, c.r);\n    if (si == 1) return 0;\n    P v = project(l, c.p);\n\
    \    P di = (si == 0) ? P(0, 0) : l.vec() * (sqrt(c.r * c.r - u * u) / l.abs());\n\
    \    r = L(v - di, v + di);\n    if (si == 0) return 1;\n    return 2;\n}\n\n\
    // need Intersect/distLP, r.s\u306F\u3088\u308Al.s\u306B\u8FD1\u3044\nint crossCS(const\
    \ C& c, const L& s, L& l) {\n    if (!crossCL(c, s, l)) return 0;\n    bool f1\
    \ = !ccw(s, l.s), f2 = !ccw(s, l.t);\n    if (f1 && f2) return 2;\n    if (!f1\
    \ && !f2) return 0;\n    if (f1)\n        l.t = l.s;\n    else\n        l.s =\
    \ l.t;\n    return 1;\n}\n\n// return number of cross point\n// l, r\u306Fc\u304B\
    \u3089\u898B\u305F\u4EA4\u70B9\u306E\u89D2\u5EA6\u3001[l, r]\u304Cd\u306B\u8986\
    \u308F\u308C\u3066\u3044\u308B\nint crossCC(const C& c, const C& d, D& l, D& r)\
    \ {\n    if (c.p == d.p) {\n        assert(sgn(c.r - d.r));  // prohibit same\
    \ circles\n        return 0;\n    }\n    D di = (c.p - d.p).abs(), bth = (d.p\
    \ - c.p).arg();\n    D costh = (c.r * c.r + di * di - d.r * d.r) / (2 * c.r *\
    \ di);\n    int ty = min(sgn(c.r + d.r, di), sgn(di, abs(c.r - d.r)));\n    if\
    \ (ty == -1) return 0;\n    if (ty == 0) costh = sgn(costh);\n    D th = acos(costh);\n\
    \    l = bth - th;\n    r = bth + th;\n    return ty + 1;\n}\n\n// p\u304B\u3089\
    c\u306B\u63A5\u7DDA\u3092\u5F15\u304F\uFF0C\u4EA4\u70B9\u306Fp1, p2\nint tangent(const\
    \ C& c, const P& p, P& p1, P& p2) {\n    D di = (c.p - p).abs();\n    int si =\
    \ sgn(c.r, di);\n    if (si == 1) return 0;\n    D th = acos(min(D(1), c.r / di));\n\
    \    D ar = (p - c.p).arg();\n    p1 = c.p + P::polar(c.r, ar - th);\n    p2 =\
    \ c.p + P::polar(c.r, ar + th);\n    if (si == 0) return 1;\n    return 2;\n}\n\
    \n//\u5171\u901A\u63A5\u7DDA\nint tangent(const C& c, const C& d, L& l, L& r,\
    \ bool inter) {\n    D di = (d.p - c.p).abs(), ar = (d.p - c.p).arg();\n    if\
    \ (sgn(di) == 0) {\n        assert(sgn(c.r - d.r));  // prohibit same circles\n\
    \        return 0;\n    }\n    D costh = c.r + (inter ? d.r : -d.r);\n    int\
    \ si = sgn(abs(costh), di);\n    costh /= di;\n    if (si == 1)\n        return\
    \ 0;\n    else if (si == 0)\n        costh = sgn(costh);\n    D th = acos(costh);\n\
    \    P base;\n    base = P::polar(1, ar - th);\n    l = L(c.p + base * c.r, d.p\
    \ + base * d.r * (inter ? -1 : 1));\n    base = P::polar(1, ar + th);\n    r =\
    \ L(c.p + base * c.r, d.p + base * d.r * (inter ? -1 : 1));\n    if (si == 0)\
    \ return 1;\n    return 2;\n}\n\nC circum_circle(P a, P b, P c) {\n    b -= a;\n\
    \    c -= a;\n    D s = 2 * crs(b, c);\n    D x = (b - c).norm(), y = c.norm(),\
    \ z = b.norm();\n    D S = x + y + z;\n    P r = (b * (S - 2 * y) * y + c * z\
    \ * (S - 2 * z)) / (s * s);\n    return C(r + a, r.abs());\n}\n\nC smallest_circle(const\
    \ Pol& p, int i, array<P, 3> q, int j) {\n    if (i == int(p.size())) {\n    \
    \    switch (j) {\n            case 0:\n                return C(P(0, 0), -1);\n\
    \            case 1:\n                return C(q[0], 0);\n            case 2:\n\
    \                return C((q[0] + q[1]) / D(2.0), (q[0] - q[1]).abs() / D(2.0));\n\
    \            case 3:\n                return circum_circle(q[0], q[1], q[2]);\n\
    \        }\n        assert(false);\n    }\n    C c = smallest_circle(p, i + 1,\
    \ q, j);\n    if (sgn((p[i] - c.p).abs(), c.r) == 1) {\n        q[j] = p[i];\n\
    \        return smallest_circle(p, i + 1, q, j + 1);\n    }\n    return c;\n}\n\
    C smallest_circle(Pol p) {\n    random_shuffle(begin(p), end(p));\n    return\
    \ smallest_circle(p, 0, array<P, 3>(), 0);\n}\n\n// C(P(0, 0), r)\u3068Tri((0,\
    \ 0), a, b)\u306E\u5171\u6709\u9762\u7A4D\nD area2CT(const C& c, const P& _a,\
    \ const P& _b) {\n    P a = _a - c.p, b = _b - c.p;\n    D r = c.r;\n    if (a\
    \ == b) return 0;\n    auto single = [&](P x, P y, bool tri) {\n        if (tri)\n\
    \            return crs(x, y);\n        else\n            return r * r * ((y *\
    \ P(x.x, -x.y)).arg());\n    };\n    bool ia = sgn(a.abs(), r) != 1, ib = sgn(b.abs(),\
    \ r) != 1;\n    if (ia && ib) return single(a, b, true);\n    L l;\n    if (!crossCS(C(P(0,\
    \ 0), r), L(a, b), l)) return single(a, b, false);\n    return single(a, l.s,\
    \ ia) + single(l.s, l.t, true) + single(l.t, b, ib);\n}\n\n// p, c\u306E\u5171\
    \u6709\u9762\u7A4D\nD area2CPol(const C& c, const Pol& po) {\n    D sm = 0;\n\
    \    P a, b = po.back();\n    for (auto p : po) {\n        a = b;\n        b =\
    \ p;\n        sm += area2CT(c, a, b);\n    }\n    return sm;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: src/geo/circle.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/geo/circle.hpp
layout: document
redirect_from:
- /library/src/geo/circle.hpp
- /library/src/geo/circle.hpp.html
title: src/geo/circle.hpp
---
