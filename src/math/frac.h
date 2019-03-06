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
    bool operator==(const Frac& r) const { return a * r.b == b * r.a; }
    bool operator!=(const Frac& r) const { return !(*this == r); }
};
