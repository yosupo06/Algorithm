template <int N, ll MD>
struct SMatrix {
    using D = ll;
    D *d;
    SMatrix() {
        d = new D[N*N]();
    }
    SMatrix(const SMatrix &r) {
        d = new D[N*N]();
        *this = r;
    }
    ~SMatrix() {
        delete[] d;
    }

    D* operator[](int p) {
        return d+(N*p);
    }
    
    D* operator[](int p) const {
        return d+(N*p);
    }
    
    SMatrix& operator=(const SMatrix &r) {
        memcpy(d, r.d, N*N*sizeof(D));
        return *this;
    }

    SMatrix operator+(const SMatrix &right) {
        SMatrix res;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                res[i][j] = d[i*N+j]+right[i][j];
                if (res[i][j] >= MD) res[i][j] -= MD;
            }
        }
        return res;
    }
    
    SMatrix operator*(const SMatrix &right) {
        SMatrix res, r;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                r[i][j] = right[j][i]; 
            }
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++) {
                    res[i][j] += d[i*N+k]*r[j][k];
                    if (res[i][j] >= MD*MD) res[i][j] -= MD*MD;
                }
                res[i][j] %= MD;
            }
        }
        return res;
    }

    SMatrix pow(ll p) {
        SMatrix res, buf = *this;
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
};