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


# :warning: src/datastructure/smallfind.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#057cdb199a48f765d2786c323ec11d3a">src/datastructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/datastructure/smallfind.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 22:01:38+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

template <int N> struct SmallFind {
    array<int, N> id;
    SmallFind() {
        for (int i = 0; i < N; i++) id[i] = i;
    }

    SmallFind(ull hs) {
        for (int i = 0; i < N; i++) {
            id[i] = hs & 0xf;
            hs >>= 4;
        }
    }

    void merge(int x, int y) {
        int xg = id[x], yg = id[y];
        if (xg == yg) return;
        for (int i = 0; i < N; i++) {
            if (id[i] == yg) id[i] = xg;
        }
    }

    bool same(int x, int y) { return id[x] == id[y]; }

    ull uf2hash() {
        array<int, N> b;
        fill(b.begin(), b.end(), -1);
        int c = 0;
        ull hs = 0;
        for (int i = N - 1; i >= 0; i--) {
            hs <<= 4;
            if (b[id[i]] == -1) {
                b[id[i]] = c++;
            }
            hs += b[id[i]];
        }
        return hs;
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "src/datastructure/smallfind.hpp"

template <int N> struct SmallFind {
    array<int, N> id;
    SmallFind() {
        for (int i = 0; i < N; i++) id[i] = i;
    }

    SmallFind(ull hs) {
        for (int i = 0; i < N; i++) {
            id[i] = hs & 0xf;
            hs >>= 4;
        }
    }

    void merge(int x, int y) {
        int xg = id[x], yg = id[y];
        if (xg == yg) return;
        for (int i = 0; i < N; i++) {
            if (id[i] == yg) id[i] = xg;
        }
    }

    bool same(int x, int y) { return id[x] == id[y]; }

    ull uf2hash() {
        array<int, N> b;
        fill(b.begin(), b.end(), -1);
        int c = 0;
        ull hs = 0;
        for (int i = N - 1; i >= 0; i--) {
            hs <<= 4;
            if (b[id[i]] == -1) {
                b[id[i]] = c++;
            }
            hs += b[id[i]];
        }
        return hs;
    }
};

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

