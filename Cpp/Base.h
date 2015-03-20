/**
 * 分類するまでもない基本的な関数たち
 */

/// aとbのgcd
ll gcd(ll a, ll b) {
    if (b==0) return a;
    return gcd(b, a%b);
}

/// 高速累乗, x^nをO(logn)で求める
ll pow(ll x, ll n) {
    ll r = 1;
    while (n) {
        if (n & 1) r *= x;
        x *= x;
        n >>= 1;
    }
    return r;
}

// x^n % md
ll pow_mod(ll x, ll n, ll md) {
	ll r = 1;
	while (n) {
		if (n & 1) r = (r * x) % md;
		x = (x * x) % md;
		n >>= 1;
	}
	return r;
}

/// xの逆元, 必ず, mdは素数かつxはmdの倍数ではない必要がある
ll invp(ll x, ll md) {
	return pow_mod(x, md-2, md);
}
