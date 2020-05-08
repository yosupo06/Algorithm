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


# :warning: src/string/ahocorasick.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#ec86b6e05e7d09e98d071ea841edf05f">src/string</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/string/ahocorasick.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct ACTrie {
    using NP = ACTrie*;
    V<int> acc;
    map<int, NP> next;
    NP fail = nullptr, dnx = nullptr;

  private:
    void add(const string& s, int id, int p = 0) {
        if (p == int(s.size())) {
            acc.push_back(id);
            return;
        }
        if (next[s[p]] == nullptr) {
            next[s[p]] = new ACTrie();
        }
        next[s[p]]->add(s, id, p + 1);
    }
    template <class OP> NP count(OP op, int p) {
        if (fail == nullptr) return this;
        for (int id : acc) {
            op(id, p);
        }
        if (dnx) {
            dnx->count(op, p);
        } else {
            dnx = fail->count(op, p);
        }
        return acc.size() ? this : dnx;
    }

  public:
    // パターンにマッチするたびにop(string ID, 発見位置の終端)を呼び出す
    // 終端が同じで複数マッチする文字列が存在する場合，長い順に呼び出される
    // s = "abaaba", pattern = {"ab", "ba"} なら
    // op(0, 2), op(1, 3), op(0, 5), op(1, 6)
    template <class OP> void match(const string& s, OP op, int p = 0) {
        if (p == int(s.size())) return;
        if (next[s[p]]) {
            next[s[p]]->count(op, p + 1);
            next[s[p]]->match(s, op, p + 1);
        } else {
            if (!fail)
                match(s, op, p + 1);  // root
            else
                fail->match(s, op, p);  // other
        }
    }
    static NP make(V<string> v) {
        NP tr = new ACTrie();
        for (int i = 0; i < int(v.size()); i++) {
            tr->add(v[i], i);
        }
        queue<NP> q;
        q.push(tr);
        tr->fail = nullptr;
        while (!q.empty()) {
            NP ntr = q.front();
            q.pop();
            for (auto p : ntr->next) {
                int i = p.first;
                NP fail = ntr->fail;
                while (fail && !fail->next.count(i)) {
                    fail = fail->fail;
                }
                ntr->next[i]->fail = (fail == nullptr) ? tr : fail->next[i];
                q.push(ntr->next[i]);
            }
        }
        return tr;
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/string/ahocorasick.hpp"
struct ACTrie {
    using NP = ACTrie*;
    V<int> acc;
    map<int, NP> next;
    NP fail = nullptr, dnx = nullptr;

  private:
    void add(const string& s, int id, int p = 0) {
        if (p == int(s.size())) {
            acc.push_back(id);
            return;
        }
        if (next[s[p]] == nullptr) {
            next[s[p]] = new ACTrie();
        }
        next[s[p]]->add(s, id, p + 1);
    }
    template <class OP> NP count(OP op, int p) {
        if (fail == nullptr) return this;
        for (int id : acc) {
            op(id, p);
        }
        if (dnx) {
            dnx->count(op, p);
        } else {
            dnx = fail->count(op, p);
        }
        return acc.size() ? this : dnx;
    }

  public:
    // パターンにマッチするたびにop(string ID, 発見位置の終端)を呼び出す
    // 終端が同じで複数マッチする文字列が存在する場合，長い順に呼び出される
    // s = "abaaba", pattern = {"ab", "ba"} なら
    // op(0, 2), op(1, 3), op(0, 5), op(1, 6)
    template <class OP> void match(const string& s, OP op, int p = 0) {
        if (p == int(s.size())) return;
        if (next[s[p]]) {
            next[s[p]]->count(op, p + 1);
            next[s[p]]->match(s, op, p + 1);
        } else {
            if (!fail)
                match(s, op, p + 1);  // root
            else
                fail->match(s, op, p);  // other
        }
    }
    static NP make(V<string> v) {
        NP tr = new ACTrie();
        for (int i = 0; i < int(v.size()); i++) {
            tr->add(v[i], i);
        }
        queue<NP> q;
        q.push(tr);
        tr->fail = nullptr;
        while (!q.empty()) {
            NP ntr = q.front();
            q.pop();
            for (auto p : ntr->next) {
                int i = p.first;
                NP fail = ntr->fail;
                while (fail && !fail->next.count(i)) {
                    fail = fail->fail;
                }
                ntr->next[i]->fail = (fail == nullptr) ? tr : fail->next[i];
                q.push(ntr->next[i]);
            }
        }
        return tr;
    }
};

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

