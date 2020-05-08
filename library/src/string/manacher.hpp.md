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


# :warning: src/string/manacher.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#ec86b6e05e7d09e98d071ea841edf05f">src/string</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/string/manacher.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template <class S> V<int> manacher(const S& s) {
    int n = int(s.size());
    V<int> r(n);
    if (n == 0) return r;
    r[0] = 1;
    for (int i = 1, j = 0; i < n; i++) {
        int& k = r[i];
        k = (j + r[j] <= i) ? 0 : min(j + r[j] - i, r[2 * j - i]);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) k++;
        if (j + r[j] < i + r[i]) j = i;
    }
    return r;
}


template <class S> V<int> manacher_even(const S& s) {
    int n = int(s.size());
    V<int> r(n + 1);
    for (int i = 1, j = 0; i < n; i++) {
        int& k = r[i];
        k = (j + r[j] <= i) ? 0 : min(j + r[j] - i, r[2 * j - i]);
        while (0 <= i - 1 - k && i + k < n && s[i - 1 - k] == s[i + k]) k++;
        if (j + r[j] < i + r[i]) j = i;
    }
    return r;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/string/manacher.hpp"
template <class S> V<int> manacher(const S& s) {
    int n = int(s.size());
    V<int> r(n);
    if (n == 0) return r;
    r[0] = 1;
    for (int i = 1, j = 0; i < n; i++) {
        int& k = r[i];
        k = (j + r[j] <= i) ? 0 : min(j + r[j] - i, r[2 * j - i]);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) k++;
        if (j + r[j] < i + r[i]) j = i;
    }
    return r;
}


template <class S> V<int> manacher_even(const S& s) {
    int n = int(s.size());
    V<int> r(n + 1);
    for (int i = 1, j = 0; i < n; i++) {
        int& k = r[i];
        k = (j + r[j] <= i) ? 0 : min(j + r[j] - i, r[2 * j - i]);
        while (0 <= i - 1 - k && i + k < n && s[i - 1 - k] == s[i + k]) k++;
        if (j + r[j] < i + r[i]) j = i;
    }
    return r;
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

