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
    
    const MatrixMod2 operator+(const MatrixMod2 &right) const {
        MatrixMod2 res(N, M);
        for (int i = 0; i < N; i++) {
            res[i] = d[i]^right[i];
        }
        return res;
    }
    
    template<int K>
    const MatrixMod2<N, K> operator*(const MatrixMod2<M, K> &right) const {
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
};
