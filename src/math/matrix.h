// Matrix type = VV<T>, Vector type = V<T>

template<class Mat>
int calc_rank(Mat m) {
    int h = m.size(), w = m[0].size();
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

template<class Mat, class Vec>
Vec solve_linear(Mat m, Vec r) {
    int h = m.size(), w = m[0].size();
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
    Vec v(w);
    for (int y = 0; y < c; y++) {
        int f = -1;
        typename Vec::value_type sm;
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
