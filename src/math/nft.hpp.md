---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/bitop.hpp
    title: src/bitop.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: src/inv_of_formal_power_series.test.cpp
    title: src/inv_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/nft_convolution.test.cpp
    title: src/nft_convolution.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"src/math/nft.hpp\"\n\n#line 2 \"src/bitop.hpp\"\n// bit\
    \ op\nint popcnt(uint x) { return __builtin_popcount(x); }\nint popcnt(ull x)\
    \ { return __builtin_popcountll(x); }\nint bsr(uint x) { return 31 - __builtin_clz(x);\
    \ }\nint bsr(ull x) { return 63 - __builtin_clzll(x); }\nint bsf(uint x) { return\
    \ __builtin_ctz(x); }\nint bsf(ull x) { return __builtin_ctzll(x); }\n#line 4\
    \ \"src/math/nft.hpp\"\n\ntemplate <class Mint> void nft(bool type, V<Mint>& a)\
    \ {\n    int n = int(a.size()), s = 0;\n    while ((1 << s) < n) s++;\n    assert(1\
    \ << s == n);\n\n    static V<Mint> ep, iep;\n    while (int(ep.size()) <= s)\
    \ {\n        ep.push_back(Mint::G.pow(Mint(-1).v / (1 << ep.size())));\n     \
    \   iep.push_back(ep.back().inv());\n    }\n    V<Mint> b(n);\n    for (int i\
    \ = 1; i <= s; i++) {\n        int w = 1 << (s - i);\n        Mint base = type\
    \ ? iep[i] : ep[i], now = 1;\n        for (int y = 0; y < n / 2; y += w) {\n \
    \           for (int x = 0; x < w; x++) {\n                auto l = a[y << 1 |\
    \ x];\n                auto r = now * a[y << 1 | x | w];\n                b[y\
    \ | x] = l + r;\n                b[y | x | n >> 1] = l - r;\n            }\n \
    \           now *= base;\n        }\n        swap(a, b);\n    }\n}\n\ntemplate\
    \ <class Mint> V<Mint> multiply_nft(const V<Mint>& a, const V<Mint>& b) {\n  \
    \  int n = int(a.size()), m = int(b.size());\n    if (!n || !m) return {};\n \
    \   if (min(n, m) <= 8) {\n        V<Mint> ans(n + m - 1);\n        for (int i\
    \ = 0; i < n; i++)\n            for (int j = 0; j < m; j++) ans[i + j] += a[i]\
    \ * b[j];\n        return ans;\n    }\n    int lg = 0;\n    while ((1 << lg) <\
    \ n + m - 1) lg++;\n    int z = 1 << lg;\n    auto a2 = a, b2 = b;\n    a2.resize(z);\n\
    \    b2.resize(z);\n    nft(false, a2);\n    nft(false, b2);\n    for (int i =\
    \ 0; i < z; i++) a2[i] *= b2[i];\n    nft(true, a2);\n    a2.resize(n + m - 1);\n\
    \    Mint iz = Mint(z).inv();\n    for (int i = 0; i < n + m - 1; i++) a2[i] *=\
    \ iz;\n    return a2;\n}\n\n// Cooley-Tukey: input -> butterfly -> bit reversing\
    \ -> output \u304B\u3089\n// bit reversing\u3092\u629C\u3044\u305F\u3082\u306E\
    \ \u76F4\u63A5\u4F7F\u3046\u306A\ntemplate <class Mint> void butterfly(bool type,\
    \ V<Mint>& a) {\n    int n = int(a.size()), h = 0;\n    while ((1 << h) < n) h++;\n\
    \    assert(1 << h == n);\n    if (n == 1) return;\n\n    static V<Mint> snow,\
    \ sinow;\n    if (snow.empty()) {\n        Mint sep = Mint(1), siep = Mint(1);\n\
    \        uint mod = Mint(-1).v;\n        uint di = 4;\n        while (mod % di\
    \ == 0) {\n            Mint ep = Mint::G.pow(mod / di);\n            Mint iep\
    \ = ep.inv();\n            snow.push_back(siep * ep);\n            sinow.push_back(sep\
    \ * iep);\n            sep *= ep;\n            siep *= iep;\n            di *=\
    \ 2;\n        }\n    }\n\n    if (!type) {\n        // fft\n        for (int ph\
    \ = 1; ph <= h; ph++) {\n            // phase ph: size w -> 2w \u306E FFT, p \u4E26\
    \u5217\n            int w = 1 << (ph - 1), p = 1 << (h - ph);\n            Mint\
    \ now = Mint(1);\n            for (int s = 0; s < w; s++) {\n                int\
    \ offset = s << (h - ph + 1);\n                for (int i = 0; i < p; i++) {\n\
    \                    auto l = a[i + offset];\n                    auto r = a[i\
    \ + offset + p] * now;\n                    a[i + offset] = l + r;\n         \
    \           a[i + offset + p] = l - r;\n                }\n                int\
    \ u = bsf(~uint(s));\n                now *= snow[u];\n            }\n       \
    \ }\n    } else {\n        // ifft\n        for (int ph = h; ph >= 1; ph--) {\n\
    \            int w = 1 << (ph - 1), p = 1 << (h - ph);\n            Mint inow\
    \ = Mint(1);\n            for (int s = 0; s < w; s++) {\n                int offset\
    \ = s << (h - ph + 1);\n                for (int i = 0; i < p; i++) {\n      \
    \              auto l = a[i + offset];\n                    auto r = a[i + offset\
    \ + p];\n                    a[i + offset] = l + r;\n                    a[i +\
    \ offset + p] = (l - r) * inow;\n                }\n                int u = bsf(~uint(s));\n\
    \                inow *= sinow[u];\n            }\n        }\n    }\n}\n\ntemplate\
    \ <class Mint> V<Mint> multiply(const V<Mint>& a, const V<Mint>& b) {\n    int\
    \ n = int(a.size()), m = int(b.size());\n    if (!n || !m) return {};\n    if\
    \ (min(n, m) < 8) {\n        V<Mint> ans(n + m - 1);\n        for (int i = 0;\
    \ i < n; i++)\n            for (int j = 0; j < m; j++) ans[i + j] += a[i] * b[j];\n\
    \        return ans;\n    }\n    int lg = 0;\n    while ((1 << lg) < n + m - 1)\
    \ lg++;\n    int z = 1 << lg;\n    auto a2 = a;\n    a2.resize(z);\n    butterfly(false,\
    \ a2);\n    if (a == b) {\n        for (int i = 0; i < z; i++) a2[i] *= a2[i];\n\
    \    } else {\n        auto b2 = b;\n        b2.resize(z);\n        butterfly(false,\
    \ b2);\n        for (int i = 0; i < z; i++) a2[i] *= b2[i];\n    }\n    butterfly(true,\
    \ a2);\n    a2.resize(n + m - 1);\n    Mint iz = Mint(z).inv();\n    for (int\
    \ i = 0; i < n + m - 1; i++) a2[i] *= iz;\n    return a2;\n}\n"
  code: "#pragma once\n\n#include \"../bitop.hpp\"\n\ntemplate <class Mint> void nft(bool\
    \ type, V<Mint>& a) {\n    int n = int(a.size()), s = 0;\n    while ((1 << s)\
    \ < n) s++;\n    assert(1 << s == n);\n\n    static V<Mint> ep, iep;\n    while\
    \ (int(ep.size()) <= s) {\n        ep.push_back(Mint::G.pow(Mint(-1).v / (1 <<\
    \ ep.size())));\n        iep.push_back(ep.back().inv());\n    }\n    V<Mint> b(n);\n\
    \    for (int i = 1; i <= s; i++) {\n        int w = 1 << (s - i);\n        Mint\
    \ base = type ? iep[i] : ep[i], now = 1;\n        for (int y = 0; y < n / 2; y\
    \ += w) {\n            for (int x = 0; x < w; x++) {\n                auto l =\
    \ a[y << 1 | x];\n                auto r = now * a[y << 1 | x | w];\n        \
    \        b[y | x] = l + r;\n                b[y | x | n >> 1] = l - r;\n     \
    \       }\n            now *= base;\n        }\n        swap(a, b);\n    }\n}\n\
    \ntemplate <class Mint> V<Mint> multiply_nft(const V<Mint>& a, const V<Mint>&\
    \ b) {\n    int n = int(a.size()), m = int(b.size());\n    if (!n || !m) return\
    \ {};\n    if (min(n, m) <= 8) {\n        V<Mint> ans(n + m - 1);\n        for\
    \ (int i = 0; i < n; i++)\n            for (int j = 0; j < m; j++) ans[i + j]\
    \ += a[i] * b[j];\n        return ans;\n    }\n    int lg = 0;\n    while ((1\
    \ << lg) < n + m - 1) lg++;\n    int z = 1 << lg;\n    auto a2 = a, b2 = b;\n\
    \    a2.resize(z);\n    b2.resize(z);\n    nft(false, a2);\n    nft(false, b2);\n\
    \    for (int i = 0; i < z; i++) a2[i] *= b2[i];\n    nft(true, a2);\n    a2.resize(n\
    \ + m - 1);\n    Mint iz = Mint(z).inv();\n    for (int i = 0; i < n + m - 1;\
    \ i++) a2[i] *= iz;\n    return a2;\n}\n\n// Cooley-Tukey: input -> butterfly\
    \ -> bit reversing -> output \u304B\u3089\n// bit reversing\u3092\u629C\u3044\u305F\
    \u3082\u306E \u76F4\u63A5\u4F7F\u3046\u306A\ntemplate <class Mint> void butterfly(bool\
    \ type, V<Mint>& a) {\n    int n = int(a.size()), h = 0;\n    while ((1 << h)\
    \ < n) h++;\n    assert(1 << h == n);\n    if (n == 1) return;\n\n    static V<Mint>\
    \ snow, sinow;\n    if (snow.empty()) {\n        Mint sep = Mint(1), siep = Mint(1);\n\
    \        uint mod = Mint(-1).v;\n        uint di = 4;\n        while (mod % di\
    \ == 0) {\n            Mint ep = Mint::G.pow(mod / di);\n            Mint iep\
    \ = ep.inv();\n            snow.push_back(siep * ep);\n            sinow.push_back(sep\
    \ * iep);\n            sep *= ep;\n            siep *= iep;\n            di *=\
    \ 2;\n        }\n    }\n\n    if (!type) {\n        // fft\n        for (int ph\
    \ = 1; ph <= h; ph++) {\n            // phase ph: size w -> 2w \u306E FFT, p \u4E26\
    \u5217\n            int w = 1 << (ph - 1), p = 1 << (h - ph);\n            Mint\
    \ now = Mint(1);\n            for (int s = 0; s < w; s++) {\n                int\
    \ offset = s << (h - ph + 1);\n                for (int i = 0; i < p; i++) {\n\
    \                    auto l = a[i + offset];\n                    auto r = a[i\
    \ + offset + p] * now;\n                    a[i + offset] = l + r;\n         \
    \           a[i + offset + p] = l - r;\n                }\n                int\
    \ u = bsf(~uint(s));\n                now *= snow[u];\n            }\n       \
    \ }\n    } else {\n        // ifft\n        for (int ph = h; ph >= 1; ph--) {\n\
    \            int w = 1 << (ph - 1), p = 1 << (h - ph);\n            Mint inow\
    \ = Mint(1);\n            for (int s = 0; s < w; s++) {\n                int offset\
    \ = s << (h - ph + 1);\n                for (int i = 0; i < p; i++) {\n      \
    \              auto l = a[i + offset];\n                    auto r = a[i + offset\
    \ + p];\n                    a[i + offset] = l + r;\n                    a[i +\
    \ offset + p] = (l - r) * inow;\n                }\n                int u = bsf(~uint(s));\n\
    \                inow *= sinow[u];\n            }\n        }\n    }\n}\n\ntemplate\
    \ <class Mint> V<Mint> multiply(const V<Mint>& a, const V<Mint>& b) {\n    int\
    \ n = int(a.size()), m = int(b.size());\n    if (!n || !m) return {};\n    if\
    \ (min(n, m) < 8) {\n        V<Mint> ans(n + m - 1);\n        for (int i = 0;\
    \ i < n; i++)\n            for (int j = 0; j < m; j++) ans[i + j] += a[i] * b[j];\n\
    \        return ans;\n    }\n    int lg = 0;\n    while ((1 << lg) < n + m - 1)\
    \ lg++;\n    int z = 1 << lg;\n    auto a2 = a;\n    a2.resize(z);\n    butterfly(false,\
    \ a2);\n    if (a == b) {\n        for (int i = 0; i < z; i++) a2[i] *= a2[i];\n\
    \    } else {\n        auto b2 = b;\n        b2.resize(z);\n        butterfly(false,\
    \ b2);\n        for (int i = 0; i < z; i++) a2[i] *= b2[i];\n    }\n    butterfly(true,\
    \ a2);\n    a2.resize(n + m - 1);\n    Mint iz = Mint(z).inv();\n    for (int\
    \ i = 0; i < n + m - 1; i++) a2[i] *= iz;\n    return a2;\n}\n"
  dependsOn:
  - src/bitop.hpp
  isVerificationFile: false
  path: src/math/nft.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - src/nft_convolution.test.cpp
  - src/inv_of_formal_power_series.test.cpp
documentation_of: src/math/nft.hpp
layout: document
redirect_from:
- /library/src/math/nft.hpp
- /library/src/math/nft.hpp.html
title: src/math/nft.hpp
---
