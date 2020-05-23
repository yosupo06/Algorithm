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


# :heavy_check_mark: src/base.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#25d902c24283ab8cfbac54dfa101ad31">src</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/base.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-23 17:50:28+09:00




## Required by

* :warning: <a href="base.cpp.html">src/base.cpp</a>
* :heavy_check_mark: <a href="datastructure/fenwick.hpp.html">src/datastructure/fenwick.hpp</a>
* :heavy_check_mark: <a href="datastructure/fenwick2d.hpp.html">src/datastructure/fenwick2d.hpp</a>
* :heavy_check_mark: <a href="datastructure/segtree.hpp.html">src/datastructure/segtree.hpp</a>
* :heavy_check_mark: <a href="datastructure/staticrangesum.hpp.html">src/datastructure/staticrangesum.hpp</a>
* :heavy_check_mark: <a href="graph/maxclique.hpp.html">src/graph/maxclique.hpp</a>
* :heavy_check_mark: <a href="math/comb.hpp.html">src/math/comb.hpp</a>
* :heavy_check_mark: <a href="math/modint61.hpp.html">src/math/modint61.hpp</a>
* :heavy_check_mark: <a href="math/nimber.hpp.html">src/math/nimber.hpp</a>
* :heavy_check_mark: <a href="string/rollinghash.hpp.html">src/string/rollinghash.hpp</a>
* :warning: <a href="string/run.hpp.html">src/string/run.hpp</a>
* :heavy_check_mark: <a href="tree/hl.hpp.html">src/tree/hl.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/src/bimaching.test.cpp.html">src/bimaching.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/src/comb.test.cpp.html">src/comb.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/src/dbg.test.cpp.html">src/dbg.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/src/doublingsa.test.cpp.html">src/doublingsa.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/src/fenwick_2d_rectangle_sum.test.cpp.html">src/fenwick_2d_rectangle_sum.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/src/hl_lca.test.cpp.html">src/hl_lca.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/src/hl_vertex_add_path_sum.test.cpp.html">src/hl_vertex_add_path_sum.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/src/hl_vertex_add_subtree_sum.test.cpp.html">src/hl_vertex_add_subtree_sum.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/src/inv_of_formal_power_series.test.cpp.html">src/inv_of_formal_power_series.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/src/lctree_lca.test.cpp.html">src/lctree_lca.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/src/lctree_vertex_add_path_sum.test.cpp.html">src/lctree_vertex_add_path_sum.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/src/max_clique.test.cpp.html">src/max_clique.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/src/modint.test.cpp.html">src/modint.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/src/modint61.test.cpp.html">src/modint61.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/src/nft_convolution.test.cpp.html">src/nft_convolution.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/src/nimber.test.cpp.html">src/nimber.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/src/number_of_substrings.test.cpp.html">src/number_of_substrings.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/src/online-zalgo.test.cpp.html">src/online-zalgo.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/src/printer.test.cpp.html">src/printer.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/src/sais.test.cpp.html">src/sais.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/src/scanner.test.cpp.html">src/scanner.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/src/staticrangesum_rectangle_sum.test.cpp.html">src/staticrangesum_rectangle_sum.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/src/zalgo.test.cpp.html">src/zalgo.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/src/zalgo_rollinghash.test.cpp.html">src/zalgo_rollinghash.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <complex>
#include <cstdio>
#include <cstring>
#include <iostream>
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

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "src/base.hpp"
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <complex>
#include <cstdio>
#include <cstring>
#include <iostream>
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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

