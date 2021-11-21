---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/base.hpp
    title: src/base.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: src/nimber.test.cpp
    title: src/nimber.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: base.hpp: line\
    \ -1: no such header\n"
  code: "#pragma once\n\n#include \"base.hpp\"\n\nstruct Nimber64;\nNimber64 mul_naive(Nimber64\
    \ l, Nimber64 r);\nstruct Nimber64 {\n    const static V<ull> factor;\n    const\
    \ static array<array<unsigned char, 256>, 256> small;\n    const static array<array<array<Nimber64,\
    \ 256>, 8>, 8> precalc;\n    ull v;\n    Nimber64() : v(0) {}\n    Nimber64(ull\
    \ _v) : v(_v) {}\n    const Nimber64 operator+(Nimber64 r) const { return v ^\
    \ r.v; }\n    const Nimber64 operator*(Nimber64 r) const {\n        Nimber64 ans;\n\
    \        for (int i = 0; i < 8; i++) {\n            for (int j = 0; j < 8; j++)\
    \ {\n                ull x = (v >> (8 * i)) % 256;\n                ull y = (r.v\
    \ >> (8 * j)) % 256;\n                ans += precalc[i][j][small[x][y]];\n   \
    \         }\n        }\n        return ans;\n    }\n    bool operator==(Nimber64\
    \ r) const { return v == r.v; }\n    Nimber64& operator+=(Nimber64 r) { return\
    \ *this = *this + r; }\n    Nimber64& operator*=(Nimber64 r) { return *this =\
    \ *this * r; }\n\n    Nimber64 pow(ull n) const {\n        Nimber64 x = *this,\
    \ r = 1;\n        while (n) {\n            if (n & 1) r = r * x;\n           \
    \ x = x * x;\n            n >>= 1;\n        }\n        return r;\n    }\n\n  \
    \  ull discrete_logarithm(Nimber64 y) {\n        ull rem = 0, mod = 1;\n     \
    \   for (ull p : factor) {\n            ull STEP = 1;\n            while (4 *\
    \ STEP * STEP < p) STEP *= 2;\n            auto inside = [&](Nimber64 x, Nimber64\
    \ z) {\n                unordered_map<ull, int> mp;\n                Nimber64\
    \ big = 1;  // x^m\n                for (int i = 0; i < int(STEP); i++) {\n  \
    \                  mp[z.v] = i;\n                    z *= x;\n               \
    \     big *= x;\n                }\n                Nimber64 now = 1;\n      \
    \          for (int step = 0; step < int(p + 10); step += STEP) {\n          \
    \          now *= big;\n                    // check [step + 1, step + STEP]\n\
    \                    if (mp.find(now.v) != mp.end()) {\n                     \
    \   return (step + STEP) - mp[now.v];\n                    }\n               \
    \ }\n                return ull(-1);\n            };\n\n            ull q = ull(-1)\
    \ / p;\n            ull res = inside((*this).pow(q), y.pow(q));\n            if\
    \ (res == ull(-1)) {\n                return ull(-1);\n            }\n       \
    \     res %= p;\n            // mod p = v\n            if (mod == 1) {\n     \
    \           rem = res;\n                mod = p;\n            } else {\n     \
    \           while (rem % p != res) rem += mod;\n                mod *= p;\n  \
    \          }\n        }\n        return rem;\n    }\n\n    bool is_primitive_root()\
    \ const {\n        for (ull p : factor) {\n            if ((*this).pow(ull(-1)\
    \ / p).v == 1) return false;\n        }\n        return true;\n    }\n};\nconst\
    \ V<ull> Nimber64::factor = {\n    6700417, 65537, 641, 257, 17, 5, 3,\n};\n\n\
    Nimber64 mul_naive(Nimber64 l, Nimber64 r) {\n    ull a = l.v, b = r.v;\n    if\
    \ (a < b) swap(a, b);\n    if (b == 0) return 0;\n    if (b == 1) return a;\n\
    \    int p = 32;\n    while (max(a, b) < (1ULL << p)) p /= 2;\n    ull power =\
    \ 1ULL << p;\n    if (a >= power && b >= power) {\n        Nimber64 ans;\n   \
    \     ans += mul_naive(a % power, b % power);\n        ans += mul_naive(a / power,\
    \ b % power).v * power;\n        ans += mul_naive(a % power, b / power).v * power;\n\
    \        auto x = mul_naive(a / power, b / power);\n        ans += x.v * power;\n\
    \        ans += mul_naive(x.v, power / 2);\n        return ans;\n    } else {\n\
    \        return Nimber64(mul_naive(a / power, b).v * power) +\n              \
    \ mul_naive(a % power, b);\n    }\n};\n\nconst array<array<unsigned char, 256>,\
    \ 256> Nimber64::small = []() {\n    array<array<unsigned char, 256>, 256> small;\n\
    \    for (int i = 0; i < 256; i++) {\n        for (int j = 0; j < 256; j++) {\n\
    \            small[i][j] = (unsigned char)(mul_naive(i, j).v);\n        }\n  \
    \  }\n    return small;\n}();\n\nconst array<array<array<Nimber64, 256>, 8>, 8>\
    \ Nimber64::precalc = []() {\n    array<array<array<Nimber64, 256>, 8>, 8> precalc;\n\
    \    for (int i = 0; i < 8; i++) {\n        for (int j = 0; j < 8; j++) {\n  \
    \          for (int k = 0; k < 256; k++) {\n                precalc[i][j][k] =\n\
    \                    mul_naive(mul_naive(1ULL << (8 * i), 1ULL << (8 * j)), k);\n\
    \            }\n        }\n    }\n    return precalc;\n}();\n"
  dependsOn:
  - src/base.hpp
  isVerificationFile: false
  path: src/math/nimber.hpp
  requiredBy: []
  timestamp: '2020-10-18 20:05:46+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - src/nimber.test.cpp
documentation_of: src/math/nimber.hpp
layout: document
redirect_from:
- /library/src/math/nimber.hpp
- /library/src/math/nimber.hpp.html
title: src/math/nimber.hpp
---
