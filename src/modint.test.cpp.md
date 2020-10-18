---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/aplusb.hpp
    title: src/aplusb.hpp
  - icon: ':heavy_check_mark:'
    path: src/base.hpp
    title: src/base.hpp
  - icon: ':heavy_check_mark:'
    path: src/bitop.hpp
    title: src/bitop.hpp
  - icon: ':heavy_check_mark:'
    path: src/math/dynamicmodint.hpp
    title: src/math/dynamicmodint.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"src/modint.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\
    \n\n#line 2 \"src/aplusb.hpp\"\n\n#include <iostream>\n\nusing namespace std;\n\
    \nvoid solve_aplusb() {\n    int a, b;\n    cin >> a >> b;\n    cout << a + b\
    \ << endl;\n}\n#line 4 \"src/modint.test.cpp\"\n\n#line 2 \"src/base.hpp\"\n#include\
    \ <algorithm>\n#include <array>\n#include <bitset>\n#include <cassert>\n#include\
    \ <complex>\n#include <cstdio>\n#include <cstring>\n#line 10 \"src/base.hpp\"\n\
    #include <map>\n#include <numeric>\n#include <queue>\n#include <set>\n#include\
    \ <string>\n#include <unordered_map>\n#include <unordered_set>\n#include <vector>\n\
    \nusing namespace std;\n\nusing uint = unsigned int;\nusing ll = long long;\n\
    using ull = unsigned long long;\nconstexpr ll TEN(int n) { return (n == 0) ? 1\
    \ : 10 * TEN(n - 1); }\ntemplate <class T> using V = vector<T>;\ntemplate <class\
    \ T> using VV = V<V<T>>;\n\n#ifdef LOCAL\n\nostream& operator<<(ostream& os, __int128_t\
    \ x) {\n    if (x < 0) {\n        os << \"-\";\n        x *= -1;\n    }\n    if\
    \ (x == 0) {\n        return os << \"0\";\n    }\n    string s;\n    while (x)\
    \ {\n        s += char(x % 10 + '0');\n        x /= 10;\n    }\n    reverse(s.begin(),\
    \ s.end());\n    return os << s;\n}\nostream& operator<<(ostream& os, __uint128_t\
    \ x) {\n    if (x == 0) {\n        return os << \"0\";\n    }\n    string s;\n\
    \    while (x) {\n        s += char(x % 10 + '0');\n        x /= 10;\n    }\n\
    \    reverse(s.begin(), s.end());\n    return os << s;\n}\n\ntemplate <class T,\
    \ class U>\nostream& operator<<(ostream& os, const pair<T, U>& p);\ntemplate <class\
    \ T> ostream& operator<<(ostream& os, const V<T>& v);\ntemplate <class T> ostream&\
    \ operator<<(ostream& os, const deque<T>& v);\ntemplate <class T, size_t N>\n\
    ostream& operator<<(ostream& os, const array<T, N>& a);\ntemplate <class T> ostream&\
    \ operator<<(ostream& os, const set<T>& s);\ntemplate <class T, class U>\nostream&\
    \ operator<<(ostream& os, const map<T, U>& m);\n\ntemplate <class T, class U>\n\
    ostream& operator<<(ostream& os, const pair<T, U>& p) {\n    return os << \"P(\"\
    \ << p.first << \", \" << p.second << \")\";\n}\n\ntemplate <class T> ostream&\
    \ operator<<(ostream& os, const V<T>& v) {\n    os << \"[\";\n    bool f = false;\n\
    \    for (auto d : v) {\n        if (f) os << \", \";\n        f = true;\n   \
    \     os << d;\n    }\n    return os << \"]\";\n}\n\ntemplate <class T> ostream&\
    \ operator<<(ostream& os, const deque<T>& v) {\n    os << \"[\";\n    bool f =\
    \ false;\n    for (auto d : v) {\n        if (f) os << \", \";\n        f = true;\n\
    \        os << d;\n    }\n    return os << \"]\";\n}\ntemplate <class T, size_t\
    \ N>\nostream& operator<<(ostream& os, const array<T, N>& a) {\n    os << \"[\"\
    ;\n    bool f = false;\n    for (auto d : a) {\n        if (f) os << \", \";\n\
    \        f = true;\n        os << d;\n    }\n    return os << \"]\";\n}\n\ntemplate\
    \ <class T> ostream& operator<<(ostream& os, const set<T>& s) {\n    os << \"\
    {\";\n    bool f = false;\n    for (auto d : s) {\n        if (f) os << \", \"\
    ;\n        f = true;\n        os << d;\n    }\n    return os << \"}\";\n}\n\n\
    template <class T, class U>\nostream& operator<<(ostream& os, const map<T, U>&\
    \ s) {\n    os << \"{\";\n    bool f = false;\n    for (auto p : s) {\n      \
    \  if (f) os << \", \";\n        f = true;\n        os << p.first << \": \" <<\
    \ p.second;\n    }\n    return os << \"}\";\n}\n\nstruct PrettyOS {\n    ostream&\
    \ os;\n    bool first;\n\n    template <class T> auto operator<<(T&& x) {\n  \
    \      if (!first) os << \", \";\n        first = false;\n        os << x;\n \
    \       return *this;\n    }\n};\ntemplate <class... T> void dbg0(T&&... t) {\n\
    \    (PrettyOS{cerr, true} << ... << t);\n}\n#define dbg(...)                \
    \                            \\\n    do {                                    \
    \                \\\n        cerr << __LINE__ << \" : \" << #__VA_ARGS__ << \"\
    \ = \"; \\\n        dbg0(__VA_ARGS__);                                  \\\n \
    \       cerr << endl;                                       \\\n    } while (false);\n\
    #else\n#define dbg(...)\n#endif\n#line 2 \"src/math/dynamicmodint.hpp\"\n\n#line\
    \ 2 \"src/bitop.hpp\"\n// bit op\nint popcnt(uint x) { return __builtin_popcount(x);\
    \ }\nint popcnt(ull x) { return __builtin_popcountll(x); }\nint bsr(uint x) {\
    \ return 31 - __builtin_clz(x); }\nint bsr(ull x) { return 63 - __builtin_clzll(x);\
    \ }\nint bsf(uint x) { return __builtin_ctz(x); }\nint bsf(ull x) { return __builtin_ctzll(x);\
    \ }\n#line 4 \"src/math/dynamicmodint.hpp\"\n\n\nstruct DynamicModInt {\n    using\
    \ M = DynamicModInt;\n\n  private:\n    static uint MD;\n    static ull iMD;\n\
    \    uint v = 0;\n\n  public:\n    static void set_mod(uint _MD) {\n        assert(2\
    \ <= _MD);\n        MD = _MD;\n        iMD = ull(-1) / _MD + 1;\n    }\n    DynamicModInt()\
    \ {}\n    DynamicModInt(ll _v) { set_v(uint(_v % MD + MD)); }\n    uint val()\
    \ const { return v; }\n    M& set_v(uint _v) {\n        v = (_v < MD) ? _v : _v\
    \ - MD;\n        return *this;\n    }\n    explicit operator bool() const { return\
    \ v != 0; }\n    M operator-() const { return M() - *this; }\n    M operator+(const\
    \ M& r) const { return M().set_v(v + r.v); }\n    M operator-(const M& r) const\
    \ { return M().set_v(v + MD - r.v); }\n    /*\n    u32 fact_fast(u32 n, u32 mod)\
    \ {\n      u64 imod = u64(-1) / mod + 1; // ceil((1<<64) / mod);\n      auto mul_mod\
    \ = [&](u32 a, u32 b) {\n        u64 c = u64(a) * b;\n        u64 d = (__uint128_t(c)\
    \ * imod) >> 64;\n        u64 e = (c - d * mod + mod);\n        //return e;\n\
    \        return (e < mod) ? e : e - mod;\n      };\n      u32 ret = 1;\n     \
    \ for (int i = 1; i <= n; ++i) ret = mul_mod(ret, i);\n      return ret;\n   \
    \ }\n    */\n    M operator*(const M& r) const {\n        ull c = ull(v) * r.v;\n\
    \        ull d = (__uint128_t(c) * iMD) >> 64;\n        return M().set_v(uint(c\
    \ - d * MD + MD));\n    }\n    M operator/(const M& r) const { return *this *\
    \ r.inv(); }\n    M& operator+=(const M& r) { return *this = *this + r; }\n  \
    \  M& operator-=(const M& r) { return *this = *this - r; }\n    M& operator*=(const\
    \ M& r) { return *this = *this * r; }\n    M& operator/=(const M& r) { return\
    \ *this = *this / r; }\n    bool operator==(const M& r) const { return v == r.v;\
    \ }\n    M pow(ll n) const {\n        M x = *this, r = 1;\n        while (n) {\n\
    \            if (n & 1) r *= x;\n            x *= x;\n            n >>= 1;\n \
    \       }\n        return r;\n    }\n    M inv() const {\n        pair<uint, ll>\
    \ p = {MD, 0}, q = {v, 1};\n        while (q.first) {\n            uint t = p.first\
    \ / q.first;\n            p.first -= t * q.first;\n            p.second -= t *\
    \ q.second;\n            swap(p, q);\n        }\n        return M(p.second);\n\
    \    }\n    friend ostream& operator<<(ostream& os, const M& r) { return os <<\
    \ r.v; }\n};\nuint DynamicModInt::MD;\null DynamicModInt::iMD;\n#line 7 \"src/modint.test.cpp\"\
    \n\nusing DMint = DynamicModInt;\n\nint main() {\n    DMint::set_mod(103);\n \
    \   for (int i = 1; i < 103; i++) {\n        ll a = DMint(i).inv().val();\n  \
    \      assert(1 <= a && a < 103);\n        assert((a * i) % 103 == 1);\n    }\n\
    \    solve_aplusb();\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    aplusb.hpp\"\n\n#include \"base.hpp\"\n#include \"math/dynamicmodint.hpp\"\n\n\
    using DMint = DynamicModInt;\n\nint main() {\n    DMint::set_mod(103);\n    for\
    \ (int i = 1; i < 103; i++) {\n        ll a = DMint(i).inv().val();\n        assert(1\
    \ <= a && a < 103);\n        assert((a * i) % 103 == 1);\n    }\n    solve_aplusb();\n\
    \    return 0;\n}\n"
  dependsOn:
  - src/aplusb.hpp
  - src/base.hpp
  - src/math/dynamicmodint.hpp
  - src/bitop.hpp
  isVerificationFile: true
  path: src/modint.test.cpp
  requiredBy: []
  timestamp: '2020-10-18 20:05:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: src/modint.test.cpp
layout: document
redirect_from:
- /verify/src/modint.test.cpp
- /verify/src/modint.test.cpp.html
title: src/modint.test.cpp
---
