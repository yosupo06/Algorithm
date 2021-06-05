---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/bitop.hpp
    title: src/bitop.hpp
  - icon: ':warning:'
    path: src/datastructure/bitvector.hpp
    title: src/datastructure/bitvector.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: datastructure/bitvector.hpp:\
    \ line -1: no such header\n"
  code: "#include \"datastructure/bitvector.hpp\"\n\ntemplate <class D> struct Mat\
    \ : VV<D> {\n    using VV<D>::VV;\n    using VV<D>::size;\n    int h() const {\
    \ return int(size()); }\n    int w() const { return int((*this)[0].size()); }\n\
    \    Mat operator*(const Mat& r) const {\n        assert(w() == r.h());\n    \
    \    Mat res(h(), V<D>(r.w()));\n        for (int i = 0; i < h(); i++) {\n   \
    \         for (int j = 0; j < r.w(); j++) {\n                for (int k = 0; k\
    \ < w(); k++) {\n                    res[i][j] += (*this)[i][k] * r[k][j];\n \
    \               }\n            }\n        }\n        return res;\n    }\n    Mat&\
    \ operator*=(const Mat& r) { return *this = *this * r; }\n    Mat pow(ll n) const\
    \ {\n        assert(h() == w());\n        Mat x = *this, r(h(), V<D>(w()));\n\
    \        for (int i = 0; i < h(); i++) r[i][i] = D(1);\n        while (n) {\n\
    \            if (n & 1) r *= x;\n            x *= x;\n            n >>= 1;\n \
    \       }\n        return r;\n    }\n};\n\ntemplate <class D> V<D> solve_linear(Mat<D>\
    \ a, V<D> b, D eps) {\n    int h = a.h(), w = a.w();\n    int r = 0;\n    V<int>\
    \ idxs;\n    for (int x = 0; x < w; x++) {\n        for (int y = r + 1; y < h;\
    \ y++) {\n            D d = hypot(a[r][x], a[y][x]);\n            if (abs(d) <=\
    \ eps) continue;\n            D c = a[r][x] / d, s = a[y][x] / d;\n          \
    \  auto rot = [&](D& u, D& v) {\n                tie(u, v) = make_pair(c * u +\
    \ s * v, c * v - s * u);\n            };\n            rot(b[r], b[y]);\n     \
    \       for (int k = x; k < w; k++) rot(a[r][k], a[y][k]);\n        }\n      \
    \  if (a[r][x] <= eps) continue;\n        r++;\n        idxs.push_back(x);\n \
    \       if (r == h) break;\n    }\n    V<D> v(w);\n    for (int y = r - 1; y >=\
    \ 0; y--) {\n        int f = idxs[y];\n        v[f] = b[y];\n        for (int\
    \ x = f + 1; x < w; x++) {\n            v[f] -= a[y][x] * v[x];\n        }\n \
    \       v[f] /= a[y][f];\n    }\n    return v;\n}\n\ntemplate <class Mint> V<Mint>\
    \ solve_linear(Mat<Mint> a, V<Mint> b) {\n    int h = a.h(), w = a.w();\n    int\
    \ r = 0;\n    V<int> idxs;\n    for (int x = 0; x < w; x++) {\n        int my\
    \ = -1;\n        for (int y = r; y < h; y++) {\n            if (a[y][x]) {\n \
    \               my = y;\n                break;\n            }\n        }\n  \
    \      if (my == -1) continue;\n        if (r != my) swap(a[r], a[my]);\n    \
    \    swap(b[r], b[my]);\n        for (int y = r + 1; y < h; y++) {\n         \
    \   if (!a[y][x]) continue;\n            auto freq = a[y][x] / a[r][x];\n    \
    \        for (int k = x; k < w; k++) a[y][k] -= freq * a[r][k];\n            b[y]\
    \ -= freq * b[r];\n        }\n        r++;\n        idxs.push_back(x);\n     \
    \   if (r == h) break;\n    }\n    V<Mint> v(w);\n    for (int y = r - 1; y >=\
    \ 0; y--) {\n        int f = idxs[y];\n        v[f] = b[y];\n        for (int\
    \ x = f + 1; x < w; x++) {\n            v[f] -= a[y][x] * v[x];\n        }\n \
    \       v[f] /= a[y][f];\n    }\n    return v;\n}\n\ntemplate <class Mint> int\
    \ calc_rank(Mat<Mint> a) {\n    int h = a.h(), w = a.w();\n    int r = 0;\n  \
    \  V<int> idxs;\n    for (int x = 0; x < w; x++) {\n        int my = -1;\n   \
    \     for (int y = r; y < h; y++) {\n            if (a[y][x]) {\n            \
    \    my = y;\n                break;\n            }\n        }\n        if (my\
    \ == -1) continue;\n        if (r != my) swap(a[r], a[my]);\n        for (int\
    \ y = r + 1; y < h; y++) {\n            if (!a[y][x]) continue;\n            auto\
    \ freq = a[y][x] / a[r][x];\n            for (int k = x; k < w; k++) a[y][k] -=\
    \ freq * a[r][k];\n        }\n        r++;\n        idxs.push_back(x);\n     \
    \   if (r == h) break;\n    }\n    return r;\n}\n\ntemplate <class Mint> Mint\
    \ calc_det(Mat<Mint> a) {\n    assert(a.h() == a.w());\n    int n = a.h();\n\n\
    \    bool flip = false;\n    for (int x = 0; x < n; x++) {\n        int my = -1;\n\
    \        for (int y = x; y < n; y++) {\n            if (a[y][x]) {\n         \
    \       my = y;\n                break;\n            }\n        }\n        if\
    \ (my == -1) return 0;\n        if (x != my) {\n            swap(a[x], a[my]);\n\
    \            if ((x - my) % 2) flip = !flip;\n        }\n        for (int y =\
    \ x + 1; y < n; y++) {\n            if (!a[y][x]) continue;\n            auto\
    \ freq = a[y][x] / a[x][x];\n            for (int k = x; k < n; k++) a[y][k] -=\
    \ freq * a[x][k];\n        }\n    }\n    Mint det = (!flip ? 1 : -1);\n    for\
    \ (int i = 0; i < n; i++) {\n        det *= a[i][i];\n    }\n    return det;\n\
    }\n\ntemplate <class Mint> Mat<Mint> inverse(Mat<Mint> a) {\n    assert(a.h()\
    \ == a.w());\n    int n = a.h();\n\n    Mat<Mint> b(n, V<Mint>(n));\n    for (int\
    \ i = 0; i < n; i++) b[i][i] = 1;\n\n    for (int x = 0; x < n; x++) {\n     \
    \   int my = -1;\n        for (int y = x; y < n; y++) {\n            if (a[y][x])\
    \ {\n                my = y;\n                break;\n            }\n        }\n\
    \        if (my == -1) return {};\n        if (x != my) {\n            swap(a[x],\
    \ a[my]);\n            swap(b[x], b[my]);\n        }\n        auto freq = a[x][x];\n\
    \        for (int j = 0; j < n; j++) {\n            a[x][j] /= freq;\n       \
    \     b[x][j] /= freq;\n        }\n        for (int y = 0; y < n; y++) {\n   \
    \         if (x == y) continue;\n            if (!a[y][x]) continue;\n       \
    \     freq = a[y][x];\n            for (int k = 0; k < n; k++) a[y][k] -= freq\
    \ * a[x][k];\n            for (int k = 0; k < n; k++) b[y][k] -= freq * b[x][k];\n\
    \        }\n    }\n    return b;\n}\n\nstruct Mat2 : V<BitVec> {\n    using V<BitVec>::V;\n\
    \    using V<BitVec>::size;\n    int h() const { return int(size()); }\n    int\
    \ w() const { return int((*this)[0].size()); }\n    Mat2 operator*(const Mat2&\
    \ r) const {\n        assert(w() == r.h());\n        Mat2 r_t = Mat2(r.h(), BitVec(r.w()));\n\
    \        for (int y = 0; y < r_t.h(); y++) {\n            for (int x = 0; x <\
    \ r_t.w(); x++) {\n                r_t[y].set(x, r[x][y]);\n            }\n  \
    \      }\n        Mat2 res(h(), BitVec(r_t.h()));\n        for (int i = 0; i <\
    \ h(); i++) {\n            for (int j = 0; j < r_t.h(); j++) {\n             \
    \   res[i].set(j, ((*this)[i] ^ r_t[j]).count() % 2 == 1);\n            }\n  \
    \      }\n        return res;\n    }\n};\n\nint calc_rank(Mat2 a) {\n    int h\
    \ = a.h(), w = a.w();\n    int r = 0;\n    V<int> idxs;\n    for (int x = 0; x\
    \ < w; x++) {\n        int my = -1;\n        for (int y = r; y < h; y++) {\n \
    \           if (a[y][x]) {\n                my = y;\n                break;\n\
    \            }\n        }\n        if (my == -1) continue;\n        if (r != my)\
    \ swap(a[r], a[my]);\n        for (int y = r + 1; y < h; y++) {\n            if\
    \ (!a[y][x]) continue;\n            a[y] ^= a[r];\n        }\n        r++;\n \
    \       idxs.push_back(x);\n        if (r == h) break;\n    }\n    return r;\n\
    }\n\nBitVec solve_linear(Mat2 a, BitVec b) {\n    int h = a.h(), w = a.w();\n\
    \    int r = 0;\n    V<int> idxs;\n    for (int x = 0; x < w; x++) {\n       \
    \ int my = -1;\n        for (int y = r; y < h; y++) {\n            if (a[y][x])\
    \ {\n                my = y;\n                break;\n            }\n        }\n\
    \        if (my == -1) continue;\n        if (r != my) swap(a[r], a[my]);\n  \
    \      b.swap_elms(r, my);\n        for (int y = r + 1; y < h; y++) {\n      \
    \      if (!a[y][x]) continue;\n            a[y] ^= a[r];\n            b.set(y,\
    \ b[y] ^ b[r]);\n        }\n        r++;\n        idxs.push_back(x);\n       \
    \ if (r == h) break;\n    }\n    BitVec v(w);\n    for (int y = r - 1; y >= 0;\
    \ y--) {\n        int f = idxs[y];\n        v.set(f, b[y]);\n        for (int\
    \ x = f + 1; x < w; x++) {\n            v.set(f, v[f] ^ (a[y][x] && v[x]));\n\
    \        }\n    }\n    return v;\n}\n"
  dependsOn:
  - src/datastructure/bitvector.hpp
  - src/bitop.hpp
  isVerificationFile: false
  path: src/math/matrix.hpp
  requiredBy: []
  timestamp: '2020-05-22 19:22:07+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/math/matrix.hpp
layout: document
redirect_from:
- /library/src/math/matrix.hpp
- /library/src/math/matrix.hpp.html
title: src/math/matrix.hpp
---
