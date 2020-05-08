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


# :warning: src/util/stopwatch.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#6433a1a19c7364347102f741d8b9cffd">src/util</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/util/stopwatch.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct StopWatch {
    bool f = false;
    clock_t st;
    void start() {
        f = true;
        st = clock();
    }
    int msecs() {
        assert(f);
        return (clock()-st)*1000 / CLOCKS_PER_SEC;
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/util/stopwatch.hpp"
struct StopWatch {
    bool f = false;
    clock_t st;
    void start() {
        f = true;
        st = clock();
    }
    int msecs() {
        assert(f);
        return (clock()-st)*1000 / CLOCKS_PER_SEC;
    }
};

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

