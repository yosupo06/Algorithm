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


# :warning: src/graph/dominator.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#5442c8f317d712204bf06ed26672e17c">src/graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/graph/dominator.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct Dominator {
    V<int> idom, sdom;
    LowLink lc;
    Dominator() {}
    template<class E>
    Dominator(const VV<E> &g, const VV<E> &rg, int s) {
        lc = LowLink(g, s);
        int n = (int)g.size();
        
        // uf init
        p.resize(n); mv.resize(n);
        fill_n(p.begin(), n, -1);
        iota(mv.begin(), mv.end(), 0);
        idom = vector<int>(n, -1);
        sdom = vector<int>(n);
        iota(sdom.begin(), sdom.end(), 0);

        vector<int> up(n);
        vector<vector<int>> bucket(n);
        int U = int(lc.vlis.size());
        for (int i = U-1; i > 0; i--) {
            int u = lc.vlis[i];
            for (E e: rg[u]) {
                if (lc.ord[e.to] == -1) continue;
                sdom[u] = lc.vlis[min(lc.ord[sdom[u]], lc.ord[sdom[compress(e.to)]])];
            }
            bucket[sdom[u]].push_back(u);
            for (int v: bucket[lc.par[u]]) {
                up[v] = compress(v);
            }
            bucket[lc.par[u]].clear();
            p[u] = lc.par[u]; // uf merge
        }

        for (int i = 1; i < U; i++) {
            int u = lc.vlis[i], v = up[u];
            if (sdom[u] == sdom[v]) idom[u] = sdom[u];
            else idom[u] = idom[v];
        }
    }

    // unionfind
    V<int> p, mv; // parent, min sdom's v
    int compress(int a) {
        if (p[a] != -1) {
            compress(p[a]);
            if (lc.ord[sdom[mv[a]]] > lc.ord[sdom[mv[p[a]]]]) {
                mv[a] = mv[p[a]];
            }
            p[a] = (p[p[a]] == -1 ? p[a] : p[p[a]]);
        }
        return mv[a];
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/graph/dominator.hpp"
struct Dominator {
    V<int> idom, sdom;
    LowLink lc;
    Dominator() {}
    template<class E>
    Dominator(const VV<E> &g, const VV<E> &rg, int s) {
        lc = LowLink(g, s);
        int n = (int)g.size();
        
        // uf init
        p.resize(n); mv.resize(n);
        fill_n(p.begin(), n, -1);
        iota(mv.begin(), mv.end(), 0);
        idom = vector<int>(n, -1);
        sdom = vector<int>(n);
        iota(sdom.begin(), sdom.end(), 0);

        vector<int> up(n);
        vector<vector<int>> bucket(n);
        int U = int(lc.vlis.size());
        for (int i = U-1; i > 0; i--) {
            int u = lc.vlis[i];
            for (E e: rg[u]) {
                if (lc.ord[e.to] == -1) continue;
                sdom[u] = lc.vlis[min(lc.ord[sdom[u]], lc.ord[sdom[compress(e.to)]])];
            }
            bucket[sdom[u]].push_back(u);
            for (int v: bucket[lc.par[u]]) {
                up[v] = compress(v);
            }
            bucket[lc.par[u]].clear();
            p[u] = lc.par[u]; // uf merge
        }

        for (int i = 1; i < U; i++) {
            int u = lc.vlis[i], v = up[u];
            if (sdom[u] == sdom[v]) idom[u] = sdom[u];
            else idom[u] = idom[v];
        }
    }

    // unionfind
    V<int> p, mv; // parent, min sdom's v
    int compress(int a) {
        if (p[a] != -1) {
            compress(p[a]);
            if (lc.ord[sdom[mv[a]]] > lc.ord[sdom[mv[p[a]]]]) {
                mv[a] = mv[p[a]];
            }
            p[a] = (p[p[a]] == -1 ? p[a] : p[p[a]]);
        }
        return mv[a];
    }
};

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

