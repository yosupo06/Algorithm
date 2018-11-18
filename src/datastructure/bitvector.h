struct BitVec {
    static constexpr size_t B = 64;
    size_t n;
    V<ull> d;
    explicit BitVec(size_t _n = 0) : n(_n), d((n + B - 1) / B) {}
    size_t size() const { return n; }
    bool operator[](size_t i) const { return ((d[i / B] >> (i % B)) & 1) != 0; }
    void set(size_t i, bool f = true) {
        if (f)
            d[i / B] |= (1ULL << (i % B));
        else
            d[i / B] &= ~(1ULL << (i % B));
    }
    void reset() { fill(d.begin(), d.end(), 0); }
    void reset(size_t i) { set(i, false); }
    void push_back(bool f) {
        if (n % B == 0) d.push_back(0);
        set(n, f);
        n++;
    }
    bool empty() const {
        for (auto& x : d) if (x) return false;
        return true;
    }

    size_t bsf() const {
        auto m = d.size();
        for (size_t i = 0; i < m; i++) {
            if (d[i]) return i * B + ::bsf(d[i]);
        }
        assert(false);
    }

    void swap_elms(size_t a, size_t b) {
        bool f = (*this)[a];
        set(a, (*this)[b]);
        set(b, f);
    }

    template <class OP> BitVec& op1(OP op) {
        for (auto& x : d) x = op(x);
        return *this;
    }

    template <class OP> BitVec& op2(const BitVec& r, OP op) {
        assert(n == r.n);
        for (size_t i = 0; i < d.size(); i++) d[i] = op(d[i], r.d[i]);
        return *this;
    }

    BitVec& operator&=(const BitVec& r) { return op2(r, bit_and<ull>()); }
    BitVec& operator|=(const BitVec& r) { return op2(r, bit_or<ull>()); }
    BitVec& operator^=(const BitVec& r) { return op2(r, bit_xor<ull>()); }
    BitVec& operator<<=(const size_t& s) {
        auto block = s / B, rem = s % B;
        if (d.size() <= block) {
            reset();
            return *this;
        }
        for (size_t i = d.size() - 1; i > block; i--) {
            if (rem == 0)
                d[i] = d[i - block];
            else {
                d[i] =
                        (d[i - block] << rem) | ((d[i - block - 1]) >> (B - rem));
            }
        }
        d[block] = d[0] << rem;
        if (n % B) d.back() &= ull(-1) >> (B - n % B);
        fill(d.begin(), d.begin() + block, 0ULL);
        return *this;
    }
    BitVec& operator>>=(const size_t& s) {
        auto block = s / B, rem = s % B;
        if (d.size() <= block) {
            reset();
            return *this;
        }
        for (size_t i = 0; i < d.size() - block; i++) {
            if (rem == 0)
                d[i] = d[i + block];
            else {
                d[i] = (d[i + block + 1]) << (B - rem) | (d[i + block] >> rem);
            }
        }
        d[d.size() - block - 1] = d.back() << rem;
        fill(d.begin() + d.size() - block, d.end(), 0ULL);
        return *this;
    }
    BitVec operator&(const BitVec& r) const { return BitVec(*this) &= r; }
    BitVec operator|(const BitVec& r) const { return BitVec(*this) |= r; }
    BitVec operator^(const BitVec& r) const { return BitVec(*this) ^= r; }
    BitVec operator<<(const size_t& s) const { return BitVec(*this) <<= s; }
    BitVec operator>>(const size_t& s) const { return BitVec(*this) >>= s; }
};
