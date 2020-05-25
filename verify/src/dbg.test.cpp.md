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


# :heavy_check_mark: src/dbg.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#25d902c24283ab8cfbac54dfa101ad31">src</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/dbg.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-23 17:50:28+09:00


* see: <a href="https://judge.yosupo.jp/problem/aplusb">https://judge.yosupo.jp/problem/aplusb</a>


## Depends on

* :question: <a href="../../library/src/aplusb.hpp.html">src/aplusb.hpp</a>
* :question: <a href="../../library/src/base.hpp.html">src/base.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#define LOCAL
#include "aplusb.hpp"
#include "base.hpp"

int main() {
    pair<int, int> a = {1, 2};
    dbg(a);
    V<int> b = {1, 2, 3};
    dbg(b);
    V<pair<int, int>> c = {{1, 2}, {3, 4}};
    dbg(c);
    pair<V<int>, V<int>> d = {{1, 2}, {3, 4, 5}};
    dbg(d);

    array<int, 3> e = {1, 2, 3};
    dbg(e);
    array<V<int>, 2> f = {{{1, 2, 3}, {4, 5}}};
    dbg(f);

    set<int> g = {1, 2, 3, 4};
    dbg(g);

    map<int, int> h; h[1] = 2; h[3] = 4;
    dbg(h);

    solve_aplusb();

    __int128_t x = 1234;
    dbg(x);
    __uint128_t y = 5678;
    dbg(y);
    return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/dbg.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#define LOCAL
#line 2 "src/aplusb.hpp"

#include <iostream>

using namespace std;

void solve_aplusb() {
    int a, b;
    cin >> a >> b;
    cout << a + b << endl;
}
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
#line 6 "src/dbg.test.cpp"

int main() {
    pair<int, int> a = {1, 2};
    dbg(a);
    V<int> b = {1, 2, 3};
    dbg(b);
    V<pair<int, int>> c = {{1, 2}, {3, 4}};
    dbg(c);
    pair<V<int>, V<int>> d = {{1, 2}, {3, 4, 5}};
    dbg(d);

    array<int, 3> e = {1, 2, 3};
    dbg(e);
    array<V<int>, 2> f = {{{1, 2, 3}, {4, 5}}};
    dbg(f);

    set<int> g = {1, 2, 3, 4};
    dbg(g);

    map<int, int> h; h[1] = 2; h[3] = 4;
    dbg(h);

    solve_aplusb();

    __int128_t x = 1234;
    dbg(x);
    __uint128_t y = 5678;
    dbg(y);
    return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

