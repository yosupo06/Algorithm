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


# :warning: src/datastructure/staticrangeunion.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#057cdb199a48f765d2786c323ec11d3a">src/datastructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/datastructure/staticrangeunion.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct StaticRangeUnion {
    using P = pair<int, int>;
    int n;
    VV<P> ques;
    StaticRangeUnion(int _n = 0) : n(_n), ques(n + 1) {}
    void merge(int a, int b, int di) {
        if (di == 0) return;
        ques[min(di, n)].push_back({a, b});
    }
    UnionFind exec() {
        UnionFind uf(n);
        V<P> que;
        for (int di = n; di >= 1; di--) {
            for (auto p : ques[di]) que.push_back(p);
            V<P> nque;
            for (auto p : que) {
                if (uf.same(p.first, p.second)) continue;
                uf.merge(p.first, p.second);
                nque.push_back({p.first + 1, p.second + 1});
            }
            que = nque;
        }
        return uf;
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/datastructure/staticrangeunion.hpp"
struct StaticRangeUnion {
    using P = pair<int, int>;
    int n;
    VV<P> ques;
    StaticRangeUnion(int _n = 0) : n(_n), ques(n + 1) {}
    void merge(int a, int b, int di) {
        if (di == 0) return;
        ques[min(di, n)].push_back({a, b});
    }
    UnionFind exec() {
        UnionFind uf(n);
        V<P> que;
        for (int di = n; di >= 1; di--) {
            for (auto p : ques[di]) que.push_back(p);
            V<P> nque;
            for (auto p : que) {
                if (uf.same(p.first, p.second)) continue;
                uf.merge(p.first, p.second);
                nque.push_back({p.first + 1, p.second + 1});
            }
            que = nque;
        }
        return uf;
    }
};

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

