/**
 * 行列ライブラリ with トロピカル
 */
struct Matrix {
    typedef ll D;
    const D INF = 1LL<<50;
    vector<valarray<D>> d;
    int N, M;
    Matrix(int N, int M) : N(N), M(M) {
        d.resize(N);
        for (int i = 0; i < N; i++) {
            d[i] = valarray<D>(INF, M);
        }
    }

    valarray<D>& operator[](int p) {
        return d[p];
    }
    
    const valarray<D>& operator[](int p) const {
        return d[p];
    }
    
    Matrix& operator=(const Matrix &other) {
        assert(other.N == N && other.M == M);
        copy_n(other.d.begin(), N, d.begin());
        return *this;
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
                res[i][j] = (d[i]+r[j]).min();
            }
        }
        return res;
    }

    Matrix pow(ll p) {
        assert(N == M);
        Matrix res(N, M), buf = *this;
        for (int i = 0; i < N; i++) res[i][i] = D(0);
        while(p != 0) {
            if (p % 2) {
                res = res*buf;
            }
            p /= 2;
            buf = buf*buf;
        }
        return res;
    }
};