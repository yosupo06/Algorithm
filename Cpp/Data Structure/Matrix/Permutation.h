struct Perm {
    int n;
    vector<int> d;
    Perm(int n) : n(n) {
        d.resize(n);
        for (int i = 0; i < n; i++) {
            d[i] = i;
        }
    }

    int& operator[](int p) {
        return d[p];
    }

    const int& operator[](int p) const {
        return d[p];
    }

    Perm operator*(const Perm &r) {
        assert(n == r.n);
        Perm res(n);
        for (int i = 0; i < n; i++) {
            res[i] = r[d[i]];
        }
        return res;
    }

    Perm pow(ll p) {
        Perm res(n), buf = *this;
        while(p != 0) {
            if (p % 2) {
                res = res*buf;
            }
            p /= 2;
            buf = buf*buf;
        }
        return res;
    }
};