---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"src/geo/primitive.hpp\"\nusing D = double;\nconst D PI =\
    \ acos(D(-1)), EPS = 1e-10;\n\nint sgn(D a) { return (a < -EPS) ? -1 : (a > EPS);\
    \ }\nint sgn(D a, D b) { return sgn(a - b); }\nstruct P {\n    D x, y;\n    P(D\
    \ _x = D(), D _y = D()) : x(_x), y(_y) {}\n    P operator+(const P& r) const {\
    \ return {x + r.x, y + r.y}; }\n    P operator-(const P& r) const { return {x\
    \ - r.x, y - r.y}; }\n    P operator*(const P& r) const {\n        return {x *\
    \ r.x - y * r.y, x * r.y + y * r.x};\n    }\n\n    P operator*(const D& r) const\
    \ { return {x * r, y * r}; }\n    P operator/(const D& r) const { return {x /\
    \ r, y / r}; }\n\n    P& operator+=(const P& r) { return *this = *this + r; }\n\
    \    P& operator-=(const P& r) { return *this = *this - r; }\n    P& operator*=(const\
    \ P& r) { return *this = *this * r; }\n    P& operator*=(const D& r) { return\
    \ *this = *this * r; }\n    P& operator/=(const D& r) { return *this = *this /\
    \ r; }\n\n    P operator-() const { return {-x, -y}; }\n\n    bool operator<(const\
    \ P& r) const {\n        return 2 * sgn(x, r.x) + sgn(y, r.y) < 0;\n    }\n  \
    \  bool operator==(const P& r) const { return sgn((*this - r).rabs()) == 0; }\n\
    \    bool operator!=(const P& r) const { return !(*this == r); }\n\n    D norm()\
    \ const { return x * x + y * y; }\n    D abs() const { return sqrt(norm()); }\n\
    \    D rabs() const { return max(std::abs(x), std::abs(y)); }  // robust abs\n\
    \    D arg() const { return atan2(y, x); }\n\n    pair<D, D> to_pair() const {\
    \ return {x, y}; }\n    static P polar(D le, D th) { return {le * cos(th), le\
    \ * sin(th)}; }\n};\nostream& operator<<(ostream& os, const P& p) {\n    return\
    \ os << \"P(\" << p.x << \", \" << p.y << \")\";\n}\n\nstruct L {\n    P s, t;\n\
    \    L(P _s = P(), P _t = P()) : s(_s), t(_t) {}\n    P vec() const { return t\
    \ - s; }\n    D abs() const { return vec().abs(); }\n    D arg() const { return\
    \ vec().arg(); }\n};\nostream& operator<<(ostream& os, const L& l) {\n    return\
    \ os << \"L(\" << l.s << \", \" << l.t << \")\";\n}\n\nD crs(P a, P b) { return\
    \ a.x * b.y - a.y * b.x; }\nD dot(P a, P b) { return a.x * b.x + a.y * b.y; }\n\
    // cross(a, b) is too small?\nint sgncrs(P a, P b) {\n    D cr = crs(a, b);\n\
    \    if (abs(cr) <= (a.rabs() + b.rabs()) * EPS) return 0;\n    return (cr < 0)\
    \ ? -1 : 1;\n}\n\n// -2, -1, 0, 1, 2 : front, clock, on, cclock, back\nint ccw(P\
    \ b, P c) {\n    int s = sgncrs(b, c);\n    if (s) return s;\n    if (!sgn(c.rabs())\
    \ || !sgn((c - b).rabs())) return 0;\n    if (dot(b, c) < 0) return 2;\n    if\
    \ (dot(-b, c - b) < 0) return -2;\n    return 0;\n}\nint ccw(P a, P b, P c) {\
    \ return ccw(b - a, c - a); }\nint ccw(L l, P p) { return ccw(l.s, l.t, p); }\n"
  code: "using D = double;\nconst D PI = acos(D(-1)), EPS = 1e-10;\n\nint sgn(D a)\
    \ { return (a < -EPS) ? -1 : (a > EPS); }\nint sgn(D a, D b) { return sgn(a -\
    \ b); }\nstruct P {\n    D x, y;\n    P(D _x = D(), D _y = D()) : x(_x), y(_y)\
    \ {}\n    P operator+(const P& r) const { return {x + r.x, y + r.y}; }\n    P\
    \ operator-(const P& r) const { return {x - r.x, y - r.y}; }\n    P operator*(const\
    \ P& r) const {\n        return {x * r.x - y * r.y, x * r.y + y * r.x};\n    }\n\
    \n    P operator*(const D& r) const { return {x * r, y * r}; }\n    P operator/(const\
    \ D& r) const { return {x / r, y / r}; }\n\n    P& operator+=(const P& r) { return\
    \ *this = *this + r; }\n    P& operator-=(const P& r) { return *this = *this -\
    \ r; }\n    P& operator*=(const P& r) { return *this = *this * r; }\n    P& operator*=(const\
    \ D& r) { return *this = *this * r; }\n    P& operator/=(const D& r) { return\
    \ *this = *this / r; }\n\n    P operator-() const { return {-x, -y}; }\n\n   \
    \ bool operator<(const P& r) const {\n        return 2 * sgn(x, r.x) + sgn(y,\
    \ r.y) < 0;\n    }\n    bool operator==(const P& r) const { return sgn((*this\
    \ - r).rabs()) == 0; }\n    bool operator!=(const P& r) const { return !(*this\
    \ == r); }\n\n    D norm() const { return x * x + y * y; }\n    D abs() const\
    \ { return sqrt(norm()); }\n    D rabs() const { return max(std::abs(x), std::abs(y));\
    \ }  // robust abs\n    D arg() const { return atan2(y, x); }\n\n    pair<D, D>\
    \ to_pair() const { return {x, y}; }\n    static P polar(D le, D th) { return\
    \ {le * cos(th), le * sin(th)}; }\n};\nostream& operator<<(ostream& os, const\
    \ P& p) {\n    return os << \"P(\" << p.x << \", \" << p.y << \")\";\n}\n\nstruct\
    \ L {\n    P s, t;\n    L(P _s = P(), P _t = P()) : s(_s), t(_t) {}\n    P vec()\
    \ const { return t - s; }\n    D abs() const { return vec().abs(); }\n    D arg()\
    \ const { return vec().arg(); }\n};\nostream& operator<<(ostream& os, const L&\
    \ l) {\n    return os << \"L(\" << l.s << \", \" << l.t << \")\";\n}\n\nD crs(P\
    \ a, P b) { return a.x * b.y - a.y * b.x; }\nD dot(P a, P b) { return a.x * b.x\
    \ + a.y * b.y; }\n// cross(a, b) is too small?\nint sgncrs(P a, P b) {\n    D\
    \ cr = crs(a, b);\n    if (abs(cr) <= (a.rabs() + b.rabs()) * EPS) return 0;\n\
    \    return (cr < 0) ? -1 : 1;\n}\n\n// -2, -1, 0, 1, 2 : front, clock, on, cclock,\
    \ back\nint ccw(P b, P c) {\n    int s = sgncrs(b, c);\n    if (s) return s;\n\
    \    if (!sgn(c.rabs()) || !sgn((c - b).rabs())) return 0;\n    if (dot(b, c)\
    \ < 0) return 2;\n    if (dot(-b, c - b) < 0) return -2;\n    return 0;\n}\nint\
    \ ccw(P a, P b, P c) { return ccw(b - a, c - a); }\nint ccw(L l, P p) { return\
    \ ccw(l.s, l.t, p); }\n"
  dependsOn: []
  isVerificationFile: false
  path: src/geo/primitive.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/geo/primitive.hpp
layout: document
redirect_from:
- /library/src/geo/primitive.hpp
- /library/src/geo/primitive.hpp.html
title: src/geo/primitive.hpp
---
