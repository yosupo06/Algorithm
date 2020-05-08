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


# :heavy_check_mark: src/datastructure/simplequeue.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#057cdb199a48f765d2786c323ec11d3a">src/datastructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/datastructure/simplequeue.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Required by

* :heavy_check_mark: <a href="../graph/bimaching.hpp.html">src/graph/bimaching.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../../verify/src/bimaching.test.cpp.html">src/bimaching.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

template <class T> struct SimpleQueue {
    V<T> payload;
    size_t pos = 0;
    void reserve(size_t size) { payload.reserve(size); }
    bool empty() const { return pos == payload.size(); }
    void push(const T& t) { payload.push_back(t); }
    T& front() {
        assert(!empty());
        return payload[pos];
    }
    void clear() {
        payload.clear();
        pos = 0;
    }
    void pop() {
        assert(!empty());
        pos++;
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "src/datastructure/simplequeue.hpp"

template <class T> struct SimpleQueue {
    V<T> payload;
    size_t pos = 0;
    void reserve(size_t size) { payload.reserve(size); }
    bool empty() const { return pos == payload.size(); }
    void push(const T& t) { payload.push_back(t); }
    T& front() {
        assert(!empty());
        return payload[pos];
    }
    void clear() {
        payload.clear();
        pos = 0;
    }
    void pop() {
        assert(!empty());
        pos++;
    }
};

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

