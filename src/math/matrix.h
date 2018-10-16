// Matrix type = VV<T>, Vector type = V<T>

struct BitVec {
    int n;
    V<ull> d;
    BitVec(int _n = 0) : n(_n), d((n+63)/64) {}
    size_t size() const { return n; }
    bool operator[](size_t i) const { return (d[i/64] >> (i%64)) & 1; }
    void set(size_t i, bool f) {
        if (f) d[i/64] |= (1ULL << (i%64));
        else d[i/64] &= ~(1ULL << (i%64));
    }
    template<class OP>
    BitVec& op1(OP op) {
        int sz = int(d.size());
        for (int i = 0; i < sz; i++) d[i] = op(d[i]);
        return *this;
    }

    template<class OP>
    BitVec& op2(const BitVec& r, OP op) {
        assert(n == r.n);
        int sz = int(d.size());
        for (int i = 0; i < sz; i++) d[i] = op(d[i], r.d[i]);
        return *this;
    }
    BitVec& operator+=(const BitVec& r) { return op2(r, bit_xor<ull>()); }
    BitVec& operator-=(const BitVec& r) { return op2(r, bit_xor<ull>()); }

    BitVec& muladd(const BitVec& a, bool b) { if (b) *this += a; return *this; }

    BitVec operator+(const BitVec& r) const { return BitVec(*this) += r; }
    BitVec operator-(const BitVec& r) const { return BitVec(*this) -= r; }
};

template<class T>
struct Vec : V<T> {
    using V<T>::V;
    using V<T>::size;

    template<class OP>
    Vec& op1(OP op) {
        int n = int(size());
        for (int i = 0; i < n; i++) (*this)[i] = op((*this)[i]);
        return *this;
    }

    template<class OP>
    Vec& op2(const Vec& r, OP op) {
        assert(size() == r.size());
        int n = int(size());
        for (int i = 0; i < n; i++) (*this)[i] = op((*this)[i], r[i]);
        return *this;
    }
    Vec& operator+=(const Vec& r) { return op2(r, plus<T>()); }
    Vec& operator-=(const Vec& r) { return op2(r, minus<T>()); }
    Vec& operator*=(const T& r) { return op1([&](T l) { return l*r; }); }

    Vec& muladd(const Vec& a, const T& b) {
        return op2(a, [&](T x, T y){ return x+y*b; });
    }

    Vec operator+(const Vec& r) const { return Vec(*this) += r; }
    Vec operator-(const Vec& r) const { return Vec(*this) -= r; }
    Vec operator*(const T& r) const { return Vec(*this) *= r; }
};
template<class T> void swap(Vec<T>& l, Vec<T>& r) { l.swap(r); }

template<class Mat>
int calc_rank(Mat m) {
    int h = m.size(), w = m[0].size();
    int c = 0;
    for (int x = 0; x < w; x++) {
        int my = -1;
        for (int y = c; y < h; y++) {
            if (m[y][x]) {
                my = y;
                break;
            }
        }
        if (my == -1) continue;
        if (c != my) swap(m[c], m[my]);
        for (int y = 0; y < h; y++) {
            if (c == y) continue;
            if (!m[y][x]) continue;
            auto freq = m[y][x] / m[c][x];
            m[y].muladd(m[c], -freq);
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
            if (m[y][x]) {
                my = y;
                break;
            }
        }
        if (my == -1) continue;
        if (c != my) {
            swap(m[c], m[my]);
            swap(r[c], r[my]);
        }
        for (int y = 0; y < h; y++) {
            if (c == y) continue;
            if (!m[y][x]) continue;
            auto freq = m[y][x] / m[c][x];
            m[y].muladd(m[c], -freq);
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
            if (m[y][x] && f == -1) {
                f = x;
            }
            sm += m[y][x] * v[x];
        }
        assert(0 <= f && f < w);
        v[f] += (r[y] - sm) / m[y][f];
    }
    return v;
}
