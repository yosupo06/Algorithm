struct Perm {
    int n;
    int *d;
    Perm(int n) : n(n) {
        d = new int[n];
        iota(d, d+n, 0);
    }
    Perm(const Perm &r) {
        d = new int[n];
        *this = r;
    }
    ~Perm() {
        delete[] d;
    }
    int& operator[](int p) {
        return d[p];
    }

    const int& operator[](int p) const {
        return d[p];
    }
    Perm& operator=(const Perm &r) {
        memcpy(d, r.d, n*sizeof(int));
        return *this;
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
    Perm inv() {
        Perm res(n);
        for (int i = 0; i < n; i++) {
            res[d[i]] = i;
        }
        return res;
    }
};