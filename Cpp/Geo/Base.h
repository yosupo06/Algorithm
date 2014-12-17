typedef long double R;
typedef complex<R> P;

const R EPS = 1e-10;
const R PI = acos(-1);
int sgn(R a) {
    if (a < -EPS) return -1;
    if (a > EPS) return 1;
    return 0;
}


bool near(P a, P b) {
    return !sgn(abs(a-b));
}

R cross(P a, P b) { return imag(conj(a)*b); }
R dot(P a, P b) { return real(conj(a)*b); }

struct L {
    P x, y;
    L() {};
    L(P x, P y) :x(x), y(y) {};
};

namespace std {
    bool operator < (P a, P b) {
        return real(a) != real(b) ? real(a) < real(b) : imag(a) < imag(b);
    }
}

int ccw(P a, P b, P c) {
    b -= a; c -= a;
    double cr = cross(b-a, c-a);
    if (cr > EPS) return 1;
    if (cr < -EPS) return -1;
    if (dot(b-a, c-a) < -EPS) return 2;
    if (dot(a-b, c-b) < -EPS) return -2;
    return 0;
}
