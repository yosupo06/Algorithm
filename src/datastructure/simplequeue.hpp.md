---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: src/graph/balancedseparator.hpp
    title: src/graph/balancedseparator.hpp
  - icon: ':heavy_check_mark:'
    path: src/graph/bimaching.hpp
    title: src/graph/bimaching.hpp
  - icon: ':heavy_check_mark:'
    path: src/graph/treedecomp.hpp
    title: src/graph/treedecomp.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: src/bimaching.test.cpp
    title: src/bimaching.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/treedecomp_width2.test.cpp
    title: src/treedecomp_width2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"src/datastructure/simplequeue.hpp\"\n\ntemplate <class T>\
    \ struct SimpleQueue {\n    V<T> payload;\n    size_t pos = 0;\n    void reserve(size_t\
    \ size) { payload.reserve(size); }\n    size_t size() const { return payload.size()\
    \ - pos; }\n    bool empty() const { return pos == payload.size(); }\n    void\
    \ push(const T& t) { payload.push_back(t); }\n    T& front() {\n        assert(!empty());\n\
    \        return payload[pos];\n    }\n    void clear() {\n        payload.clear();\n\
    \        pos = 0;\n    }\n    void pop() {\n        assert(!empty());\n      \
    \  pos++;\n    }\n};\n"
  code: "#pragma once\n\ntemplate <class T> struct SimpleQueue {\n    V<T> payload;\n\
    \    size_t pos = 0;\n    void reserve(size_t size) { payload.reserve(size); }\n\
    \    size_t size() const { return payload.size() - pos; }\n    bool empty() const\
    \ { return pos == payload.size(); }\n    void push(const T& t) { payload.push_back(t);\
    \ }\n    T& front() {\n        assert(!empty());\n        return payload[pos];\n\
    \    }\n    void clear() {\n        payload.clear();\n        pos = 0;\n    }\n\
    \    void pop() {\n        assert(!empty());\n        pos++;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: src/datastructure/simplequeue.hpp
  requiredBy:
  - src/graph/treedecomp.hpp
  - src/graph/balancedseparator.hpp
  - src/graph/bimaching.hpp
  timestamp: '2020-07-12 20:41:58+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - src/treedecomp_width2.test.cpp
  - src/bimaching.test.cpp
documentation_of: src/datastructure/simplequeue.hpp
layout: document
redirect_from:
- /library/src/datastructure/simplequeue.hpp
- /library/src/datastructure/simplequeue.hpp.html
title: src/datastructure/simplequeue.hpp
---
