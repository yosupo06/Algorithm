---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: src/string/run.hpp
    title: src/string/run.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: src/run.test.cpp
    title: src/run.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/zalgo.test.cpp
    title: src/zalgo.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"src/string/zalgo.hpp\"\n\n// s[0..r[i]] == s[i..i+r[i]]\n\
    template <class S> V<int> z_algo(const S& s) {\n    int n = int(s.size());\n \
    \   V<int> r(n + 1);\n    r[0] = 0;\n    for (int i = 1, j = 0; i <= n; i++) {\n\
    \        int& k = r[i];\n        k = (j + r[j] <= i) ? 0 : min(j + r[j] - i, r[i\
    \ - j]);\n        while (i + k < n && s[k] == s[i + k]) k++;\n        if (j +\
    \ r[j] < i + r[i]) j = i;\n    }\n    r[0] = n;\n    return r;\n}\n"
  code: "#pragma once\n\n// s[0..r[i]] == s[i..i+r[i]]\ntemplate <class S> V<int>\
    \ z_algo(const S& s) {\n    int n = int(s.size());\n    V<int> r(n + 1);\n   \
    \ r[0] = 0;\n    for (int i = 1, j = 0; i <= n; i++) {\n        int& k = r[i];\n\
    \        k = (j + r[j] <= i) ? 0 : min(j + r[j] - i, r[i - j]);\n        while\
    \ (i + k < n && s[k] == s[i + k]) k++;\n        if (j + r[j] < i + r[i]) j = i;\n\
    \    }\n    r[0] = n;\n    return r;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: src/string/zalgo.hpp
  requiredBy:
  - src/string/run.hpp
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - src/zalgo.test.cpp
  - src/run.test.cpp
documentation_of: src/string/zalgo.hpp
layout: document
redirect_from:
- /library/src/string/zalgo.hpp
- /library/src/string/zalgo.hpp.html
title: src/string/zalgo.hpp
---
