template<class D>
Matrix<D> inverse(Matrix<D> x, D eps) {
    assert(x.N == x.M);
    int N = x.N;
    Matrix<D> r(N, N);
    for (int i = 0; i < N; i++) r[i][i] = D(1);
    for (int i = 0; i < N; i++) {
        if (abs(x[i][i]) <= eps) {
            D md = -1;
            int mj = -1;
            for (int j = i+1; j < N; j++) {
                if (md < abs(x[i][j])) {
                    md = abs(x[i][j]);
                    mj = j;
                }
            }
            assert(mj != -1);
            swap(x[i], x[mj]);
            swap(r[i], r[mj]);
        }
        D m = x[i][i];
        for (int j = 0; j < N; j++) {
            x[i][j] /= m;
            r[i][j] /= m;
        }
        for (int j = 0; j < N; j++) {
            if (i == j) continue;
            D m = x[j][i];
            for (int k = 0; k < N; k++) {
                r[j][k] -= r[i][k]*m;
                x[j][k] -= x[i][k]*m;
            }
        }
    }
    return r;
}

template<class D>
int rnk(Matrix<D> x, D eps) {
    int N = x.N, M = x.M;
    for (int i = 0; i < N; i++) {
        if (abs(x[i][i]) <= eps) {
            D md = -1;
            int mj = -1;
            for (int j = i+1; j < N; j++) {
                if (md < abs(x[i][j])) {
                    md = abs(x[i][j]);
                    mj = j;
                }
            }
            if (mj == -1) return i;
            swap(x[i], x[mj]);
        }
        D m = x[i][i];
        for (int j = 0; j < M; j++) {
            x[i][j] /= m;
        }
        for (int j = i+1; j < N; j++) {
            D m = x[j][i];
            for (int k = 0; k < M; k++) {
                x[j][k] -= x[i][k]*m;
            }
        }
    }
    return N;
}
