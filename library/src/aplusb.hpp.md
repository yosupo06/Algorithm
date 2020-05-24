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
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :heavy_check_mark: src/aplusb.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#25d902c24283ab8cfbac54dfa101ad31">src</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/aplusb.hpp">View this file on GitHub</a>
    - Last commit date: 1970-01-01 00:00:00+00:00




## Verified with

* :heavy_check_mark: <a href="../../verify/src/comb.test.cpp.html">src/comb.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/src/dbg.test.cpp.html">src/dbg.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/src/modint.test.cpp.html">src/modint.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/src/modint61.test.cpp.html">src/modint61.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/src/printer.test.cpp.html">src/printer.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/src/scanner.test.cpp.html">src/scanner.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

#include <iostream>

using namespace std;

void solve_aplusb() {
    int a, b;
    cin >> a >> b;
    cout << a + b << endl;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "src/aplusb.hpp"

#include <iostream>

using namespace std;

void solve_aplusb() {
    int a, b;
    cin >> a >> b;
    cout << a + b << endl;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

