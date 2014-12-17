typedef long long ll;

ll gcd(ll a, ll b) {
    if (b==0) return a;
    return gcd(b, a%b);
}

ll comb(int n, int k) {
    if (n < k) return 0;
    ll result = 1;
    for (int i = 1; i <= k; i++) {
        result *= n - i + 1;
        result /= i;
    }
    return result;
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

ll comb_pmod(int n, int k, ll mod) {
	if (n < k || k < 0) return 0;
	ll r = 1;
	for (int i = 1; i <= k; i++) {
		r *= i;
		r %= mod;
	}
	r = invp(r, mod);
	for (int i = n-k+1; i <= n; i++) {
		r = (r * i) % mod;
	}
	return r;
}

template<int N, int K>
struct Combinations {
    ll data[N][K] = {};
    Combinations() {
        data[0][0] = 1;
        for (int i = 1; i < N; i++) {
            data[i][0] = 1;
            for (int j = 1; j < K; j++) {
                data[i][j] = data[i-1][j]+data[i-1][j-1];
            }
        }
    }
    ll* operator[](int n) {
        return data[n];
    }
    const ll* operator[](int n) const {
        return data[n];
    }
};
