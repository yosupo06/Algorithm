#pragma once

#include "../bitop.h"


struct DynamicModInt {
    using M = DynamicModInt;

  private:
    static uint MD;
    static ull iMD;
    uint v = 0;

  public:
    static void set_mod(uint _MD) {
        assert(2 <= _MD);
        MD = _MD;
        iMD = ull(-1) / _MD + 1;
    }
    DynamicModInt() {}
    DynamicModInt(ll _v) { set_v(uint(_v % MD + MD)); }
    uint val() const { return v; }
    M& set_v(uint _v) {
        v = (_v < MD) ? _v : _v - MD;
        return *this;
    }
    explicit operator bool() const { return v != 0; }
    M operator-() const { return M() - *this; }
    M operator+(const M& r) const { return M().set_v(v + r.v); }
    M operator-(const M& r) const { return M().set_v(v + MD - r.v); }
    /*
    u32 fact_fast(u32 n, u32 mod) {
      u64 imod = u64(-1) / mod + 1; // ceil((1<<64) / mod);
      auto mul_mod = [&](u32 a, u32 b) {
        u64 c = u64(a) * b;
        u64 d = (__uint128_t(c) * imod) >> 64;
        u64 e = (c - d * mod + mod);
        //return e;
        return (e < mod) ? e : e - mod;
      };
      u32 ret = 1;
      for (int i = 1; i <= n; ++i) ret = mul_mod(ret, i);
      return ret;
    }
    */
    M operator*(const M& r) const {
        ull c = ull(v) * r.v;
        ull d = (__uint128_t(c) * iMD) >> 64;
        return M().set_v(uint(c - d * MD + MD));
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
    M inv() const {
        pair<uint, ll> p = {MD, 0}, q = {v, 1};
        while (q.first) {
            uint t = p.first / q.first;
            p.first -= t * q.first;
            p.second -= t * q.second;
            swap(p, q);
        }
        return M(p.second);
    }
    friend ostream& operator<<(ostream& os, const M& r) { return os << r.v; }
};
uint DynamicModInt::MD;
ull DynamicModInt::iMD;
