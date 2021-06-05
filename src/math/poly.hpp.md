---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/util/random.hpp
    title: src/util/random.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: src/inv_of_formal_power_series.test.cpp
    title: src/inv_of_formal_power_series.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"src/math/poly.hpp\"\n\n#line 2 \"src/util/random.hpp\"\n\
    \n#include <algorithm>\n#include <array>\n#include <cassert>\n#include <chrono>\n\
    #include <cstdint>\n#include <numeric>\n#include <random>\n#include <set>\n#include\
    \ <vector>\n\nstruct Random {\n  private:\n    // Use xoshiro256**\n    // Refereces:\
    \ http://xoshiro.di.unimi.it/xoshiro256starstar.c\n    static uint64_t rotl(const\
    \ uint64_t x, int k) {\n        return (x << k) | (x >> (64 - k));\n    }\n\n\
    \    std::array<uint64_t, 4> s;\n\n    uint64_t next() {\n        const uint64_t\
    \ result_starstar = rotl(s[1] * 5, 7) * 9;\n\n        const uint64_t t = s[1]\
    \ << 17;\n\n        s[2] ^= s[0];\n        s[3] ^= s[1];\n        s[1] ^= s[2];\n\
    \        s[0] ^= s[3];\n\n        s[2] ^= t;\n\n        s[3] = rotl(s[3], 45);\n\
    \n        return result_starstar;\n    }\n\n    // random choice from [0, upper]\n\
    \    uint64_t next(uint64_t upper) {\n        if (!(upper & (upper + 1))) {\n\
    \            // b = 00..0011..11\n            return next() & upper;\n       \
    \ }\n        int lg = 63 - __builtin_clzll(upper);\n        uint64_t mask = (lg\
    \ == 63) ? ~0ULL : (1ULL << (lg + 1)) - 1;\n        while (true) {\n         \
    \   uint64_t r = next() & mask;\n            if (r <= upper) return r;\n     \
    \   }\n    }\n\n  public:\n    Random(uint64_t seed = 0) {\n        // Use splitmix64\n\
    \        // Reference: http://xoshiro.di.unimi.it/splitmix64.c\n        for (int\
    \ i = 0; i < 4; i++) {\n            uint64_t z = (seed += 0x9e3779b97f4a7c15);\n\
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
    \    return gen;\n}\n#line 4 \"src/math/poly.hpp\"\ntemplate <class D> struct\
    \ Poly {\n    V<D> v;\n    Poly(const V<D>& _v = {}) : v(_v) { shrink(); }\n \
    \   void shrink() {\n        while (v.size() && !v.back()) v.pop_back();\n   \
    \ }\n\n    int size() const { return int(v.size()); }\n    D freq(int p) const\
    \ { return (p < size()) ? v[p] : D(0); }\n\n    Poly operator+(const Poly& r)\
    \ const {\n        auto n = max(size(), r.size());\n        V<D> res(n);\n   \
    \     for (int i = 0; i < n; i++) res[i] = freq(i) + r.freq(i);\n        return\
    \ res;\n    }\n    Poly operator-(const Poly& r) const {\n        int n = max(size(),\
    \ r.size());\n        V<D> res(n);\n        for (int i = 0; i < n; i++) res[i]\
    \ = freq(i) - r.freq(i);\n        return res;\n    }\n    Poly operator*(const\
    \ Poly& r) const { return {multiply(v, r.v)}; }\n    Poly operator*(const D& r)\
    \ const {\n        int n = size();\n        V<D> res(n);\n        for (int i =\
    \ 0; i < n; i++) res[i] = v[i] * r;\n        return res;\n    }\n    Poly operator/(const\
    \ D &r) const{\n        return *this * r.inv();\n    }\n    Poly operator/(const\
    \ Poly& r) const {\n        if (size() < r.size()) return {{}};\n        int n\
    \ = size() - r.size() + 1;\n        return (rev().pre(n) * r.rev().inv(n)).pre(n).rev(n);\n\
    \    }\n    Poly operator%(const Poly& r) const { return *this - *this / r * r;\
    \ }\n    Poly operator<<(int s) const {\n        V<D> res(size() + s);\n     \
    \   for (int i = 0; i < size(); i++) res[i + s] = v[i];\n        return res;\n\
    \    }\n    Poly operator>>(int s) const {\n        if (size() <= s) return Poly();\n\
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
    \    for (int i = 0; i < n; i++) cdet *= c[i];\n    return acdet / cdet;\n}\n"
  code: "#pragma once\n\n#include \"../util/random.hpp\"\ntemplate <class D> struct\
    \ Poly {\n    V<D> v;\n    Poly(const V<D>& _v = {}) : v(_v) { shrink(); }\n \
    \   void shrink() {\n        while (v.size() && !v.back()) v.pop_back();\n   \
    \ }\n\n    int size() const { return int(v.size()); }\n    D freq(int p) const\
    \ { return (p < size()) ? v[p] : D(0); }\n\n    Poly operator+(const Poly& r)\
    \ const {\n        auto n = max(size(), r.size());\n        V<D> res(n);\n   \
    \     for (int i = 0; i < n; i++) res[i] = freq(i) + r.freq(i);\n        return\
    \ res;\n    }\n    Poly operator-(const Poly& r) const {\n        int n = max(size(),\
    \ r.size());\n        V<D> res(n);\n        for (int i = 0; i < n; i++) res[i]\
    \ = freq(i) - r.freq(i);\n        return res;\n    }\n    Poly operator*(const\
    \ Poly& r) const { return {multiply(v, r.v)}; }\n    Poly operator*(const D& r)\
    \ const {\n        int n = size();\n        V<D> res(n);\n        for (int i =\
    \ 0; i < n; i++) res[i] = v[i] * r;\n        return res;\n    }\n    Poly operator/(const\
    \ D &r) const{\n        return *this * r.inv();\n    }\n    Poly operator/(const\
    \ Poly& r) const {\n        if (size() < r.size()) return {{}};\n        int n\
    \ = size() - r.size() + 1;\n        return (rev().pre(n) * r.rev().inv(n)).pre(n).rev(n);\n\
    \    }\n    Poly operator%(const Poly& r) const { return *this - *this / r * r;\
    \ }\n    Poly operator<<(int s) const {\n        V<D> res(size() + s);\n     \
    \   for (int i = 0; i < size(); i++) res[i + s] = v[i];\n        return res;\n\
    \    }\n    Poly operator>>(int s) const {\n        if (size() <= s) return Poly();\n\
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
    \    for (int i = 0; i < n; i++) cdet *= c[i];\n    return acdet / cdet;\n}\n"
  dependsOn:
  - src/util/random.hpp
  isVerificationFile: false
  path: src/math/poly.hpp
  requiredBy: []
  timestamp: '2020-05-24 19:01:57+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - src/inv_of_formal_power_series.test.cpp
documentation_of: src/math/poly.hpp
layout: document
redirect_from:
- /library/src/math/poly.hpp
- /library/src/math/poly.hpp.html
title: src/math/poly.hpp
---
