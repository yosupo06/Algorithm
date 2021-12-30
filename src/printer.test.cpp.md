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
    path: src/util/fast_io.hpp
    title: src/util/fast_io.hpp
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
  bundledCode: "#line 1 \"src/printer.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\
    \n\n#line 2 \"src/aplusb.hpp\"\n\n#include <iostream>\n\nusing namespace std;\n\
    \nvoid solve_aplusb() {\n    int a, b;\n    cin >> a >> b;\n    cout << a + b\
    \ << endl;\n}\n#line 2 \"src/base.hpp\"\n#include <algorithm>\n#include <array>\n\
    #include <bitset>\n#include <cassert>\n#include <complex>\n#include <cstdio>\n\
    #include <cstring>\n#line 10 \"src/base.hpp\"\n#include <map>\n#include <numeric>\n\
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
    \ 2 \"src/util/fast_io.hpp\"\n\n#include <unistd.h>\n\nstruct Scanner {\n    int\
    \ fd = -1;\n    char line[(1 << 15) + 1];\n    size_t st = 0, ed = 0;\n    void\
    \ reread() {\n        memmove(line, line + st, ed - st);\n        ed -= st;\n\
    \        st = 0;\n        ed += ::read(fd, line + ed, (1 << 15) - ed);\n     \
    \   line[ed] = '\\0';\n    }\n    bool succ() {\n        while (true) {\n    \
    \        if (st == ed) {\n                reread();\n                if (st ==\
    \ ed) return false;\n            }\n            while (st != ed && isspace(line[st]))\
    \ st++;\n            if (st != ed) break;\n        }\n        if (ed - st <= 50)\
    \ {\n            bool sep = false;\n            for (size_t i = st; i < ed; i++)\
    \ {\n                if (isspace(line[i])) {\n                    sep = true;\n\
    \                    break;\n                }\n            }\n            if\
    \ (!sep) reread();\n        }\n        return true;\n    }\n    template <class\
    \ T, enable_if_t<is_same<T, string>::value, int> = 0>\n    bool read_single(T&\
    \ ref) {\n        if (!succ()) return false;\n        while (true) {\n       \
    \     size_t sz = 0;\n            while (st + sz < ed && !isspace(line[st + sz]))\
    \ sz++;\n            ref.append(line + st, sz);\n            st += sz;\n     \
    \       if (!sz || st != ed) break;\n            reread();            \n     \
    \   }\n        return true;\n    }\n    template <class T, enable_if_t<is_integral<T>::value,\
    \ int> = 0>\n    bool read_single(T& ref) {\n        if (!succ()) return false;\n\
    \        bool neg = false;\n        if (line[st] == '-') {\n            neg =\
    \ true;\n            st++;\n        }\n        ref = T(0);\n        while (isdigit(line[st]))\
    \ {\n            ref = 10 * ref + (line[st++] & 0xf);\n        }\n        if (neg)\
    \ ref = -ref;\n        return true;\n    }\n    template <class T> bool read_single(V<T>&\
    \ ref) {\n        for (auto& d : ref) {\n            if (!read_single(d)) return\
    \ false;\n        }\n        return true;\n    }\n    void read() {}\n    template\
    \ <class H, class... T> void read(H& h, T&... t) {\n        bool f = read_single(h);\n\
    \        assert(f);\n        read(t...);\n    }\n    Scanner(FILE* fp) : fd(fileno(fp))\
    \ {}\n};\n\nstruct Printer {\n  public:\n    template <bool F = false> void write()\
    \ {}\n    template <bool F = false, class H, class... T>\n    void write(const\
    \ H& h, const T&... t) {\n        if (F) write_single(' ');\n        write_single(h);\n\
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
    \        }\n    }\n};\n#line 6 \"src/printer.test.cpp\"\n\nint main() {\n    Printer\
    \ pr(tmpfile());\n    pr.writeln(\"Hello\");\n    pr.writeln(string(\"World\"\
    ));\n\n    solve_aplusb();\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    aplusb.hpp\"\n#include \"base.hpp\"\n#include \"util/fast_io.hpp\"\n\nint main()\
    \ {\n    Printer pr(tmpfile());\n    pr.writeln(\"Hello\");\n    pr.writeln(string(\"\
    World\"));\n\n    solve_aplusb();\n}\n"
  dependsOn:
  - src/aplusb.hpp
  - src/base.hpp
  - src/util/fast_io.hpp
  isVerificationFile: true
  path: src/printer.test.cpp
  requiredBy: []
  timestamp: '2021-12-30 20:52:19+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: src/printer.test.cpp
layout: document
redirect_from:
- /verify/src/printer.test.cpp
- /verify/src/printer.test.cpp.html
title: src/printer.test.cpp
---
