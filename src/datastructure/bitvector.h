#pragma once

#include "bitop.h"

struct BitVec {
    static constexpr size_t B = 64;
    size_t n;
    V<ull> d;
    explicit BitVec(size_t _n = 0) : n(_n), d((n + B - 1) / B) {}
    void erase_last() {
        if (n % B) d.back() &= ull(-1) >> (B - n % B);
    }
    size_t size() const { return n; }
    bool operator[](size_t i) const { return (d[i / B] >> (i % B) & 1) != 0; }
    void set(size_t i, bool f = true) {
        if (f)
            d[i / B] |= 1ULL << (i % B);
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
        for (auto& x : d)
            if (x) return false;
        return true;
    }

    size_t bsf() const {
        auto m = d.size();
        for (size_t i = 0; i < m; i++) {
            if (d[i]) return i * B + ::bsf(d[i]);
        }
        assert(false);
    }

    size_t count() const {
        size_t sm = 0;
        for (auto x : d) sm += popcnt(x);
        return sm;
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

    BitVec& flip() {
        op1(bit_not<ull>());
        if (n % B) d.back() &= ~(-1ULL << (n % B));
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
            else
                d[i] = d[i - block] << rem | d[i - block - 1] >> (B - rem);
        }
        d[block] = d[0] << rem;
        erase_last();
        fill(d.begin(), d.begin() + block, 0ULL);
        return *this;
    }
    BitVec& operator>>=(const size_t& s) {
        auto block = s / B, rem = s % B;
        if (d.size() <= block) {
            reset();
            return *this;
        }
        for (size_t i = 0; i < d.size() - block - 1; i++) {
            if (rem == 0)
                d[i] = d[i + block];
            else
                d[i] = d[i + block + 1] << (B - rem) | d[i + block] >> rem;
        }
        d[d.size() - block - 1] = d.back() >> rem;
        fill(d.begin() + d.size() - block, d.end(), 0ULL);
        return *this;
    }
    BitVec& operator~() const { return BitVec(*this).flip(); }
    BitVec operator&(const BitVec& r) const { return BitVec(*this) &= r; }
    BitVec operator|(const BitVec& r) const { return BitVec(*this) |= r; }
    BitVec operator^(const BitVec& r) const { return BitVec(*this) ^= r; }
    BitVec operator<<(const size_t& s) const { return BitVec(*this) <<= s; }
    BitVec operator>>(const size_t& s) const { return BitVec(*this) >>= s; }

    BitVec substr(size_t st, size_t le) const {
        assert(st + le <= n);
        BitVec res(le);
        size_t i = 0;
        while (i < le) {
            res.d[i / B] |= d[(st + i) / B] >> ((st + i) % B) << (i % B);
            i += min(B - i % B, B - (st + i) % B);
        }
        res.erase_last();
        return res;
    }
    bool substr_match(size_t st, const BitVec& pat) const {
        size_t le = pat.size();
        assert(st + le <= n);
        size_t i = 0;
        while (i < le) {
            size_t u = min({le - i, B - i % B, B - (st + i) % B});
            ull z = pat.d[i / B] >> (i % B) ^ d[(st + i) / B] >> ((st + i) % B);
            if (z << (B - u)) return false;
            i += u;
        }
        return true;
    }

    bool operator==(const BitVec& r) const { return d == r.d; }
};
