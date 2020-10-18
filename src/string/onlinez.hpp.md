---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: src/online-zalgo.test.cpp
    title: src/online-zalgo.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"src/string/onlinez.hpp\"\n\nstruct OnlineZ {\n    string\
    \ s;\n    V<int> mp = {-1}, nx;\n    int j = -1;\n    V<int> inc(char c) {\n \
    \       // calc nx\n        s.push_back(c);\n        if (mp.back() == -1)\n  \
    \          nx.push_back(-1);\n        else\n            nx.push_back(s[mp.back()]\
    \ != c ? mp.back() : nx[mp.back()]);\n        // calc mp\n        int i = int(s.size())\
    \ - 1;\n        while (j >= 0 && s[i] != s[j]) j = mp[j];\n        j++;\n    \
    \    mp.push_back(j);\n\n        V<int> res;\n        int u = nx.back();\n   \
    \     while (u != -1) {\n            if (s[u] != c) {\n                res.push_back(int(s.size())\
    \ - 1 - u);\n                u = mp[u];\n            } else {\n              \
    \  u = nx[u];\n            }\n        }\n        return res;\n    }\n};\n"
  code: "#pragma once\n\nstruct OnlineZ {\n    string s;\n    V<int> mp = {-1}, nx;\n\
    \    int j = -1;\n    V<int> inc(char c) {\n        // calc nx\n        s.push_back(c);\n\
    \        if (mp.back() == -1)\n            nx.push_back(-1);\n        else\n \
    \           nx.push_back(s[mp.back()] != c ? mp.back() : nx[mp.back()]);\n   \
    \     // calc mp\n        int i = int(s.size()) - 1;\n        while (j >= 0 &&\
    \ s[i] != s[j]) j = mp[j];\n        j++;\n        mp.push_back(j);\n\n       \
    \ V<int> res;\n        int u = nx.back();\n        while (u != -1) {\n       \
    \     if (s[u] != c) {\n                res.push_back(int(s.size()) - 1 - u);\n\
    \                u = mp[u];\n            } else {\n                u = nx[u];\n\
    \            }\n        }\n        return res;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: src/string/onlinez.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - src/online-zalgo.test.cpp
documentation_of: src/string/onlinez.hpp
layout: document
redirect_from:
- /library/src/string/onlinez.hpp
- /library/src/string/onlinez.hpp.html
title: src/string/onlinez.hpp
---
