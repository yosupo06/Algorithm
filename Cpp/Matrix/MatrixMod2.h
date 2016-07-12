
/**
 * 行列ライブラリ with Mod2
 */
template<int N, int M>
struct MatrixMod2 {
    array<bitset<M>, N> d;

    MatrixMod2() {
        for (int i = 0; i < N; i++) {
            d[i].reset();
        }
    }

    bitset<M>& operator[](int p) {return d[p];}
    const bitset<M>& operator[](int p) const {return d[p];}
    
    MatrixMod2& operator=(const MatrixMod2 &other) {
        d = other.d;
        return *this;
    }

    MatrixMod2 operator+(const MatrixMod2 &right) const {
        MatrixMod2 res(N, M);
        for (int i = 0; i < N; i++) {
            res[i] = d[i]^right[i];
        }
        return res;
    }
    
    template<int K>
    MatrixMod2<N, K> operator*(const MatrixMod2<M, K> &right) const {
        MatrixMod2<N, K> res;
        MatrixMod2<K, M> r;
        for (int i = 0; i < K; i++) {
            for (int j = 0; j < M; j++) {
                r[i][j] = right[j][i]; 
            }
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < K; j++) {
                res[i][j] = (d[i]&r[j]).count() % 2;
            }
        }
        return res;
    }

    MatrixMod2 pow(ll p) {
        assert(N == M);
        MatrixMod2<N, M> res, buf = *this;
        for (int i = 0; i < N; i++) res[i][i] = true;
        while(p != 0) {
            if (p % 2) {
                res = res*buf;
            }
            p /= 2;
            buf = buf*buf;
        }
        return res;
    }

    int inverse() {
        assert(N == M);
        MatrixMod2 r;
        for (int i = 0; i < N; i++) r[i][i] = true;
        for (int i = 0; i < N; i++) {
            if (!d[i][i]) {
                int j;
                for (j = i+1; j < N; j++) {
                    if (d[j][i]) {
                        swap(d[i], d[j]);
                        swap(r[i], r[j]);
                        break;
                    }
                }
                if (j == N) return i;
            }
            for (int j = 0; j < N; j++) {
                if (i == j) continue;
                if (d[j][i]) {
                    d[j] ^= d[i];
                    r[j] ^= r[i];
                }
            }
        }
        *this = r;
        return N;
    }
};
