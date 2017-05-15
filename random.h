ll rand_int(ll l, ll r) { //[l, r]
    using D = uniform_int_distribution<ll>;
    static random_device rd;
    static mt19937 gen(rd());
    return D(l, r)(gen);
}

template<class URNG>
ll rand_int(ll l, ll r, URNG &gen) { //[l, r]
    using D = uniform_int_distribution<ll>;
    return D(l, r)(gen);
}

string rand_lower_string(int n) {
    string s = "";
    for (int i = 0; i < n; i++) {
        s += 'a' + rand_int(0, 25);
    }
    return s;
}

template<class URNG>
string rand_lower_string(int n, URNG &gen) {
    string s = "";
    for (int i = 0; i < n; i++) {
        s += 'a' + rand_int(0, 25, gen);
    }
    return s;
}
