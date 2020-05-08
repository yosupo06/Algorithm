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


# :warning: src/datastructure/convexhull.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#057cdb199a48f765d2786c323ec11d3a">src/datastructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/datastructure/convexhull.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<class T>
struct ConvexHull {
    using L = array<T, 2>;

    bool que_incr;
    ConvexHull(bool _que_incr) : que_incr(_que_incr) {}

    deque<L> lines;
    // can remove mid?
    static bool is_need(L mid, L left, L right) {
        assert(left[0] <= mid[0] && mid[0] <= right[0]);
        return (right[0]-mid[0])*(left[1]-mid[1]) < (mid[0]-left[0])*(mid[1]-right[1]);
    }
    //work with 2^(60 + 64)
    /*static bool is_need(L mid, L left, L right) {
        assert(left[0] <= mid[0] && mid[0] <= right[0]);
        ll a = (right[0]-mid[0]), b = (left[1]-mid[1]), c = (mid[0]-left[0]), d = (mid[1]-right[1]);
        long double x = (long double)(a) * b - (long double)(c) * d;
        if (abs(x) > (1LL << 60)) return x < 0;
        int fl = b < 0, fr = d < 0;
        if (fl != fr) return fl == 1;
        ull z = ull(a) * ull(abs(b)) - ull(c) * ull(abs(d));
        if (fl == 0) return (1ULL << 63) < z;
        return z < (1ULL << 63);
    }*/

    void insert_front(L l) {
        if (lines.empty()) {
            lines.push_front(l);
            return;
        }
        assert(l[0] <= lines[0][0]);
        if (l[0] == lines[0][0]) {
            if (l[1] <= lines[0][1]) return;
            lines.pop_front();
        }
        while (lines.size() >= 2 && !is_need(lines.front(), l, lines[1])) {
            lines.pop_front();
        }
        lines.push_front(l);
    }
    void insert_back(L l) {
        if (lines.empty()) {
            lines.push_back(l);
            return;
        }
        assert(lines.back()[0] <= l[0]);
        if (lines.back()[0] == l[0]) {
            if (l[1] <= lines.back()[1]) return;
            lines.pop_back();
        }
        while (lines.size() >= 2 && !is_need(lines.back(), lines[lines.size()-2], l)) {
            lines.pop_back();
        }
        lines.push_back(l);
    }
    /**
    Insert line
    line's degree must be minimum or maximum
     */
    void insert_line(L line) {
        if (lines.empty()) {
            lines.push_back(line);
            return;
        }
        if (line[0] <= lines[0][0]) insert_front(line);
        else if (lines.back()[0] <= line[0]) insert_back(line);
        else assert(false); //line's degree must be minimum or maximum
    }
    /// get maximum y
    T b_x;
    T first = true;
    T max_y(T x) {
        assert(lines.size());
        auto value = [&](L l) { return l[0] * x + l[1]; };
        if (que_incr) {
            assert(first || b_x <= x);
            first = false; b_x = x;
            while (lines.size() >= 2 &&
                   value(lines[0]) <= value(lines[1])) {
                lines.pop_front();
            }
            return value(lines.front());
        } else {
            assert(first || x <= b_x);
            first = false; b_x = x;
            while (lines.size() >= 2 &&
                   value(lines[lines.size()-2]) >= value(lines.back())) {
                lines.pop_back();
            }
            return value(lines.back());
        }
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/datastructure/convexhull.hpp"
template<class T>
struct ConvexHull {
    using L = array<T, 2>;

    bool que_incr;
    ConvexHull(bool _que_incr) : que_incr(_que_incr) {}

    deque<L> lines;
    // can remove mid?
    static bool is_need(L mid, L left, L right) {
        assert(left[0] <= mid[0] && mid[0] <= right[0]);
        return (right[0]-mid[0])*(left[1]-mid[1]) < (mid[0]-left[0])*(mid[1]-right[1]);
    }
    //work with 2^(60 + 64)
    /*static bool is_need(L mid, L left, L right) {
        assert(left[0] <= mid[0] && mid[0] <= right[0]);
        ll a = (right[0]-mid[0]), b = (left[1]-mid[1]), c = (mid[0]-left[0]), d = (mid[1]-right[1]);
        long double x = (long double)(a) * b - (long double)(c) * d;
        if (abs(x) > (1LL << 60)) return x < 0;
        int fl = b < 0, fr = d < 0;
        if (fl != fr) return fl == 1;
        ull z = ull(a) * ull(abs(b)) - ull(c) * ull(abs(d));
        if (fl == 0) return (1ULL << 63) < z;
        return z < (1ULL << 63);
    }*/

    void insert_front(L l) {
        if (lines.empty()) {
            lines.push_front(l);
            return;
        }
        assert(l[0] <= lines[0][0]);
        if (l[0] == lines[0][0]) {
            if (l[1] <= lines[0][1]) return;
            lines.pop_front();
        }
        while (lines.size() >= 2 && !is_need(lines.front(), l, lines[1])) {
            lines.pop_front();
        }
        lines.push_front(l);
    }
    void insert_back(L l) {
        if (lines.empty()) {
            lines.push_back(l);
            return;
        }
        assert(lines.back()[0] <= l[0]);
        if (lines.back()[0] == l[0]) {
            if (l[1] <= lines.back()[1]) return;
            lines.pop_back();
        }
        while (lines.size() >= 2 && !is_need(lines.back(), lines[lines.size()-2], l)) {
            lines.pop_back();
        }
        lines.push_back(l);
    }
    /**
    Insert line
    line's degree must be minimum or maximum
     */
    void insert_line(L line) {
        if (lines.empty()) {
            lines.push_back(line);
            return;
        }
        if (line[0] <= lines[0][0]) insert_front(line);
        else if (lines.back()[0] <= line[0]) insert_back(line);
        else assert(false); //line's degree must be minimum or maximum
    }
    /// get maximum y
    T b_x;
    T first = true;
    T max_y(T x) {
        assert(lines.size());
        auto value = [&](L l) { return l[0] * x + l[1]; };
        if (que_incr) {
            assert(first || b_x <= x);
            first = false; b_x = x;
            while (lines.size() >= 2 &&
                   value(lines[0]) <= value(lines[1])) {
                lines.pop_front();
            }
            return value(lines.front());
        } else {
            assert(first || x <= b_x);
            first = false; b_x = x;
            while (lines.size() >= 2 &&
                   value(lines[lines.size()-2]) >= value(lines.back())) {
                lines.pop_back();
            }
            return value(lines.back());
        }
    }
};

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

