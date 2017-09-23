template<class D>
struct Matrix {
    VV<D> d;
    int N, M;
    Matrix(int N, int M) : d(VV<D>(N, V<D>(M))), N(N), M(M) {}

    V<D>& operator[](int p) {return d[p];}
    const V<D>& operator[](int p) const {return d[p];}

    const Matrix operator+(const Matrix &right) const {
        assert(right.N == N && right.M == M);
        Matrix res(N, M);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                res[i][j] = d[i][j]+right[i][j];
            }
        }
        return res;
    }

    const Matrix operator*(const Matrix &right) const {
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

    const Matrix operator*(const D &x) const {
        Matrix res(N, M);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                res[i][j] = d[i][j]*x;
            }
        }
        return res;
    }
};

template<class T>
Matrix<T> pow(Matrix<T> x, ll p) {
    assert(x.N == x.M);
    int N = x.N;
    Matrix<T> res(N, N), buf = x;
    for (int i = 0; i < N; i++) res[i][i] = T(1);
    while(p != 0) {
        if (p % 2) {
            res = res*buf;
        }
        p /= 2;
        buf = buf*buf;
    }
    return res;
}

// m * v = r
template<class Mat>
bool solve_linear(Mat m, Mat r) {
    int N = m.N, M = m.M;
    int c = 0;
    for (int x: rng(M)) {
        int my = -1;
        for (int y: rng(c, N)) {
            if (m[y][x].v) {
                my = y;
                break;
            }
        }
        if (my == -1) continue;
        for (int i: rng(M)) {
            swap(m[c][i], m[my][i]);
        }
        swap(r[c][0], r[my][0]);
        for (int y: rng(N)) {
            if (c == y) continue;
            if (m[y][x].v == 0) continue;
            auto freq = m[y][x] / m[c][x];
            for (int k: rng(M)) {
                m[y][k] -= freq * m[c][k];
            }
            r[y][0] -= freq * r[c][0];
        }
        c++;
        if (c == N) break;
    }
    for (int y: rng(c, N)) {
        if (r[y][0]) return false;
    }
    return true;
}
