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
    Poly<D> p = V<D>{D(1)};
    int m = (!n) ? -1 : bsr(ull(n));
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
template<class D>
Poly<D> berlekamp_massey(const V<D> &s) {
    int N = int(s.size());
    V<D> b = {D(-1)}, c = {D(-1)};
    D y = D(1);
    for (int ed = 1; ed <= N; ed++) {
        int L = int(c.size()), M = int(b.size());
        D x = 0;
        for (int i = 0; i < L; i++) {
            x += c[i]*s[ed-L+i];
        }
        b.push_back(0); M++;
        if (!x) {
            continue;
        }
        D freq = x/y;
        if (L < M) {
            //use b
            auto tmp = c;
            c.insert(begin(c), M-L, D(0));
            for (int i = 0; i < M; i++) {
                c[M-1-i] -= freq*b[M-1-i];
            }
            b = tmp;
            y = x;
        } else {
            //use c
            for (int i = 0; i < M; i++) {
                c[L-1-i] -= freq*b[M-1-i];
            }
        }
    }
    return Poly<D>(c);
}

template<class Mint>
V<Mint> randV(int N) {
    V<Mint> res(N);
    for (int i = 0; i < N; i++) {
        res[i] = Mint(rand_int(1, Mint(-1).v));
    }
    return res;
}

template<class Mint>
Mint det(const V<Mint> &diag, const V<pair<int, int>> &edges) {
    int N = int(diag.size());
    if (N == 0) return 1;
    V<Mint> c = randV<Mint>(N), l = randV<Mint>(N), r = randV<Mint>(N);
    // l * mat * r
    V<Mint> buf(2*N), tmp(N);
    for (int fe = 0; fe < 2*N; fe++) {
        for (int i = 0; i < N; i++) {
            buf[fe] += l[i]*r[i];
        }
        for (int i = 0; i < N; i++) {
            r[i] *= c[i];
        }
        for (int i = 0; i < N; i++) {
            tmp[i] = diag[i] * r[i];
        }
        for (auto e: edges) {
            tmp[e.first] -= r[e.second];
            tmp[e.second] -= r[e.first];
        }
        r = tmp;
    }
    auto u = berlekamp_massey(buf);
    auto acdet = u.freq(0) * Mint(-1);
    if (!acdet) return 0;
    if (u.size() != N+1) return det(diag, edges);
    Mint cdet = 1;
    for (int i = 0; i < N; i++) {
        cdet *= c[i];
    }
    if (N % 2) acdet *= Mint(-1);
    return acdet / cdet;
}
