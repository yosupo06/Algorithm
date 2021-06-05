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
  bundledCode: "#line 1 \"src/datastructure/radixheap.hpp\"\n// D.key must be unsigned\
    \ integer\ntemplate <class D> struct RadixHeap {\n    using C = typename make_unsigned<decltype(D().key)>::type;\n\
    \    static int bsr1(C x) { return (x == 0) ? 0 : bsr(x) + 1; }\n    size_t sz\
    \ = 0, cnt = 0;\n    C last = 0;\n    VV<D> v = VV<D>(sizeof(C) * 8 + 1);\n  \
    \  RadixHeap() {}\n    void push(D x) {\n        assert(decltype(x.key)(last)\
    \ <= x.key);\n        sz++;\n        v[bsr1(x.key ^ last)].push_back(x);\n   \
    \ }\n    void pull() {\n        if (cnt < v[0].size()) return;\n        int i\
    \ = 1;\n        while (v[i].empty()) i++;\n        last = min_element(v[i].begin(),\
    \ v[i].end(), [&](D l, D r) {\n                   return l.key < r.key;\n    \
    \           })->key;\n        for (D x : v[i]) {\n            v[bsr1(x.key ^ last)].push_back(x);\n\
    \        }\n        v[i].clear();\n    }\n    D top() {\n        pull();\n   \
    \     return v[0][cnt];\n    }\n    void pop() {\n        pull();\n        sz--;\n\
    \        cnt++;\n    }\n    size_t size() const { return sz; }\n    bool empty()\
    \ const { return sz == 0; }\n};\n"
  code: "// D.key must be unsigned integer\ntemplate <class D> struct RadixHeap {\n\
    \    using C = typename make_unsigned<decltype(D().key)>::type;\n    static int\
    \ bsr1(C x) { return (x == 0) ? 0 : bsr(x) + 1; }\n    size_t sz = 0, cnt = 0;\n\
    \    C last = 0;\n    VV<D> v = VV<D>(sizeof(C) * 8 + 1);\n    RadixHeap() {}\n\
    \    void push(D x) {\n        assert(decltype(x.key)(last) <= x.key);\n     \
    \   sz++;\n        v[bsr1(x.key ^ last)].push_back(x);\n    }\n    void pull()\
    \ {\n        if (cnt < v[0].size()) return;\n        int i = 1;\n        while\
    \ (v[i].empty()) i++;\n        last = min_element(v[i].begin(), v[i].end(), [&](D\
    \ l, D r) {\n                   return l.key < r.key;\n               })->key;\n\
    \        for (D x : v[i]) {\n            v[bsr1(x.key ^ last)].push_back(x);\n\
    \        }\n        v[i].clear();\n    }\n    D top() {\n        pull();\n   \
    \     return v[0][cnt];\n    }\n    void pop() {\n        pull();\n        sz--;\n\
    \        cnt++;\n    }\n    size_t size() const { return sz; }\n    bool empty()\
    \ const { return sz == 0; }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: src/datastructure/radixheap.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/datastructure/radixheap.hpp
layout: document
redirect_from:
- /library/src/datastructure/radixheap.hpp
- /library/src/datastructure/radixheap.hpp.html
title: src/datastructure/radixheap.hpp
---
