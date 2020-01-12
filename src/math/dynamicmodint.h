#pragma once

struct DynamicModInt {
    using M = DynamicModInt;

  private:
    static uint MD;

  public:
    static void set_mod(uint _MD) {
        MD = _MD;
    }
    uint v = 0;
    DynamicModInt() {}
    DynamicModInt(ll _v) { set_v(uint(_v % MD + MD)); }
    M& set_v(uint _v) {
        v = (_v < MD) ? _v : _v - MD;
        return *this;
    }
    explicit operator bool() const { return v != 0; }
    M operator-() const { return M() - *this; }
    M operator+(const M& r) const { return M().set_v(v + r.v); }
    M operator-(const M& r) const { return M().set_v(v + MD - r.v); }
    M operator*(const M& r) const { return M().set_v(uint(ull(v) * r.v % MD)); }
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
