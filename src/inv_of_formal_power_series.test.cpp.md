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
    path: src/math/poly.hpp
    title: src/math/poly.hpp
  - icon: ':heavy_check_mark:'
    path: src/util/fast_io.hpp
    title: src/util/fast_io.hpp
  - icon: ':heavy_check_mark:'
    path: src/util/random.hpp
    title: src/util/random.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/inv_of_formal_power_series
    links:
    - https://judge.yosupo.jp/problem/inv_of_formal_power_series
  bundledCode: "#line 1 \"src/inv_of_formal_power_series.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/inv_of_formal_power_series\"\n\n#line 2 \"\
    src/base.hpp\"\n#include <algorithm>\n#include <array>\n#include <bitset>\n#include\
    \ <cassert>\n#include <complex>\n#include <cstdio>\n#include <cstring>\n#include\
    \ <iostream>\n#include <map>\n#include <numeric>\n#include <queue>\n#include <set>\n\
    #include <string>\n#include <unordered_map>\n#include <unordered_set>\n#include\
    \ <vector>\n\nusing namespace std;\n\nusing uint = unsigned int;\nusing ll = long\
    \ long;\nusing ull = unsigned long long;\nconstexpr ll TEN(int n) { return (n\
    \ == 0) ? 1 : 10 * TEN(n - 1); }\ntemplate <class T> using V = vector<T>;\ntemplate\
    \ <class T> using VV = V<V<T>>;\n\n#ifdef LOCAL\n\nostream& operator<<(ostream&\
    \ os, __int128_t x) {\n    if (x < 0) {\n        os << \"-\";\n        x *= -1;\n\
    \    }\n    if (x == 0) {\n        return os << \"0\";\n    }\n    string s;\n\
    \    while (x) {\n        s += char(x % 10 + '0');\n        x /= 10;\n    }\n\
    \    reverse(s.begin(), s.end());\n    return os << s;\n}\nostream& operator<<(ostream&\
    \ os, __uint128_t x) {\n    if (x == 0) {\n        return os << \"0\";\n    }\n\
    \    string s;\n    while (x) {\n        s += char(x % 10 + '0');\n        x /=\
    \ 10;\n    }\n    reverse(s.begin(), s.end());\n    return os << s;\n}\n\ntemplate\
    \ <class T, class U>\nostream& operator<<(ostream& os, const pair<T, U>& p);\n\
    template <class T> ostream& operator<<(ostream& os, const V<T>& v);\ntemplate\
    \ <class T> ostream& operator<<(ostream& os, const deque<T>& v);\ntemplate <class\
    \ T, size_t N>\nostream& operator<<(ostream& os, const array<T, N>& a);\ntemplate\
    \ <class T> ostream& operator<<(ostream& os, const set<T>& s);\ntemplate <class\
    \ T, class U>\nostream& operator<<(ostream& os, const map<T, U>& m);\n\ntemplate\
    \ <class T, class U>\nostream& operator<<(ostream& os, const pair<T, U>& p) {\n\
    \    return os << \"P(\" << p.first << \", \" << p.second << \")\";\n}\n\ntemplate\
    \ <class T> ostream& operator<<(ostream& os, const V<T>& v) {\n    os << \"[\"\
    ;\n    bool f = false;\n    for (auto d : v) {\n        if (f) os << \", \";\n\
    \        f = true;\n        os << d;\n    }\n    return os << \"]\";\n}\n\ntemplate\
    \ <class T> ostream& operator<<(ostream& os, const deque<T>& v) {\n    os << \"\
    [\";\n    bool f = false;\n    for (auto d : v) {\n        if (f) os << \", \"\
    ;\n        f = true;\n        os << d;\n    }\n    return os << \"]\";\n}\ntemplate\
    \ <class T, size_t N>\nostream& operator<<(ostream& os, const array<T, N>& a)\
    \ {\n    os << \"[\";\n    bool f = false;\n    for (auto d : a) {\n        if\
    \ (f) os << \", \";\n        f = true;\n        os << d;\n    }\n    return os\
    \ << \"]\";\n}\n\ntemplate <class T> ostream& operator<<(ostream& os, const set<T>&\
    \ s) {\n    os << \"{\";\n    bool f = false;\n    for (auto d : s) {\n      \
    \  if (f) os << \", \";\n        f = true;\n        os << d;\n    }\n    return\
    \ os << \"}\";\n}\n\ntemplate <class T, class U>\nostream& operator<<(ostream&\
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
    \        }\n    }\n};\n#line 2 \"src/math/modint.hpp\"\n\ntemplate <uint MD> struct\
    \ ModInt {\n    using M = ModInt;\n    static constexpr uint get_mod() { return\
    \ MD; }\n    const static M G;\n    uint v;\n    ModInt(ll _v = 0) { set_v(uint(_v\
    \ % MD + MD)); }\n    M& set_v(uint _v) {\n        v = (_v < MD) ? _v : _v - MD;\n\
    \        return *this;\n    }\n    explicit operator bool() const { return v !=\
    \ 0; }\n    M operator-() const { return M() - *this; }\n    M operator+(const\
    \ M& r) const { return M().set_v(v + r.v); }\n    M operator-(const M& r) const\
    \ { return M().set_v(v + MD - r.v); }\n    M operator*(const M& r) const { return\
    \ M().set_v(uint(ull(v) * r.v % MD)); }\n    M operator/(const M& r) const { return\
    \ *this * r.inv(); }\n    M& operator+=(const M& r) { return *this = *this + r;\
    \ }\n    M& operator-=(const M& r) { return *this = *this - r; }\n    M& operator*=(const\
    \ M& r) { return *this = *this * r; }\n    M& operator/=(const M& r) { return\
    \ *this = *this / r; }\n    bool operator==(const M& r) const { return v == r.v;\
    \ }\n    M pow(ll n) const {\n        M x = *this, r = 1;\n        while (n) {\n\
    \            if (n & 1) r *= x;\n            x *= x;\n            n >>= 1;\n \
    \       }\n        return r;\n    }\n    M inv() const { return pow(MD - 2); }\n\
    \    friend ostream& operator<<(ostream& os, const M& r) { return os << r.v; }\n\
    };\n// using Mint = ModInt<998244353>;\n// template<> const Mint Mint::G = Mint(3);\n\
    #line 2 \"src/util/random.hpp\"\n\n#line 6 \"src/util/random.hpp\"\n#include <chrono>\n\
    #include <cstdint>\n#line 9 \"src/util/random.hpp\"\n#include <random>\n#line\
    \ 12 \"src/util/random.hpp\"\n\nstruct Random {\n  private:\n    // Use xoshiro256**\n\
    \    // Refereces: http://xoshiro.di.unimi.it/xoshiro256starstar.c\n    static\
    \ uint64_t rotl(const uint64_t x, int k) {\n        return (x << k) | (x >> (64\
    \ - k));\n    }\n\n    std::array<uint64_t, 4> s;\n\n    uint64_t next() {\n \
    \       const uint64_t result_starstar = rotl(s[1] * 5, 7) * 9;\n\n        const\
    \ uint64_t t = s[1] << 17;\n\n        s[2] ^= s[0];\n        s[3] ^= s[1];\n \
    \       s[1] ^= s[2];\n        s[0] ^= s[3];\n\n        s[2] ^= t;\n\n       \
    \ s[3] = rotl(s[3], 45);\n\n        return result_starstar;\n    }\n\n    // random\
    \ choice from [0, upper]\n    uint64_t next(uint64_t upper) {\n        if (!(upper\
    \ & (upper + 1))) {\n            // b = 00..0011..11\n            return next()\
    \ & upper;\n        }\n        int lg = 63 - __builtin_clzll(upper);\n       \
    \ uint64_t mask = (lg == 63) ? ~0ULL : (1ULL << (lg + 1)) - 1;\n        while\
    \ (true) {\n            uint64_t r = next() & mask;\n            if (r <= upper)\
    \ return r;\n        }\n    }\n\n  public:\n    Random(uint64_t seed = 0) {\n\
    \        // Use splitmix64\n        // Reference: http://xoshiro.di.unimi.it/splitmix64.c\n\
    \        for (int i = 0; i < 4; i++) {\n            uint64_t z = (seed += 0x9e3779b97f4a7c15);\n\
    \            z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;\n            z = (z ^ (z\
    \ >> 27)) * 0x94d049bb133111eb;\n            s[i] = z ^ (z >> 31);\n        }\n\
    \    }\n\n    // random choice from [lower, upper]\n    template <class T> T uniform(T\
    \ lower, T upper) {\n        assert(lower <= upper);\n        return T(lower +\
    \ next(uint64_t(upper - lower)));\n    }\n\n    bool uniform_bool() { return uniform(0,\
    \ 1) == 1; }\n\n    double uniform01() {\n        uint64_t v = next(1ULL << 63);\n\
    \        return double(v) / (1ULL << 63);\n    }\n\n    template <class T> std::pair<T,\
    \ T> uniform_pair(T lower, T upper) {\n        assert(upper - lower >= 1);\n \
    \       T a, b;\n        do {\n            a = uniform(lower, upper);\n      \
    \      b = uniform(lower, upper);\n        } while (a == b);\n        if (a >\
    \ b) std::swap(a, b);\n        return {a, b};\n    }\n\n    // generate random\
    \ lower string that length = n\n    std::string lower_string(size_t n) {\n   \
    \     std::string res = \"\";\n        for (size_t i = 0; i < n; i++) {\n    \
    \        res += uniform('a', 'z');\n        }\n        return res;\n    }\n\n\
    \    // random shuffle\n    template <class Iter> void shuffle(Iter first, Iter\
    \ last) {\n        if (first == last) return;\n        // Reference and edit:\n\
    \        // cpprefjp - C++\u65E5\u672C\u8A9E\u30EA\u30D5\u30A1\u30EC\u30F3\u30B9\
    \n        // (https://cpprefjp.github.io/reference/algorithm/shuffle.html)\n \
    \       int len = 1;\n        for (auto it = first + 1; it != last; it++) {\n\
    \            len++;\n            int j = uniform(0, len - 1);\n            if\
    \ (j != len - 1) iter_swap(it, first + j);\n        }\n    }\n\n    // generate\
    \ random permutation that length = n\n    template <class T> std::vector<T> perm(size_t\
    \ n) {\n        std::vector<T> idx(n);\n        std::iota(idx.begin(), idx.end(),\
    \ T(0));\n        shuffle(idx.begin(), idx.end());\n        return idx;\n    }\n\
    \n    template <class T> std::vector<T> choice(size_t n, T lower, T upper) {\n\
    \        assert(n <= upper - lower + 1);\n        std::set<T> res;\n        while\
    \ (res.size() < n) res.insert(uniform(lower, upper));\n        return {res.begin(),\
    \ res.end()};\n    }\n};\nRandom& global_gen() {\n    static Random gen;\n   \
    \ return gen;\n}\nRandom get_random_gen() {\n    return Random(chrono::steady_clock::now().time_since_epoch().count());\n\
    }\nRandom& global_runtime_gen() {\n    static Random gen = get_random_gen();\n\
    \    return gen;\n}\n#line 2 \"src/math/nft.hpp\"\n\n#line 2 \"src/bitop.hpp\"\
    \n// bit op\nint popcnt(uint x) { return __builtin_popcount(x); }\nint popcnt(ull\
    \ x) { return __builtin_popcountll(x); }\nint bsr(uint x) { return 31 - __builtin_clz(x);\
    \ }\nint bsr(ull x) { return 63 - __builtin_clzll(x); }\nint bsf(uint x) { return\
    \ __builtin_ctz(x); }\nint bsf(ull x) { return __builtin_ctzll(x); }\n#line 4\
    \ \"src/math/nft.hpp\"\n\ntemplate <class Mint> void nft(bool type, V<Mint>& a)\
    \ {\n    int n = int(a.size()), s = 0;\n    while ((1 << s) < n) s++;\n    assert(1\
    \ << s == n);\n\n    static V<Mint> ep, iep;\n    while (int(ep.size()) <= s)\
    \ {\n        ep.push_back(Mint::G.pow(Mint(-1).v / (1 << ep.size())));\n     \
    \   iep.push_back(ep.back().inv());\n    }\n    V<Mint> b(n);\n    for (int i\
    \ = 1; i <= s; i++) {\n        int w = 1 << (s - i);\n        Mint base = type\
    \ ? iep[i] : ep[i], now = 1;\n        for (int y = 0; y < n / 2; y += w) {\n \
    \           for (int x = 0; x < w; x++) {\n                auto l = a[y << 1 |\
    \ x];\n                auto r = now * a[y << 1 | x | w];\n                b[y\
    \ | x] = l + r;\n                b[y | x | n >> 1] = l - r;\n            }\n \
    \           now *= base;\n        }\n        swap(a, b);\n    }\n}\n\ntemplate\
    \ <class Mint> V<Mint> multiply_nft(const V<Mint>& a, const V<Mint>& b) {\n  \
    \  int n = int(a.size()), m = int(b.size());\n    if (!n || !m) return {};\n \
    \   if (min(n, m) <= 8) {\n        V<Mint> ans(n + m - 1);\n        for (int i\
    \ = 0; i < n; i++)\n            for (int j = 0; j < m; j++) ans[i + j] += a[i]\
    \ * b[j];\n        return ans;\n    }\n    int lg = 0;\n    while ((1 << lg) <\
    \ n + m - 1) lg++;\n    int z = 1 << lg;\n    auto a2 = a, b2 = b;\n    a2.resize(z);\n\
    \    b2.resize(z);\n    nft(false, a2);\n    nft(false, b2);\n    for (int i =\
    \ 0; i < z; i++) a2[i] *= b2[i];\n    nft(true, a2);\n    a2.resize(n + m - 1);\n\
    \    Mint iz = Mint(z).inv();\n    for (int i = 0; i < n + m - 1; i++) a2[i] *=\
    \ iz;\n    return a2;\n}\n\n// Cooley-Tukey: input -> butterfly -> bit reversing\
    \ -> output \u304B\u3089\n// bit reversing\u3092\u629C\u3044\u305F\u3082\u306E\
    \ \u76F4\u63A5\u4F7F\u3046\u306A\ntemplate <class Mint> void butterfly(bool type,\
    \ V<Mint>& a) {\n    int n = int(a.size()), h = 0;\n    while ((1 << h) < n) h++;\n\
    \    assert(1 << h == n);\n    if (n == 1) return;\n\n    static V<Mint> snow,\
    \ sinow;\n    if (snow.empty()) {\n        Mint sep = Mint(1), siep = Mint(1);\n\
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
    \ i = 0; i < n + m - 1; i++) a2[i] *= iz;\n    return a2;\n}\n#line 2 \"src/math/poly.hpp\"\
    \n\n#line 4 \"src/math/poly.hpp\"\ntemplate <class D> struct Poly {\n    V<D>\
    \ v;\n    Poly(const V<D>& _v = {}) : v(_v) { shrink(); }\n    void shrink() {\n\
    \        while (v.size() && !v.back()) v.pop_back();\n    }\n\n    int size()\
    \ const { return int(v.size()); }\n    D freq(int p) const { return (p < size())\
    \ ? v[p] : D(0); }\n\n    Poly operator+(const Poly& r) const {\n        auto\
    \ n = max(size(), r.size());\n        V<D> res(n);\n        for (int i = 0; i\
    \ < n; i++) res[i] = freq(i) + r.freq(i);\n        return res;\n    }\n    Poly\
    \ operator-(const Poly& r) const {\n        int n = max(size(), r.size());\n \
    \       V<D> res(n);\n        for (int i = 0; i < n; i++) res[i] = freq(i) - r.freq(i);\n\
    \        return res;\n    }\n    Poly operator*(const Poly& r) const { return\
    \ {multiply(v, r.v)}; }\n    Poly operator*(const D& r) const {\n        int n\
    \ = size();\n        V<D> res(n);\n        for (int i = 0; i < n; i++) res[i]\
    \ = v[i] * r;\n        return res;\n    }\n    Poly operator/(const D &r) const{\n\
    \        return *this * r.inv();\n    }\n    Poly operator/(const Poly& r) const\
    \ {\n        if (size() < r.size()) return {{}};\n        int n = size() - r.size()\
    \ + 1;\n        return (rev().pre(n) * r.rev().inv(n)).pre(n).rev(n);\n    }\n\
    \    Poly operator%(const Poly& r) const { return *this - *this / r * r; }\n \
    \   Poly operator<<(int s) const {\n        V<D> res(size() + s);\n        for\
    \ (int i = 0; i < size(); i++) res[i + s] = v[i];\n        return res;\n    }\n\
    \    Poly operator>>(int s) const {\n        if (size() <= s) return Poly();\n\
    \        V<D> res(size() - s);\n        for (int i = 0; i < size() - s; i++) res[i]\
    \ = v[i + s];\n        return res;\n    }\n    Poly& operator+=(const Poly& r)\
    \ { return *this = *this + r; }\n    Poly& operator-=(const Poly& r) { return\
    \ *this = *this - r; }\n    Poly& operator*=(const Poly& r) { return *this = *this\
    \ * r; }\n    Poly& operator*=(const D& r) { return *this = *this * r; }\n   \
    \ Poly& operator/=(const Poly& r) { return *this = *this / r; }\n    Poly& operator/=(const\
    \ D &r) {return *this = *this/r;}\n    Poly& operator%=(const Poly& r) { return\
    \ *this = *this % r; }\n    Poly& operator<<=(const size_t& n) { return *this\
    \ = *this << n; }\n    Poly& operator>>=(const size_t& n) { return *this = *this\
    \ >> n; }\n\n    Poly pre(int le) const {\n        return {{v.begin(), v.begin()\
    \ + min(size(), le)}};\n    }\n    Poly rev(int n = -1) const {\n        V<D>\
    \ res = v;\n        if (n != -1) res.resize(n);\n        reverse(res.begin(),\
    \ res.end());\n        return res;\n    }\n    Poly diff() const {\n        V<D>\
    \ res(max(0, size() - 1));\n        for (int i = 1; i < size(); i++) res[i - 1]\
    \ = freq(i) * i;\n        return res;\n    }\n    Poly inte() const {\n      \
    \  V<D> res(size() + 1);\n        for (int i = 0; i < size(); i++) res[i + 1]\
    \ = freq(i) / (i + 1);\n        return res;\n    }\n\n    // f * f.inv() = 1 +\
    \ g(x)x^m\n    Poly inv(int m) const {\n        Poly res = Poly({D(1) / freq(0)});\n\
    \        for (int i = 1; i < m; i *= 2) {\n            res = (res * D(2) - res\
    \ * res * pre(2 * i)).pre(2 * i);\n        }\n        return res.pre(m);\n   \
    \ }\n    Poly exp(int n) const {\n        assert(freq(0) == 0);\n        Poly\
    \ f({1}), g({1});\n        for (int i = 1; i < n; i *= 2) {\n            g = (g\
    \ * 2 - f * g * g).pre(i);\n            Poly q = diff().pre(i - 1);\n        \
    \    Poly w = (q + g * (f.diff() - f * q)).pre(2 * i - 1);\n            f = (f\
    \ + f * (*this - w.inte()).pre(2 * i)).pre(2 * i);\n        }\n        return\
    \ f.pre(n);\n    }\n    Poly log(int n) const {\n        assert(freq(0) == 1);\n\
    \        auto f = pre(n);\n        return (f.diff() * f.inv(n - 1)).pre(n - 1).inte();\n\
    \    }\n    Poly sqrt(int n) const {\n        assert(freq(0) == 1);\n        Poly\
    \ f = pre(n + 1);\n        Poly g({1});\n        for (int i = 1; i < n; i *= 2)\
    \ {\n            g = (g + f.pre(2 * i) * g.inv(2 * i)) / 2;\n        }\n     \
    \   return g.pre(n + 1);\n    }\n\n    Poly pow_mod(ll n, const Poly& mod) {\n\
    \        Poly x = *this, r = {{1}};\n        while (n) {\n            if (n &\
    \ 1) r = r * x % mod;\n            x = x * x % mod;\n            n >>= 1;\n  \
    \      }\n        return r;\n    }\n\n    friend ostream& operator<<(ostream&\
    \ os, const Poly& p) {\n        if (p.size() == 0) return os << \"0\";\n     \
    \   for (auto i = 0; i < p.size(); i++) {\n            if (p.v[i]) {\n       \
    \         os << p.v[i] << \"x^\" << i;\n                if (i != p.size() - 1)\
    \ os << \"+\";\n            }\n        }\n        return os;\n    }\n};\n\ntemplate\
    \ <class Mint> struct MultiEval {\n    using NP = MultiEval*;\n    NP l, r;\n\
    \    V<Mint> que;\n    int sz;\n    Poly<Mint> mul;\n    MultiEval(const V<Mint>&\
    \ _que, int off, int _sz) : sz(_sz) {\n        if (sz <= 100) {\n            que\
    \ = {_que.begin() + off, _que.begin() + off + sz};\n            mul = {{1}};\n\
    \            for (auto x : que) mul *= {{-x, 1}};\n            return;\n     \
    \   }\n        l = new MultiEval(_que, off, sz / 2);\n        r = new MultiEval(_que,\
    \ off + sz / 2, sz - sz / 2);\n        mul = l->mul * r->mul;\n    }\n    MultiEval(const\
    \ V<Mint>& _que) : MultiEval(_que, 0, int(_que.size())) {}\n    void query(const\
    \ Poly<Mint>& _pol, V<Mint>& res) const {\n        if (sz <= 100) {\n        \
    \    for (auto x : que) {\n                Mint sm = 0, base = 1;\n          \
    \      for (int i = 0; i < _pol.size(); i++) {\n                    sm += base\
    \ * _pol.freq(i);\n                    base *= x;\n                }\n       \
    \         res.push_back(sm);\n            }\n            return;\n        }\n\
    \        auto pol = _pol % mul;\n        l->query(pol, res);\n        r->query(pol,\
    \ res);\n    }\n    V<Mint> query(const Poly<Mint>& pol) const {\n        V<Mint>\
    \ res;\n        query(pol, res);\n        return res;\n    }\n};\n\ntemplate <class\
    \ Mint> Poly<Mint> berlekamp_massey(const V<Mint>& s) {\n    int n = int(s.size());\n\
    \    V<Mint> b = {Mint(-1)}, c = {Mint(-1)};\n    Mint y = Mint(1);\n    for (int\
    \ ed = 1; ed <= n; ed++) {\n        int l = int(c.size()), m = int(b.size());\n\
    \        Mint x = 0;\n        for (int i = 0; i < l; i++) {\n            x +=\
    \ c[i] * s[ed - l + i];\n        }\n        b.push_back(0);\n        m++;\n  \
    \      if (!x) continue;\n        Mint freq = x / y;\n        if (l < m) {\n \
    \           // use b\n            auto tmp = c;\n            c.insert(begin(c),\
    \ m - l, Mint(0));\n            for (int i = 0; i < m; i++) {\n              \
    \  c[m - 1 - i] -= freq * b[m - 1 - i];\n            }\n            b = tmp;\n\
    \            y = x;\n        } else {\n            // use c\n            for (int\
    \ i = 0; i < m; i++) {\n                c[l - 1 - i] -= freq * b[m - 1 - i];\n\
    \            }\n        }\n    }\n    return c;\n}\n\ntemplate <class E, class\
    \ Mint = decltype(E().f)>\nMint sparse_det(const VV<E>& g) {\n    int n = int(g.size());\n\
    \    if (n == 0) return 1;\n    auto rand_v = [&]() {\n        V<Mint> res(n);\n\
    \        for (int i = 0; i < n; i++) {\n            res[i] = Mint(global_gen().uniform<int>(1,\
    \ Mint::get_mod() - 1));\n        }\n        return res;\n    };\n    V<Mint>\
    \ c = rand_v(), l = rand_v(), r = rand_v();\n    // l * mat * r\n    V<Mint> buf(2\
    \ * n);\n    for (int fe = 0; fe < 2 * n; fe++) {\n        for (int i = 0; i <\
    \ n; i++) {\n            buf[fe] += l[i] * r[i];\n        }\n        for (int\
    \ i = 0; i < n; i++) {\n            r[i] *= c[i];\n        }\n        V<Mint>\
    \ tmp(n);\n        for (int i = 0; i < n; i++) {\n            for (auto e : g[i])\
    \ {\n                tmp[i] += r[e.to] * e.f;\n            }\n        }\n    \
    \    r = tmp;\n    }\n    auto u = berlekamp_massey(buf);\n    if (u.size() !=\
    \ n + 1) return sparse_det(g);\n    auto acdet = u.freq(0) * Mint(-1);\n    if\
    \ (n % 2) acdet *= Mint(-1);\n    if (!acdet) return 0;\n    Mint cdet = 1;\n\
    \    for (int i = 0; i < n; i++) cdet *= c[i];\n    return acdet / cdet;\n}\n\
    #line 9 \"src/inv_of_formal_power_series.test.cpp\"\n\nusing Mint = ModInt<998244353>;\n\
    template <> const Mint Mint::G = Mint(3);\n\nint main() {\n    Scanner sc(stdin);\n\
    \    Printer pr(stdout);\n\n    int n;\n    sc.read(n);\n    V<Mint> _a(n);\n\
    \    for (int i = 0; i < n; i++) {\n        int x;\n        sc.read(x);\n    \
    \    _a[i] = Mint(x);\n    }\n    Poly<Mint> a = _a;\n    auto b = a.inv(n);\n\
    \n    for (int i = 0; i < n; i++) {\n        pr.write(b.freq(i).v);\n        pr.write('\
    \ ');\n    }\n    pr.writeln();\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/inv_of_formal_power_series\"\
    \n\n#include \"base.hpp\"\n#include \"util/fast_io.hpp\"\n#include \"math/modint.hpp\"\
    \n#include \"util/random.hpp\"\n#include \"math/nft.hpp\"\n#include \"math/poly.hpp\"\
    \n\nusing Mint = ModInt<998244353>;\ntemplate <> const Mint Mint::G = Mint(3);\n\
    \nint main() {\n    Scanner sc(stdin);\n    Printer pr(stdout);\n\n    int n;\n\
    \    sc.read(n);\n    V<Mint> _a(n);\n    for (int i = 0; i < n; i++) {\n    \
    \    int x;\n        sc.read(x);\n        _a[i] = Mint(x);\n    }\n    Poly<Mint>\
    \ a = _a;\n    auto b = a.inv(n);\n\n    for (int i = 0; i < n; i++) {\n     \
    \   pr.write(b.freq(i).v);\n        pr.write(' ');\n    }\n    pr.writeln();\n\
    \    return 0;\n}\n"
  dependsOn:
  - src/base.hpp
  - src/util/fast_io.hpp
  - src/math/modint.hpp
  - src/util/random.hpp
  - src/math/nft.hpp
  - src/bitop.hpp
  - src/math/poly.hpp
  isVerificationFile: true
  path: src/inv_of_formal_power_series.test.cpp
  requiredBy: []
  timestamp: '2020-10-18 20:05:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: src/inv_of_formal_power_series.test.cpp
layout: document
redirect_from:
- /verify/src/inv_of_formal_power_series.test.cpp
- /verify/src/inv_of_formal_power_series.test.cpp.html
title: src/inv_of_formal_power_series.test.cpp
---
