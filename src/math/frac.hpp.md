---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/bitop.hpp
    title: src/bitop.hpp
  - icon: ':warning:'
    path: src/math/primitive.hpp
    title: src/math/primitive.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: math/primitive.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n\n#include \"math/primitive.hpp\"\n\n\ntemplate <class I> struct\
    \ Frac {\n    I a, b;  // a / b\n    Frac(I _a = 0) : a(_a), b(1) {}\n    Frac(I\
    \ _a, I _b) {\n        I g = gcd(_a, _b);\n        if (_b < 0) g = -g;\n     \
    \   a = _a / g;\n        b = _b / g;\n    }\n    Frac operator-() const {\n  \
    \      Frac f;\n        f.a = -a;\n        f.b = b;\n        return f;\n    }\n\
    \    Frac operator+(const Frac& r) const { return {r.b * a + b * r.a, b * r.b};\
    \ }\n    Frac operator-(const Frac& r) const { return *this + (-r); }\n    Frac\
    \ operator*(const Frac& r) const { return {a * r.a, b * r.b}; }\n    Frac operator/(const\
    \ Frac& r) const { return {a * r.b, b * r.a}; }\n    Frac& operator+=(const Frac&\
    \ r) { return *this = *this + r; }\n    Frac& operator-=(const Frac& r) { return\
    \ *this = *this - r; }\n    Frac& operator*=(const Frac& r) { return *this = *this\
    \ * r; }\n    Frac& operator/=(const Frac& r) { return *this = *this / r; }\n\
    \    bool operator<(const Frac& r) const { return a * r.b < b * r.a; }\n    bool\
    \ operator>(const Frac& r) const { return r < *this; }\n    bool operator<=(const\
    \ Frac& r) const { return !(r < *this); }\n    bool operator>=(const Frac& r)\
    \ const { return !(*this < r); }\n    bool operator==(const Frac& r) const {\n\
    \        return !(*this < r) && !(r < *this);\n    }\n    bool operator!=(const\
    \ Frac& r) const { return !(*this == r); }\n\n    static Frac rec(Frac x, Frac\
    \ y, Frac l, Frac r) {\n        auto flip = [&](Frac& f) { f = Frac(1) - f; };\n\
    \        auto cross = [&](const Frac& f, const Frac& g) {\n            return\
    \ f.a * g.b - f.b * g.a;\n        };\n        Frac m = {l.a + r.a, l.b + r.b};\n\
    \        if (x < m && m < y) return m;\n        bool s = !(x < m);\n        if\
    \ (s) {\n            flip(l);\n            flip(r);\n            flip(m);\n  \
    \          flip(x);\n            flip(y);\n            swap(l, r);\n         \
    \   swap(x, y);\n        }\n        I k = cross(r, y) / cross(y, l) + 1;\n   \
    \     Frac p = {k * l.a + r.a, k * l.b + r.b};\n        if (x < p) {\n       \
    \     if (s) flip(p);\n            return p;\n        }\n        Frac q = rec(x,\
    \ y, p, {(k - 1) * l.a + r.a, (k - 1) * l.b + r.b});\n        if (s) flip(q);\n\
    \        return q;\n    }\n    static Frac in_bet(Frac x, Frac y) {\n        if\
    \ (y < x) swap(x, y);\n        Frac ret;\n        I num = x.a >= 0 ? x.a / x.b\
    \ : -((x.b - 1 - x.a) / x.b);\n        x.a -= x.b * num;\n        y.a -= y.b *\
    \ num;\n        if (Frac{1, 1} < y)\n            ret = Frac{1, 1};\n        else\n\
    \            ret = rec(x, y, Frac{0, 1}, Frac{1, 1});\n        ret.a += ret.b\
    \ * num;\n        return ret;\n    }\n};\n"
  dependsOn:
  - src/math/primitive.hpp
  - src/bitop.hpp
  isVerificationFile: false
  path: src/math/frac.hpp
  requiredBy: []
  timestamp: '2020-05-22 19:22:07+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/math/frac.hpp
layout: document
redirect_from:
- /library/src/math/frac.hpp
- /library/src/math/frac.hpp.html
title: src/math/frac.hpp
---
