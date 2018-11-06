template <class D> struct Mat : VV<D> {
    using VV<D>::VV;
    using VV<D>::size;
    int h() const { return int(size()); }
    int w() const { return int((*this)[0].size()); }
};

template <class D> V<D> solve_linear(Mat<D> a, V<D> b, D eps) {
    int h = a.h(), w = a.w();
    int r = 0;
    V<int> idxs;
    for (int x = 0; x < w; x++) {
        for (int y = r + 1; y < h; y++) {
            D d = hypot(a[r][x], a[y][x]);
            if (abs(d) <= eps) continue;
            D c = a[r][x] / d, s = a[y][x] / d;
            auto rot = [&](D& x, D& y) {
                tie(x, y) = make_pair(c * x + s * y, c * y - s * x);
            };
            rot(b[r], b[y]);
            for (int k = x; k < w; k++) rot(a[r][k], a[y][k]);
        }
        if (a[r][x] <= eps) continue;
        r++;
        idxs.push_back(x);
        if (r == h) break;
    }
    V<D> v(w);
    for (int y = r - 1; y >= 0; y--) {
        int f = idxs[y];
        v[f] = b[y];
        for (int x = f + 1; x < w; x++) {
            v[f] -= a[y][x] * v[x];
        }
        v[f] /= a[y][f];
    }
    return v;
}

template <class Mint> V<Mint> solve_linear(Mat<Mint> a, V<Mint> b) {
    int h = a.h(), w = a.w();
    int r = 0;
    V<int> idxs;
    for (int x = 0; x < w; x++) {
        int my = -1;
        for (int y = r; y < h; y++) {
            if (a[y][x]) {
                my = y;
                break;
            }
        }
        if (my == -1) continue;
        if (r != my) swap(a[r], a[my]);
        swap(b[r], b[my]);
        for (int y = r + 1; y < h; y++) {
            if (!a[y][x]) continue;
            auto freq = a[y][x] / a[r][x];
            for (int k = x; k < w; k++) a[y][k] -= freq * a[r][k];
            b[y] -= freq * b[r];
        }
        r++;
        idxs.push_back(x);
        if (r == h) break;
    }
    V<Mint> v(w);
    for (int y = r - 1; y >= 0; y--) {
        int f = idxs[y];
        v[f] = b[y];
        for (int x = f + 1; x < w; x++) {
            v[f] -= a[y][x] * v[x];
        }
        v[f] /= a[y][f];
    }
    return v;
}

template <class Mint> int calc_rank(Mat<Mint> a) {
    int h = a.h(), w = a.w();
    int r = 0;
    V<int> idxs;
    for (int x = 0; x < w; x++) {
        int my = -1;
        for (int y = r; y < h; y++) {
            if (a[y][x]) {
                my = y;
                break;
            }
        }
        if (my == -1) continue;
        if (r != my) swap(a[r], a[my]);
        for (int y = r + 1; y < h; y++) {
            if (!a[y][x]) continue;
            auto freq = a[y][x] / a[r][x];
            for (int k = x; k < w; k++) a[y][k] -= freq * a[r][k];
        }
        r++;
        idxs.push_back(x);
        if (r == h) break;
    }
    return r;
}

template <class Mint> Mint calc_det(Mat<Mint> a) {
    assert(a.h() == a.w());
    int n = a.h();

    bool flip = false;
    for (int x = 0; x < n; x++) {
        int my = -1;
        for (int y = x; y < n; y++) {
            if (a[y][x]) {
                my = y;
                break;
            }
        }
        if (my == -1) return 0;
        if (x != my) {
            swap(a[x], a[my]);
            if ((x - my) % 2) flip = !flip;
        }
        for (int y = x + 1; y < n; y++) {
            if (!a[y][x]) continue;
            auto freq = a[y][x] / a[x][x];
            for (int k = x; k < n; k++) a[y][k] -= freq * a[x][k];
        }
    }
    Mint det = (!flip ? 1 : -1);
    for (int i = 0; i < n; i++) {
        det *= a[i][i];
    }
    return det;
}

template <class Mint> Mat<Mint> inverse(Mat<Mint> a) {
    assert(a.h() == a.w());
    int n = a.h();

    Mat<Mint> b(n, V<Mint>(n));
    for (int i = 0; i < n; i++) b[i][i] = 1;

    for (int x = 0; x < n; x++) {
        int my = -1;
        for (int y = x; y < n; y++) {
            if (a[y][x]) {
                my = y;
                break;
            }
        }
        if (my == -1) return {};
        if (x != my) {
            swap(a[x], a[my]);
            swap(b[x], b[my]);
        }
        auto freq = a[x][x];
        for (int j = 0; j < n; j++) {
            a[x][j] /= freq;
            b[x][j] /= freq;
        }
        for (int y = 0; y < n; y++) {
            if (x == y) continue;
            if (!a[y][x]) continue;
            auto freq = a[y][x];
            for (int k = 0; k < n; k++) a[y][k] -= freq * a[x][k];
            for (int k = 0; k < n; k++) b[y][k] -= freq * b[x][k];
        }
    }
    return b;
}

struct Mat2 : V<BitVec> {
    using V<BitVec>::V;
    using V<BitVec>::size;
    int h() const { return int(size()); }
    int w() const { return int((*this)[0].size()); }
};

int calc_rank(Mat2 a) {
    int h = a.h(), w = a.w();
    int r = 0;
    V<int> idxs;
    for (int x = 0; x < w; x++) {
        int my = -1;
        for (int y = r; y < h; y++) {
            if (a[y][x]) {
                my = y;
                break;
            }
        }
        if (my == -1) continue;
        if (r != my) swap(a[r], a[my]);
        for (int y = r + 1; y < h; y++) {
            if (!a[y][x]) continue;
            a[y] ^= a[r];
        }
        r++;
        idxs.push_back(x);
        if (r == h) break;
    }
    return r;
}

BitVec solve_linear(Mat2 a, BitVec b) {
    int h = a.h(), w = a.w();
    int r = 0;
    V<int> idxs;
    for (int x = 0; x < w; x++) {
        int my = -1;
        for (int y = r; y < h; y++) {
            if (a[y][x]) {
                my = y;
                break;
            }
        }
        if (my == -1) continue;
        if (r != my) swap(a[r], a[my]);
        b.swap_elms(r, my);
        for (int y = r + 1; y < h; y++) {
            if (!a[y][x]) continue;
            a[y] ^= a[r];
            b.set(y, b[y] ^ b[r]);
        }
        r++;
        idxs.push_back(x);
        if (r == h) break;
    }
    BitVec v(w);
    for (int y = r - 1; y >= 0; y--) {
        int f = idxs[y];
        v.set(f, b[y]);
        for (int x = f + 1; x < w; x++) {
            v.set(f, v[f] ^ (a[y][x] && v[x]));
        }
    }
    return v;
}
