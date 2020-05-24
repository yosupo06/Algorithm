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
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :heavy_check_mark: src/tree/hl.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#3698aa34afa89577c63cbcf539eb96f7">src/tree</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/tree/hl.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-23 17:50:28+09:00




## Depends on

* :heavy_check_mark: <a href="../base.hpp.html">src/base.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../../verify/src/hl_lca.test.cpp.html">src/hl_lca.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/src/hl_vertex_add_path_sum.test.cpp.html">src/hl_vertex_add_path_sum.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/src/hl_vertex_add_subtree_sum.test.cpp.html">src/hl_vertex_add_subtree_sum.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include "../base.hpp"

struct HL {
    // inside index of HL
    struct I {
        int i;
    };
    V<int> _ord;          // int -> I
    V<int> _rord;         // I -> int
    V<int> _big, _small;  // I -> I
    // optionals
    V<int> dps;       // node depth(int -> int)
    int pc = 0;       // path count(optional)
    V<int> pid, psz;  // path id, size (optional)
    V<int> _out;       // ouv[i] is end of subtree(I -> I)
    HL() {}
    HL(size_t n)
        : _ord(n), _rord(n), _big(n), _small(n), dps(n), pid(n), _out(n) {}
    I ord(int v) const { return v == -1 ? I{-1} : I{_ord[v]}; }
    int rord(I i) const { return i.i == -1 ? -1 : _rord[i.i]; }
    I par(I i) const { return I{_small[i.i] == i.i ? _big[i.i] : i.i - 1}; }
    I subtree_out(int v) const { return I{_out[ord(v).i]}; };
    int par(int v) const { return rord(par(ord(v))); }
    int lca(int a, int b) const {
        int ai = ord(a).i;
        int bi = ord(b).i;
        while (ai != bi) {
            if (ai > bi) swap(ai, bi);
            if (_small[bi] <= ai)
                break;
            else
                bi = _big[bi];
        }
        return rord(I{ai});
    }
    // aの直前までbから登る、f(I, I)の引数は両閉区間
    template <class F> void get_path(int a, int b, F f) const {
        int ai = ord(a).i;
        int bi = ord(b).i;
        while (ai < bi) {
            if (_small[bi] <= ai)
                f(I{ai + 1}, I{bi});
            else
                f(I{_small[bi]}, I{bi});
            bi = _big[bi];
        }
    }
    int to(int a, int b) {  // aからbの方向へ1移動する
        int ai = ord(a).i;
        int bi = ord(b).i;
        assert(ai < bi);
        while (true) {
            if (_small[bi] <= ai)
                return rord(I{ai + 1});
            else if (_big[bi] == ai)
                return rord(I{_small[bi]});
            bi = _big[bi];
        }
        assert(false);
    }
    int dist(int a, int b) const {
        int c = lca(a, b);
        return dps[a] + dps[b] - 2 * dps[c];
    }
};

template <class E> struct HLExec : HL {
    const VV<E>& g;
    V<int> tch;
    int id = 0;
    HLExec(const VV<E>& _g, int r) : HL(_g.size()), g(_g), tch(g.size(), -1) {
        assert(dfs_sz(r, -1) == int(g.size()));
        dfs(r, -1);
        init_extra();
    }
    void init_extra() {
        // ord, rord, big, small以外を使わないなら不要
        int n = int(g.size());

        // dps
        dps[rord(I{0})] = 0;
        for (int i = 1; i < n; i++) {
            dps[rord(I{i})] = dps[rord(par(I{i}))] + 1;
        }

        // pid, psz, pc
        int l = 0;
        while (l < n) {
            int r = l + 1;
            while (r < n && _small[r] == l) r++;
            psz.push_back(r - l);
            for (int i = l; i < r; i++) {
                pid[i] = pc;
            }
            l = r;
            pc++;
        }

        // out
        for (int i = n - 1; i >= 0; i--) {
            _out[i] = max(_out[i], i + 1);
            int p = ord(par(rord(I{i}))).i;
            if (p != -1) _out[p] = max(_out[p], _out[i]);
        }
    }
    int dfs_sz(int p, int b) {
        int sz = 1, msz = -1;
        for (auto e : g[p]) {
            if (e.to == b) continue;
            int u = dfs_sz(e.to, p);
            sz += u;
            if (msz < u) tie(tch[p], msz) = make_pair(e.to, u);
        }
        return sz;
    }
    void dfs(int p, int b) {
        int q = id++, bq = ord(b).i;
        _ord[p] = q;
        _rord[q] = p;
        if (b == -1 || bq != q - 1) {
            _small[q] = q;
            _big[q] = bq;
        } else {
            _small[q] = _small[bq];
            _big[q] = _big[bq];
        }
        if (tch[p] == -1) return;
        dfs(tch[p], p);
        for (auto e : g[p]) {
            if (e.to == b || e.to == tch[p]) continue;
            dfs(e.to, p);
        }
    }
};

