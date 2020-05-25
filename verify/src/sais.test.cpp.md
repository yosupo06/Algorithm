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


# :heavy_check_mark: src/sais.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#25d902c24283ab8cfbac54dfa101ad31">src</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/sais.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-24 20:46:05+09:00


* see: <a href="https://judge.yosupo.jp/problem/suffixarray">https://judge.yosupo.jp/problem/suffixarray</a>


## Depends on

* :heavy_check_mark: <a href="../../library/src/base.hpp.html">src/base.hpp</a>
* :heavy_check_mark: <a href="../../library/src/string/suffixarray.hpp.html">src/string/suffixarray.hpp</a>
* :heavy_check_mark: <a href="../../library/src/util/fast_io.hpp.html">src/util/fast_io.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"

#include "base.hpp"
#include "util/fast_io.hpp"
#include "string/suffixarray.hpp"

int main() {
    Scanner sc(stdin);
    Printer pr(stdout);
    string s;
    sc.read(s);
    auto sa = sa_is(s);
    pr.writeln(V<int>{sa.begin() + 1, sa.end()});
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/sais.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"

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
#line 2 "src/util/fast_io.hpp"

#include <unistd.h>

struct Scanner {
    int fd = -1;
    char line[(1 << 15) + 1];
    size_t st = 0, ed = 0;
    void reread() {
        memmove(line, line + st, ed - st);
        ed -= st;
        st = 0;
        ed += ::read(fd, line + ed, (1 << 15) - ed);
        line[ed] = '\0';
    }
    bool succ() {
        while (true) {
            if (st == ed) {
                reread();
                if (st == ed) return false;
            }
            while (st != ed && isspace(line[st])) st++;
            if (st != ed) break;
        }
        if (ed - st <= 50) {
            bool sep = false;
            for (size_t i = st; i < ed; i++) {
                if (isspace(line[i])) {
                    sep = true;
                    break;
                }
            }
            if (!sep) reread();
        }
        return true;
    }
    template <class T, enable_if_t<is_same<T, string>::value, int> = 0>
    bool read_single(T& ref) {
        if (!succ()) return false;
        while (true) {
            size_t sz = 0;
            while (st + sz < ed && !isspace(line[st + sz])) sz++;
            ref.append(line + st, sz);
            st += sz;
            if (!sz || st != ed) break;
            reread();            
        }
        return true;
    }
    template <class T, enable_if_t<is_integral<T>::value, int> = 0>
    bool read_single(T& ref) {
        if (!succ()) return false;
        bool neg = false;
        if (line[st] == '-') {
            neg = true;
            st++;
        }
        ref = T(0);
        while (isdigit(line[st])) {
            ref = 10 * ref + (line[st++] & 0xf);
        }
        if (neg) ref = -ref;
        return true;
    }
    template <class T> bool read_single(V<T>& ref) {
        for (auto& d : ref) {
            if (!read_single(d)) return false;
        }
        return true;
    }
    void read() {}
    template <class H, class... T> void read(H& h, T&... t) {
        bool f = read_single(h);
        assert(f);
        read(t...);
    }
    Scanner(FILE* fp) : fd(fileno(fp)) {}
};

struct Printer {
  public:
    template <bool F = false> void write() {}
    template <bool F = false, class H, class... T>
    void write(const H& h, const T&... t) {
        if (F) write_single(' ');
        write_single(h);
        write<true>(t...);
    }
    template <class... T> void writeln(const T&... t) {
        write(t...);
        write_single('\n');
    }

    Printer(FILE* _fp) : fp(_fp) {}
    ~Printer() { flush(); }

  private:
    static constexpr size_t SIZE = 1 << 15;
    FILE* fp;
    char line[SIZE], small[50];
    size_t pos = 0;
    void flush() {
        fwrite(line, 1, pos, fp);
        pos = 0;
    }
    void write_single(const char& val) {
        if (pos == SIZE) flush();
        line[pos++] = val;
    }
    template <class T, enable_if_t<is_integral<T>::value, int> = 0>
    void write_single(T val) {
        if (pos > (1 << 15) - 50) flush();
        if (val == 0) {
            write_single('0');
            return;
        }
        if (val < 0) {
            write_single('-');
            val = -val;  // todo min
        }
        size_t len = 0;
        while (val) {
            small[len++] = char(0x30 | (val % 10));
            val /= 10;
        }
        for (size_t i = 0; i < len; i++) {
            line[pos + i] = small[len - 1 - i];
        }
        pos += len;
    }
    void write_single(const string& s) {
        for (char c : s) write_single(c);
    }
    void write_single(const char* s) {
        size_t len = strlen(s);
        for (size_t i = 0; i < len; i++) write_single(s[i]);
    }
    template <class T> void write_single(const V<T>& val) {
        auto n = val.size();
        for (size_t i = 0; i < n; i++) {
            if (i) write_single(' ');
            write_single(val[i]);
        }
    }
};
#line 1 "src/string/suffixarray.hpp"
template <class Str> struct SA {
    Str s;
    V<int> sa, rsa, lcp;
    SA() {}
    SA(Str _s, V<int> _sa) : s(_s), sa(_sa) {
        int n = int(s.size());
        // make rsa
        rsa = V<int>(n + 1);
        for (int i = 0; i <= n; i++) {
            rsa[sa[i]] = i;
        }
        // make lcp
        lcp = V<int>(n);
        int h = 0;
        for (int i = 0; i < n; i++) {
            int j = sa[rsa[i] - 1];
            if (h > 0) h--;
            for (; j + h < n && i + h < n; h++) {
                if (s[j + h] != s[i + h]) break;
            }
            lcp[rsa[i] - 1] = h;
        }
    }
};

template <class Str> V<int> sa_is(Str s, int B = 200) {
    int n = int(s.size());
    V<int> sa(n + 1);
    if (n == 0) return sa;

    for (int i = 0; i < n; i++) s[i]++;
    s.push_back(0);
    B++;

    V<bool> ls(n + 1);
    ls[n] = true;
    for (int i = n - 1; i >= 0; i--) {
        ls[i] = (s[i] == s[i + 1]) ? ls[i + 1] : (s[i] < s[i + 1]);
    }
    V<int> sum_l(B + 1), sum_s(B + 1);
    for (int i = 0; i <= n; i++) {
        if (!ls[i])
            sum_s[s[i]]++;
        else
            sum_l[s[i] + 1]++;
    }
    for (int i = 0; i < B; i++) {
        sum_l[i + 1] += sum_s[i];
        sum_s[i + 1] += sum_l[i + 1];
    }

    auto induce = [&](const V<int>& lms) {
        fill(begin(sa), end(sa), -1);
        auto buf0 = sum_s;
        for (auto d : lms) {
            sa[buf0[s[d]]++] = d;
        }
        auto buf1 = sum_l;
        for (int i = 0; i <= n; i++) {
            int v = sa[i];
            if (v >= 1 && !ls[v - 1]) {
                sa[buf1[s[v - 1]]++] = v - 1;
            }
        }
        auto buf2 = sum_l;
        for (int i = n; i >= 0; i--) {
            int v = sa[i];
            if (v >= 1 && ls[v - 1]) {
                sa[--buf2[s[v - 1] + 1]] = v - 1;
            }
        }
    };

    V<int> lms, lms_map(n + 1, -1);
    for (int i = 1; i <= n; i++) {
        if (!ls[i - 1] && ls[i]) {
            lms_map[i] = int(lms.size());
            lms.push_back(i);
        }
    }

    induce(lms);

    if (lms.size() >= 2) {
        int m = int(lms.size()) - 1;
        V<int> lms2;
        for (int v : sa) {
            if (lms_map[v] != -1) lms2.push_back(v);
        }
        int rec_n = 1;
        V<int> rec_s(m);
        rec_s[lms_map[lms2[1]]] = 1;
        for (int i = 2; i <= m; i++) {
            int l = lms2[i - 1], r = lms2[i];
            int nl = lms[lms_map[l] + 1], nr = lms[lms_map[r] + 1];
            if (nl - l != nr - r)
                rec_n++;
            else {
                while (l <= nl) {
                    if (s[l] != s[r]) {
                        rec_n++;
                        break;
                    }
                    l++;
                    r++;
                }
            }
            rec_s[lms_map[lms2[i]]] = rec_n;
        }

        V<int> nx_lms;
        auto ch_sa = sa_is(rec_s, rec_n);
        for (int d : ch_sa) {
            nx_lms.push_back(lms[d]);
        }
        induce(nx_lms);
    }

    return sa;
}

template <class Str> V<int> doublingSA(Str s) {
    int n = (int)s.size();
    V<int> sa(n + 1);
    V<int> rsa(n + 1);
    iota(sa.begin(), sa.end(), 0);
    for (int i = 0; i <= n; i++) {
        rsa[i] = i < n ? s[i] : -1;
    }
    vector<int> tmp(n + 1);
    for (int k = 1; k <= n; k *= 2) {
        auto cmp = [&](int x, int y) {
            if (rsa[x] != rsa[y]) return rsa[x] < rsa[y];
            int rx = x + k <= n ? rsa[x + k] : -1;
            int ry = y + k <= n ? rsa[y + k] : -1;
            return rx < ry;
        };
        sort(sa.begin(), sa.end(), cmp);
        tmp[sa[0]] = 0;
        for (int i = 1; i <= n; i++) {
            tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
        }
        copy(tmp.begin(), tmp.end(), begin(rsa));
    }
    return sa;
}

// tを完全に含む範囲を出力,O(|t|logn)
template <class Str> array<int, 2> find(const SA<Str>& sa, const string& t) {
    int n = (int)sa.s.size(), m = (int)t.size();
    array<int, 2> ans;
    int l, r;

    l = 0, r = n + 1;
    while (r - l > 1) {
        int md = (l + r) / 2;
        if (sa.s.compare(sa.sa[md], m, t) < 0) {
            l = md;
        } else {
            r = md;
        }
    }
    ans[0] = r;

    l = 0, r = n + 1;
    while (r - l > 1) {
        int md = (l + r) / 2;
        if (sa.s.compare(sa.sa[md], m, t) <= 0) {
            l = md;
        } else {
            r = md;
        }
    }
    ans[1] = r;
    return ans;
}
#line 6 "src/sais.test.cpp"

int main() {
    Scanner sc(stdin);
    Printer pr(stdout);
    string s;
    sc.read(s);
    auto sa = sa_is(s);
    pr.writeln(V<int>{sa.begin() + 1, sa.end()});
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

