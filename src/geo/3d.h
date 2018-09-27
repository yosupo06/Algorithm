struct Pt3 {
    D x, y, z;
    Pt3() {}
    Pt3(D _x, D _y, D _z) : x(_x), y(_y), z(_z) {}
    Pt3 operator+(const Pt3& r) const { return Pt3(x+r.x, y+r.y, z+r.z); }
    Pt3 operator-(const Pt3& r) const { return Pt3(x-r.x, y-r.y, z-r.z); }
    Pt3& operator-=(const Pt3& r) { return *this = *this - r; }
    Pt3 operator-() const { return Pt3(-x, -y, -z); }

    D abs() const { return sqrt(x * x + y * y + z * z); }
    D rabs() const { return max({std::abs(x), std::abs(y), std::abs(z)}); }
};

struct L3 {
    Pt3 s, t;
    L3() {}
    L3(Pt3 s, Pt3 t) : s(s), t(t) {}
    Pt3 vec() const { return t - s; }
    D abs() const { return vec().abs(); }
};

/*
cng viewpoint
l.sを(0, 0, 0), l.tを(0, 0, l.abs()), pを(0, y>0, z)へ移したときのqの座標を返す
*/
Pt3 cng_vp(L3 l, Pt3 p, Pt3 q) {
    l.t -= l.s; p -= l.s; q -= l.s;

    Pt2 base;
    base = Pt2::polar(1, PI / 2 - Pt2(l.t.x, l.t.y).arg());
    tie(l.t.x, l.t.y) = (Pt2(l.t.x, l.t.y) * base).to_pair();
    tie(p.x, p.y) = (Pt2(p.x, p.y) * base).to_pair();
    tie(q.x, q.y) = (Pt2(q.x, q.y) * base).to_pair();

    base = Pt2::polar(1, PI / 2 - Pt2(l.t.y, l.t.z).arg());
    tie(l.t.y, l.t.z) = (Pt2(l.t.y, l.t.z) * base).to_pair();
    tie(p.y, p.z) = (Pt2(p.y, p.z) * base).to_pair();
    tie(q.y, q.z) = (Pt2(q.y, q.z) * base).to_pair();

    base = Pt2::polar(1, PI / 2 - Pt2(p.x, p.y).arg());
    tie(p.x, p.y) = (Pt2(p.x, p.y) * base).to_pair();
    tie(q.x, q.y) = (Pt2(q.x, q.y) * base).to_pair();

    return q;
}
