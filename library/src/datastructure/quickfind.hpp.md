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


# :warning: src/datastructure/quickfind.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#057cdb199a48f765d2786c323ec11d3a">src/datastructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/datastructure/quickfind.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct QuickFind {
    V<int> id;
    VV<int> groups;
    int gc;  // group count
    QuickFind(int n = 0) {
        id = V<int>(n);
        groups = VV<int>(n);
        for (int i = 0; i < n; i++) {
            id[i] = i;
            groups[i] = {i};
        }
        gc = n;
    }
    void merge(int a, int b) {
        if (same(a, b)) return;
        gc--;
        int x = id[a], y = id[b];
        if (groups[x].size() < groups[y].size()) swap(x, y);
        for (int j : groups[y]) {
            id[j] = x;
            groups[x].push_back(j);
        }
        groups[y].clear();
    }
    bool same(int a, int b) { return id[a] == id[b]; }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/datastructure/quickfind.hpp"
struct QuickFind {
    V<int> id;
    VV<int> groups;
    int gc;  // group count
    QuickFind(int n = 0) {
        id = V<int>(n);
        groups = VV<int>(n);
        for (int i = 0; i < n; i++) {
            id[i] = i;
            groups[i] = {i};
        }
        gc = n;
    }
    void merge(int a, int b) {
        if (same(a, b)) return;
        gc--;
        int x = id[a], y = id[b];
        if (groups[x].size() < groups[y].size()) swap(x, y);
        for (int j : groups[y]) {
            id[j] = x;
            groups[x].push_back(j);
        }
        groups[y].clear();
    }
    bool same(int a, int b) { return id[a] == id[b]; }
};

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

