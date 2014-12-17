template <int N>
struct SMatrix {
    int d[MN][MN];
    typedef double D;
    vector<valarray<D>> d;
    int N, M;
    SMatrix(int n, int m) {
        N = n; M = m;
        d.resize(n);
        for (int i = 0; i < N; i++) {
            d[i] = valarray<D>(D(0), m);
        }
    }

    valarray<D>& operator[](int p) {
        return d[p];
    }
    
    const valarray<D>& operator[](int p) const {
        return d[p];
    }
    
    SMatrix& operator=(const SMatrix &other) {
        assert(other.N == N && other.M == M);
        copy_n(other.d.begin(), N, d.begin());
        return *this;
    }

    SMatrix operator+(const SMatrix &right) {
        assert(right.N == N && right.M == M);
        SMatrix res(N, M);
        for (int i = 0; i < N; i++) {
            res[i] = d[i]+right[i];
        }
        return res;
    }
    
    SMatrix operator*(const SMatrix &right) {
        assert(M == right.N);
        SMatrix res(N, right.M), r(right.M, right.N);
        for (int i = 0; i < right.M; i++) {
            for (int j = 0; j < right.N; j++) {
                r[i][j] = right[j][i]; 
            }
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < right.M; j++) {
                res[i][j] = (d[i]*r[j]).sum();
            }
        }
        return res;
    }

    SMatrix operator*(const D x) {
        SMatrix res(N, M);
        for (int i = 0; i < N; i++) {
            res[i] = d[i]*x;
        }
        return res;
    }

    SMatrix pow(ll p) {
        assert(N == M);
        SMatrix res(N, M), buf = *this;
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
    
    void mulL(int i, D x) {
        d[i] *= x;
    }
    
    void excL(int i, int j) {
        swap(d[i], d[j]);
    }
    //line i -> i+(j*x)
    void addL(int i, int j, D x) {
        d[i] += d[j]*x;
    }
    
    int inverse() {
        assert(N == M);
        SMatrix r(N, N);
        for (int i = 0; i < N; i++) r[i][i] = D(1);
        for (int i = 0; i < N; i++) {
            if (d[i][i] == 0) {
                int j;
                for (j = i+1; j < N; j++) {
                    if (abs(d[i][j]) > EPS) { //TODO: EPS
                        r.excL(i, j);
                        excL(i, j);
                        break;
                    }
                }
                if (j == N) return i;
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