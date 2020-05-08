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


# :warning: src/graph/bridge.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#5442c8f317d712204bf06ed26672e17c">src/graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/graph/bridge.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct Bridge {
    V<int> id;
    VV<int> groups;
    VV<int> tr;
};

template <class E> struct BridgeExec : Bridge {
    const VV<E>& g;
    int n;
    int ordc = 0;
    V<int> low, ord, vlist;
    V<int> used;
    BridgeExec(const VV<E>& _g)
        : g(_g), n(int(g.size())), low(n), ord(n), used(n) {
        id = V<int>(n);
        for (int i = 0; i < n; i++) {
            if (used[i]) continue;
            dfs1(i, -1);
            dfs2(i, -1);
        }
    }
    void dfs1(int p, int b) {
        used[p] = 1;
        low[p] = ord[p] = ordc++;
        vlist.push_back(p);
        bool rt = true;
        for (auto e : g[p]) {
            int d = e.to;
            if (rt && d == b) {
                rt = false;
                continue;
            }
            if (!used[d]) {
                dfs1(d, p);
                low[p] = min(low[p], low[d]);
            } else {
                low[p] = min(low[p], ord[d]);
            }
        }
    }
    void dfs2(int p, int b) {
        used[p] = 2;
        bool is_root = low[p] == ord[p];
        if (is_root) {
            int idc = int(groups.size());
            id[p] = idc;
            groups.push_back({p});
            tr.push_back({});
            if (b != -1) {
                tr[idc].push_back(id[b]);
                tr[id[b]].push_back(idc);
            }
        } else {
            id[p] = id[b];
            groups[id[p]].push_back(p);
        }
        for (auto e : g[p]) {
            int d = e.to;
            if (d == b || used[d] == 2) continue;
            dfs2(d, p);
        }
    }
};

template <class E> Bridge get_bridge(const VV<E>& g) {
    return BridgeExec<E>(g);
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/graph/bridge.hpp"
struct Bridge {
    V<int> id;
    VV<int> groups;
    VV<int> tr;
};

template <class E> struct BridgeExec : Bridge {
    const VV<E>& g;
    int n;
    int ordc = 0;
    V<int> low, ord, vlist;
    V<int> used;
    BridgeExec(const VV<E>& _g)
        : g(_g), n(int(g.size())), low(n), ord(n), used(n) {
        id = V<int>(n);
        for (int i = 0; i < n; i++) {
            if (used[i]) continue;
            dfs1(i, -1);
            dfs2(i, -1);
        }
    }
    void dfs1(int p, int b) {
        used[p] = 1;
        low[p] = ord[p] = ordc++;
        vlist.push_back(p);
        bool rt = true;
        for (auto e : g[p]) {
            int d = e.to;
            if (rt && d == b) {
                rt = false;
                continue;
            }
            if (!used[d]) {
                dfs1(d, p);
                low[p] = min(low[p], low[d]);
            } else {
                low[p] = min(low[p], ord[d]);
            }
        }
    }
    void dfs2(int p, int b) {
        used[p] = 2;
        bool is_root = low[p] == ord[p];
        if (is_root) {
            int idc = int(groups.size());
            id[p] = idc;
            groups.push_back({p});
            tr.push_back({});
            if (b != -1) {
                tr[idc].push_back(id[b]);
                tr[id[b]].push_back(idc);
            }
        } else {
            id[p] = id[b];
            groups[id[p]].push_back(p);
        }
        for (auto e : g[p]) {
            int d = e.to;
            if (d == b || used[d] == 2) continue;
            dfs2(d, p);
        }
    }
};

template <class E> Bridge get_bridge(const VV<E>& g) {
    return BridgeExec<E>(g);
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

