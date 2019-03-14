struct Prime {
    int n;
    vector<bool> used;
    vector<int> pr;
    vector<ull> bpr;
    Prime(int _n) : n(_n) {
        used = vector<bool>(n+1, false);
        for (int i = 2; i <= n; i++) {
            if (used[i]) continue;
            pr.push_back(i);
            bpr.push_back(((__int128_t(1)<<64)+i-1) / i);
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

bool is_prime(ll n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    ll d = n - 1;
    while (d % 2 == 0) d /= 2;
    // Michal Forisek, Jakub Jancina, Fast Primality Testing for Integers That Fit into a Machine Word
    V<ll> alist{2, 325, 9375, 28178, 450775, 9780504, 1795265022};  // n < 2^64
    for (ll a : alist) {
        ll t = d;
        ll y = pow_mod<__int128_t>(a, t, n);  // over
        while (t != n - 1 && y != 1 && y != n - 1) {
            y = __int128_t(y) * y % n;  // flow
            t <<= 1;
        }
        if (y != n - 1 && t % 2 == 0) {
            return false;
        }
    }
    return true;
}

ll pollard_single(ll n) {
    auto f = [&](ll x) { return (__int128_t(x) * x + 1) % n; };
    if (is_prime(n)) return n;
    if (n % 2 == 0) return 2;
    ll st = 0;
    while (true) {
        st++;
        ll x = st, y = f(x);
        while (true) {
            ll p = gcd((y - x + n), n);
            if (p == 0 || p == n) break;
            if (p != 1) return p;
            x = f(x);
            y = f(f(y));
        }
    }
}

V<ll> pollard(ll n) {
    if (n == 1) return {};
    ll x = pollard_single(n);
    if (x == n) return {x};
    V<ll> le = pollard(x);
    V<ll> ri = pollard(n / x);
    le.insert(end(le), begin(ri), end(ri));
    return le;
}

ll primitive_root(ll p) {
    auto v = pollard(p - 1);
    while (true) {
        ll g = rand_int(1, p - 1);  //[1, p-1]
        bool ok = true;
        for (auto d : v) {
            ll f = (p - 1) / d;
            if (pow_mod<__int128_t>(g, f, p) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return g;
    }
}
