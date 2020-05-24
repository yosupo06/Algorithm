---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :heavy_check_mark: src/modint.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#25d902c24283ab8cfbac54dfa101ad31">src</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/modint.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-23 17:50:28+09:00


* see: <a href="https://judge.yosupo.jp/problem/aplusb">https://judge.yosupo.jp/problem/aplusb</a>


## Depends on

* :question: <a href="../../library/src/aplusb.hpp.html">src/aplusb.hpp</a>
* :question: <a href="../../library/src/base.hpp.html">src/base.hpp</a>
* :question: <a href="../../library/src/bitop.hpp.html">src/bitop.hpp</a>
* :heavy_check_mark: <a href="../../library/src/math/dynamicmodint.hpp.html">src/math/dynamicmodint.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "aplusb.hpp"

#include "base.hpp"
#include "math/dynamicmodint.hpp"

using DMint = DynamicModInt;

int main() {
    DMint::set_mod(103);
    for (int i = 1; i < 103; i++) {
        ll a = DMint(i).inv().val();
        assert(1 <= a && a < 103);
        assert((a * i) % 103 == 1);
    }
    solve_aplusb();
    return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/modint.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#line 2 "src/aplusb.hpp"

#include <iostream>

using namespace std;

void solve_aplusb() {
    int a, b;
    cin >> a >> b;
    cout << a + b << endl;
}
#line 4 "src/modint.test.cpp"

#line 2 "src/base.hpp"
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <complex>
#include <cstdio>
#include <cstring>
#line 10 "src/base.hpp"
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;

#ifdef LOCAL

ostream& operator<<(ostream& os, __int128_t x) {
    if (x < 0) {
        os << "-";
        x *= -1;
    }
    if (x == 0) {
        return os << "0";
    }
    string s;
    while (x) {
        s += char(x % 10 + '0');
        x /= 10;
    }
    reverse(s.begin(), s.end());
    return os << s;
}
ostream& operator<<(ostream& os, __uint128_t x) {
    if (x == 0) {
        return os << "0";
    }
    string s;
    while (x) {
        s += char(x % 10 + '0');
        x /= 10;
    }
    reverse(s.begin(), s.end());
    return os << s;
}

template <class T, class U>
ostream& operator<<(ostream& os, const pair<T, U>& p);
template <class T> ostream& operator<<(ostream& os, const V<T>& v);
template <class T, size_t N>
ostream& operator<<(ostream& os, const array<T, N>& a);
template <class T> ostream& operator<<(ostream& os, const set<T>& s);
template <class T, class U>
ostream& operator<<(ostream& os, const map<T, U>& m);

template <class T, class U>
ostream& operator<<(ostream& os, const pair<T, U>& p) {
    return os << "P(" << p.first << ", " << p.second << ")";
}

template <class T> ostream& operator<<(ostream& os, const V<T>& v) {
    os << "[";
    bool f = false;
    for (auto d : v) {
        if (f) os << ", ";
        f = true;
        os << d;
    }
    return os << "]";
}

template <class T, size_t N>
ostream& operator<<(ostream& os, const array<T, N>& a) {
    os << "[";
    bool f = false;
    for (auto d : a) {
        if (f) os << ", ";
        f = true;
        os << d;
    }
    return os << "]";
}

template <class T> ostream& operator<<(ostream& os, const set<T>& s) {
    os << "{";
    bool f = false;
    for (auto d : s) {
        if (f) os << ", ";
        f = true;
        os << d;
    }
    return os << "}";
}

template <class T, class U>
ostream& operator<<(ostream& os, const map<T, U>& s) {
    os << "{";
    bool f = false;
    for (auto p : s) {
        if (f) os << ", ";
        f = true;
        os << p.first << ": " << p.second;
    }
    return os << "}";
}

struct PrettyOS {
    ostream& os;
    bool first;

    template <class T> auto operator<<(T&& x) {
        if (!first) os << ", ";
        first = false;
        os << x;
        return *this;
    }
};
template <class... T> void dbg0(T&&... t) {
    (PrettyOS{cerr, true} << ... << t);
}
#define dbg(...)                                            \
    do {                                                    \
        cerr << __LINE__ << " : " << #__VA_ARGS__ << " = "; \
        dbg0(__VA_ARGS__);                                  \
        cerr << endl;                                       \
    } while (false);
#else
#define dbg(...)
#endif
#line 2 "src/math/dynamicmodint.hpp"

#line 2 "src/bitop.hpp"
// bit op
int popcnt(uint x) { return __builtin_popcount(x); }
int popcnt(ull x) { return __builtin_popcountll(x); }
int bsr(uint x) { return 31 - __builtin_clz(x); }
int bsr(ull x) { return 63 - __builtin_clzll(x); }
int bsf(uint x) { return __builtin_ctz(x); }
int bsf(ull x) { return __builtin_ctzll(x); }
#line 4 "src/math/dynamicmodint.hpp"


struct DynamicModInt {
    using M = DynamicModInt;

  private:
    static uint MD;
    static ull iMD;
    uint v = 0;

  public:
    static void set_mod(uint _MD) {
        assert(2 <= _MD);
        MD = _MD;
        iMD = ull(-1) / _MD + 1;
    }
    DynamicModInt() {}
    DynamicModInt(ll _v) { set_v(uint(_v % MD + MD)); }
    uint val() const { return v; }
    M& set_v(uint _v) {
        v = (_v < MD) ? _v : _v - MD;
        return *this;
    }
    explicit operator bool() const { return v != 0; }
    M operator-() const { return M() - *this; }
    M operator+(const M& r) const { return M().set_v(v + r.v); }
    M operator-(const M& r) const { return M().set_v(v + MD - r.v); }
    /*
    u32 fact_fast(u32 n, u32 mod) {
      u64 imod = u64(-1) / mod + 1; // ceil((1<<64) / mod);
      auto mul_mod = [&](u32 a, u32 b) {
        u64 c = u64(a) * b;
        u64 d = (__uint128_t(c) * imod) >> 64;
        u64 e = (c - d * mod + mod);
        //return e;
        return (e < mod) ? e : e - mod;
      };
      u32 ret = 1;
      for (int i = 1; i <= n; ++i) ret = mul_mod(ret, i);
      return ret;
    }
    */
    M operator*(const M& r) const {
        ull c = ull(v) * r.v;
        ull d = (__uint128_t(c) * iMD) >> 64;
        return M().set_v(uint(c - d * MD + MD));
    }
    M operator/(const M& r) const { return *this * r.inv(); }
    M& operator+=(const M& r) { return *this = *this + r; }
    M& operator-=(const M& r) { return *this = *this - r; }
    M& operator*=(const M& r) { return *this = *this * r; }
    M& operator/=(const M& r) { return *this = *this / r; }
    bool operator==(const M& r) const { return v == r.v; }
    M pow(ll n) const {
        M x = *this, r = 1;
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
    M inv() const {
        pair<uint, ll> p = {MD, 0}, q = {v, 1};
        while (q.first) {
            uint t = p.first / q.first;
            p.first -= t * q.first;
            p.second -= t * q.second;
            swap(p, q);
        }
        return M(p.second);
    }
    friend ostream& operator<<(ostream& os, const M& r) { return os << r.v; }
};
uint DynamicModInt::MD;
ull DynamicModInt::iMD;
#line 7 "src/modint.test.cpp"

using DMint = DynamicModInt;

int main() {
    DMint::set_mod(103);
    for (int i = 1; i < 103; i++) {
        ll a = DMint(i).inv().val();
        assert(1 <= a && a < 103);
        assert((a * i) % 103 == 1);
    }
    solve_aplusb();
    return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

