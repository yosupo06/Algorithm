ll rand_int(ll l, ll r) { //[l, r]
    using D = uniform_int_distribution<ll>;
    static random_device rd;
    static mt19937 gen(rd());
    return D(l, r)(gen);
}

double rand_double(double l, double r) { //[l, r]
    using D = uniform_real_distribution<double>;
    static random_device rd;
    static mt19937 gen(rd());
    return D(l, r)(gen);
}

template<class URNG>
ll rand_int_log(ll l, ll r, URNG &gen) {
    assert(0 <= l);
    long double a = log1p(l);
    long double b = log1p(r);
    while (true) {
        long double c = uniform_real_distribution<long double>(a, b)(gen);
        ll z = (ll)(round(expm1(c)));
        if (l <= z && z <= r) return z;
    }
}

string rand_lower_string(int n) {
    string s = "";
    for (int i = 0; i < n; i++) {
        s += 'a' + rand_int(0, 25);
    }
    return s;
}
