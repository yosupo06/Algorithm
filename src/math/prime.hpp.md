---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"src/math/prime.hpp\"\nbool is_prime(ll n) {\n    if (n <=\
    \ 1) return false;\n    if (n == 2) return true;\n    if (n % 2 == 0) return false;\n\
    \    ll d = n - 1;\n    while (d % 2 == 0) d /= 2;\n    for (ll a : {2, 3, 5,\
    \ 7, 11, 13, 17, 19, 23, 29, 31, 37}) {\n        if (n <= a) break;\n        ll\
    \ t = d;\n        ll y = pow_mod<__int128_t>(a, t, n);  // over\n        while\
    \ (t != n - 1 && y != 1 && y != n - 1) {\n            y = __int128_t(y) * y %\
    \ n;  // flow\n            t <<= 1;\n        }\n        if (y != n - 1 && t %\
    \ 2 == 0) {\n            return false;\n        }\n    }\n    return true;\n}\n\
    \nll pollard_single(ll n) {\n    auto f = [&](ll x) { return (__int128_t(x) *\
    \ x + 1) % n; };\n    if (is_prime(n)) return n;\n    if (n % 2 == 0) return 2;\n\
    \    ll st = 0;\n    while (true) {\n        st++;\n        ll x = st, y = f(x);\n\
    \        while (true) {\n            ll p = gcd((y - x + n), n);\n           \
    \ if (p == 0 || p == n) break;\n            if (p != 1) return p;\n          \
    \  x = f(x);\n            y = f(f(y));\n        }\n    }\n}\n\nV<ll> pollard(ll\
    \ n) {\n    if (n == 1) return {};\n    ll x = pollard_single(n);\n    if (x ==\
    \ n) return {x};\n    V<ll> le = pollard(x);\n    V<ll> ri = pollard(n / x);\n\
    \    le.insert(le.end(), ri.begin(), ri.end());\n    return le;\n}\n\nll primitive_root(ll\
    \ p) {\n    auto v = pollard(p - 1);\n    while (true) {\n        ll g = global_gen.uniform(1LL,\
    \ p - 1);  //[1, p-1]\n        bool ok = true;\n        for (auto d : v) {\n \
    \           ll f = (p - 1) / d;\n            if (pow_mod<__int128_t>(g, f, p)\
    \ == 1) {\n                ok = false;\n                break;\n            }\n\
    \        }\n        if (ok) return g;\n    }\n}\n"
  code: "bool is_prime(ll n) {\n    if (n <= 1) return false;\n    if (n == 2) return\
    \ true;\n    if (n % 2 == 0) return false;\n    ll d = n - 1;\n    while (d %\
    \ 2 == 0) d /= 2;\n    for (ll a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37})\
    \ {\n        if (n <= a) break;\n        ll t = d;\n        ll y = pow_mod<__int128_t>(a,\
    \ t, n);  // over\n        while (t != n - 1 && y != 1 && y != n - 1) {\n    \
    \        y = __int128_t(y) * y % n;  // flow\n            t <<= 1;\n        }\n\
    \        if (y != n - 1 && t % 2 == 0) {\n            return false;\n        }\n\
    \    }\n    return true;\n}\n\nll pollard_single(ll n) {\n    auto f = [&](ll\
    \ x) { return (__int128_t(x) * x + 1) % n; };\n    if (is_prime(n)) return n;\n\
    \    if (n % 2 == 0) return 2;\n    ll st = 0;\n    while (true) {\n        st++;\n\
    \        ll x = st, y = f(x);\n        while (true) {\n            ll p = gcd((y\
    \ - x + n), n);\n            if (p == 0 || p == n) break;\n            if (p !=\
    \ 1) return p;\n            x = f(x);\n            y = f(f(y));\n        }\n \
    \   }\n}\n\nV<ll> pollard(ll n) {\n    if (n == 1) return {};\n    ll x = pollard_single(n);\n\
    \    if (x == n) return {x};\n    V<ll> le = pollard(x);\n    V<ll> ri = pollard(n\
    \ / x);\n    le.insert(le.end(), ri.begin(), ri.end());\n    return le;\n}\n\n\
    ll primitive_root(ll p) {\n    auto v = pollard(p - 1);\n    while (true) {\n\
    \        ll g = global_gen.uniform(1LL, p - 1);  //[1, p-1]\n        bool ok =\
    \ true;\n        for (auto d : v) {\n            ll f = (p - 1) / d;\n       \
    \     if (pow_mod<__int128_t>(g, f, p) == 1) {\n                ok = false;\n\
    \                break;\n            }\n        }\n        if (ok) return g;\n\
    \    }\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: src/math/prime.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/math/prime.hpp
layout: document
redirect_from:
- /library/src/math/prime.hpp
- /library/src/math/prime.hpp.html
title: src/math/prime.hpp
---
