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


# :heavy_check_mark: src/graph/primitive.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#5442c8f317d712204bf06ed26672e17c">src/graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/graph/primitive.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-26 02:54:27+09:00




## Required by

* :heavy_check_mark: <a href="treedecomp.hpp.html">src/graph/treedecomp.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../../verify/src/treedecomp_width2.test.cpp.html">src/treedecomp_width2.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

struct SimpleEdge {
    int to;
};
ostream& operator<<(ostream& os, const SimpleEdge& e) {
    return os << "E(" << e.to << ")";
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "src/graph/primitive.hpp"

struct SimpleEdge {
    int to;
};
ostream& operator<<(ostream& os, const SimpleEdge& e) {
    return os << "E(" << e.to << ")";
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

