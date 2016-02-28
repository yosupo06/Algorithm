/**
 * 行列ライブラリ
 */
struct Matrix {
    using D = long double;
    vector<vector<D>> d;
    int N, M;
    Matrix(int N, int M) : N(N), M(M) {
        d.resize(N);
        for (int i = 0; i < N; i++) {
            d[i] = vector<D>(M, D(0));
        }
    }

    vector<D>& operator[](int p) { return d[p]; }
    const vector<D>& operator[](int p) const { return d[p]; }
    
    Matrix& operator=(const Matrix &other) {
        assert(other.N == N && other.M == M);
        copy_n(other.d.begin(), N, d.begin());
        return *this;
    }

    Matrix operator+(const Matrix &right) {
        assert(right.N == N && right.M == M);
        Matrix res(N, M);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                res[i][j] = d[i][j]+right[i][j];
            }
        }
        return res;
    }
    
    Matrix operator*(const Matrix &right) {
        assert(M == right.N);
        Matrix res(N, right.M), r(right.M, right.N);
        for (int i = 0; i < right.M; i++) {
            for (int j = 0; j < right.N; j++) {
                r[i][j] = right[j][i]; 
            }
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < right.M; j++) {
                for (int k = 0; k < M; k++) {
                    res[i][j] += d[i][k]*r[j][k];
                }
            }
        }
        return res;
    }

    Matrix operator*(const D x) {
        Matrix res(N, M);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                res[i][j] = d[i][j]*x;
            }
        }
        return res;
    }

    Matrix pow(ll p) {
        assert(N == M);
        Matrix res(N, M), buf = *this;
        for (int i = 0; i < N; i++) res[i][i] = D(1);
        while(p != 0) {
            if (p % 2) {
                res = res*buf;
            }
            p /= 2;
            buf = buf*buf;
        }
        return res;
    }

    using QR = pair<Matrix, Matrix>; // Q*, R
    QR qr() {
        assert(N <= M);
        Matrix A = *this;
        Matrix B(N, N);
        for (int i = 0; i < N; i++) {
            B[i][i] = 1;
        }
        for (int i = 0; i < N; i++) {
            for (int j = i+1; j < N; j++) {
                double r = hypot(A[i][i], A[j][i]);
                if (abs(r) <= 1e-11) continue;
                double c = A[i][i]/r;
                double s = A[j][i]/r;
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
        return make_pair(B, A);
    }
    static Matrix solve(QR q, Matrix ar) {
        int N = q.first.N, M = q.second.M;
        assert(ar.N == M && ar.M == 1);
        auto b = q.first*ar;
        Matrix ans(M, 1);
        for (int i = M-1; i >= 0; i--) {
            ans[i][0] = b[i][0];
            for (int j = i+1; j < b.N; j++) {
                ans[i][0] -= q.second[i][j] * ans[j][0];
            }
            ans[i][0] /= q.second[i][i];
        }
        return ans;
    }


    void mulL(int i, D x) {
        for (int j = 0; j < M; j++) {
            d[i][j] *= x;
        }
    }
    
    void excL(int i, int j) {
        for (int k = 0; k < M; k++) {
            swap(d[i][k], d[j][k]);
        }
    }
    //line i -> i+(j*x)
    void addL(int i, int j, D x) {
        for (int k = 0; k < M; k++) {
            d[i][k] += d[j][k]*x;
        }
    }
    
    int inverse() {
        assert(N == M);
        Matrix r(N, N);
        for (int i = 0; i < N; i++) r[i][i] = D(1);
        for (int i = 0; i < N; i++) {
            if (abs(d[i][i]) <= 1e-11) {
                D md = -1;
                int mj = -1;
                for (int j = i+1; j < N; j++) {
                    if (md < abs(d[i][j])) {
                        md = abs(d[i][j]);
                        mj = j;
                    }
                }
                assert(mj != -1);
                r.excL(i, mj);
                excL(i, mj);
            }
            r.mulL(i, 1/d[i][i]);
            mulL(i, 1/d[i][i]);
            for (int j = 0; j < N; j++) {
                if (i == j) continue;
                r.addL(j, i, -d[j][i]);
                addL(j, i, -d[j][i]);
            }
        }
        *this = r;
        return N;
    }
};
