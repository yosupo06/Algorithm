int bsr(int x) { return 31 - __builtin_clz(x); }

template<class T = ll> T gcd(T a, T b) {return (b==0) ? a : gcd(b, a%b);}
template<class T = ll> T lcm(T a, T b) {return a/gcd(a, b)*b;}

/// g:gcd(a, b), ax+by=g
template<class T = ll> struct EG { T g, x, y; };

template<class T>
EG<T> ext_gcd(T a, T b) {
    if (b==0) {
        return EG<T>{a, 1, 0};
    } else {
        auto e = ext_gcd(b, a%b);
        return EG<T>{e.g, e.y, e.x-a/b*e.y};
    }
}

template<class T>
T pow(T x, ll n) {
    T r = 1;
    while (n) {
        if (n & 1) r *= x;
        x *= x;
        n >>= 1;
    }
    return r;
}

template<class T>
T pow(T x, ll n, T md) {
    T r = 1;
    while (n) {
        if (n & 1) r = (r*x)%md;
        x = (x*x)%md;
        n >>= 1;
    }
    return r;
}

ll invp(ll x, ll md) {
    return pow_mod(x, md-2, md);
}


template<uint MD>
struct ModInt {
    uint v;
    ModInt() : v{0} {}
    ModInt(ll v) : v{normS(v%MD+MD)} {}
    static uint normS(const uint &x) {return (x<MD)?x:x-MD;};
    static ModInt make(const uint &x) {ModInt m; m.v = x; return m;}
    ModInt operator+(const ModInt &r) const {return make(normS(v+r.v));}
    ModInt operator-(const ModInt &r) const {return make(normS(v+MD-r.v));}
    ModInt operator*(const ModInt &r) const {return make((ull)v*r.v%MD);}
    ModInt& operator+=(const ModInt &r) {return *this=*this+r;}
    ModInt& operator-=(const ModInt &r) {return *this=*this-r;}
    ModInt& operator*=(const ModInt &r) {return *this=*this*r;}
    static ModInt inv(const ModInt &x) {
        return pow(ModInt(x), MD-2);
    }
};

ll rand_int(ll l, ll r) { //[l, r)
    using D = uniform_int_distribution<ll>;
    static random_device rd;
    static mt19937 gen(rd());
    return D(l, r-1)(gen);
}
