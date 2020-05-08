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


# :warning: src/math/qr.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#fb2ef479237c7a939531a404fd0e5cb7">src/math</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/math/qr.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:35:33+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<class T>
struct QR {
    Matrix<T> q, r;
    static QR decomp(const Matrix<T> &x, T eps) {
        int N = x.N, M = x.M;
        assert(N <= M);
        Matrix<T> A = x;
        Matrix<T> B(N, N);
        for (int i = 0; i < N; i++) {
            B[i][i] = 1;
        }
        for (int i = 0; i < N; i++) {
            for (int j = i+1; j < N; j++) {
                T r = hypot(A[i][i], A[j][i]);
                if (abs(r) <= eps) continue;
                T c = A[i][i]/r, s = A[j][i]/r;
                for (int k = i; k < M; k++) {
                    tie(A[i][k], A[j][k]) =
                        make_pair(c*A[i][k]+s*A[j][k], -s*A[i][k]+c*A[j][k]);
                }
                for (int k = 0; k < N; k++) {
                    tie(B[i][k], B[j][k]) =
                        make_pair(c*B[i][k]+s*B[j][k], -s*B[i][k]+c*B[j][k]);
                }
                if (A[i][i] == 0) {
                    // not full rank
                    assert(false);
                }
            }
        }
        return QR{B, A};
    }
    static Matrix<T> solve(QR<T> qr, Matrix<T> ar) {
        int N = qr.q.N, M = qr.r.M;
        assert(ar.N == M && ar.M == 1);
        auto b = qr.q*ar;
        Matrix<T> ans(M, 1);
        for (int i = M-1; i >= 0; i--) {
            ans[i][0] = b[i][0];
            for (int j = i+1; j < b.N; j++) {
                ans[i][0] -= qr.r[i][j] * ans[j][0];
            }
            ans[i][0] /= qr.r[i][i];
        }
        return ans;
    }    
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/math/qr.hpp"
template<class T>
struct QR {
    Matrix<T> q, r;
    static QR decomp(const Matrix<T> &x, T eps) {
        int N = x.N, M = x.M;
        assert(N <= M);
        Matrix<T> A = x;
        Matrix<T> B(N, N);
        for (int i = 0; i < N; i++) {
            B[i][i] = 1;
        }
        for (int i = 0; i < N; i++) {
            for (int j = i+1; j < N; j++) {
                T r = hypot(A[i][i], A[j][i]);
                if (abs(r) <= eps) continue;
                T c = A[i][i]/r, s = A[j][i]/r;
                for (int k = i; k < M; k++) {
                    tie(A[i][k], A[j][k]) =
                        make_pair(c*A[i][k]+s*A[j][k], -s*A[i][k]+c*A[j][k]);
                }
                for (int k = 0; k < N; k++) {
                    tie(B[i][k], B[j][k]) =
                        make_pair(c*B[i][k]+s*B[j][k], -s*B[i][k]+c*B[j][k]);
                }
                if (A[i][i] == 0) {
                    // not full rank
                    assert(false);
                }
            }
        }
        return QR{B, A};
    }
    static Matrix<T> solve(QR<T> qr, Matrix<T> ar) {
        int N = qr.q.N, M = qr.r.M;
        assert(ar.N == M && ar.M == 1);
        auto b = qr.q*ar;
        Matrix<T> ans(M, 1);
        for (int i = M-1; i >= 0; i--) {
            ans[i][0] = b[i][0];
            for (int j = i+1; j < b.N; j++) {
                ans[i][0] -= qr.r[i][j] * ans[j][0];
            }
            ans[i][0] /= qr.r[i][i];
        }
        return ans;
    }    
};

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

