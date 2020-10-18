---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/bitop.hpp
    title: src/bitop.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: src/math/frac.hpp
    title: src/math/frac.hpp
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: bitop.hpp: line\
    \ -1: no such header\n"
  code: "#pragma once\n\n#include \"bitop.hpp\"\n\n//binary gcd\nll gcd(ll _a, ll\
    \ _b) {\n    ull a = abs(_a), b = abs(_b);\n    if (a == 0) return b;\n    if\
    \ (b == 0) return a;\n    int shift = bsf(a|b);\n    a >>= bsf(a);\n    do {\n\
    \        b >>= bsf(b);\n        if (a > b) swap(a, b);\n        b -= a;\n    }\
    \ while (b);\n    return (a << shift);\n}\n\n/// g:gcd(a, b), ax+by=g\nstruct\
    \ EG { ll g, x, y; };\nEG ext_gcd(ll a, ll b) {\n    if (b == 0) {\n        if\
    \ (a >= 0) return EG{a, 1, 0};\n        else return EG{-a, -1, 0};\n    } else\
    \ {\n        auto e = ext_gcd(b, a % b);\n        return EG{e.g, e.y, e.x - a\
    \ / b * e.y};\n    }\n}\n\n\nll inv_mod(ll x, ll md) {\n    auto z = ext_gcd(x,\
    \ md).x;\n    return (z % md + md) % md;\n}\n\ntemplate<class T, class U>\nT pow_mod(T\
    \ x, U n, T md) {\n    T r = 1 % md;\n    x %= md;\n    while (n) {\n        if\
    \ (n & 1) r = (r * x) % md;\n        x = (x * x) % md;\n        n >>= 1;\n   \
    \ }\n    return r;\n}\n\n// (rem, mod)\npair<ll, ll> crt(const V<ll>& b, const\
    \ V<ll>& c) {\n    int n = int(b.size());\n    ll r = 0, m = 1;\n    for (int\
    \ i = 0; i < n; i++) {\n        auto eg = ext_gcd(m, c[i]);\n        ll g = eg.g,\
    \ im = eg.x;\n        if ((b[i] - r) % g) return {0, -1};\n        ll tmp = (b[i]\
    \ - r) / g * im % (c[i] / g);\n        r += m * tmp;\n        m *= c[i] / g;\n\
    \    }\n    return {(r % m + m) % m, m};\n}\n"
  dependsOn:
  - src/bitop.hpp
  isVerificationFile: false
  path: src/math/primitive.hpp
  requiredBy:
  - src/math/frac.hpp
  timestamp: '2020-05-22 19:22:07+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/math/primitive.hpp
layout: document
redirect_from:
- /library/src/math/primitive.hpp
- /library/src/math/primitive.hpp.html
title: src/math/primitive.hpp
---
