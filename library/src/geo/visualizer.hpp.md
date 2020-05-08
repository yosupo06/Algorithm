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


# :warning: src/geo/visualizer.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#0a5d4e383899a81c6f7ba383cf1d6fea">src/geo</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/geo/visualizer.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct Vis {
    struct Col {
        int r, g, b;
    };
    FILE* fp;
    D off, f;
    Vis(string s, D d, D u) : off(d), f(1000 / (u - d)) {
        fp = fopen(s.c_str(), "w");
        fprintf(
                fp,
                "<html><head><script>"
                "onload = function draw() {"
                "var cv = document.getElementById('c');"
                "var ct = cv.getContext('2d');");
    }
    D norm(D x) { return (x - off) * f; }
    void set_col(Col c) {
        fprintf(fp, "ct.fillStyle = \"rgb(%d, %d, %d)\";", c.r, c.g, c.b);
        fprintf(fp, "ct.strokeStyle = \"rgb(%d, %d, %d)\";", c.r, c.g, c.b);
    }
    void line(L l, Col col = {0, 0, 0}) {
        set_col(col);
        fprintf(fp,
                "ct.beginPath();"
                "ct.moveTo(%Lf, %Lf);"
                "ct.lineTo(%Lf, %Lf);"
                "ct.closePath();"
                "ct.stroke();",
                norm(l.s.x), norm(l.s.y), norm(l.t.x), norm(l.t.y));
    }
    void point(P p, Col col = {0, 0, 0}) {
        set_col(col);
        fprintf(fp,
                "ct.beginPath();"
                "ct.arc(%Lf, %Lf, 2, 0, Math.PI * 2, true);"
                "ct.fill();",
                norm(p.x), norm(p.y));
    }
    ~Vis() {
        fprintf(fp,
                "}</script></head><body>"
                "<canvas id=\"c\" width=\"1000\" height=\"1000\">"
                "</canvas></body></html>");
        fclose(fp);
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/geo/visualizer.hpp"
struct Vis {
    struct Col {
        int r, g, b;
    };
    FILE* fp;
    D off, f;
    Vis(string s, D d, D u) : off(d), f(1000 / (u - d)) {
        fp = fopen(s.c_str(), "w");
        fprintf(
                fp,
                "<html><head><script>"
                "onload = function draw() {"
                "var cv = document.getElementById('c');"
                "var ct = cv.getContext('2d');");
    }
    D norm(D x) { return (x - off) * f; }
    void set_col(Col c) {
        fprintf(fp, "ct.fillStyle = \"rgb(%d, %d, %d)\";", c.r, c.g, c.b);
        fprintf(fp, "ct.strokeStyle = \"rgb(%d, %d, %d)\";", c.r, c.g, c.b);
    }
    void line(L l, Col col = {0, 0, 0}) {
        set_col(col);
        fprintf(fp,
                "ct.beginPath();"
                "ct.moveTo(%Lf, %Lf);"
                "ct.lineTo(%Lf, %Lf);"
                "ct.closePath();"
                "ct.stroke();",
                norm(l.s.x), norm(l.s.y), norm(l.t.x), norm(l.t.y));
    }
    void point(P p, Col col = {0, 0, 0}) {
        set_col(col);
        fprintf(fp,
                "ct.beginPath();"
                "ct.arc(%Lf, %Lf, 2, 0, Math.PI * 2, true);"
                "ct.fill();",
                norm(p.x), norm(p.y));
    }
    ~Vis() {
        fprintf(fp,
                "}</script></head><body>"
                "<canvas id=\"c\" width=\"1000\" height=\"1000\">"
                "</canvas></body></html>");
        fclose(fp);
    }
};

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

