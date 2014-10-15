struct TMatrix {
    typedef ll D;
    const D INF = 1LL<<50;
    vector<valarray<D>> d;
    int N, M;
    TMatrix(int n, int m, bool f = false) {
        N = n; M = m;
        d.resize(n);
        for (int i = 0; i < N; i++) {
            d[i] = valarray<D>(INF, m);
        }
        if (f) {
            assert(N==M);
            for (int i = 0; i < N; i++) d[i][i] = 0;
        }
    }
    valarray<D>& operator[](int p) {
        return d[p];
    }
    
    const valarray<D>& operator[](int p) const {
        return d[p];
    }
    
    TMatrix& operator=(const TMatrix &other) {
        assert(other.N == N && other.M == M);
        copy_n(other.d.begin(), N, d.begin());
        return *this;
    }
    
    TMatrix operator*(const TMatrix &right) {
        assert(M == right.N);
        TMatrix res(N, right.M), r(right.M, right.N);
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

    TMatrix pow(ll p) {
        TMatrix res(N, M, true), buf = *this;
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