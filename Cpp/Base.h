/**
 * Ubuntu
 * gsettings set org.gnome.desktop.interface gtk-key-theme Emacs
 * setxkbmap -option ctrl:nocaps
 **/

ll gcd(ll a, ll b) {return (b==0) ? a : gcd(b, a%b);}
ll lcm(ll a, ll b) {return a/gcd(a, b)*b;}

struct EG { ll g, x, y; };
EG ext_gcd(ll a, ll b) {
    if (b==0) {
        return EG{a, 1, 0};
    } else {
        auto e = ext_gcd(b, a%b);
        return EG{e.g, e.y, e.x-a/b*e.y};
    }
}

/// x^n
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


/// x^n % md
ll pow_mod(ll x, ll n, ll md) {
    ll r = 1;
    while (n) {
        if (n & 1) r = (r * x) % md;
        x = (x * x) % md;
        n >>= 1;
    }
    return r;
}

/// xの逆元, xとmdは互いに素
ll invp(ll x, ll md) {
    return pow_mod(x, md-2, md);
}


//binary search reverse
int bsr(int x) {
    return 31 - __builtin_clz(x);
}

template<uint MD>
struct ModInt {
    uint v;
    ModInt() : v(0) {}
    ModInt(ll v) : v(normS(v%MD+MD)) {}
    uint value() {return v;}
    static uint normS(const uint &x) {return (x<MD)?x:x-MD;};
    static ModInt make(const uint &x) {ModInt m; m.v = x; return m;}
    const ModInt operator+(const ModInt &r) const {return make(normS(v+r.v));}
    const ModInt operator-(const ModInt &r) const {return make(normS(v+normS(MD-r.v)));}
    const ModInt operator*(const ModInt &r) const {return make((ull)v*r.v%MD);}
    ModInt& operator+=(const ModInt &r) {return *this=*this+r;}
    ModInt& operator-=(const ModInt &r) {return *this=*this-r;}
    ModInt& operator*=(const ModInt &r) {return *this=*this*r;}
    static ModInt inv(const ModInt &x) {
        return pow(ModInt(x), MD-2);
    }
};

template<uint MD>
struct ModInt {
    static constexpr uint two(ull x, ull md) {return (ll)x*x%md;}
    static constexpr uint pow(ull x, ull n, ull md) {
        return (!n) ? 1 : (ll)two(pow(x, n/2, md), md) * (n%2 ? x : 1) % md;
    }
    static constexpr ull R = (1ULL<<32);
    static constexpr uint Ri = pow(R%MD, MD-2, MD);
    static constexpr uint MDi = (R-pow(MD, (1U<<31)-1, R))%R;
    uint v;
    ModInt() : v(0) {}
    ModInt(ll v) : v(((v%MD+MD)<<32)%MD) {}
    uint value() {return (ull)v*Ri%MD;}
    static uint normS(const uint &x) {return (x<MD)?x:x-MD;};
    static ModInt make(const uint &x) {ModInt m; m.v = x; return m;}
    const ModInt operator+(const ModInt &r) const {return make(normS(v+r.v));}
    const ModInt operator-(const ModInt &r) const {return make(normS(v+normS(MD-r.v)));}
    const ModInt operator*(const ModInt &r) const {
        return make(normS((v*r.v+(ull)(v*r.v*MDi)*MD)>>32));
    }
    ModInt& operator+=(const ModInt &r) {return *this=*this+r;}
    ModInt& operator-=(const ModInt &r) {return *this=*this-r;}
    ModInt& operator*=(const ModInt &r) {return *this=*this*r;}
};

