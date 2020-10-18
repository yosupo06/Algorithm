---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/base.hpp
    title: src/base.hpp
  - icon: ':heavy_check_mark:'
    path: src/string/suffixarray.hpp
    title: src/string/suffixarray.hpp
  - icon: ':heavy_check_mark:'
    path: src/util/fast_io.hpp
    title: src/util/fast_io.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/suffixarray
    links:
    - https://judge.yosupo.jp/problem/suffixarray
  bundledCode: "#line 1 \"src/doublingsa.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/suffixarray\"\
    \n\n#line 2 \"src/base.hpp\"\n#include <algorithm>\n#include <array>\n#include\
    \ <bitset>\n#include <cassert>\n#include <complex>\n#include <cstdio>\n#include\
    \ <cstring>\n#include <iostream>\n#include <map>\n#include <numeric>\n#include\
    \ <queue>\n#include <set>\n#include <string>\n#include <unordered_map>\n#include\
    \ <unordered_set>\n#include <vector>\n\nusing namespace std;\n\nusing uint = unsigned\
    \ int;\nusing ll = long long;\nusing ull = unsigned long long;\nconstexpr ll TEN(int\
    \ n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }\ntemplate <class T> using V =\
    \ vector<T>;\ntemplate <class T> using VV = V<V<T>>;\n\n#ifdef LOCAL\n\nostream&\
    \ operator<<(ostream& os, __int128_t x) {\n    if (x < 0) {\n        os << \"\
    -\";\n        x *= -1;\n    }\n    if (x == 0) {\n        return os << \"0\";\n\
    \    }\n    string s;\n    while (x) {\n        s += char(x % 10 + '0');\n   \
    \     x /= 10;\n    }\n    reverse(s.begin(), s.end());\n    return os << s;\n\
    }\nostream& operator<<(ostream& os, __uint128_t x) {\n    if (x == 0) {\n    \
    \    return os << \"0\";\n    }\n    string s;\n    while (x) {\n        s +=\
    \ char(x % 10 + '0');\n        x /= 10;\n    }\n    reverse(s.begin(), s.end());\n\
    \    return os << s;\n}\n\ntemplate <class T, class U>\nostream& operator<<(ostream&\
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
    \ (false);\n#else\n#define dbg(...)\n#endif\n#line 2 \"src/util/fast_io.hpp\"\n\
    \n#include <unistd.h>\n\nstruct Scanner {\n    int fd = -1;\n    char line[(1\
    \ << 15) + 1];\n    size_t st = 0, ed = 0;\n    void reread() {\n        memmove(line,\
    \ line + st, ed - st);\n        ed -= st;\n        st = 0;\n        ed += ::read(fd,\
    \ line + ed, (1 << 15) - ed);\n        line[ed] = '\\0';\n    }\n    bool succ()\
    \ {\n        while (true) {\n            if (st == ed) {\n                reread();\n\
    \                if (st == ed) return false;\n            }\n            while\
    \ (st != ed && isspace(line[st])) st++;\n            if (st != ed) break;\n  \
    \      }\n        if (ed - st <= 50) {\n            bool sep = false;\n      \
    \      for (size_t i = st; i < ed; i++) {\n                if (isspace(line[i]))\
    \ {\n                    sep = true;\n                    break;\n           \
    \     }\n            }\n            if (!sep) reread();\n        }\n        return\
    \ true;\n    }\n    template <class T, enable_if_t<is_same<T, string>::value,\
    \ int> = 0>\n    bool read_single(T& ref) {\n        if (!succ()) return false;\n\
    \        while (true) {\n            size_t sz = 0;\n            while (st + sz\
    \ < ed && !isspace(line[st + sz])) sz++;\n            ref.append(line + st, sz);\n\
    \            st += sz;\n            if (!sz || st != ed) break;\n            reread();\
    \            \n        }\n        return true;\n    }\n    template <class T,\
    \ enable_if_t<is_integral<T>::value, int> = 0>\n    bool read_single(T& ref) {\n\
    \        if (!succ()) return false;\n        bool neg = false;\n        if (line[st]\
    \ == '-') {\n            neg = true;\n            st++;\n        }\n        ref\
    \ = T(0);\n        while (isdigit(line[st])) {\n            ref = 10 * ref + (line[st++]\
    \ & 0xf);\n        }\n        if (neg) ref = -ref;\n        return true;\n   \
    \ }\n    template <class T> bool read_single(V<T>& ref) {\n        for (auto&\
    \ d : ref) {\n            if (!read_single(d)) return false;\n        }\n    \
    \    return true;\n    }\n    void read() {}\n    template <class H, class...\
    \ T> void read(H& h, T&... t) {\n        bool f = read_single(h);\n        assert(f);\n\
    \        read(t...);\n    }\n    Scanner(FILE* fp) : fd(fileno(fp)) {}\n};\n\n\
    struct Printer {\n  public:\n    template <bool F = false> void write() {}\n \
    \   template <bool F = false, class H, class... T>\n    void write(const H& h,\
    \ const T&... t) {\n        if (F) write_single(' ');\n        write_single(h);\n\
    \        write<true>(t...);\n    }\n    template <class... T> void writeln(const\
    \ T&... t) {\n        write(t...);\n        write_single('\\n');\n    }\n\n  \
    \  Printer(FILE* _fp) : fp(_fp) {}\n    ~Printer() { flush(); }\n\n  private:\n\
    \    static constexpr size_t SIZE = 1 << 15;\n    FILE* fp;\n    char line[SIZE],\
    \ small[50];\n    size_t pos = 0;\n    void flush() {\n        fwrite(line, 1,\
    \ pos, fp);\n        pos = 0;\n    }\n    void write_single(const char& val) {\n\
    \        if (pos == SIZE) flush();\n        line[pos++] = val;\n    }\n    template\
    \ <class T, enable_if_t<is_integral<T>::value, int> = 0>\n    void write_single(T\
    \ val) {\n        if (pos > (1 << 15) - 50) flush();\n        if (val == 0) {\n\
    \            write_single('0');\n            return;\n        }\n        if (val\
    \ < 0) {\n            write_single('-');\n            val = -val;  // todo min\n\
    \        }\n        size_t len = 0;\n        while (val) {\n            small[len++]\
    \ = char(0x30 | (val % 10));\n            val /= 10;\n        }\n        for (size_t\
    \ i = 0; i < len; i++) {\n            line[pos + i] = small[len - 1 - i];\n  \
    \      }\n        pos += len;\n    }\n    void write_single(const string& s) {\n\
    \        for (char c : s) write_single(c);\n    }\n    void write_single(const\
    \ char* s) {\n        size_t len = strlen(s);\n        for (size_t i = 0; i <\
    \ len; i++) write_single(s[i]);\n    }\n    template <class T> void write_single(const\
    \ V<T>& val) {\n        auto n = val.size();\n        for (size_t i = 0; i < n;\
    \ i++) {\n            if (i) write_single(' ');\n            write_single(val[i]);\n\
    \        }\n    }\n};\n#line 1 \"src/string/suffixarray.hpp\"\ntemplate <class\
    \ Str> struct SA {\n    Str s;\n    V<int> sa, rsa, lcp;\n    SA() {}\n    SA(Str\
    \ _s, V<int> _sa) : s(_s), sa(_sa) {\n        int n = int(s.size());\n       \
    \ // make rsa\n        rsa = V<int>(n + 1);\n        for (int i = 0; i <= n; i++)\
    \ {\n            rsa[sa[i]] = i;\n        }\n        // make lcp\n        lcp\
    \ = V<int>(n);\n        int h = 0;\n        for (int i = 0; i < n; i++) {\n  \
    \          int j = sa[rsa[i] - 1];\n            if (h > 0) h--;\n            for\
    \ (; j + h < n && i + h < n; h++) {\n                if (s[j + h] != s[i + h])\
    \ break;\n            }\n            lcp[rsa[i] - 1] = h;\n        }\n    }\n\
    };\n\ntemplate <class Str> V<int> sa_is(Str s, int B = 200) {\n    int n = int(s.size());\n\
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
    \    ans[1] = r;\n    return ans;\n}\n#line 6 \"src/doublingsa.test.cpp\"\n\n\
    int main() {\n    Scanner sc(stdin);\n    Printer pr(stdout);\n    string s;\n\
    \    sc.read(s);\n    auto sa = doublingSA(s);\n    pr.writeln(V<int>{sa.begin()\
    \ + 1, sa.end()});\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/suffixarray\"\n\n#include\
    \ \"base.hpp\"\n#include \"util/fast_io.hpp\"\n#include \"string/suffixarray.hpp\"\
    \n\nint main() {\n    Scanner sc(stdin);\n    Printer pr(stdout);\n    string\
    \ s;\n    sc.read(s);\n    auto sa = doublingSA(s);\n    pr.writeln(V<int>{sa.begin()\
    \ + 1, sa.end()});\n}\n"
  dependsOn:
  - src/base.hpp
  - src/util/fast_io.hpp
  - src/string/suffixarray.hpp
  isVerificationFile: true
  path: src/doublingsa.test.cpp
  requiredBy: []
  timestamp: '2020-10-18 20:05:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: src/doublingsa.test.cpp
layout: document
redirect_from:
- /verify/src/doublingsa.test.cpp
- /verify/src/doublingsa.test.cpp.html
title: src/doublingsa.test.cpp
---
