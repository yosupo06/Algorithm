template<class D>
Matrix<D> inverse(Matrix<D> x, D eps) {
    assert(x.N == x.M);
    int N = x.N;
    Matrix<D> r(N, N);
    for (int i = 0; i < N; i++) r[i][i] = D(1);
    for (int i = 0; i < N; i++) {
        if (abs(x[i][i]) <= eps) {
            D md = eps;
            int mj = -1;
            for (int j = i+1; j < N; j++) {
                if (md < abs(x[j][i])) {
                    md = abs(x[j][i]);
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
                if (md < abs(x[j][i])) {
                    md = abs(x[j][i]);
                    mj = j;
                }
            }
            if (abs(md) <= eps) return -1;
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


// for modint
template<class D>
D det(Matrix<D> x) {
    int N = x.N, M = x.M;
    assert(N == M);
    Mint base = 1;
    for (int i = 0; i < N; i++) {
        if (!x[i][i].v) {
            for (int j = i+1; j < N; j++) {
                if (x[j][i].v) {
                    swap(x[i], x[j]);
                    if ((j-i)%2) base = Mint(0)-base;
                    break;
                }
            }
            if (!x[i][i].v) return 0;
        }
        //determinent *= m?
        base *= x[i][i];
        D im = D::inv(x[i][i]);
        for (int j = 0; j < M; j++) {
            x[i][j] *= im;
        }
        //no relation to determinent
        for (int j = i+1; j < N; j++) {
            D m = x[j][i];
            for (int k = 0; k < M; k++) {
                x[j][k] -= x[i][k]*m;
            }
        }
    }
    for (int i = 0; i < N; i++) {
        base *= x[i][i];
    }
    return base;
}
