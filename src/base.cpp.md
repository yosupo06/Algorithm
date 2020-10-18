---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"src/base.cpp\"\n//#pragma GCC optimize(\"Ofast\")\n//#pragma\
    \ GCC target(\"avx\")\n//#undef LOCAL\n\n#include <yosupo/fastio.hpp>\nusing namespace\
    \ yosupo;\n\n#line 2 \"src/base.hpp\"\n#include <algorithm>\n#include <array>\n\
    #include <bitset>\n#include <cassert>\n#include <complex>\n#include <cstdio>\n\
    #include <cstring>\n#include <iostream>\n#include <map>\n#include <numeric>\n\
    #include <queue>\n#include <set>\n#include <string>\n#include <unordered_map>\n\
    #include <unordered_set>\n#include <vector>\n\nusing namespace std;\n\nusing uint\
    \ = unsigned int;\nusing ll = long long;\nusing ull = unsigned long long;\nconstexpr\
    \ ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }\ntemplate <class T>\
    \ using V = vector<T>;\ntemplate <class T> using VV = V<V<T>>;\n\n#ifdef LOCAL\n\
    \nostream& operator<<(ostream& os, __int128_t x) {\n    if (x < 0) {\n       \
    \ os << \"-\";\n        x *= -1;\n    }\n    if (x == 0) {\n        return os\
    \ << \"0\";\n    }\n    string s;\n    while (x) {\n        s += char(x % 10 +\
    \ '0');\n        x /= 10;\n    }\n    reverse(s.begin(), s.end());\n    return\
    \ os << s;\n}\nostream& operator<<(ostream& os, __uint128_t x) {\n    if (x ==\
    \ 0) {\n        return os << \"0\";\n    }\n    string s;\n    while (x) {\n \
    \       s += char(x % 10 + '0');\n        x /= 10;\n    }\n    reverse(s.begin(),\
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
    \    }\n    return os << \"}\";\n}\n\ntemplate <class T, class U>\nostream& operator<<(ostream&\
    \ os, const map<T, U>& s) {\n    os << \"{\";\n    bool f = false;\n    for (auto\
    \ p : s) {\n        if (f) os << \", \";\n        f = true;\n        os << p.first\
    \ << \": \" << p.second;\n    }\n    return os << \"}\";\n}\n\nstruct PrettyOS\
    \ {\n    ostream& os;\n    bool first;\n\n    template <class T> auto operator<<(T&&\
    \ x) {\n        if (!first) os << \", \";\n        first = false;\n        os\
    \ << x;\n        return *this;\n    }\n};\ntemplate <class... T> void dbg0(T&&...\
    \ t) {\n    (PrettyOS{cerr, true} << ... << t);\n}\n#define dbg(...)         \
    \                                   \\\n    do {                             \
    \                       \\\n        cerr << __LINE__ << \" : \" << #__VA_ARGS__\
    \ << \" = \"; \\\n        dbg0(__VA_ARGS__);                                 \
    \ \\\n        cerr << endl;                                       \\\n    } while\
    \ (false);\n#else\n#define dbg(...)\n#endif\n#line 9 \"src/base.cpp\"\n\nScanner\
    \ sc = Scanner(stdin);\nPrinter pr = Printer(stdout);\n\nint main() {\n    return\
    \ 0;\n}\n\n"
  code: "//#pragma GCC optimize(\"Ofast\")\n//#pragma GCC target(\"avx\")\n//#undef\
    \ LOCAL\n\n#include <yosupo/fastio.hpp>\nusing namespace yosupo;\n\n#include \"\
    base.hpp\"\n\nScanner sc = Scanner(stdin);\nPrinter pr = Printer(stdout);\n\n\
    int main() {\n    return 0;\n}\n\n"
  dependsOn: []
  isVerificationFile: false
  path: src/base.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/base.cpp
layout: document
redirect_from:
- /library/src/base.cpp
- /library/src/base.cpp.html
title: src/base.cpp
---
