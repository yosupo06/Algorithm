template<class D>
struct Poly {
    V<D> v;
    int size() const {return int(v.size());}
    Poly(int N = 0) : v(V<D>(N)) {}
    Poly(const V<D> &v) : v(v) {shrink();}
    Poly& shrink() {while (v.size() && !v.back()) v.pop_back(); return *this;}
    D freq(int p) const { return (p < size()) ? v[p] : D(0); }

    Poly operator+(const Poly &r) const {
        int N = size(), M = r.size();
        V<D> res(max(N, M));
        for (int i = 0; i < max(N, M); i++) res[i] = freq(i)+r.freq(i);
        return Poly(res);
    }
    Poly operator-(const Poly &r) const {
        int N = size(), M = r.size();
        V<D> res(max(N, M));
        for (int i = 0; i < max(N, M); i++) res[i] = freq(i)-r.freq(i);
        return Poly(res);
    }
    Poly operator*(const Poly &r) const {
        int N = size(), M = r.size();
        if (min(N, M) == 0) return Poly();
        assert(N+M-1 >= 0);
        V<D> res = multiply(v, r.v);
        return Poly(res);
    }
    Poly operator*(const D &r) const {
        V<D> res(size());
        for (int i = 0; i < size(); i++) res[i] = v[i]*r;
        return Poly(res);
    }
    Poly& operator+=(const Poly &r) {return *this = *this+r;}
    Poly& operator-=(const Poly &r) {return *this = *this-r;}
    Poly& operator*=(const Poly &r) {return *this = *this*r;}
    Poly& operator*=(const D &r) {return *this = *this*r;}

    Poly operator<<(const int n) const {
        assert(n >= 0);
        V<D> res(size()+n);
        for (int i = 0; i < size(); i++) {
            res[i+n] = v[i];
        }
        return Poly(res);
    }
    Poly operator>>(const int n) const {
        assert(n >= 0);
        if (size() <= n) return Poly();
        V<D> res(size()-n);
        for (int i = n; i < size(); i++) {
            res[i-n] = v[i];
        }
        return Poly(res);
    }

    // x % y
    Poly rem(const Poly &y) const {
        return *this - y * div(y);
    }
    Poly rem_inv(const Poly &y, const Poly &ny, int B) const {
        return *this - y * div_inv(ny, B);
    }
    Poly div(const Poly &y) const {
        int B = max(size(), y.size());
        return div_inv(y.inv(B), B);
    }
    Poly div_inv(const Poly &ny, int B) const {
        return (*this*ny)>>(B-1);
    }
    // this * this.inv() = x^n + r(x) (size())
    Poly strip(int n) const {
        V<D> res = v;
        res.resize(min(n, size()));
        return Poly(res);
    }
    Poly rev(int n = -1) const {
        V<D> res = v;
        if (n != -1) res.resize(n);
        reverse(begin(res), end(res));
        return Poly(res);
    }
    // f * f.inv() = x^B + r(x) (B >= n)
    Poly inv(int n) const {
        int N = size();
        assert(N >= 1);
        assert(n >= N-1);
        Poly c = rev();
        Poly d = Poly(V<D>({D(1)/c.freq(0)}));
        int i;
        for (i = 1; i+N-2 < n; i *= 2) {
            auto u = V<D>({2});
            d = (d * (Poly(V<D>{2})-c*d)).strip(2*i);
        }
        return d.rev(n+1-N);
    }
};
template<class D>
string to_string(const Poly<D> &p) {
    if (p.size() == 0) return "0";
    string s = "";
    for (int i = 0; i < p.size(); i++) {
        if (p.v[i]) {
            s += to_string(p.v[i])+"x^"+to_string(i);
            if (i != p.size()-1) s += "+";
        }
    }
    return s;
}
// x^n % mod
template<class D>
Poly<D> nth_mod(ll n, const Poly<D> &mod) {
    int B = mod.size() * 2 - 1;
    Poly<D> mod_inv = mod.inv(B);
    Poly<D> p = V<D>{Mint(1)};
    int m = (!n) ? -1 : bsr(n);
    for (int i = m; i >= 0; i--) {
        if (n & (1LL<<i)) {
            // += 1
            p = (p<<1).rem_inv(mod, mod_inv, B);
        }
        if (i) {
            // *= 2
            p = (p*p).rem_inv(mod, mod_inv, B);
        }
    }
    return p;
}