template <class E> HL get_hl(const VV<E>& g, int r) { return HLExec<E>(g, r); }

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "src/tree/hl.hpp"

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
#line 4 "src/tree/hl.hpp"

struct HL {
    // inside index of HL
    struct I {
        int i;
    };
    V<int> _ord;          // int -> I
    V<int> _rord;         // I -> int
    V<int> _big, _small;  // I -> I
    // optionals
    V<int> dps;       // node depth(int -> int)
    int pc = 0;       // path count(optional)
    V<int> pid, psz;  // path id, size (optional)
    V<int> _out;       // ouv[i] is end of subtree(I -> I)
    HL() {}
    HL(size_t n)
        : _ord(n), _rord(n), _big(n), _small(n), dps(n), pid(n), _out(n) {}
    I ord(int v) const { return v == -1 ? I{-1} : I{_ord[v]}; }
    int rord(I i) const { return i.i == -1 ? -1 : _rord[i.i]; }
    I par(I i) const { return I{_small[i.i] == i.i ? _big[i.i] : i.i - 1}; }
    I subtree_out(int v) const { return I{_out[ord(v).i]}; };
    int par(int v) const { return rord(par(ord(v))); }
    int lca(int a, int b) const {
        int ai = ord(a).i;
        int bi = ord(b).i;
        while (ai != bi) {
            if (ai > bi) swap(ai, bi);
            if (_small[bi] <= ai)
                break;
            else
                bi = _big[bi];
        }
        return rord(I{ai});
    }
    // aの直前までbから登る、f(I, I)の引数は両閉区間
    template <class F> void get_path(int a, int b, F f) const {
        int ai = ord(a).i;
        int bi = ord(b).i;
        while (ai < bi) {
            if (_small[bi] <= ai)
                f(I{ai + 1}, I{bi});
            else
                f(I{_small[bi]}, I{bi});
            bi = _big[bi];
        }
    }
    int to(int a, int b) {  // aからbの方向へ1移動する
        int ai = ord(a).i;
        int bi = ord(b).i;
        assert(ai < bi);
        while (true) {
            if (_small[bi] <= ai)
                return rord(I{ai + 1});
            else if (_big[bi] == ai)
                return rord(I{_small[bi]});
            bi = _big[bi];
        }
        assert(false);
    }
    int dist(int a, int b) const {
        int c = lca(a, b);
        return dps[a] + dps[b] - 2 * dps[c];
    }
};

template <class E> struct HLExec : HL {
    const VV<E>& g;
    V<int> tch;
    int id = 0;
    HLExec(const VV<E>& _g, int r) : HL(_g.size()), g(_g), tch(g.size(), -1) {
        assert(dfs_sz(r, -1) == int(g.size()));
        dfs(r, -1);
        init_extra();
    }
    void init_extra() {
        // ord, rord, big, small以外を使わないなら不要
        int n = int(g.size());

        // dps
        dps[rord(I{0})] = 0;
        for (int i = 1; i < n; i++) {
            dps[rord(I{i})] = dps[rord(par(I{i}))] + 1;
        }

        // pid, psz, pc
        int l = 0;
        while (l < n) {
            int r = l + 1;
            while (r < n && _small[r] == l) r++;
            psz.push_back(r - l);
            for (int i = l; i < r; i++) {
                pid[i] = pc;
            }
            l = r;
            pc++;
        }

        // out
        for (int i = n - 1; i >= 0; i--) {
            _out[i] = max(_out[i], i + 1);
            int p = ord(par(rord(I{i}))).i;
            if (p != -1) _out[p] = max(_out[p], _out[i]);
        }
    }
    int dfs_sz(int p, int b) {
        int sz = 1, msz = -1;
        for (auto e : g[p]) {
            if (e.to == b) continue;
            int u = dfs_sz(e.to, p);
            sz += u;
            if (msz < u) tie(tch[p], msz) = make_pair(e.to, u);
        }
        return sz;
    }
    void dfs(int p, int b) {
        int q = id++, bq = ord(b).i;
        _ord[p] = q;
        _rord[q] = p;
        if (b == -1 || bq != q - 1) {
            _small[q] = q;
            _big[q] = bq;
        } else {
            _small[q] = _small[bq];
            _big[q] = _big[bq];
        }
        if (tch[p] == -1) return;
        dfs(tch[p], p);
        for (auto e : g[p]) {
            if (e.to == b || e.to == tch[p]) continue;
            dfs(e.to, p);
        }
    }
};

template <class E> HL get_hl(const VV<E>& g, int r) { return HLExec<E>(g, r); }

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

