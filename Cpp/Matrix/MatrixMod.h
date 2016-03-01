/**
 * 行列ライブラリ with Mod
 */
template<ll MD>
struct Matrix {
    using D = ModInt<MD>;
    vector<vector<D>> d;
    int N, M;
    Matrix(int N, int M) : N(N), M(M),
        d(vector<vector<D>>(N, vector<D>(M, D(0)))) {}

    vector<D>& operator[](int p) {return d[p];}
    const vector<D>& operator[](int p) const {return d[p];}

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
        assert(M = right.N);
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
        
    void mulL(int i, D x) {
        for (int j = 0; j < M; j++) {
            d[i][j] *= x;
        }
    }
    
    void excL(int i, int j) {
        swap(d[i], d[j]);
    }
    //line i -> i+(j*x)
    void addL(int i, int j, D x) {
        for (int k = 0; k < M; k++) {
            d[i][k] += d[j][k]*x;
        }
    }
    
    int rnk() {
        for (int i = 0; i < N; i++) {
            if (d[i][i].value() == 0) {
                int j;
                for (j = i+1; j < N; j++) {
                    if (d[j][i].value()) {
                        excL(i, j);
                        break;
                    }
                }
                if (j == N) return i;
            }
            mulL(i, D::inv(d[i][i]));
            for (int j = i+1; j < N; j++) {
                addL(j, i, d[j][i] * D(-1));
            }
        }
        return N;
    }
};