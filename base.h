#pragma once
#include "includes.h" // for test
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
template<class T> using V = vector<T>;
template<class T> using VV = V<V<T>>;
constexpr ll TEN(int n) { return (n==0) ? 1 : 10*TEN(n-1); }

int bsr(uint x) { return 31 - __builtin_clz(x); }
int bsr(ull x) { return 63 - __builtin_clzll(x); }
int bsf(uint x) { return __builtin_ctz(x); }
int bsf(ull x) { return __builtin_ctzll(x); }

ll gcd(ll _a, ll _b) {
    ull a = abs(_a), b = abs(_b);
    if (a == 0) return b;
    if (b == 0) return a;
    int shift = bsf(a|b);
    a >>= bsf(a);
    do {
        b >>= bsf(b);
        if (a > b) swap(a, b);
        b -= a;
    } while (b);
    return (a << shift);
}


/// g:gcd(a, b), ax+by=g
struct EG { ll g, x, y; };
EG ext_gcd(ll a, ll b) {
    if (b==0) {
        return EG{a, 1, 0};
    } else {
        auto e = ext_gcd(b, a%b);
        return EG{e.g, e.y, e.x-a/b*e.y};
    }
}

template<class T>
T pow(T x, ll n, T r = 1) {
    while (n) {
        if (n & 1) r *= x;
        x *= x;
        n >>= 1;
    }
    return r;
}

template<uint MD>
struct ModInt {
    uint v;
    ModInt() : v{0} {}
    ModInt(ll v) : v{normS(v%MD+MD)} {}
    explicit operator bool() const {return v != 0;}
    static uint normS(const uint &x) {return (x<MD)?x:x-MD;};
    static ModInt make(const uint &x) {ModInt m; m.v = x; return m;}
    static ModInt inv(const ModInt &x) {return pow(ModInt(x), MD-2);} 
    ModInt operator+(const ModInt &r) const {return make(normS(v+r.v));}
    ModInt operator-(const ModInt &r) const {return make(normS(v+MD-r.v));}
    ModInt operator*(const ModInt &r) const {return make((ull)v*r.v%MD);}
    ModInt operator/(const ModInt &r) const {return *this*inv(r);}
    ModInt& operator+=(const ModInt &r) {return *this=*this+r;}
    ModInt& operator-=(const ModInt &r) {return *this=*this-r;}
    ModInt& operator*=(const ModInt &r) {return *this=*this*r;}
    ModInt& operator/=(const ModInt &r) {return *this=*this/r;}
};
template<uint MD> string to_string(ModInt<MD> m) {return to_string(m.v);}
using Mint = ModInt<TEN(9)+7>;

template<class R>
struct Pc {
    R x, y;
    Pc() : x(0), y(0) {}
    Pc(R x, R y) : x(x), y(y) {}
    Pc operator+(const Pc &r) const {return Pc(x+r.x, y+r.y);}
    Pc operator-(const Pc &r) const {return Pc(x-r.x, y-r.y);}
    Pc operator*(const Pc &r) const {return Pc(x*r.x-y*r.y, x*r.y+y*r.x);}
    Pc operator*(const R &r) const {return Pc(x*r, y*r);}
    Pc& operator+=(const Pc &r) {return *this=*this+r;}
    Pc& operator-=(const Pc &r) {return *this=*this-r;}
    Pc& operator*=(const Pc &r) {return *this=*this*r;}   
    Pc& operator*=(const R &r) {return *this=*this*r;}
    static Pc polar(R r, R th) {return Pc(cos(th)*r, sin(th)*r);}
};
