---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/base.hpp
    title: src/base.hpp
  - icon: ':heavy_check_mark:'
    path: src/tree/hl.hpp
    title: src/tree/hl.hpp
  - icon: ':heavy_check_mark:'
    path: src/util/fast_io.hpp
    title: src/util/fast_io.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/lca
    links:
    - https://judge.yosupo.jp/problem/lca
  bundledCode: "#line 1 \"src/hl_lca.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/lca\"\
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
    \        }\n    }\n};\n#line 2 \"src/tree/hl.hpp\"\n\n#line 4 \"src/tree/hl.hpp\"\
    \n\nstruct HL {\n    // inside index of HL\n    struct I {\n        int i;\n \
    \   };\n    V<int> _ord;          // int -> I\n    V<int> _rord;         // I\
    \ -> int\n    V<int> _big, _small;  // I -> I\n    // optionals\n    V<int> dps;\
    \       // node depth(int -> int)\n    int pc = 0;       // path count(optional)\n\
    \    V<int> pid, psz;  // path id, size (optional)\n    V<int> _out;       //\
    \ ouv[i] is end of subtree(I -> I)\n    HL() {}\n    HL(size_t n)\n        : _ord(n),\
    \ _rord(n), _big(n), _small(n), dps(n), pid(n), _out(n) {}\n    I ord(int v) const\
    \ { return v == -1 ? I{-1} : I{_ord[v]}; }\n    int rord(I i) const { return i.i\
    \ == -1 ? -1 : _rord[i.i]; }\n    I par(I i) const { return I{_small[i.i] == i.i\
    \ ? _big[i.i] : i.i - 1}; }\n    I subtree_out(int v) const { return I{_out[ord(v).i]};\
    \ };\n    int par(int v) const { return rord(par(ord(v))); }\n    int lca(int\
    \ a, int b) const {\n        int ai = ord(a).i;\n        int bi = ord(b).i;\n\
    \        while (ai != bi) {\n            if (ai > bi) swap(ai, bi);\n        \
    \    if (_small[bi] <= ai)\n                break;\n            else\n       \
    \         bi = _big[bi];\n        }\n        return rord(I{ai});\n    }\n    //\
    \ a\u306E\u76F4\u524D\u307E\u3067b\u304B\u3089\u767B\u308B\u3001f(I, I)\u306E\u5F15\
    \u6570\u306F\u4E21\u9589\u533A\u9593\n    template <class F> void get_path(int\
    \ a, int b, F f) const {\n        int ai = ord(a).i;\n        int bi = ord(b).i;\n\
    \        while (ai < bi) {\n            if (_small[bi] <= ai)\n              \
    \  f(I{ai + 1}, I{bi});\n            else\n                f(I{_small[bi]}, I{bi});\n\
    \            bi = _big[bi];\n        }\n    }\n    int to(int a, int b) {  //\
    \ a\u304B\u3089b\u306E\u65B9\u5411\u30781\u79FB\u52D5\u3059\u308B\n        int\
    \ ai = ord(a).i;\n        int bi = ord(b).i;\n        assert(ai < bi);\n     \
    \   while (true) {\n            if (_small[bi] <= ai)\n                return\
    \ rord(I{ai + 1});\n            else if (_big[bi] == ai)\n                return\
    \ rord(I{_small[bi]});\n            bi = _big[bi];\n        }\n        assert(false);\n\
    \    }\n    int dist(int a, int b) const {\n        int c = lca(a, b);\n     \
    \   return dps[a] + dps[b] - 2 * dps[c];\n    }\n};\n\ntemplate <class E> struct\
    \ HLExec : HL {\n    const VV<E>& g;\n    V<int> tch;\n    int id = 0;\n    HLExec(const\
    \ VV<E>& _g, int r) : HL(_g.size()), g(_g), tch(g.size(), -1) {\n        assert(dfs_sz(r,\
    \ -1) == int(g.size()));\n        dfs(r, -1);\n        init_extra();\n    }\n\
    \    void init_extra() {\n        // ord, rord, big, small\u4EE5\u5916\u3092\u4F7F\
    \u308F\u306A\u3044\u306A\u3089\u4E0D\u8981\n        int n = int(g.size());\n\n\
    \        // dps\n        dps[rord(I{0})] = 0;\n        for (int i = 1; i < n;\
    \ i++) {\n            dps[rord(I{i})] = dps[rord(par(I{i}))] + 1;\n        }\n\
    \n        // pid, psz, pc\n        int l = 0;\n        while (l < n) {\n     \
    \       int r = l + 1;\n            while (r < n && _small[r] == l) r++;\n   \
    \         psz.push_back(r - l);\n            for (int i = l; i < r; i++) {\n \
    \               pid[i] = pc;\n            }\n            l = r;\n            pc++;\n\
    \        }\n\n        // out\n        for (int i = n - 1; i >= 0; i--) {\n   \
    \         _out[i] = max(_out[i], i + 1);\n            int p = ord(par(rord(I{i}))).i;\n\
    \            if (p != -1) _out[p] = max(_out[p], _out[i]);\n        }\n    }\n\
    \    int dfs_sz(int p, int b) {\n        int sz = 1, msz = -1;\n        for (auto\
    \ e : g[p]) {\n            if (e.to == b) continue;\n            int u = dfs_sz(e.to,\
    \ p);\n            sz += u;\n            if (msz < u) tie(tch[p], msz) = make_pair(e.to,\
    \ u);\n        }\n        return sz;\n    }\n    void dfs(int p, int b) {\n  \
    \      int q = id++, bq = ord(b).i;\n        _ord[p] = q;\n        _rord[q] =\
    \ p;\n        if (b == -1 || bq != q - 1) {\n            _small[q] = q;\n    \
    \        _big[q] = bq;\n        } else {\n            _small[q] = _small[bq];\n\
    \            _big[q] = _big[bq];\n        }\n        if (tch[p] == -1) return;\n\
    \        dfs(tch[p], p);\n        for (auto e : g[p]) {\n            if (e.to\
    \ == b || e.to == tch[p]) continue;\n            dfs(e.to, p);\n        }\n  \
    \  }\n};\n\ntemplate <class E> HL get_hl(const VV<E>& g, int r) { return HLExec<E>(g,\
    \ r); }\n#line 6 \"src/hl_lca.test.cpp\"\n\nint main() {\n    Scanner sc(stdin);\n\
    \    Printer pr(stdout);\n    int n, q;\n    sc.read(n, q);\n    struct E { int\
    \ to; };\n    VV<E> g(n);\n    for (int i = 1; i < n; i++) {\n        int p;\n\
    \        sc.read(p);\n        g[p].push_back({i});\n        g[i].push_back({p});\n\
    \    }\n    auto hl = get_hl(g, 0);\n    for (int i = 0; i < q; i++) {\n     \
    \   int u, v;\n        sc.read(u, v);\n        auto lca_id = hl.lca(u, v);\n \
    \       pr.writeln(lca_id);\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/lca\"\n\n#include \"base.hpp\"\
    \n#include \"util/fast_io.hpp\"\n#include \"tree/hl.hpp\"\n\nint main() {\n  \
    \  Scanner sc(stdin);\n    Printer pr(stdout);\n    int n, q;\n    sc.read(n,\
    \ q);\n    struct E { int to; };\n    VV<E> g(n);\n    for (int i = 1; i < n;\
    \ i++) {\n        int p;\n        sc.read(p);\n        g[p].push_back({i});\n\
    \        g[i].push_back({p});\n    }\n    auto hl = get_hl(g, 0);\n    for (int\
    \ i = 0; i < q; i++) {\n        int u, v;\n        sc.read(u, v);\n        auto\
    \ lca_id = hl.lca(u, v);\n        pr.writeln(lca_id);\n    }\n    return 0;\n\
    }\n"
  dependsOn:
  - src/base.hpp
  - src/util/fast_io.hpp
  - src/tree/hl.hpp
  isVerificationFile: true
  path: src/hl_lca.test.cpp
  requiredBy: []
  timestamp: '2020-10-18 20:05:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: src/hl_lca.test.cpp
layout: document
redirect_from:
- /verify/src/hl_lca.test.cpp
- /verify/src/hl_lca.test.cpp.html
title: src/hl_lca.test.cpp
---
