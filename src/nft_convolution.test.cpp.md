---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/base.hpp
    title: src/base.hpp
  - icon: ':heavy_check_mark:'
    path: src/bitop.hpp
    title: src/bitop.hpp
  - icon: ':heavy_check_mark:'
    path: src/math/modint.hpp
    title: src/math/modint.hpp
  - icon: ':heavy_check_mark:'
    path: src/math/nft.hpp
    title: src/math/nft.hpp
  - icon: ':heavy_check_mark:'
    path: src/util/fast_io.hpp
    title: src/util/fast_io.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/convolution_mod
    links:
    - https://judge.yosupo.jp/problem/convolution_mod
  bundledCode: "#line 1 \"src/nft_convolution.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/convolution_mod\"\
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
    \        }\n    }\n};\n#line 2 \"src/bitop.hpp\"\n// bit op\nint popcnt(uint x)\
    \ { return __builtin_popcount(x); }\nint popcnt(ull x) { return __builtin_popcountll(x);\
    \ }\nint bsr(uint x) { return 31 - __builtin_clz(x); }\nint bsr(ull x) { return\
    \ 63 - __builtin_clzll(x); }\nint bsf(uint x) { return __builtin_ctz(x); }\nint\
    \ bsf(ull x) { return __builtin_ctzll(x); }\n#line 2 \"src/math/modint.hpp\"\n\
    \ntemplate <uint MD> struct ModInt {\n    using M = ModInt;\n    static constexpr\
    \ uint get_mod() { return MD; }\n    const static M G;\n    uint v;\n    ModInt(ll\
    \ _v = 0) { set_v(uint(_v % MD + MD)); }\n    M& set_v(uint _v) {\n        v =\
    \ (_v < MD) ? _v : _v - MD;\n        return *this;\n    }\n    explicit operator\
    \ bool() const { return v != 0; }\n    M operator-() const { return M() - *this;\
    \ }\n    M operator+(const M& r) const { return M().set_v(v + r.v); }\n    M operator-(const\
    \ M& r) const { return M().set_v(v + MD - r.v); }\n    M operator*(const M& r)\
    \ const { return M().set_v(uint(ull(v) * r.v % MD)); }\n    M operator/(const\
    \ M& r) const { return *this * r.inv(); }\n    M& operator+=(const M& r) { return\
    \ *this = *this + r; }\n    M& operator-=(const M& r) { return *this = *this -\
    \ r; }\n    M& operator*=(const M& r) { return *this = *this * r; }\n    M& operator/=(const\
    \ M& r) { return *this = *this / r; }\n    bool operator==(const M& r) const {\
    \ return v == r.v; }\n    M pow(ll n) const {\n        M x = *this, r = 1;\n \
    \       while (n) {\n            if (n & 1) r *= x;\n            x *= x;\n   \
    \         n >>= 1;\n        }\n        return r;\n    }\n    M inv() const { return\
    \ pow(MD - 2); }\n    friend ostream& operator<<(ostream& os, const M& r) { return\
    \ os << r.v; }\n};\n// using Mint = ModInt<998244353>;\n// template<> const Mint\
    \ Mint::G = Mint(3);\n#line 2 \"src/math/nft.hpp\"\n\n#line 4 \"src/math/nft.hpp\"\
    \n\ntemplate <class Mint> void nft(bool type, V<Mint>& a) {\n    int n = int(a.size()),\
    \ s = 0;\n    while ((1 << s) < n) s++;\n    assert(1 << s == n);\n\n    static\
    \ V<Mint> ep, iep;\n    while (int(ep.size()) <= s) {\n        ep.push_back(Mint::G.pow(Mint(-1).v\
    \ / (1 << ep.size())));\n        iep.push_back(ep.back().inv());\n    }\n    V<Mint>\
    \ b(n);\n    for (int i = 1; i <= s; i++) {\n        int w = 1 << (s - i);\n \
    \       Mint base = type ? iep[i] : ep[i], now = 1;\n        for (int y = 0; y\
    \ < n / 2; y += w) {\n            for (int x = 0; x < w; x++) {\n            \
    \    auto l = a[y << 1 | x];\n                auto r = now * a[y << 1 | x | w];\n\
    \                b[y | x] = l + r;\n                b[y | x | n >> 1] = l - r;\n\
    \            }\n            now *= base;\n        }\n        swap(a, b);\n   \
    \ }\n}\n\ntemplate <class Mint> V<Mint> multiply_nft(const V<Mint>& a, const V<Mint>&\
    \ b) {\n    int n = int(a.size()), m = int(b.size());\n    if (!n || !m) return\
    \ {};\n    if (min(n, m) <= 8) {\n        V<Mint> ans(n + m - 1);\n        for\
    \ (int i = 0; i < n; i++)\n            for (int j = 0; j < m; j++) ans[i + j]\
    \ += a[i] * b[j];\n        return ans;\n    }\n    int lg = 0;\n    while ((1\
    \ << lg) < n + m - 1) lg++;\n    int z = 1 << lg;\n    auto a2 = a, b2 = b;\n\
    \    a2.resize(z);\n    b2.resize(z);\n    nft(false, a2);\n    nft(false, b2);\n\
    \    for (int i = 0; i < z; i++) a2[i] *= b2[i];\n    nft(true, a2);\n    a2.resize(n\
    \ + m - 1);\n    Mint iz = Mint(z).inv();\n    for (int i = 0; i < n + m - 1;\
    \ i++) a2[i] *= iz;\n    return a2;\n}\n\n// Cooley-Tukey: input -> butterfly\
    \ -> bit reversing -> output \u304B\u3089\n// bit reversing\u3092\u629C\u3044\u305F\
    \u3082\u306E \u76F4\u63A5\u4F7F\u3046\u306A\ntemplate <class Mint> void butterfly(bool\
    \ type, V<Mint>& a) {\n    int n = int(a.size()), h = 0;\n    while ((1 << h)\
    \ < n) h++;\n    assert(1 << h == n);\n    if (n == 1) return;\n\n    static V<Mint>\
    \ snow, sinow;\n    if (snow.empty()) {\n        Mint sep = Mint(1), siep = Mint(1);\n\
    \        uint mod = Mint(-1).v;\n        uint di = 4;\n        while (mod % di\
    \ == 0) {\n            Mint ep = Mint::G.pow(mod / di);\n            Mint iep\
    \ = ep.inv();\n            snow.push_back(siep * ep);\n            sinow.push_back(sep\
    \ * iep);\n            sep *= ep;\n            siep *= iep;\n            di *=\
    \ 2;\n        }\n    }\n\n    if (!type) {\n        // fft\n        for (int ph\
    \ = 1; ph <= h; ph++) {\n            // phase ph: size w -> 2w \u306E FFT, p \u4E26\
    \u5217\n            int w = 1 << (ph - 1), p = 1 << (h - ph);\n            Mint\
    \ now = Mint(1);\n            for (int s = 0; s < w; s++) {\n                int\
    \ offset = s << (h - ph + 1);\n                for (int i = 0; i < p; i++) {\n\
    \                    auto l = a[i + offset];\n                    auto r = a[i\
    \ + offset + p] * now;\n                    a[i + offset] = l + r;\n         \
    \           a[i + offset + p] = l - r;\n                }\n                int\
    \ u = bsf(~uint(s));\n                now *= snow[u];\n            }\n       \
    \ }\n    } else {\n        // ifft\n        for (int ph = h; ph >= 1; ph--) {\n\
    \            int w = 1 << (ph - 1), p = 1 << (h - ph);\n            Mint inow\
    \ = Mint(1);\n            for (int s = 0; s < w; s++) {\n                int offset\
    \ = s << (h - ph + 1);\n                for (int i = 0; i < p; i++) {\n      \
    \              auto l = a[i + offset];\n                    auto r = a[i + offset\
    \ + p];\n                    a[i + offset] = l + r;\n                    a[i +\
    \ offset + p] = (l - r) * inow;\n                }\n                int u = bsf(~uint(s));\n\
    \                inow *= sinow[u];\n            }\n        }\n    }\n}\n\ntemplate\
    \ <class Mint> V<Mint> multiply(const V<Mint>& a, const V<Mint>& b) {\n    int\
    \ n = int(a.size()), m = int(b.size());\n    if (!n || !m) return {};\n    if\
    \ (min(n, m) < 8) {\n        V<Mint> ans(n + m - 1);\n        for (int i = 0;\
    \ i < n; i++)\n            for (int j = 0; j < m; j++) ans[i + j] += a[i] * b[j];\n\
    \        return ans;\n    }\n    int lg = 0;\n    while ((1 << lg) < n + m - 1)\
    \ lg++;\n    int z = 1 << lg;\n    auto a2 = a;\n    a2.resize(z);\n    butterfly(false,\
    \ a2);\n    if (a == b) {\n        for (int i = 0; i < z; i++) a2[i] *= a2[i];\n\
    \    } else {\n        auto b2 = b;\n        b2.resize(z);\n        butterfly(false,\
    \ b2);\n        for (int i = 0; i < z; i++) a2[i] *= b2[i];\n    }\n    butterfly(true,\
    \ a2);\n    a2.resize(n + m - 1);\n    Mint iz = Mint(z).inv();\n    for (int\
    \ i = 0; i < n + m - 1; i++) a2[i] *= iz;\n    return a2;\n}\n#line 8 \"src/nft_convolution.test.cpp\"\
    \n\nusing Mint = ModInt<998244353>;\ntemplate <> const Mint Mint::G = Mint(3);\n\
    \nint main() {\n    Scanner sc(stdin);\n    Printer pr(stdout);\n\n    int n,\
    \ m;\n    sc.read(n, m);\n\n    V<Mint> a(n);\n    for (int i = 0; i < n; i++)\
    \ {\n        sc.read(a[i].v);\n    }\n    V<Mint> b(m);\n    for (int i = 0; i\
    \ < m; i++) {\n        sc.read(b[i].v);\n    }\n    auto c = multiply(a, b);\n\
    \    for (auto x : c) {\n        pr.write(x.v);\n        pr.write(' ');\n    }\n\
    \    pr.writeln();\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/convolution_mod\"\n\n#include\
    \ \"base.hpp\"\n#include \"util/fast_io.hpp\"\n#include \"bitop.hpp\"\n#include\
    \ \"math/modint.hpp\"\n#include \"math/nft.hpp\"\n\nusing Mint = ModInt<998244353>;\n\
    template <> const Mint Mint::G = Mint(3);\n\nint main() {\n    Scanner sc(stdin);\n\
    \    Printer pr(stdout);\n\n    int n, m;\n    sc.read(n, m);\n\n    V<Mint> a(n);\n\
    \    for (int i = 0; i < n; i++) {\n        sc.read(a[i].v);\n    }\n    V<Mint>\
    \ b(m);\n    for (int i = 0; i < m; i++) {\n        sc.read(b[i].v);\n    }\n\
    \    auto c = multiply(a, b);\n    for (auto x : c) {\n        pr.write(x.v);\n\
    \        pr.write(' ');\n    }\n    pr.writeln();\n    return 0;\n}\n"
  dependsOn:
  - src/base.hpp
  - src/util/fast_io.hpp
  - src/bitop.hpp
  - src/math/modint.hpp
  - src/math/nft.hpp
  isVerificationFile: true
  path: src/nft_convolution.test.cpp
  requiredBy: []
  timestamp: '2020-10-18 20:05:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: src/nft_convolution.test.cpp
layout: document
redirect_from:
- /verify/src/nft_convolution.test.cpp
- /verify/src/nft_convolution.test.cpp.html
title: src/nft_convolution.test.cpp
---
