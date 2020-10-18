---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"src/math/fft.hpp\"\nusing D = double;\nconst D PI = acos(D(-1));\n\
    using Pc = complex<D>;\n\nvoid fft(bool type, V<Pc>& a) {\n    int n = int(a.size()),\
    \ s = 0;\n    while ((1 << s) < n) s++;\n    assert(1 << s == n);\n\n    static\
    \ V<Pc> ep[30];\n    if (!ep[s].size()) {\n        for (int i = 0; i < n; i++)\
    \ {\n            ep[s].push_back(polar<D>(1, i * 2 * PI / n));\n        }\n  \
    \  }\n    V<Pc> b(n);\n    for (int i = 1; i <= s; i++) {\n        int w = 1 <<\
    \ (s - i);\n        for (int y = 0; y < n / 2; y += w) {\n            Pc now =\
    \ ep[s][y];\n            if (type) now = conj(now);\n            for (int x =\
    \ 0; x < w; x++) {\n                auto l = a[y << 1 | x];\n                auto\
    \ u = now, v = a[y << 1 | x | w];\n                auto r = Pc(u.real() * v.real()\
    \ - u.imag() * v.imag(),\n                            u.real() * v.imag() + u.imag()\
    \ * v.real());\n                b[y | x] = l + r;\n                b[y | x | n\
    \ >> 1] = l - r;\n            }\n        }\n        swap(a, b);\n    }\n}\n\n\
    V<Pc> multiply(const V<Pc>& a, const V<Pc>& b) {\n    int A = int(a.size()), B\
    \ = int(b.size());\n    if (!A || !B) return {};\n    int lg = 0;\n    while ((1\
    \ << lg) < A + B - 1) lg++;\n    int N = 1 << lg;\n    V<Pc> ac(N), bc(N);\n \
    \   for (int i = 0; i < A; i++) ac[i] = a[i];\n    for (int i = 0; i < B; i++)\
    \ bc[i] = b[i];\n    fft(false, ac);\n    fft(false, bc);\n    for (int i = 0;\
    \ i < N; i++) {\n        ac[i] *= bc[i];\n    }\n    fft(true, ac);\n    V<Pc>\
    \ c(A + B - 1);\n    for (int i = 0; i < A + B - 1; i++) {\n        c[i] = ac[i]\
    \ / D(N);\n    }\n    return c;\n}\n\nV<D> multiply(const V<D>& a, const V<D>&\
    \ b) {\n    int A = int(a.size()), B = int(b.size());\n    if (!A || !B) return\
    \ {};\n    int lg = 0;\n    while ((1 << lg) < A + B - 1) lg++;\n    int N = 1\
    \ << lg;\n    V<Pc> d(N);\n    for (int i = 0; i < N; i++) d[i] = Pc(i < A ? a[i]\
    \ : 0, i < B ? b[i] : 0);\n    fft(false, d);\n    for (int i = 0; i < N / 2 +\
    \ 1; i++) {\n        auto j = i ? (N - i) : 0;\n        Pc x = Pc(d[i].real()\
    \ + d[j].real(), d[i].imag() - d[j].imag());\n        Pc y = Pc(d[i].imag() +\
    \ d[j].imag(), -d[i].real() + d[j].real());\n        d[i] = x * y / D(4);\n  \
    \      if (i != j) d[j] = conj(d[i]);\n    }\n    fft(true, d);\n    V<D> c(A\
    \ + B - 1);\n    for (int i = 0; i < A + B - 1; i++) {\n        c[i] = d[i].real()\
    \ / N;\n    }\n    return c;\n}\n\ntemplate <class Mint, int K = 3, int SHIFT\
    \ = 11>\nV<Mint> multiply(const V<Mint>& a, const V<Mint>& b) {\n    int A = int(a.size()),\
    \ B = int(b.size());\n    if (!A || !B) return {};\n    int lg = 0;\n    while\
    \ ((1 << lg) < A + B - 1) lg++;\n    int N = 1 << lg;\n\n    VV<Pc> x(K, V<Pc>(N)),\
    \ y(K, V<Pc>(N));\n    for (int ph = 0; ph < K; ph++) {\n        V<Pc> z(N);\n\
    \        for (int i = 0; i < N; i++) {\n            D nx = 0, ny = 0;\n      \
    \      if (i < A) nx = (a[i].v >> (ph * SHIFT)) & ((1 << SHIFT) - 1);\n      \
    \      if (i < B) ny = (b[i].v >> (ph * SHIFT)) & ((1 << SHIFT) - 1);\n      \
    \      z[i] = Pc(nx, ny);\n        }\n        fft(false, z);\n        for (int\
    \ i = 0; i < N; i++) {\n            z[i] *= 0.5;\n        }\n        for (int\
    \ i = 0; i < N; i++) {\n            int j = (i) ? N - i : 0;\n            x[ph][i]\
    \ = Pc(z[i].real() + z[j].real(), z[i].imag() - z[j].imag());\n            y[ph][i]\
    \ =\n                Pc(z[i].imag() + z[j].imag(), -z[i].real() + z[j].real());\n\
    \        }\n    }\n    VV<Pc> z(K, V<Pc>(N));\n    for (int xp = 0; xp < K; xp++)\
    \ {\n        for (int yp = 0; yp < K; yp++) {\n            int zp = (xp + yp)\
    \ % K;\n            for (int i = 0; i < N; i++) {\n                if (xp + yp\
    \ < K) {\n                    z[zp][i] += x[xp][i] * y[yp][i];\n             \
    \   } else {\n                    z[zp][i] += x[xp][i] * y[yp][i] * Pc(0, 1);\n\
    \                }\n            }\n        }\n    }\n    for (int ph = 0; ph <\
    \ K; ph++) {\n        fft(true, z[ph]);\n    }\n    V<Mint> c(A + B - 1);\n  \
    \  Mint base = 1;\n    for (int ph = 0; ph < 2 * K - 1; ph++) {\n        for (int\
    \ i = 0; i < A + B - 1; i++) {\n            if (ph < K) {\n                c[i]\
    \ += Mint(ll(round(z[ph][i].real() / N))) * base;\n            } else {\n    \
    \            c[i] += Mint(ll(round(z[ph - K][i].imag() / N))) * base;\n      \
    \      }\n        }\n        base *= 1 << SHIFT;\n    }\n    return c;\n}\n"
  code: "using D = double;\nconst D PI = acos(D(-1));\nusing Pc = complex<D>;\n\n\
    void fft(bool type, V<Pc>& a) {\n    int n = int(a.size()), s = 0;\n    while\
    \ ((1 << s) < n) s++;\n    assert(1 << s == n);\n\n    static V<Pc> ep[30];\n\
    \    if (!ep[s].size()) {\n        for (int i = 0; i < n; i++) {\n           \
    \ ep[s].push_back(polar<D>(1, i * 2 * PI / n));\n        }\n    }\n    V<Pc> b(n);\n\
    \    for (int i = 1; i <= s; i++) {\n        int w = 1 << (s - i);\n        for\
    \ (int y = 0; y < n / 2; y += w) {\n            Pc now = ep[s][y];\n         \
    \   if (type) now = conj(now);\n            for (int x = 0; x < w; x++) {\n  \
    \              auto l = a[y << 1 | x];\n                auto u = now, v = a[y\
    \ << 1 | x | w];\n                auto r = Pc(u.real() * v.real() - u.imag() *\
    \ v.imag(),\n                            u.real() * v.imag() + u.imag() * v.real());\n\
    \                b[y | x] = l + r;\n                b[y | x | n >> 1] = l - r;\n\
    \            }\n        }\n        swap(a, b);\n    }\n}\n\nV<Pc> multiply(const\
    \ V<Pc>& a, const V<Pc>& b) {\n    int A = int(a.size()), B = int(b.size());\n\
    \    if (!A || !B) return {};\n    int lg = 0;\n    while ((1 << lg) < A + B -\
    \ 1) lg++;\n    int N = 1 << lg;\n    V<Pc> ac(N), bc(N);\n    for (int i = 0;\
    \ i < A; i++) ac[i] = a[i];\n    for (int i = 0; i < B; i++) bc[i] = b[i];\n \
    \   fft(false, ac);\n    fft(false, bc);\n    for (int i = 0; i < N; i++) {\n\
    \        ac[i] *= bc[i];\n    }\n    fft(true, ac);\n    V<Pc> c(A + B - 1);\n\
    \    for (int i = 0; i < A + B - 1; i++) {\n        c[i] = ac[i] / D(N);\n   \
    \ }\n    return c;\n}\n\nV<D> multiply(const V<D>& a, const V<D>& b) {\n    int\
    \ A = int(a.size()), B = int(b.size());\n    if (!A || !B) return {};\n    int\
    \ lg = 0;\n    while ((1 << lg) < A + B - 1) lg++;\n    int N = 1 << lg;\n   \
    \ V<Pc> d(N);\n    for (int i = 0; i < N; i++) d[i] = Pc(i < A ? a[i] : 0, i <\
    \ B ? b[i] : 0);\n    fft(false, d);\n    for (int i = 0; i < N / 2 + 1; i++)\
    \ {\n        auto j = i ? (N - i) : 0;\n        Pc x = Pc(d[i].real() + d[j].real(),\
    \ d[i].imag() - d[j].imag());\n        Pc y = Pc(d[i].imag() + d[j].imag(), -d[i].real()\
    \ + d[j].real());\n        d[i] = x * y / D(4);\n        if (i != j) d[j] = conj(d[i]);\n\
    \    }\n    fft(true, d);\n    V<D> c(A + B - 1);\n    for (int i = 0; i < A +\
    \ B - 1; i++) {\n        c[i] = d[i].real() / N;\n    }\n    return c;\n}\n\n\
    template <class Mint, int K = 3, int SHIFT = 11>\nV<Mint> multiply(const V<Mint>&\
    \ a, const V<Mint>& b) {\n    int A = int(a.size()), B = int(b.size());\n    if\
    \ (!A || !B) return {};\n    int lg = 0;\n    while ((1 << lg) < A + B - 1) lg++;\n\
    \    int N = 1 << lg;\n\n    VV<Pc> x(K, V<Pc>(N)), y(K, V<Pc>(N));\n    for (int\
    \ ph = 0; ph < K; ph++) {\n        V<Pc> z(N);\n        for (int i = 0; i < N;\
    \ i++) {\n            D nx = 0, ny = 0;\n            if (i < A) nx = (a[i].v >>\
    \ (ph * SHIFT)) & ((1 << SHIFT) - 1);\n            if (i < B) ny = (b[i].v >>\
    \ (ph * SHIFT)) & ((1 << SHIFT) - 1);\n            z[i] = Pc(nx, ny);\n      \
    \  }\n        fft(false, z);\n        for (int i = 0; i < N; i++) {\n        \
    \    z[i] *= 0.5;\n        }\n        for (int i = 0; i < N; i++) {\n        \
    \    int j = (i) ? N - i : 0;\n            x[ph][i] = Pc(z[i].real() + z[j].real(),\
    \ z[i].imag() - z[j].imag());\n            y[ph][i] =\n                Pc(z[i].imag()\
    \ + z[j].imag(), -z[i].real() + z[j].real());\n        }\n    }\n    VV<Pc> z(K,\
    \ V<Pc>(N));\n    for (int xp = 0; xp < K; xp++) {\n        for (int yp = 0; yp\
    \ < K; yp++) {\n            int zp = (xp + yp) % K;\n            for (int i =\
    \ 0; i < N; i++) {\n                if (xp + yp < K) {\n                    z[zp][i]\
    \ += x[xp][i] * y[yp][i];\n                } else {\n                    z[zp][i]\
    \ += x[xp][i] * y[yp][i] * Pc(0, 1);\n                }\n            }\n     \
    \   }\n    }\n    for (int ph = 0; ph < K; ph++) {\n        fft(true, z[ph]);\n\
    \    }\n    V<Mint> c(A + B - 1);\n    Mint base = 1;\n    for (int ph = 0; ph\
    \ < 2 * K - 1; ph++) {\n        for (int i = 0; i < A + B - 1; i++) {\n      \
    \      if (ph < K) {\n                c[i] += Mint(ll(round(z[ph][i].real() /\
    \ N))) * base;\n            } else {\n                c[i] += Mint(ll(round(z[ph\
    \ - K][i].imag() / N))) * base;\n            }\n        }\n        base *= 1 <<\
    \ SHIFT;\n    }\n    return c;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: src/math/fft.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/math/fft.hpp
layout: document
redirect_from:
- /library/src/math/fft.hpp
- /library/src/math/fft.hpp.html
title: src/math/fft.hpp
---
