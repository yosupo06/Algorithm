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
  bundledCode: "#line 1 \"src/string/manacher.hpp\"\ntemplate <class S> V<int> manacher(const\
    \ S& s) {\n    int n = int(s.size());\n    V<int> r(n);\n    if (n == 0) return\
    \ r;\n    r[0] = 1;\n    for (int i = 1, j = 0; i < n; i++) {\n        int& k\
    \ = r[i];\n        k = (j + r[j] <= i) ? 0 : min(j + r[j] - i, r[2 * j - i]);\n\
    \        while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) k++;\n      \
    \  if (j + r[j] < i + r[i]) j = i;\n    }\n    return r;\n}\n\n\ntemplate <class\
    \ S> V<int> manacher_even(const S& s) {\n    int n = int(s.size());\n    V<int>\
    \ r(n + 1);\n    for (int i = 1, j = 0; i < n; i++) {\n        int& k = r[i];\n\
    \        k = (j + r[j] <= i) ? 0 : min(j + r[j] - i, r[2 * j - i]);\n        while\
    \ (0 <= i - 1 - k && i + k < n && s[i - 1 - k] == s[i + k]) k++;\n        if (j\
    \ + r[j] < i + r[i]) j = i;\n    }\n    return r;\n}\n"
  code: "template <class S> V<int> manacher(const S& s) {\n    int n = int(s.size());\n\
    \    V<int> r(n);\n    if (n == 0) return r;\n    r[0] = 1;\n    for (int i =\
    \ 1, j = 0; i < n; i++) {\n        int& k = r[i];\n        k = (j + r[j] <= i)\
    \ ? 0 : min(j + r[j] - i, r[2 * j - i]);\n        while (0 <= i - k && i + k <\
    \ n && s[i - k] == s[i + k]) k++;\n        if (j + r[j] < i + r[i]) j = i;\n \
    \   }\n    return r;\n}\n\n\ntemplate <class S> V<int> manacher_even(const S&\
    \ s) {\n    int n = int(s.size());\n    V<int> r(n + 1);\n    for (int i = 1,\
    \ j = 0; i < n; i++) {\n        int& k = r[i];\n        k = (j + r[j] <= i) ?\
    \ 0 : min(j + r[j] - i, r[2 * j - i]);\n        while (0 <= i - 1 - k && i + k\
    \ < n && s[i - 1 - k] == s[i + k]) k++;\n        if (j + r[j] < i + r[i]) j =\
    \ i;\n    }\n    return r;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: src/string/manacher.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/string/manacher.hpp
layout: document
redirect_from:
- /library/src/string/manacher.hpp
- /library/src/string/manacher.hpp.html
title: src/string/manacher.hpp
---
