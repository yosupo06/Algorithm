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


# :warning: src/datastructure/dice.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#057cdb199a48f765d2786c323ec11d3a">src/datastructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/datastructure/dice.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/**
 * +x=0 +y=1 +z=2
 * d = [+x, +y, +z]
 * dir[4] = [+x, +y, -x, -y]
 * Dice(a, b): +x=a +y=bとなるサイコロ生成
 * get(dir): dir方向の値を取得
 * rot(dir): dir方向に転がす
 */
struct Dice {
    int d[3];
    Dice(int a, int b) {
        for (int i = 0; i < 3; i++) {
            d[i] = (a + i) % 3 + a / 3 * 3;
        }
        while (d[1] != b) rot(1);
    }
    int get(int dir) {
        if (dir < 2) {
            return d[dir];
        } else {
            dir -= 2;
            return 5 - d[dir];
        }
    }
    void rot(int dir) {
        int t = d[2];
        if (dir < 2) {
            d[2] = 5 - d[dir];
            d[dir] = t;
        } else {
            dir -= 2;
            d[2] = d[dir];
            d[dir] = 5 - t;
        }
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/datastructure/dice.hpp"
/**
 * +x=0 +y=1 +z=2
 * d = [+x, +y, +z]
 * dir[4] = [+x, +y, -x, -y]
 * Dice(a, b): +x=a +y=bとなるサイコロ生成
 * get(dir): dir方向の値を取得
 * rot(dir): dir方向に転がす
 */
struct Dice {
    int d[3];
    Dice(int a, int b) {
        for (int i = 0; i < 3; i++) {
            d[i] = (a + i) % 3 + a / 3 * 3;
        }
        while (d[1] != b) rot(1);
    }
    int get(int dir) {
        if (dir < 2) {
            return d[dir];
        } else {
            dir -= 2;
            return 5 - d[dir];
        }
    }
    void rot(int dir) {
        int t = d[2];
        if (dir < 2) {
            d[2] = 5 - d[dir];
            d[dir] = t;
        } else {
            dir -= 2;
            d[2] = d[dir];
            d[dir] = 5 - t;
        }
    }
};

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

