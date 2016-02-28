/**
 * Ubuntu
 * gsettings set org.gnome.desktop.interface gtk-key-theme Emacs
 * setxkbmap -option ctrl:nocaps
 **/

ll gcd(ll a, ll b) {
    if (b==0) return a;
    return gcd(b, a%b);
}

ll lcm(ll a, ll b) {
    return a/gcd(a, b)*b;
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
    ModInt(ll v) : v((v%MD+MD)%MD) {}
    ModInt normS(uint x) {return (x<MD)?x:x-MD;};
    ModInt operator+(ModInt r) {return ModInt(normS(v+r.v));};
    ModInt operator-(ModInt r) {return *this+ModInt(MD-r.v);};
    ModInt operator*(ModInt r) {return ModInt((ll)v*r.v%MD);};
    ModInt operator+=(ModInt r) {return *this=*this+r;}
    ModInt operator-=(ModInt r) {return *this=*this-r;}
    ModInt operator*=(ModInt r) {return *this=*this*r;}
    static ModInt inv(ModInt x) {
        return pow(ModInt(x), MD-2);
    }
};

