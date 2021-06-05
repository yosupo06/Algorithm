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
  bundledCode: "#line 1 \"src/string/mp.hpp\"\ntemplate <class S> V<int> mp(const\
    \ S& s) {\n    int n = int(s.size());\n    V<int> r(n + 1);\n    r[0] = -1;\n\
    \    for (int i = 0, j = -1; i < n; i++) {\n        while (j >= 0 && s[i] != s[j])\
    \ j = r[j];\n        j++;\n        r[i + 1] = j;\n    }\n    return r;\n}\n"
  code: "template <class S> V<int> mp(const S& s) {\n    int n = int(s.size());\n\
    \    V<int> r(n + 1);\n    r[0] = -1;\n    for (int i = 0, j = -1; i < n; i++)\
    \ {\n        while (j >= 0 && s[i] != s[j]) j = r[j];\n        j++;\n        r[i\
    \ + 1] = j;\n    }\n    return r;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: src/string/mp.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/string/mp.hpp
layout: document
redirect_from:
- /library/src/string/mp.hpp
- /library/src/string/mp.hpp.html
title: src/string/mp.hpp
---
