// Matrix type = VV<T>, Vector type = V<T>

template<class T>
struct Vec : public V<T> {
    using V<T>::V;
};

template<class T>
struct Mat : public VV<T> {
    int h() const { return int(this->size()); }
    int w() const { return int((*this)[0].size()); }
};

template<class T>
Vec<T> operator+(const Vec<T> &l, const Vec<T> &r) {
    assert(l.size() == r.size());
    int N = int(l.size());
    V<T> res(N);
    for (int i = 0; i < N; i++) res[i] = l[i] + r[i];
    return res;
}

template<class T>
Mat<T> operator+(const Mat<T> &l, const Mat<T> &r) {
    assert(l.size() == r.size());
    int N = int(l.size());
    VV<T> res(N);
    for (int i = 0; i < N; i++) res[i] = l[i] + r[i];
    return res;
}

template<class T>
int rank(Mat<T> m) {
    int h = m.h(), w = m.w();
    int c = 0;
    for (int x = 0; x < w; x++) {
        int my = -1;
        for (int y = c; y < h; y++) {
            if (m[y][x].v) {
                my = y;
                break;
            }
        }
        if (my == -1) continue;
        swap(m[c], m[my]);
        for (int y = 0; y < h; y++) {
            if (c == y) continue;
            if (m[y][x].v == 0) continue;
            auto freq = m[y][x] / m[c][x];
            for (int k = 0; k < w; k++) {
                m[y][k] -= freq * m[c][k];
            }
        }
        c++;
        if (c == h) break;
    }
    return c;
}

template<class T>
Vec<T> solve_linear(Mat<T> m, Vec<T> r) {
    int h = m.h(), w = m.w();
    int c = 0;
    for (int x = 0; x < w; x++) {
        int my = -1;
        for (int y = c; y < h; y++) {
            if (m[y][x].v) {
                my = y;
                break;
            }
        }
        if (my == -1) continue;
        swap(m[c], m[my]);
        swap(r[c], r[my]);
        for (int y = 0; y < h; y++) {
            if (c == y) continue;
            if (m[y][x].v == 0) continue;
            auto freq = m[y][x] / m[c][x];
            for (int k = 0; k < w; k++) {
                m[y][k] -= freq * m[c][k];
            }
            r[y] -= freq * r[c];
        }
        c++;
        if (c == h) break;
    }
    Vec<T> v(w);
    for (int y = 0; y < c; y++) {
        int f = -1;
        T sm;
        for (int x = 0; x < w; x++) {
            if (m[y][x].v && f == -1) {
                f = x;
            }
            sm += m[y][x] * v[x];
        }
        assert(0 <= f && f < w);
        v[f] += (r[y] - sm) / m[y][f];
    }
    return v;
}
