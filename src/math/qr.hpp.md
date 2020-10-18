---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"src/math/qr.hpp\"\ntemplate<class T>\nstruct QR {\n    Matrix<T>\
    \ q, r;\n    static QR decomp(const Matrix<T> &x, T eps) {\n        int N = x.N,\
    \ M = x.M;\n        assert(N <= M);\n        Matrix<T> A = x;\n        Matrix<T>\
    \ B(N, N);\n        for (int i = 0; i < N; i++) {\n            B[i][i] = 1;\n\
    \        }\n        for (int i = 0; i < N; i++) {\n            for (int j = i+1;\
    \ j < N; j++) {\n                T r = hypot(A[i][i], A[j][i]);\n            \
    \    if (abs(r) <= eps) continue;\n                T c = A[i][i]/r, s = A[j][i]/r;\n\
    \                for (int k = i; k < M; k++) {\n                    tie(A[i][k],\
    \ A[j][k]) =\n                        make_pair(c*A[i][k]+s*A[j][k], -s*A[i][k]+c*A[j][k]);\n\
    \                }\n                for (int k = 0; k < N; k++) {\n          \
    \          tie(B[i][k], B[j][k]) =\n                        make_pair(c*B[i][k]+s*B[j][k],\
    \ -s*B[i][k]+c*B[j][k]);\n                }\n                if (A[i][i] == 0)\
    \ {\n                    // not full rank\n                    assert(false);\n\
    \                }\n            }\n        }\n        return QR{B, A};\n    }\n\
    \    static Matrix<T> solve(QR<T> qr, Matrix<T> ar) {\n        int N = qr.q.N,\
    \ M = qr.r.M;\n        assert(ar.N == M && ar.M == 1);\n        auto b = qr.q*ar;\n\
    \        Matrix<T> ans(M, 1);\n        for (int i = M-1; i >= 0; i--) {\n    \
    \        ans[i][0] = b[i][0];\n            for (int j = i+1; j < b.N; j++) {\n\
    \                ans[i][0] -= qr.r[i][j] * ans[j][0];\n            }\n       \
    \     ans[i][0] /= qr.r[i][i];\n        }\n        return ans;\n    }    \n};\n"
  code: "template<class T>\nstruct QR {\n    Matrix<T> q, r;\n    static QR decomp(const\
    \ Matrix<T> &x, T eps) {\n        int N = x.N, M = x.M;\n        assert(N <= M);\n\
    \        Matrix<T> A = x;\n        Matrix<T> B(N, N);\n        for (int i = 0;\
    \ i < N; i++) {\n            B[i][i] = 1;\n        }\n        for (int i = 0;\
    \ i < N; i++) {\n            for (int j = i+1; j < N; j++) {\n               \
    \ T r = hypot(A[i][i], A[j][i]);\n                if (abs(r) <= eps) continue;\n\
    \                T c = A[i][i]/r, s = A[j][i]/r;\n                for (int k =\
    \ i; k < M; k++) {\n                    tie(A[i][k], A[j][k]) =\n            \
    \            make_pair(c*A[i][k]+s*A[j][k], -s*A[i][k]+c*A[j][k]);\n         \
    \       }\n                for (int k = 0; k < N; k++) {\n                   \
    \ tie(B[i][k], B[j][k]) =\n                        make_pair(c*B[i][k]+s*B[j][k],\
    \ -s*B[i][k]+c*B[j][k]);\n                }\n                if (A[i][i] == 0)\
    \ {\n                    // not full rank\n                    assert(false);\n\
    \                }\n            }\n        }\n        return QR{B, A};\n    }\n\
    \    static Matrix<T> solve(QR<T> qr, Matrix<T> ar) {\n        int N = qr.q.N,\
    \ M = qr.r.M;\n        assert(ar.N == M && ar.M == 1);\n        auto b = qr.q*ar;\n\
    \        Matrix<T> ans(M, 1);\n        for (int i = M-1; i >= 0; i--) {\n    \
    \        ans[i][0] = b[i][0];\n            for (int j = i+1; j < b.N; j++) {\n\
    \                ans[i][0] -= qr.r[i][j] * ans[j][0];\n            }\n       \
    \     ans[i][0] /= qr.r[i][i];\n        }\n        return ans;\n    }    \n};\n"
  dependsOn: []
  isVerificationFile: false
  path: src/math/qr.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/math/qr.hpp
layout: document
redirect_from:
- /library/src/math/qr.hpp
- /library/src/math/qr.hpp.html
title: src/math/qr.hpp
---
