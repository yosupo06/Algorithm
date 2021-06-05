---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"src/datastructure/wavelet.hpp\"\n// wavelet matrix\nstruct\
    \ Wavelet {\n    // space: 32N bits\n    struct BitVector {\n        V<int> _rank\
    \ = {0};\n        BitVector(V<char> v = V<char>()) {\n            _rank.reserve(v.size()\
    \ + 1);\n            for (int d : v) _rank.push_back(_rank.back() + d);\n    \
    \    }\n        int rank(bool f, int k) { return f ? _rank[k] : (k - _rank[k]);\
    \ }\n        int rank(bool f, int l, int r) { return rank(f, r) - rank(f, l);\
    \ }\n    };\n    // space: 1.5N bits\n    /*struct BitVector {\n        V<ull>\
    \ v;\n        V<int> _rank;\n        BitVector(V<char> _v = V<char>()) {\n   \
    \         int n = int(_v.size());\n            v = V<ull>((n + 63) / 64);\n  \
    \          _rank = V<int>(v.size() + 1);\n            for (int i = 0; i < n; i++)\
    \ {\n                if (_v[i]) {\n                    v[i / 64] |= 1ULL << (i\
    \ % 64);\n                    _rank[i / 64 + 1]++;\n                }\n      \
    \      }\n            for (int i = 0; i < int(v.size()); i++) {\n            \
    \    _rank[i+1] += _rank[i];\n            }\n        }\n        int rank(int k)\
    \ {\n            int a = _rank[k / 64];\n            if (k % 64) a += __builtin_popcountll(v[k\
    \ / 64] << (64 - k % 64));\n            return a;\n        }\n        int rank(bool\
    \ f, int k) { return f ? rank(k) : k - rank(k); }\n        int rank(bool f, int\
    \ l, int r) { return rank(f, r) - rank(f, l); }\n    };*/\n\n    int n, lg = 1;\n\
    \    V<int> mid;\n    V<BitVector> data;\n    Wavelet(V<int> v = V<int>()) : n(int(v.size()))\
    \ {\n        int ma = 0;\n        for (int x : v) ma = max(ma, x);\n        while\
    \ ((1 << lg) <= ma) lg++;\n        mid = V<int>(lg);\n        data = V<BitVector>(lg);\n\
    \        for (int lv = lg - 1; lv >= 0; lv--) {\n            V<char> buf;\n  \
    \          VV<int> nx(2);\n            for (int d : v) {\n                bool\
    \ f = (d & (1 << lv)) > 0;\n                buf.push_back(f);\n              \
    \  nx[f].push_back(d);\n            }\n            mid[lv] = int(nx[0].size());\n\
    \            data[lv] = BitVector(buf);\n            v.clear();\n            v.insert(v.end(),\
    \ nx[0].begin(), nx[0].end());\n            v.insert(v.end(), nx[1].begin(), nx[1].end());\n\
    \        }\n    }\n    pair<int, int> succ(bool f, int a, int b, int lv) {\n \
    \       int na = data[lv].rank(f, a) + (f ? mid[lv] : 0);\n        int nb = data[lv].rank(f,\
    \ b) + (f ? mid[lv] : 0);\n        return make_pair(na, nb);\n    }\n    // count\
    \ i, s.t. (a <= i < b) && (v[i] < u)\n    int rank(int a, int b, int u) {\n  \
    \      if ((1 << lg) <= u) return b - a;\n        int ans = 0;\n        for (int\
    \ lv = lg - 1; lv >= 0; lv--) {\n            bool f = (u & (1 << lv)) > 0;\n \
    \           if (f) ans += data[lv].rank(false, a, b);\n            tie(a, b) =\
    \ succ(f, a, b, lv);\n        }\n        return ans;\n    }\n    // k-th(0-indexed!)\
    \ number in v[a..b]\n    int select(int a, int b, int k) {\n        int u = 0;\n\
    \        for (int lv = lg - 1; lv >= 0; lv--) {\n            int le = data[lv].rank(false,\
    \ a, b);\n            bool f = (le <= k);\n            if (f) {\n            \
    \    u += (1 << lv);\n                k -= le;\n            }\n            tie(a,\
    \ b) = succ(f, a, b, lv);\n        }\n        return u;\n    }\n};\n\nstruct CompressWavelet\
    \ {\n    Wavelet wt;\n    V<int> v, vidx;\n    int zip(int x) {\n        return\
    \ int(lower_bound(vidx.begin(), vidx.end(), x) - vidx.begin());\n    }\n    CompressWavelet(V<int>\
    \ _v = V<int>()) : v(_v), vidx(v) {\n        sort(vidx.begin(), vidx.end());\n\
    \        vidx.erase(unique(vidx.begin(), vidx.end()), vidx.end());\n        for\
    \ (auto& d : v) d = zip(d);\n        wt = Wavelet(v);\n    }\n    int rank(int\
    \ a, int b, int u) { return wt.rank(a, b, zip(u)); }\n    int select(int a, int\
    \ b, int k) { return vidx[wt.select(a, b, k)]; }\n};\n"
  code: "// wavelet matrix\nstruct Wavelet {\n    // space: 32N bits\n    struct BitVector\
    \ {\n        V<int> _rank = {0};\n        BitVector(V<char> v = V<char>()) {\n\
    \            _rank.reserve(v.size() + 1);\n            for (int d : v) _rank.push_back(_rank.back()\
    \ + d);\n        }\n        int rank(bool f, int k) { return f ? _rank[k] : (k\
    \ - _rank[k]); }\n        int rank(bool f, int l, int r) { return rank(f, r) -\
    \ rank(f, l); }\n    };\n    // space: 1.5N bits\n    /*struct BitVector {\n \
    \       V<ull> v;\n        V<int> _rank;\n        BitVector(V<char> _v = V<char>())\
    \ {\n            int n = int(_v.size());\n            v = V<ull>((n + 63) / 64);\n\
    \            _rank = V<int>(v.size() + 1);\n            for (int i = 0; i < n;\
    \ i++) {\n                if (_v[i]) {\n                    v[i / 64] |= 1ULL\
    \ << (i % 64);\n                    _rank[i / 64 + 1]++;\n                }\n\
    \            }\n            for (int i = 0; i < int(v.size()); i++) {\n      \
    \          _rank[i+1] += _rank[i];\n            }\n        }\n        int rank(int\
    \ k) {\n            int a = _rank[k / 64];\n            if (k % 64) a += __builtin_popcountll(v[k\
    \ / 64] << (64 - k % 64));\n            return a;\n        }\n        int rank(bool\
    \ f, int k) { return f ? rank(k) : k - rank(k); }\n        int rank(bool f, int\
    \ l, int r) { return rank(f, r) - rank(f, l); }\n    };*/\n\n    int n, lg = 1;\n\
    \    V<int> mid;\n    V<BitVector> data;\n    Wavelet(V<int> v = V<int>()) : n(int(v.size()))\
    \ {\n        int ma = 0;\n        for (int x : v) ma = max(ma, x);\n        while\
    \ ((1 << lg) <= ma) lg++;\n        mid = V<int>(lg);\n        data = V<BitVector>(lg);\n\
    \        for (int lv = lg - 1; lv >= 0; lv--) {\n            V<char> buf;\n  \
    \          VV<int> nx(2);\n            for (int d : v) {\n                bool\
    \ f = (d & (1 << lv)) > 0;\n                buf.push_back(f);\n              \
    \  nx[f].push_back(d);\n            }\n            mid[lv] = int(nx[0].size());\n\
    \            data[lv] = BitVector(buf);\n            v.clear();\n            v.insert(v.end(),\
    \ nx[0].begin(), nx[0].end());\n            v.insert(v.end(), nx[1].begin(), nx[1].end());\n\
    \        }\n    }\n    pair<int, int> succ(bool f, int a, int b, int lv) {\n \
    \       int na = data[lv].rank(f, a) + (f ? mid[lv] : 0);\n        int nb = data[lv].rank(f,\
    \ b) + (f ? mid[lv] : 0);\n        return make_pair(na, nb);\n    }\n    // count\
    \ i, s.t. (a <= i < b) && (v[i] < u)\n    int rank(int a, int b, int u) {\n  \
    \      if ((1 << lg) <= u) return b - a;\n        int ans = 0;\n        for (int\
    \ lv = lg - 1; lv >= 0; lv--) {\n            bool f = (u & (1 << lv)) > 0;\n \
    \           if (f) ans += data[lv].rank(false, a, b);\n            tie(a, b) =\
    \ succ(f, a, b, lv);\n        }\n        return ans;\n    }\n    // k-th(0-indexed!)\
    \ number in v[a..b]\n    int select(int a, int b, int k) {\n        int u = 0;\n\
    \        for (int lv = lg - 1; lv >= 0; lv--) {\n            int le = data[lv].rank(false,\
    \ a, b);\n            bool f = (le <= k);\n            if (f) {\n            \
    \    u += (1 << lv);\n                k -= le;\n            }\n            tie(a,\
    \ b) = succ(f, a, b, lv);\n        }\n        return u;\n    }\n};\n\nstruct CompressWavelet\
    \ {\n    Wavelet wt;\n    V<int> v, vidx;\n    int zip(int x) {\n        return\
    \ int(lower_bound(vidx.begin(), vidx.end(), x) - vidx.begin());\n    }\n    CompressWavelet(V<int>\
    \ _v = V<int>()) : v(_v), vidx(v) {\n        sort(vidx.begin(), vidx.end());\n\
    \        vidx.erase(unique(vidx.begin(), vidx.end()), vidx.end());\n        for\
    \ (auto& d : v) d = zip(d);\n        wt = Wavelet(v);\n    }\n    int rank(int\
    \ a, int b, int u) { return wt.rank(a, b, zip(u)); }\n    int select(int a, int\
    \ b, int k) { return vidx[wt.select(a, b, k)]; }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: src/datastructure/wavelet.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/datastructure/wavelet.hpp
layout: document
redirect_from:
- /library/src/datastructure/wavelet.hpp
- /library/src/datastructure/wavelet.hpp.html
title: src/datastructure/wavelet.hpp
---
