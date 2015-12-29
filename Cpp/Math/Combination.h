//nCk
ll comb(int n, int k) {
    if (n < k || k < 0) return 0;
    ll result = 1;
    for (int i = 1; i <= k; i++) {
        result *= n - i + 1;
        result /= i;
    }
    return result;
}

//nCk % md
ll comb_pmod(int n, int k, ll md) {
	if (n < k || k < 0) return 0;
	ll r = 1;
	for (int i = 1; i <= k; i++) {
		r *= i;
		r %= md;
	}
	r = invp(r, md);
	for (int i = n-k+1; i <= n; i++) {
		r = (r * i) % md;
	}
	return r;
}

//fact[i]:i! ifact[i]:i!の逆元
ll comb_st(int n, int k) {
    if (n < k || k < 0) return 0;
    return fact[n]*ifact[k]%MD*ifact[n-k]%MD;
}
