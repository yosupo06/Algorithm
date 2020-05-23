#pragma once

#include "base.hpp"

// ModInt of 2^61 - 1
struct ModInt61 {
    static constexpr ull MD = (1ULL << 61) - 1;
    using M = ModInt61;
    static constexpr ull get_mod() { return MD; }
    const static M G;
    ull v;
    ModInt61(ll _v = 0) { set_v(_v % MD + MD); }
    M& set_v(ull _v) {
        v = (_v < MD) ? _v : _v - MD;
        return *this;
    }
    explicit operator bool() const { return v != 0; }
    M operator-() const { return M() - *this; }
    M operator+(const M& r) const { return M().set_v(v + r.v); }
    M operator-(const M& r) const { return M().set_v(v + MD - r.v); }
    M operator*(const M& r) const {
        __uint128_t z = __uint128_t(v) * r.v;
        
        return M().set_v(ull((z & ((1ULL << 61) - 1)) + (z >> 61)));
    }
    M operator/(const M& r) const { return *this * r.inv(); }
    M& operator+=(const M& r) { return *this = *this + r; }
    M& operator-=(const M& r) { return *this = *this - r; }
    M& operator*=(const M& r) { return *this = *this * r; }
    M& operator/=(const M& r) { return *this = *this / r; }
    bool operator==(const M& r) const { return v == r.v; }
    M pow(ll n) const {
        M x = *this, r = 1;
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
    M inv() const { return pow(MD - 2); }
    friend ostream& operator<<(ostream& os, const M& r) { return os << r.v; }
};
