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


# :heavy_check_mark: src/string/onlinez.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#ec86b6e05e7d09e98d071ea841edf05f">src/string</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/string/onlinez.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Verified with

* :heavy_check_mark: <a href="../../../verify/src/online-zalgo.test.cpp.html">src/online-zalgo.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once

struct OnlineZ {
    string s;
    V<int> mp = {-1}, nx;
    int j = -1;
    V<int> inc(char c) {
        // calc nx
        s.push_back(c);
        if (mp.back() == -1)
            nx.push_back(-1);
        else
            nx.push_back(s[mp.back()] != c ? mp.back() : nx[mp.back()]);
        // calc mp
        int i = int(s.size()) - 1;
        while (j >= 0 && s[i] != s[j]) j = mp[j];
        j++;
        mp.push_back(j);

        V<int> res;
        int u = nx.back();
        while (u != -1) {
            if (s[u] != c) {
                res.push_back(int(s.size()) - 1 - u);
                u = mp[u];
            } else {
                u = nx[u];
            }
        }
        return res;
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "src/string/onlinez.hpp"

struct OnlineZ {
    string s;
    V<int> mp = {-1}, nx;
    int j = -1;
    V<int> inc(char c) {
        // calc nx
        s.push_back(c);
        if (mp.back() == -1)
            nx.push_back(-1);
        else
            nx.push_back(s[mp.back()] != c ? mp.back() : nx[mp.back()]);
        // calc mp
        int i = int(s.size()) - 1;
        while (j >= 0 && s[i] != s[j]) j = mp[j];
        j++;
        mp.push_back(j);

        V<int> res;
        int u = nx.back();
        while (u != -1) {
            if (s[u] != c) {
                res.push_back(int(s.size()) - 1 - u);
                u = mp[u];
            } else {
                u = nx[u];
            }
        }
        return res;
    }
};

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

