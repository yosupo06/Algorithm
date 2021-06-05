---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: src/doublingsa.test.cpp
    title: src/doublingsa.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/number_of_substrings.test.cpp
    title: src/number_of_substrings.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/sais.test.cpp
    title: src/sais.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"src/string/suffixarray.hpp\"\ntemplate <class Str> struct\
    \ SA {\n    Str s;\n    V<int> sa, rsa, lcp;\n    SA() {}\n    SA(Str _s, V<int>\
    \ _sa) : s(_s), sa(_sa) {\n        int n = int(s.size());\n        // make rsa\n\
    \        rsa = V<int>(n + 1);\n        for (int i = 0; i <= n; i++) {\n      \
    \      rsa[sa[i]] = i;\n        }\n        // make lcp\n        lcp = V<int>(n);\n\
    \        int h = 0;\n        for (int i = 0; i < n; i++) {\n            int j\
    \ = sa[rsa[i] - 1];\n            if (h > 0) h--;\n            for (; j + h < n\
    \ && i + h < n; h++) {\n                if (s[j + h] != s[i + h]) break;\n   \
    \         }\n            lcp[rsa[i] - 1] = h;\n        }\n    }\n};\n\ntemplate\
    \ <class Str> V<int> sa_is(Str s, int B = 200) {\n    int n = int(s.size());\n\
    \    V<int> sa(n + 1);\n    if (n == 0) return sa;\n\n    for (int i = 0; i <\
    \ n; i++) s[i]++;\n    s.push_back(0);\n    B++;\n\n    V<bool> ls(n + 1);\n \
    \   ls[n] = true;\n    for (int i = n - 1; i >= 0; i--) {\n        ls[i] = (s[i]\
    \ == s[i + 1]) ? ls[i + 1] : (s[i] < s[i + 1]);\n    }\n    V<int> sum_l(B + 1),\
    \ sum_s(B + 1);\n    for (int i = 0; i <= n; i++) {\n        if (!ls[i])\n   \
    \         sum_s[s[i]]++;\n        else\n            sum_l[s[i] + 1]++;\n    }\n\
    \    for (int i = 0; i < B; i++) {\n        sum_l[i + 1] += sum_s[i];\n      \
    \  sum_s[i + 1] += sum_l[i + 1];\n    }\n\n    auto induce = [&](const V<int>&\
    \ lms) {\n        fill(begin(sa), end(sa), -1);\n        auto buf0 = sum_s;\n\
    \        for (auto d : lms) {\n            sa[buf0[s[d]]++] = d;\n        }\n\
    \        auto buf1 = sum_l;\n        for (int i = 0; i <= n; i++) {\n        \
    \    int v = sa[i];\n            if (v >= 1 && !ls[v - 1]) {\n               \
    \ sa[buf1[s[v - 1]]++] = v - 1;\n            }\n        }\n        auto buf2 =\
    \ sum_l;\n        for (int i = n; i >= 0; i--) {\n            int v = sa[i];\n\
    \            if (v >= 1 && ls[v - 1]) {\n                sa[--buf2[s[v - 1] +\
    \ 1]] = v - 1;\n            }\n        }\n    };\n\n    V<int> lms, lms_map(n\
    \ + 1, -1);\n    for (int i = 1; i <= n; i++) {\n        if (!ls[i - 1] && ls[i])\
    \ {\n            lms_map[i] = int(lms.size());\n            lms.push_back(i);\n\
    \        }\n    }\n\n    induce(lms);\n\n    if (lms.size() >= 2) {\n        int\
    \ m = int(lms.size()) - 1;\n        V<int> lms2;\n        for (int v : sa) {\n\
    \            if (lms_map[v] != -1) lms2.push_back(v);\n        }\n        int\
    \ rec_n = 1;\n        V<int> rec_s(m);\n        rec_s[lms_map[lms2[1]]] = 1;\n\
    \        for (int i = 2; i <= m; i++) {\n            int l = lms2[i - 1], r =\
    \ lms2[i];\n            int nl = lms[lms_map[l] + 1], nr = lms[lms_map[r] + 1];\n\
    \            if (nl - l != nr - r)\n                rec_n++;\n            else\
    \ {\n                while (l <= nl) {\n                    if (s[l] != s[r])\
    \ {\n                        rec_n++;\n                        break;\n      \
    \              }\n                    l++;\n                    r++;\n       \
    \         }\n            }\n            rec_s[lms_map[lms2[i]]] = rec_n;\n   \
    \     }\n\n        V<int> nx_lms;\n        auto ch_sa = sa_is(rec_s, rec_n);\n\
    \        for (int d : ch_sa) {\n            nx_lms.push_back(lms[d]);\n      \
    \  }\n        induce(nx_lms);\n    }\n\n    return sa;\n}\n\ntemplate <class Str>\
    \ V<int> doublingSA(Str s) {\n    int n = (int)s.size();\n    V<int> sa(n + 1);\n\
    \    V<int> rsa(n + 1);\n    iota(sa.begin(), sa.end(), 0);\n    for (int i =\
    \ 0; i <= n; i++) {\n        rsa[i] = i < n ? s[i] : -1;\n    }\n    vector<int>\
    \ tmp(n + 1);\n    for (int k = 1; k <= n; k *= 2) {\n        auto cmp = [&](int\
    \ x, int y) {\n            if (rsa[x] != rsa[y]) return rsa[x] < rsa[y];\n   \
    \         int rx = x + k <= n ? rsa[x + k] : -1;\n            int ry = y + k <=\
    \ n ? rsa[y + k] : -1;\n            return rx < ry;\n        };\n        sort(sa.begin(),\
    \ sa.end(), cmp);\n        tmp[sa[0]] = 0;\n        for (int i = 1; i <= n; i++)\
    \ {\n            tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);\n\
    \        }\n        copy(tmp.begin(), tmp.end(), begin(rsa));\n    }\n    return\
    \ sa;\n}\n\n// t\u3092\u5B8C\u5168\u306B\u542B\u3080\u7BC4\u56F2\u3092\u51FA\u529B\
    ,O(|t|logn)\ntemplate <class Str> array<int, 2> find(const SA<Str>& sa, const\
    \ string& t) {\n    int n = (int)sa.s.size(), m = (int)t.size();\n    array<int,\
    \ 2> ans;\n    int l, r;\n\n    l = 0, r = n + 1;\n    while (r - l > 1) {\n \
    \       int md = (l + r) / 2;\n        if (sa.s.compare(sa.sa[md], m, t) < 0)\
    \ {\n            l = md;\n        } else {\n            r = md;\n        }\n \
    \   }\n    ans[0] = r;\n\n    l = 0, r = n + 1;\n    while (r - l > 1) {\n   \
    \     int md = (l + r) / 2;\n        if (sa.s.compare(sa.sa[md], m, t) <= 0) {\n\
    \            l = md;\n        } else {\n            r = md;\n        }\n    }\n\
    \    ans[1] = r;\n    return ans;\n}\n"
  code: "template <class Str> struct SA {\n    Str s;\n    V<int> sa, rsa, lcp;\n\
    \    SA() {}\n    SA(Str _s, V<int> _sa) : s(_s), sa(_sa) {\n        int n = int(s.size());\n\
    \        // make rsa\n        rsa = V<int>(n + 1);\n        for (int i = 0; i\
    \ <= n; i++) {\n            rsa[sa[i]] = i;\n        }\n        // make lcp\n\
    \        lcp = V<int>(n);\n        int h = 0;\n        for (int i = 0; i < n;\
    \ i++) {\n            int j = sa[rsa[i] - 1];\n            if (h > 0) h--;\n \
    \           for (; j + h < n && i + h < n; h++) {\n                if (s[j + h]\
    \ != s[i + h]) break;\n            }\n            lcp[rsa[i] - 1] = h;\n     \
    \   }\n    }\n};\n\ntemplate <class Str> V<int> sa_is(Str s, int B = 200) {\n\
    \    int n = int(s.size());\n    V<int> sa(n + 1);\n    if (n == 0) return sa;\n\
    \n    for (int i = 0; i < n; i++) s[i]++;\n    s.push_back(0);\n    B++;\n\n \
    \   V<bool> ls(n + 1);\n    ls[n] = true;\n    for (int i = n - 1; i >= 0; i--)\
    \ {\n        ls[i] = (s[i] == s[i + 1]) ? ls[i + 1] : (s[i] < s[i + 1]);\n   \
    \ }\n    V<int> sum_l(B + 1), sum_s(B + 1);\n    for (int i = 0; i <= n; i++)\
    \ {\n        if (!ls[i])\n            sum_s[s[i]]++;\n        else\n         \
    \   sum_l[s[i] + 1]++;\n    }\n    for (int i = 0; i < B; i++) {\n        sum_l[i\
    \ + 1] += sum_s[i];\n        sum_s[i + 1] += sum_l[i + 1];\n    }\n\n    auto\
    \ induce = [&](const V<int>& lms) {\n        fill(begin(sa), end(sa), -1);\n \
    \       auto buf0 = sum_s;\n        for (auto d : lms) {\n            sa[buf0[s[d]]++]\
    \ = d;\n        }\n        auto buf1 = sum_l;\n        for (int i = 0; i <= n;\
    \ i++) {\n            int v = sa[i];\n            if (v >= 1 && !ls[v - 1]) {\n\
    \                sa[buf1[s[v - 1]]++] = v - 1;\n            }\n        }\n   \
    \     auto buf2 = sum_l;\n        for (int i = n; i >= 0; i--) {\n           \
    \ int v = sa[i];\n            if (v >= 1 && ls[v - 1]) {\n                sa[--buf2[s[v\
    \ - 1] + 1]] = v - 1;\n            }\n        }\n    };\n\n    V<int> lms, lms_map(n\
    \ + 1, -1);\n    for (int i = 1; i <= n; i++) {\n        if (!ls[i - 1] && ls[i])\
    \ {\n            lms_map[i] = int(lms.size());\n            lms.push_back(i);\n\
    \        }\n    }\n\n    induce(lms);\n\n    if (lms.size() >= 2) {\n        int\
    \ m = int(lms.size()) - 1;\n        V<int> lms2;\n        for (int v : sa) {\n\
    \            if (lms_map[v] != -1) lms2.push_back(v);\n        }\n        int\
    \ rec_n = 1;\n        V<int> rec_s(m);\n        rec_s[lms_map[lms2[1]]] = 1;\n\
    \        for (int i = 2; i <= m; i++) {\n            int l = lms2[i - 1], r =\
    \ lms2[i];\n            int nl = lms[lms_map[l] + 1], nr = lms[lms_map[r] + 1];\n\
    \            if (nl - l != nr - r)\n                rec_n++;\n            else\
    \ {\n                while (l <= nl) {\n                    if (s[l] != s[r])\
    \ {\n                        rec_n++;\n                        break;\n      \
    \              }\n                    l++;\n                    r++;\n       \
    \         }\n            }\n            rec_s[lms_map[lms2[i]]] = rec_n;\n   \
    \     }\n\n        V<int> nx_lms;\n        auto ch_sa = sa_is(rec_s, rec_n);\n\
    \        for (int d : ch_sa) {\n            nx_lms.push_back(lms[d]);\n      \
    \  }\n        induce(nx_lms);\n    }\n\n    return sa;\n}\n\ntemplate <class Str>\
    \ V<int> doublingSA(Str s) {\n    int n = (int)s.size();\n    V<int> sa(n + 1);\n\
    \    V<int> rsa(n + 1);\n    iota(sa.begin(), sa.end(), 0);\n    for (int i =\
    \ 0; i <= n; i++) {\n        rsa[i] = i < n ? s[i] : -1;\n    }\n    vector<int>\
    \ tmp(n + 1);\n    for (int k = 1; k <= n; k *= 2) {\n        auto cmp = [&](int\
    \ x, int y) {\n            if (rsa[x] != rsa[y]) return rsa[x] < rsa[y];\n   \
    \         int rx = x + k <= n ? rsa[x + k] : -1;\n            int ry = y + k <=\
    \ n ? rsa[y + k] : -1;\n            return rx < ry;\n        };\n        sort(sa.begin(),\
    \ sa.end(), cmp);\n        tmp[sa[0]] = 0;\n        for (int i = 1; i <= n; i++)\
    \ {\n            tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);\n\
    \        }\n        copy(tmp.begin(), tmp.end(), begin(rsa));\n    }\n    return\
    \ sa;\n}\n\n// t\u3092\u5B8C\u5168\u306B\u542B\u3080\u7BC4\u56F2\u3092\u51FA\u529B\
    ,O(|t|logn)\ntemplate <class Str> array<int, 2> find(const SA<Str>& sa, const\
    \ string& t) {\n    int n = (int)sa.s.size(), m = (int)t.size();\n    array<int,\
    \ 2> ans;\n    int l, r;\n\n    l = 0, r = n + 1;\n    while (r - l > 1) {\n \
    \       int md = (l + r) / 2;\n        if (sa.s.compare(sa.sa[md], m, t) < 0)\
    \ {\n            l = md;\n        } else {\n            r = md;\n        }\n \
    \   }\n    ans[0] = r;\n\n    l = 0, r = n + 1;\n    while (r - l > 1) {\n   \
    \     int md = (l + r) / 2;\n        if (sa.s.compare(sa.sa[md], m, t) <= 0) {\n\
    \            l = md;\n        } else {\n            r = md;\n        }\n    }\n\
    \    ans[1] = r;\n    return ans;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: src/string/suffixarray.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - src/doublingsa.test.cpp
  - src/sais.test.cpp
  - src/number_of_substrings.test.cpp
documentation_of: src/string/suffixarray.hpp
layout: document
redirect_from:
- /library/src/string/suffixarray.hpp
- /library/src/string/suffixarray.hpp.html
title: src/string/suffixarray.hpp
---
