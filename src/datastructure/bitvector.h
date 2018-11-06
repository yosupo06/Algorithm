struct BitVector {
    size_t n;
    V<ull> d;
    BitVector(size_t _n = 0) : n(_n), d((n+63)/64) {}
    size_t size() const { return n; }
    bool operator[](size_t i) const { return (d[i/64] >> (i%64)) & 1; }
    void set(size_t i, bool f) {
        if (f) d[i/64] |= (1ULL << (i%64));
        else d[i/64] &= ~(1ULL << (i%64));
    }
    void push_back(bool f) {
        if (n % 64 == 0) d.push_back(0);
        set(n, f);
        n++;
    }

    void swap_elms(int a, int b) { uint f = (*this)[a]; set(a, (*this)[b]); set(b, f); }

    template<class OP>
    BitVec& op1(OP op) {
        for (size_t i = 0; i < d.size(); i++) d[i] = op(d[i]);
        return *this;
    }

    template<class OP>
    BitVec& op2(const BitVec& r, OP op) {
        assert(n == r.n);
        for (size_t i = 0; i < d.size(); i++) d[i] = op(d[i], r.d[i]);
        return *this;
    }
    BitVec& operator^=(const BitVec& r) { return op2(r, bit_xor<ull>()); }
    BitVec operator^(const BitVec& r) const { return BitVec(*this) ^= r; }
};
