struct Perm {
    //i -> a[i]
    vector<int> a;
    Perm(int n) {
        a = vector<int>(n);
        iota(begin(a), end(a), 0);
    }
    Perm(vector<int> a) : a(a) {}
    Perm operator*(const Perm &r) const {
        int n = int(a.size());
        Perm res(n);
        for (int i = 0; i < n; i++) {
            res.a[i] = r.a[a[i]];
        }
        return res;
    }
    Perm& operator*=(const Perm &r) {
        return *this = *this*r;
    }
};
