---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"src/datastructure/Develop/FenwickTree2D.hpp\"\n/**\n * Fenwick\
    \ Tree 2D\n */\ntemplate <int N>\nstruct FenwickTree2D {\n    using D = ll;\n\
    \    FenwickTree<N> seg[N+1];\n    \n    void init() {\n        for (int i = 0;\
    \ i <= N; i++) {\n            seg[i].init();\n        }\n    }\n\n    /// \u8981\
    \u7D20(x, y)\u306Bd\u3092\u52A0\u7B97\u3059\u308B\n    void add(int x, int y,\
    \ D d) {\n        x++;\n        while (x <= N) {\n            seg[x].add(y, d);\n\
    \            x += x & -x;\n        }\n    }\n\n    /// x\u5EA7\u6A19\u304C[0,\
    \ x) y\u5EA7\u6A19\u304C[0, y)\u306E\u9577\u65B9\u5F62\u533A\u9593\u306Esum\n\
    \    D sum(int x, int y) {\n        D s = 0;\n        while (x > 0) {\n      \
    \      s += seg[x].sum(y);\n            x -= x & -x;\n        }\n        return\
    \ s;\n    }\n\n    /// x\u5EA7\u6A19\u304C[lx, hx) y\u5EA7\u6A19\u304C[ly, hy)\u306E\
    \u9577\u65B9\u5F62\u533A\u9593\u306Esum\n    D sum(int lx, int ly, int hx, int\
    \ hy) {\n        return (sum(hx, hy) + sum(lx, ly))\n             - (sum(lx, hy)\
    \ + sum(hx, ly));\n    }\n};\n"
  code: "/**\n * Fenwick Tree 2D\n */\ntemplate <int N>\nstruct FenwickTree2D {\n\
    \    using D = ll;\n    FenwickTree<N> seg[N+1];\n    \n    void init() {\n  \
    \      for (int i = 0; i <= N; i++) {\n            seg[i].init();\n        }\n\
    \    }\n\n    /// \u8981\u7D20(x, y)\u306Bd\u3092\u52A0\u7B97\u3059\u308B\n  \
    \  void add(int x, int y, D d) {\n        x++;\n        while (x <= N) {\n   \
    \         seg[x].add(y, d);\n            x += x & -x;\n        }\n    }\n\n  \
    \  /// x\u5EA7\u6A19\u304C[0, x) y\u5EA7\u6A19\u304C[0, y)\u306E\u9577\u65B9\u5F62\
    \u533A\u9593\u306Esum\n    D sum(int x, int y) {\n        D s = 0;\n        while\
    \ (x > 0) {\n            s += seg[x].sum(y);\n            x -= x & -x;\n     \
    \   }\n        return s;\n    }\n\n    /// x\u5EA7\u6A19\u304C[lx, hx) y\u5EA7\
    \u6A19\u304C[ly, hy)\u306E\u9577\u65B9\u5F62\u533A\u9593\u306Esum\n    D sum(int\
    \ lx, int ly, int hx, int hy) {\n        return (sum(hx, hy) + sum(lx, ly))\n\
    \             - (sum(lx, hy) + sum(hx, ly));\n    }\n};"
  dependsOn: []
  isVerificationFile: false
  path: src/datastructure/Develop/FenwickTree2D.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/datastructure/Develop/FenwickTree2D.hpp
layout: document
redirect_from:
- /library/src/datastructure/Develop/FenwickTree2D.hpp
- /library/src/datastructure/Develop/FenwickTree2D.hpp.html
title: src/datastructure/Develop/FenwickTree2D.hpp
---
