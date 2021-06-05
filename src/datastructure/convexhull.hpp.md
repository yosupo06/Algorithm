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
  bundledCode: "#line 1 \"src/datastructure/convexhull.hpp\"\ntemplate<class T>\n\
    struct ConvexHull {\n    using L = array<T, 2>;\n\n    bool que_incr;\n    ConvexHull(bool\
    \ _que_incr) : que_incr(_que_incr) {}\n\n    deque<L> lines;\n    // can remove\
    \ mid?\n    static bool is_need(L mid, L left, L right) {\n        assert(left[0]\
    \ <= mid[0] && mid[0] <= right[0]);\n        return (right[0]-mid[0])*(left[1]-mid[1])\
    \ < (mid[0]-left[0])*(mid[1]-right[1]);\n    }\n    //work with 2^(60 + 64)\n\
    \    /*static bool is_need(L mid, L left, L right) {\n        assert(left[0] <=\
    \ mid[0] && mid[0] <= right[0]);\n        ll a = (right[0]-mid[0]), b = (left[1]-mid[1]),\
    \ c = (mid[0]-left[0]), d = (mid[1]-right[1]);\n        long double x = (long\
    \ double)(a) * b - (long double)(c) * d;\n        if (abs(x) > (1LL << 60)) return\
    \ x < 0;\n        int fl = b < 0, fr = d < 0;\n        if (fl != fr) return fl\
    \ == 1;\n        ull z = ull(a) * ull(abs(b)) - ull(c) * ull(abs(d));\n      \
    \  if (fl == 0) return (1ULL << 63) < z;\n        return z < (1ULL << 63);\n \
    \   }*/\n\n    void insert_front(L l) {\n        if (lines.empty()) {\n      \
    \      lines.push_front(l);\n            return;\n        }\n        assert(l[0]\
    \ <= lines[0][0]);\n        if (l[0] == lines[0][0]) {\n            if (l[1] <=\
    \ lines[0][1]) return;\n            lines.pop_front();\n        }\n        while\
    \ (lines.size() >= 2 && !is_need(lines.front(), l, lines[1])) {\n            lines.pop_front();\n\
    \        }\n        lines.push_front(l);\n    }\n    void insert_back(L l) {\n\
    \        if (lines.empty()) {\n            lines.push_back(l);\n            return;\n\
    \        }\n        assert(lines.back()[0] <= l[0]);\n        if (lines.back()[0]\
    \ == l[0]) {\n            if (l[1] <= lines.back()[1]) return;\n            lines.pop_back();\n\
    \        }\n        while (lines.size() >= 2 && !is_need(lines.back(), lines[lines.size()-2],\
    \ l)) {\n            lines.pop_back();\n        }\n        lines.push_back(l);\n\
    \    }\n    /**\n    Insert line\n    line's degree must be minimum or maximum\n\
    \     */\n    void insert_line(L line) {\n        if (lines.empty()) {\n     \
    \       lines.push_back(line);\n            return;\n        }\n        if (line[0]\
    \ <= lines[0][0]) insert_front(line);\n        else if (lines.back()[0] <= line[0])\
    \ insert_back(line);\n        else assert(false); //line's degree must be minimum\
    \ or maximum\n    }\n    /// get maximum y\n    T b_x;\n    T first = true;\n\
    \    T max_y(T x) {\n        assert(lines.size());\n        auto value = [&](L\
    \ l) { return l[0] * x + l[1]; };\n        if (que_incr) {\n            assert(first\
    \ || b_x <= x);\n            first = false; b_x = x;\n            while (lines.size()\
    \ >= 2 &&\n                   value(lines[0]) <= value(lines[1])) {\n        \
    \        lines.pop_front();\n            }\n            return value(lines.front());\n\
    \        } else {\n            assert(first || x <= b_x);\n            first =\
    \ false; b_x = x;\n            while (lines.size() >= 2 &&\n                 \
    \  value(lines[lines.size()-2]) >= value(lines.back())) {\n                lines.pop_back();\n\
    \            }\n            return value(lines.back());\n        }\n    }\n};\n"
  code: "template<class T>\nstruct ConvexHull {\n    using L = array<T, 2>;\n\n  \
    \  bool que_incr;\n    ConvexHull(bool _que_incr) : que_incr(_que_incr) {}\n\n\
    \    deque<L> lines;\n    // can remove mid?\n    static bool is_need(L mid, L\
    \ left, L right) {\n        assert(left[0] <= mid[0] && mid[0] <= right[0]);\n\
    \        return (right[0]-mid[0])*(left[1]-mid[1]) < (mid[0]-left[0])*(mid[1]-right[1]);\n\
    \    }\n    //work with 2^(60 + 64)\n    /*static bool is_need(L mid, L left,\
    \ L right) {\n        assert(left[0] <= mid[0] && mid[0] <= right[0]);\n     \
    \   ll a = (right[0]-mid[0]), b = (left[1]-mid[1]), c = (mid[0]-left[0]), d =\
    \ (mid[1]-right[1]);\n        long double x = (long double)(a) * b - (long double)(c)\
    \ * d;\n        if (abs(x) > (1LL << 60)) return x < 0;\n        int fl = b <\
    \ 0, fr = d < 0;\n        if (fl != fr) return fl == 1;\n        ull z = ull(a)\
    \ * ull(abs(b)) - ull(c) * ull(abs(d));\n        if (fl == 0) return (1ULL <<\
    \ 63) < z;\n        return z < (1ULL << 63);\n    }*/\n\n    void insert_front(L\
    \ l) {\n        if (lines.empty()) {\n            lines.push_front(l);\n     \
    \       return;\n        }\n        assert(l[0] <= lines[0][0]);\n        if (l[0]\
    \ == lines[0][0]) {\n            if (l[1] <= lines[0][1]) return;\n          \
    \  lines.pop_front();\n        }\n        while (lines.size() >= 2 && !is_need(lines.front(),\
    \ l, lines[1])) {\n            lines.pop_front();\n        }\n        lines.push_front(l);\n\
    \    }\n    void insert_back(L l) {\n        if (lines.empty()) {\n          \
    \  lines.push_back(l);\n            return;\n        }\n        assert(lines.back()[0]\
    \ <= l[0]);\n        if (lines.back()[0] == l[0]) {\n            if (l[1] <= lines.back()[1])\
    \ return;\n            lines.pop_back();\n        }\n        while (lines.size()\
    \ >= 2 && !is_need(lines.back(), lines[lines.size()-2], l)) {\n            lines.pop_back();\n\
    \        }\n        lines.push_back(l);\n    }\n    /**\n    Insert line\n   \
    \ line's degree must be minimum or maximum\n     */\n    void insert_line(L line)\
    \ {\n        if (lines.empty()) {\n            lines.push_back(line);\n      \
    \      return;\n        }\n        if (line[0] <= lines[0][0]) insert_front(line);\n\
    \        else if (lines.back()[0] <= line[0]) insert_back(line);\n        else\
    \ assert(false); //line's degree must be minimum or maximum\n    }\n    /// get\
    \ maximum y\n    T b_x;\n    T first = true;\n    T max_y(T x) {\n        assert(lines.size());\n\
    \        auto value = [&](L l) { return l[0] * x + l[1]; };\n        if (que_incr)\
    \ {\n            assert(first || b_x <= x);\n            first = false; b_x =\
    \ x;\n            while (lines.size() >= 2 &&\n                   value(lines[0])\
    \ <= value(lines[1])) {\n                lines.pop_front();\n            }\n \
    \           return value(lines.front());\n        } else {\n            assert(first\
    \ || x <= b_x);\n            first = false; b_x = x;\n            while (lines.size()\
    \ >= 2 &&\n                   value(lines[lines.size()-2]) >= value(lines.back()))\
    \ {\n                lines.pop_back();\n            }\n            return value(lines.back());\n\
    \        }\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: src/datastructure/convexhull.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/datastructure/convexhull.hpp
layout: document
redirect_from:
- /library/src/datastructure/convexhull.hpp
- /library/src/datastructure/convexhull.hpp.html
title: src/datastructure/convexhull.hpp
---
