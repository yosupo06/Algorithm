int nlz(unsigned int x) {
    double dx = x;
    return 1054 - (*(unsigned long *)(&(dx)) >> 52);
}

ll gcd(ll a, ll b) {
    if (b==0) return a;
    return gcd(b, a%b);
}

ll pow_mod(ll x, ll n, ll mod) {
	ll r = 1;
	while (n) {
		if (n & 1) r = (r * x) % mod;
		x = (x * x) % mod;
		n >>= 1;
	}
	return r;
}

ll invp(ll r, ll mod) {
	return pow_mod(r, mod-2, mod);
}
