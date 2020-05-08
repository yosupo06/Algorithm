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


# :warning: src/datastructure/radixheap.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#057cdb199a48f765d2786c323ec11d3a">src/datastructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/datastructure/radixheap.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// D.key must be unsigned integer
template <class D> struct RadixHeap {
    using C = typename make_unsigned<decltype(D().key)>::type;
    static int bsr1(C x) { return (x == 0) ? 0 : bsr(x) + 1; }
    size_t sz = 0, cnt = 0;
    C last = 0;
    VV<D> v = VV<D>(sizeof(C) * 8 + 1);
    RadixHeap() {}
    void push(D x) {
        assert(decltype(x.key)(last) <= x.key);
        sz++;
        v[bsr1(x.key ^ last)].push_back(x);
    }
    void pull() {
        if (cnt < v[0].size()) return;
        int i = 1;
        while (v[i].empty()) i++;
        last = min_element(v[i].begin(), v[i].end(), [&](D l, D r) {
                   return l.key < r.key;
               })->key;
        for (D x : v[i]) {
            v[bsr1(x.key ^ last)].push_back(x);
        }
        v[i].clear();
    }
    D top() {
        pull();
        return v[0][cnt];
    }
    void pop() {
        pull();
        sz--;
        cnt++;
    }
    size_t size() const { return sz; }
    bool empty() const { return sz == 0; }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/datastructure/radixheap.hpp"
// D.key must be unsigned integer
template <class D> struct RadixHeap {
    using C = typename make_unsigned<decltype(D().key)>::type;
    static int bsr1(C x) { return (x == 0) ? 0 : bsr(x) + 1; }
    size_t sz = 0, cnt = 0;
    C last = 0;
    VV<D> v = VV<D>(sizeof(C) * 8 + 1);
    RadixHeap() {}
    void push(D x) {
        assert(decltype(x.key)(last) <= x.key);
        sz++;
        v[bsr1(x.key ^ last)].push_back(x);
    }
    void pull() {
        if (cnt < v[0].size()) return;
        int i = 1;
        while (v[i].empty()) i++;
        last = min_element(v[i].begin(), v[i].end(), [&](D l, D r) {
                   return l.key < r.key;
               })->key;
        for (D x : v[i]) {
            v[bsr1(x.key ^ last)].push_back(x);
        }
        v[i].clear();
    }
    D top() {
        pull();
        return v[0][cnt];
    }
    void pop() {
        pull();
        sz--;
        cnt++;
    }
    size_t size() const { return sz; }
    bool empty() const { return sz == 0; }
};

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

