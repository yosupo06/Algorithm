//binary gcd
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
    if (b == 0) {
        if (a >= 0) return EG{a, 1, 0};
        else return EG{-a, -1, 0};
    } else {
        auto e = ext_gcd(b, a % b);
        return EG{e.g, e.y, e.x - a / b * e.y};
    }
}

ll inv_mod(ll x, ll md) {
    auto z = ext_gcd(x, md).x;
    return (z % md + md) % md;
}

template<class T, class U>
T pow_mod(T x, U n, T md) {
    T r = 1 % md;
    while (n) {
        if (n & 1) r = (r * x) % md;
        x = (x * x) % md;
        n >>= 1;
    }
    return r;
}
