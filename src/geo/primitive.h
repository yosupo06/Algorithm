using D = double;
const D PI = acos(D(-1)), EPS = 1e-10;

int sgn(D a) { return (a < -EPS) ? -1 : (a > EPS); }
int sgn(D a, D b) { return sgn(a - b); }
// relative sign
// int rsgn(D a, D f) {
//     if (abs(a) <= f*EPS) return 0;
//     return (a < 0) ? -1 : 1;
// }
struct Pt2 {
    D x, y;
    Pt2(D _x = D(), D _y = D()) : x(_x), y(_y) {}
    Pt2 operator+(const Pt2& r) const { return Pt2(x + r.x, y + r.y); }
    Pt2 operator-(const Pt2& r) const { return Pt2(x - r.x, y - r.y); }
    Pt2 operator*(const Pt2& r) const { return Pt2(x*r.x-y*r.y, x*r.y+y*r.x);
    }

    Pt2 operator*(const D& r) const { return Pt2(x * r, y * r); }
    Pt2 operator/(const D& r) const { return Pt2(x / r, y / r); }

    Pt2& operator+=(const Pt2& r) { return *this = *this + r; }
    Pt2& operator-=(const Pt2& r) { return *this = *this - r; }
    Pt2& operator*=(const Pt2& r) { return *this = *this * r; }
    Pt2& operator*=(const D& r) { return *this = *this * r; }
    Pt2& operator/=(const D& r) { return *this = *this / r; }

    Pt2 operator-() const { return Pt2(-x, -y); }

    bool operator<(const Pt2& r) const { return 2*sgn(x, r.x)+sgn(y, r.y)<0; }
    bool operator==(const Pt2& r) const { return sgn((*this-r).rabs()) == 0; }
    bool operator!=(const Pt2& r) const { return !(*this == r); }

    D norm() const { return x * x + y * y; }
    D abs() const { return sqrt(norm()); }
    D rabs() const { return max(std::abs(x), std::abs(y)); }  // robust abs
    D arg() const { return atan2(y, x); }

    pair<D, D> to_pair() const { return make_pair(x, y); }
    static Pt2 polar(D le, D th) { return Pt2(le * cos(th), le * sin(th)); }
};
ostream& operator<<(ostream& os, const Pt2& p) {
    return os << "P(" << p.x << ", " << p.y << ")";
}
using P = Pt2;

struct L {
    P s, t;
    L(P _s = P(), P _t = P()) : s(_s), t(_t) {}
    P vec() const { return t - s; }
    D abs() const { return vec().abs(); }
    D arg() const { return vec().arg(); }
};
ostream& operator<<(ostream& os, const L& l) {
    return os << "L(" << l.s << ", " << l.t << ")";
}

D crs(P a, P b) { return a.x * b.y - a.y * b.x; }
D dot(P a, P b) { return a.x * b.x + a.y * b.y; }
// cross(a, b) is too small?
int sgncrs(P a, P b) {
    D cr = crs(a, b);
    if (abs(cr) <= (a.rabs() + b.rabs()) * EPS) return 0;
    return (cr < 0) ? -1 : 1;
}

// -2, -1, 0, 1, 2 : front, clock, on, cclock, back
int ccw(P b, P c) {
    int s = sgncrs(b, c);
    if (s) return s;
    if (!sgn(c.rabs()) || !sgn((c - b).rabs())) return 0;
    if (dot(b, c) < 0) return 2;
    if (dot(-b, c - b) < 0) return -2;
    return 0;
}
int ccw(P a, P b, P c) { return ccw(b - a, c - a); }
int ccw(L l, P p) { return ccw(l.s, l.t, p); }

D deg2rad(D x) { return x / 180 * PI; }
D rad2deg(D x) { return x / PI * 180; }

//角度を[0, 2*PI)に
D radNorP(D x) { return fmod(fmod(x, 2 * PI) + 2 * PI, 2 * PI); }

//角度を[-PI, PI)に
D radNorN(D x) {
    x = radNorP(x);
    if (x >= PI) x -= 2 * PI;
    return x;
}

/**
 * radianで、xが[l, r]に入っているかを判別する
 * 0:OFF
 * 1:IN
 * 2:ON
 */
bool inR(D l, D r, D x) {
    l = radNorP(l);
    r = radNorP(r);
    x = radNorP(x);
    if (!sgn(l, x) || !sgn(r, x)) return 2;
    if (!sgn(l, r)) return 0;
    if (sgn(l, r) == 1) {
        if (sgn(l, x) == 1 && sgn(x, r) == 1) return 1;
    } else {
        if (sgn(x, r) == 1 || sgn(l, x) == 1) return 1;
    }
    return 0;
}
D ssqrt(D d) {
    d = max(D(0), d);
    return sqrt(d);
}

D sacos(D d) {
    d = max(D(-1), d);
    d = min(D(1), d);
    return acos(d);
}
