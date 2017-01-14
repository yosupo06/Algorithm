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
