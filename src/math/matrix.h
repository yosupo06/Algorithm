// Matrix type = VV<T>, Vector type = V<T>

struct BitVec {
    using value_type = uint;
    int n;
    V<ull> d;
    BitVec(int _n = 0) : n(_n), d((n+63)/64) {}
    size_t size() const { return n; }
    uint operator[](size_t i) const { return (d[i/64] >> (i%64)) & 1; }
    void set(size_t i, uint f) {
        if (f & 1) d[i/64] |= (1ULL << (i%64));
        else d[i/64] &= ~(1ULL << (i%64));
    }
    void push_back(uint f) {
        assert(f <= 1);
        if (n % 64 == 0) d.push_back(0);
        set(n, f);
        n++;
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

    BitVec& muladd(const BitVec& a, uint b) { if (b & 1) *this += a; return *this; }
    void swap_elms(int a, int b) { uint f = (*this)[a]; set(a, (*this)[b]); set(b, f); }

    BitVec operator+(const BitVec& r) const { return BitVec(*this) += r; }
    BitVec operator-(const BitVec& r) const { return BitVec(*this) -= r; }
};

template<class T>
struct Vec : V<T> {
    using V<T>::V;
    using V<T>::size;
    void set(int i, T x) { (*this)[i] = x; }
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
    void swap_elms(int a, int b) { swap((*this)[a], (*this)[b]); }
    Vec operator+(const Vec& r) const { return Vec(*this) += r; }
    Vec operator-(const Vec& r) const { return Vec(*this) -= r; }
    Vec operator*(const T& r) const { return Vec(*this) *= r; }
};

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
    V<int> idxs;
    for (int x = 0; x < w; x++) {
        int my = -1;
        for (int y = c; y < h; y++) {
            if (m[y][x]) {
                my = y;
                break;
            }
        }
        if (my == -1) continue;
        idxs.push_back(x);
        if (c != my) swap(m[c], m[my]);
        r.swap_elms(c, my);
        for (int y = 0; y < h; y++) {
            if (c == y) continue;
            if (!m[y][x]) continue;
            auto freq = m[y][x] / m[c][x];
            m[y].muladd(m[c], -freq);
            r.set(y, r[y] - freq * r[c]);
        }
        c++;
        if (c == h) break;
    }
    Vec v(w);
    for (int y = 0; y < c; y++) {
        int f = idxs[y];
        assert(0 <= f && f < w);
        v.set(f, r[y]);
        for (int x = f+1; x < w; x++) {
            v.set(f, v[f] - m[y][x] * v[x]);
        }
        v.set(f, v[f] / m[y][f]);
    }
    return v;
}
