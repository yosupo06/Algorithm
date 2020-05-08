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
<script type="text/javascript" src="../../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../../assets/css/copy-button.css" />


# :warning: src/datastructure/Develop/FenwickTree2D.hpp

<a href="../../../../index.html">Back to top page</a>

* category: <a href="../../../../index.html#6ded3f220a7ec9530d5ce67338fd1fda">src/datastructure/Develop</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/datastructure/Develop/FenwickTree2D.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/**
 * Fenwick Tree 2D
 */
template <int N>
struct FenwickTree2D {
    using D = ll;
    FenwickTree<N> seg[N+1];
    
    void init() {
        for (int i = 0; i <= N; i++) {
            seg[i].init();
        }
    }

    /// 要素(x, y)にdを加算する
    void add(int x, int y, D d) {
        x++;
        while (x <= N) {
            seg[x].add(y, d);
            x += x & -x;
        }
    }

    /// x座標が[0, x) y座標が[0, y)の長方形区間のsum
    D sum(int x, int y) {
        D s = 0;
        while (x > 0) {
            s += seg[x].sum(y);
            x -= x & -x;
        }
        return s;
    }

    /// x座標が[lx, hx) y座標が[ly, hy)の長方形区間のsum
    D sum(int lx, int ly, int hx, int hy) {
        return (sum(hx, hy) + sum(lx, ly))
             - (sum(lx, hy) + sum(hx, ly));
    }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/datastructure/Develop/FenwickTree2D.hpp"
/**
 * Fenwick Tree 2D
 */
template <int N>
struct FenwickTree2D {
    using D = ll;
    FenwickTree<N> seg[N+1];
    
    void init() {
        for (int i = 0; i <= N; i++) {
            seg[i].init();
        }
    }

    /// 要素(x, y)にdを加算する
    void add(int x, int y, D d) {
        x++;
        while (x <= N) {
            seg[x].add(y, d);
            x += x & -x;
        }
    }

    /// x座標が[0, x) y座標が[0, y)の長方形区間のsum
    D sum(int x, int y) {
        D s = 0;
        while (x > 0) {
            s += seg[x].sum(y);
            x -= x & -x;
        }
        return s;
    }

    /// x座標が[lx, hx) y座標が[ly, hy)の長方形区間のsum
    D sum(int lx, int ly, int hx, int hy) {
        return (sum(hx, hy) + sum(lx, ly))
             - (sum(lx, hy) + sum(hx, ly));
    }
};

```
{% endraw %}

<a href="../../../../index.html">Back to top page</a>

