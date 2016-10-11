struct Prime {
    int n;
    vector<bool> used;
    vector<int> pr;
    vector<ull> bpr;
    Prime(int n) : n(n) {
        used = vector<bool>(n+1, false);
        for (int i = 2; i <= n; i++) {
            if (used[i]) continue;
            pr.push_back(i);
            bpr.push_back(((__int128(1)<<64)+i-1) / i);
            for (int j = 2*i; j <= n; j += i) {
                used[j] = true;
            }
        }
    }    
    map<ll, int> fact(ll x) {
        assert(x <= (ll)n*n);
        int pc = (int)pr.size();
        map<ll, int> mp;
        for (int i = 0; i < pc; i++) {
            ll d = pr[i]; ull rd = bpr[i];
            if (x < d*d) break;
            while (true) {
                ll xd = __int128(x)*rd >> 64;
                if (xd * d != x) break;
                x = xd;
                mp[d]++;
            }
        }
        if (x > 1) mp[x]++;
        return mp;
    }
};

bool isPrime(ll n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    ll d = n-1;
    while (d % 2 == 0) d /= 2;
    vector<ll> alist{2,3,1662803}; // n < 1.12e12
//    vector<ll> alist{2,3,5,7,11,13,17,19,23,29,31,37}; // n < 2^64
    for (ll a: alist) {
        if (n <= a) break;
        ll t = d;
        ll y = pow<__int128>(a, t, n); //over
        while (t != n-1 && y != 1 && y != n-1) {
            y = __int128(y)*y % n; //flow
            t <<= 1;
        }
        if (y != n-1 && t % 2 == 0) {
            return false;
        }
    }
    return true;
}

ull xor64(ull y) {
    y = y ^ (y<<13);
    y = y ^ (y>>7);
    y = y ^ (y<<17);
    return y;
}

ll pollard(ll n) {
    ll x = 2, y = 2, d = 1;
    int c = 0;
    constexpr int C = 3000;
    while (c < C and d == 1) {
        x = xor64(x)%n;
        y = xor64(xor64(y)%n)%n;
        d = gcd(abs(x-y), n);
        c++;
    }
//    printf("%lld %lld\n", n, d);
    if (c == C) return -2;
    if (d == n) return -1;
    return d;
}
