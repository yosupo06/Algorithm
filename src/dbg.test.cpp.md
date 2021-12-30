---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/aplusb.hpp
    title: src/aplusb.hpp
  - icon: ':heavy_check_mark:'
    path: src/base.hpp
    title: src/base.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"src/dbg.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\
    \n\n#define LOCAL\n#line 2 \"src/aplusb.hpp\"\n\n#include <iostream>\n\nusing\
    \ namespace std;\n\nvoid solve_aplusb() {\n    int a, b;\n    cin >> a >> b;\n\
    \    cout << a + b << endl;\n}\n#line 2 \"src/base.hpp\"\n#include <algorithm>\n\
    #include <array>\n#include <bitset>\n#include <cassert>\n#include <complex>\n\
    #include <cstdio>\n#include <cstring>\n#line 10 \"src/base.hpp\"\n#include <map>\n\
    #include <numeric>\n#include <queue>\n#include <set>\n#include <string>\n#include\
    \ <unordered_map>\n#include <unordered_set>\n#include <vector>\n\nusing namespace\
    \ std;\n\nusing uint = unsigned int;\nusing ll = long long;\nusing ull = unsigned\
    \ long long;\nconstexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1);\
    \ }\ntemplate <class T> using V = vector<T>;\ntemplate <class T> using VV = V<V<T>>;\n\
    \n#ifdef LOCAL\n\nostream& operator<<(ostream& os, __int128_t x) {\n    if (x\
    \ < 0) {\n        os << \"-\";\n        x *= -1;\n    }\n    if (x == 0) {\n \
    \       return os << \"0\";\n    }\n    string s;\n    while (x) {\n        s\
    \ += char(x % 10 + '0');\n        x /= 10;\n    }\n    reverse(s.begin(), s.end());\n\
    \    return os << s;\n}\nostream& operator<<(ostream& os, __uint128_t x) {\n \
    \   if (x == 0) {\n        return os << \"0\";\n    }\n    string s;\n    while\
    \ (x) {\n        s += char(x % 10 + '0');\n        x /= 10;\n    }\n    reverse(s.begin(),\
    \ s.end());\n    return os << s;\n}\n\ntemplate <class T, class U>\nostream& operator<<(ostream&\
    \ os, const pair<T, U>& p);\ntemplate <class T> ostream& operator<<(ostream& os,\
    \ const V<T>& v);\ntemplate <class T> ostream& operator<<(ostream& os, const deque<T>&\
    \ v);\ntemplate <class T, size_t N>\nostream& operator<<(ostream& os, const array<T,\
    \ N>& a);\ntemplate <class T> ostream& operator<<(ostream& os, const set<T>& s);\n\
    template <class T, class U>\nostream& operator<<(ostream& os, const map<T, U>&\
    \ m);\n\ntemplate <class T, class U>\nostream& operator<<(ostream& os, const pair<T,\
    \ U>& p) {\n    return os << \"P(\" << p.first << \", \" << p.second << \")\"\
    ;\n}\n\ntemplate <class T> ostream& operator<<(ostream& os, const V<T>& v) {\n\
    \    os << \"[\";\n    bool f = false;\n    for (auto d : v) {\n        if (f)\
    \ os << \", \";\n        f = true;\n        os << d;\n    }\n    return os <<\
    \ \"]\";\n}\n\ntemplate <class T> ostream& operator<<(ostream& os, const deque<T>&\
    \ v) {\n    os << \"[\";\n    bool f = false;\n    for (auto d : v) {\n      \
    \  if (f) os << \", \";\n        f = true;\n        os << d;\n    }\n    return\
    \ os << \"]\";\n}\ntemplate <class T, size_t N>\nostream& operator<<(ostream&\
    \ os, const array<T, N>& a) {\n    os << \"[\";\n    bool f = false;\n    for\
    \ (auto d : a) {\n        if (f) os << \", \";\n        f = true;\n        os\
    \ << d;\n    }\n    return os << \"]\";\n}\n\ntemplate <class T> ostream& operator<<(ostream&\
    \ os, const set<T>& s) {\n    os << \"{\";\n    bool f = false;\n    for (auto\
    \ d : s) {\n        if (f) os << \", \";\n        f = true;\n        os << d;\n\
    \    }\n    return os << \"}\";\n}\ntemplate <class T> ostream& operator<<(ostream&\
    \ os, const multiset<T>& s) {\n    os << \"{\";\n    bool f = false;\n    for\
    \ (auto d : s) {\n        if (f) os << \", \";\n        f = true;\n        os\
    \ << d;\n    }\n    return os << \"}\";\n}\n\ntemplate <class T, class U>\nostream&\
    \ operator<<(ostream& os, const map<T, U>& s) {\n    os << \"{\";\n    bool f\
    \ = false;\n    for (auto p : s) {\n        if (f) os << \", \";\n        f =\
    \ true;\n        os << p.first << \": \" << p.second;\n    }\n    return os <<\
    \ \"}\";\n}\n\nstruct PrettyOS {\n    ostream& os;\n    bool first;\n\n    template\
    \ <class T> auto operator<<(T&& x) {\n        if (!first) os << \", \";\n    \
    \    first = false;\n        os << x;\n        return *this;\n    }\n};\ntemplate\
    \ <class... T> void dbg0(T&&... t) {\n    (PrettyOS{cerr, true} << ... << t);\n\
    }\n#define dbg(...)                                            \\\n    do {  \
    \                                                  \\\n        cerr << __LINE__\
    \ << \" : \" << #__VA_ARGS__ << \" = \"; \\\n        dbg0(__VA_ARGS__);      \
    \                            \\\n        cerr << endl;                       \
    \                \\\n    } while (false);\n#else\n#define dbg(...)\n#endif\n#line\
    \ 6 \"src/dbg.test.cpp\"\n\nint main() {\n    pair<int, int> a = {1, 2};\n   \
    \ dbg(a);\n    V<int> b = {1, 2, 3};\n    dbg(b);\n    V<pair<int, int>> c = {{1,\
    \ 2}, {3, 4}};\n    dbg(c);\n    pair<V<int>, V<int>> d = {{1, 2}, {3, 4, 5}};\n\
    \    dbg(d);\n\n    array<int, 3> e = {1, 2, 3};\n    dbg(e);\n    array<V<int>,\
    \ 2> f = {{{1, 2, 3}, {4, 5}}};\n    dbg(f);\n\n    set<int> g = {1, 2, 3, 4};\n\
    \    dbg(g);\n\n    map<int, int> h; h[1] = 2; h[3] = 4;\n    dbg(h);\n\n    solve_aplusb();\n\
    \n    __int128_t x = 1234;\n    dbg(x);\n    __uint128_t y = 5678;\n    dbg(y);\n\
    \    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#define LOCAL\n\
    #include \"aplusb.hpp\"\n#include \"base.hpp\"\n\nint main() {\n    pair<int,\
    \ int> a = {1, 2};\n    dbg(a);\n    V<int> b = {1, 2, 3};\n    dbg(b);\n    V<pair<int,\
    \ int>> c = {{1, 2}, {3, 4}};\n    dbg(c);\n    pair<V<int>, V<int>> d = {{1,\
    \ 2}, {3, 4, 5}};\n    dbg(d);\n\n    array<int, 3> e = {1, 2, 3};\n    dbg(e);\n\
    \    array<V<int>, 2> f = {{{1, 2, 3}, {4, 5}}};\n    dbg(f);\n\n    set<int>\
    \ g = {1, 2, 3, 4};\n    dbg(g);\n\n    map<int, int> h; h[1] = 2; h[3] = 4;\n\
    \    dbg(h);\n\n    solve_aplusb();\n\n    __int128_t x = 1234;\n    dbg(x);\n\
    \    __uint128_t y = 5678;\n    dbg(y);\n    return 0;\n}\n"
  dependsOn:
  - src/aplusb.hpp
  - src/base.hpp
  isVerificationFile: true
  path: src/dbg.test.cpp
  requiredBy: []
  timestamp: '2021-12-30 20:52:19+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: src/dbg.test.cpp
layout: document
redirect_from:
- /verify/src/dbg.test.cpp
- /verify/src/dbg.test.cpp.html
title: src/dbg.test.cpp
---
