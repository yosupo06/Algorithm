---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"src/datastructure/sparsetable.hpp\"\ntemplate <class D,\
    \ class OP> struct SparseTable {\n    D e;\n    OP op;\n    VV<D> data;\n    SparseTable(V<D>\
    \ v = V<D>(), D _e = D(), OP _op = OP()) : e(_e), op(_op) {\n        int n = int(v.size());\n\
    \        if (n == 0) return;\n        int lg = bsr(uint(n)) + 1;\n        data\
    \ = VV<D>(lg);\n        data[0] = v;\n        int l = 1;\n        for (int s =\
    \ 1; s < lg; s++) {\n            data[s] = V<D>(n);\n            for (int i =\
    \ 0; i < n - l; i++) {\n                data[s][i] = op(data[s - 1][i], data[s\
    \ - 1][i + l]);\n            }\n            l <<= 1;\n        }\n    }\n    D\
    \ query(int l, int r) const {\n        assert(l <= r);\n        if (l == r) return\
    \ e;\n        int u = bsr(uint(r - l));\n        return op(data[u][l], data[u][r\
    \ - (1 << u)]);\n    }\n};\ntemplate <class D, class OP>\nSparseTable<D, OP> get_sparse_table(V<D>\
    \ v, D e, OP op) {\n    return SparseTable<D, OP>(v, e, op);\n}\n\ntemplate <class\
    \ D, class OP> struct LowMemorySparseTable {\n    static constexpr int B = 16;\n\
    \    V<D> data;\n    D e;\n    OP op;\n    SparseTable<D, OP> st;\n    V<D> comp_arr(V<D>\
    \ v) {\n        int n = int(v.size());\n        V<D> comp(n / B);\n        for\
    \ (int i = 0; i < n / B; i++) {\n            D res = data[i * B];\n          \
    \  for (int j = 1; j < B; j++) {\n                res = op(res, data[i * B + j]);\n\
    \            }\n            comp[i] = res;\n        }\n        return comp;\n\
    \    }\n    LowMemorySparseTable(V<D> v = V<D>(), D _e = D(), OP _op = OP())\n\
    \        : data(v), e(_e), op(_op), st(comp_arr(v), _e, _op) {}\n    D query(int\
    \ l, int r) const {\n        assert(l <= r);\n        if (l == r) return e;\n\
    \        int lb = (l + B - 1) / B, rb = r / B;\n        D res = e;\n        if\
    \ (lb >= rb) {\n            for (int i = l; i < r; i++) {\n                res\
    \ = op(res, data[i]);\n            }\n            return res;\n        }\n\n \
    \       while (l % B) {\n            res = op(res, data[l]);\n            l++;\n\
    \        }\n        while (r % B) {\n            r--;\n            res = op(res,\
    \ data[r]);\n        }\n        res = op(res, st.query(lb, rb));\n        return\
    \ res;\n    }\n};\ntemplate <class D, class OP>\nLowMemorySparseTable<D, OP> get_low_memory_sparse_table(V<D>\
    \ v, D e, OP op) {\n    return LowMemorySparseTable<D, OP>(v, e, op);\n}\n"
  code: "template <class D, class OP> struct SparseTable {\n    D e;\n    OP op;\n\
    \    VV<D> data;\n    SparseTable(V<D> v = V<D>(), D _e = D(), OP _op = OP())\
    \ : e(_e), op(_op) {\n        int n = int(v.size());\n        if (n == 0) return;\n\
    \        int lg = bsr(uint(n)) + 1;\n        data = VV<D>(lg);\n        data[0]\
    \ = v;\n        int l = 1;\n        for (int s = 1; s < lg; s++) {\n         \
    \   data[s] = V<D>(n);\n            for (int i = 0; i < n - l; i++) {\n      \
    \          data[s][i] = op(data[s - 1][i], data[s - 1][i + l]);\n            }\n\
    \            l <<= 1;\n        }\n    }\n    D query(int l, int r) const {\n \
    \       assert(l <= r);\n        if (l == r) return e;\n        int u = bsr(uint(r\
    \ - l));\n        return op(data[u][l], data[u][r - (1 << u)]);\n    }\n};\ntemplate\
    \ <class D, class OP>\nSparseTable<D, OP> get_sparse_table(V<D> v, D e, OP op)\
    \ {\n    return SparseTable<D, OP>(v, e, op);\n}\n\ntemplate <class D, class OP>\
    \ struct LowMemorySparseTable {\n    static constexpr int B = 16;\n    V<D> data;\n\
    \    D e;\n    OP op;\n    SparseTable<D, OP> st;\n    V<D> comp_arr(V<D> v) {\n\
    \        int n = int(v.size());\n        V<D> comp(n / B);\n        for (int i\
    \ = 0; i < n / B; i++) {\n            D res = data[i * B];\n            for (int\
    \ j = 1; j < B; j++) {\n                res = op(res, data[i * B + j]);\n    \
    \        }\n            comp[i] = res;\n        }\n        return comp;\n    }\n\
    \    LowMemorySparseTable(V<D> v = V<D>(), D _e = D(), OP _op = OP())\n      \
    \  : data(v), e(_e), op(_op), st(comp_arr(v), _e, _op) {}\n    D query(int l,\
    \ int r) const {\n        assert(l <= r);\n        if (l == r) return e;\n   \
    \     int lb = (l + B - 1) / B, rb = r / B;\n        D res = e;\n        if (lb\
    \ >= rb) {\n            for (int i = l; i < r; i++) {\n                res = op(res,\
    \ data[i]);\n            }\n            return res;\n        }\n\n        while\
    \ (l % B) {\n            res = op(res, data[l]);\n            l++;\n        }\n\
    \        while (r % B) {\n            r--;\n            res = op(res, data[r]);\n\
    \        }\n        res = op(res, st.query(lb, rb));\n        return res;\n  \
    \  }\n};\ntemplate <class D, class OP>\nLowMemorySparseTable<D, OP> get_low_memory_sparse_table(V<D>\
    \ v, D e, OP op) {\n    return LowMemorySparseTable<D, OP>(v, e, op);\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: src/datastructure/sparsetable.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/datastructure/sparsetable.hpp
layout: document
redirect_from:
- /library/src/datastructure/sparsetable.hpp
- /library/src/datastructure/sparsetable.hpp.html
title: src/datastructure/sparsetable.hpp
---
