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

string rand_lower_string(int n) {
    string s = "";
    for (int i = 0; i < n; i++) {
        s += 'a' + rand_int(0, 25);
    }
    return s;
}
