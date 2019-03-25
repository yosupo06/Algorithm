template <class I> struct Frac {
    I a, b;  // a / b
    Frac(I _a = 0) : a(_a), b(1) {}
    Frac(I _a, I _b) {
        I g = gcd(_a, _b);
        if (_b < 0) g = -g;
        a = _a / g;
        b = _b / g;
    }
    Frac operator-() const {
        Frac f;
        f.a = -a;
        f.b = b;
        return f;
    }
    Frac operator+(const Frac& r) const { return {r.b * a + b * r.a, b * r.b}; }
    Frac operator-(const Frac& r) const { return *this + (-r); }
    Frac operator*(const Frac& r) const { return {a * r.a, b * r.b}; }
    Frac operator/(const Frac& r) const { return {a * r.b, b * r.a}; }
    Frac& operator+=(const Frac& r) { return *this = *this + r; }
    Frac& operator-=(const Frac& r) { return *this = *this - r; }
    Frac& operator*=(const Frac& r) { return *this = *this * r; }
    Frac& operator/=(const Frac& r) { return *this = *this / r; }
    bool operator<(const Frac& r) const { return a * r.b < b * r.a; }
    bool operator>(const Frac& r) const { return r < *this; }
    bool operator<=(const Frac& r) const { return !(r < *this); }
    bool operator>=(const Frac& r) const { return !(*this < r); }
    bool operator==(const Frac& r) const {
        return !(*this < r) && !(r < *this);
    }
    bool operator!=(const Frac& r) const { return !(*this == r); }

    static Frac rec(Frac x, Frac y, Frac l, Frac r) {
        auto flip = [&](Frac& f) { f = Frac(1) - f; };
        auto cross = [&](const Frac& f, const Frac& g) {
            return f.a * g.b - f.b * g.a;
        };
        Frac m = {l.a + r.a, l.b + r.b};
        if (x < m && m < y) return m;
        bool s = !(x < m);
        if (s) {
            flip(l);
            flip(r);
            flip(m);
            flip(x);
            flip(y);
            swap(l, r);
            swap(x, y);
        }
        I k = cross(r, y) / cross(y, l) + 1;
        Frac p = {k * l.a + r.a, k * l.b + r.b};
        if (x < p) {
            if (s) flip(p);
            return p;
        }
        Frac q = rec(x, y, p, {(k - 1) * l.a + r.a, (k - 1) * l.b + r.b});
        if (s) flip(q);
        return q;
    }
    static Frac in_bet(Frac x, Frac y) {
        if (y < x) swap(x, y);
        Frac ret;
        I num = x.a >= 0 ? x.a / x.b : -((x.b - 1 - x.a) / x.b);
        x.a -= x.b * num;
        y.a -= y.b * num;
        if (Frac{1, 1} < y)
            ret = Frac{1, 1};
        else
            ret = rec(x, y, Frac{0, 1}, Frac{1, 1});
        ret.a += ret.b * num;
        return ret;
    }
};
