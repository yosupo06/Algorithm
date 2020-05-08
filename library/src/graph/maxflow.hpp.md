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


# :warning: src/graph/maxflow.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#5442c8f317d712204bf06ed26672e17c">src/graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/graph/maxflow.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/*
struct E {
    int to, rev, cap;
};
VV<E> g;
auto add_edge = [&](int from, int to, int cap) {
    g[from].push_back(E{to, int(g[to].size()), cap});
    g[to].push_back(E{from, int(g[from].size())-1, 0});
};
*/

template<class C>
struct MaxFlow {
    C flow;
    V<char> dual;  // false: S-side true: T-side
};

template<class C, class E>
struct MFExec {
    static constexpr C INF = numeric_limits<C>::max();
    C eps;
    VV<E>& g;
    int s, t;
    V<int> level, iter;

    C dfs(int v, C f) {
        if (v == t) return f;
        C res = 0;
        for (int& i = iter[v]; i < int(g[v].size()); i++) {
            E& e = g[v][i];
            if (e.cap <= eps || level[v] >= level[e.to]) continue;
            C d = dfs(e.to, min(f, e.cap));
            e.cap -= d;
            g[e.to][e.rev].cap += d;
            res += d;
            f -= d;
            if (f == 0) break;
        }
        return res;
    }

    MaxFlow<C> info;
    MFExec(VV<E>& _g, int _s, int _t, C _eps)
        : eps(_eps), g(_g), s(_s), t(_t) {
        int N = int(g.size());

        C& flow = (info.flow = 0);
        while (true) {
            queue<int> que;
            level = V<int>(N, -1);
            level[s] = 0;
            que.push(s);
            while (!que.empty()) {
                int v = que.front(); que.pop();
                for (E e: g[v]) {
                    if (e.cap <= eps || level[e.to] >= 0) continue;
                    level[e.to] = level[v] + 1;
                    que.push(e.to);
                }
            }
            if (level[t] == -1) break;
            iter = V<int>(N, 0);
            while (true) {
                C f = dfs(s, INF);
                if (!f) break;
                flow += f;
            }
        }
        for (int i = 0; i < N; i++) info.dual.push_back(level[i] == -1);
    }
};

template<class C, class E>
MaxFlow<C> get_mf(VV<E>& g, int s, int t, C eps) {
    return MFExec<C, E>(g, s, t, eps).info;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/graph/maxflow.hpp"
/*
struct E {
    int to, rev, cap;
};
VV<E> g;
auto add_edge = [&](int from, int to, int cap) {
    g[from].push_back(E{to, int(g[to].size()), cap});
    g[to].push_back(E{from, int(g[from].size())-1, 0});
};
*/

template<class C>
struct MaxFlow {
    C flow;
    V<char> dual;  // false: S-side true: T-side
};

template<class C, class E>
struct MFExec {
    static constexpr C INF = numeric_limits<C>::max();
    C eps;
    VV<E>& g;
    int s, t;
    V<int> level, iter;

    C dfs(int v, C f) {
        if (v == t) return f;
        C res = 0;
        for (int& i = iter[v]; i < int(g[v].size()); i++) {
            E& e = g[v][i];
            if (e.cap <= eps || level[v] >= level[e.to]) continue;
            C d = dfs(e.to, min(f, e.cap));
            e.cap -= d;
            g[e.to][e.rev].cap += d;
            res += d;
            f -= d;
            if (f == 0) break;
        }
        return res;
    }

    MaxFlow<C> info;
    MFExec(VV<E>& _g, int _s, int _t, C _eps)
        : eps(_eps), g(_g), s(_s), t(_t) {
        int N = int(g.size());

        C& flow = (info.flow = 0);
        while (true) {
            queue<int> que;
            level = V<int>(N, -1);
            level[s] = 0;
            que.push(s);
            while (!que.empty()) {
                int v = que.front(); que.pop();
                for (E e: g[v]) {
                    if (e.cap <= eps || level[e.to] >= 0) continue;
                    level[e.to] = level[v] + 1;
                    que.push(e.to);
                }
            }
            if (level[t] == -1) break;
            iter = V<int>(N, 0);
            while (true) {
                C f = dfs(s, INF);
                if (!f) break;
                flow += f;
            }
        }
        for (int i = 0; i < N; i++) info.dual.push_back(level[i] == -1);
    }
};

template<class C, class E>
MaxFlow<C> get_mf(VV<E>& g, int s, int t, C eps) {
    return MFExec<C, E>(g, s, t, eps).info;
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

