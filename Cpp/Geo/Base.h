#include <complex>
#include <vector>
#include <cmath>
using namespace std;

const double EPS = 1e-9;
const double MPI = acos(-1);
const double M2PI = 2*MPI;

typedef complex<double> P;
struct L {
    P x, y;
    L() {};
    L(P a, P b) {x=a, y=b;};
};

namespace std {
    bool operator < (P a, P b) {
        return real(a) != real(b) ? real(a) < real(b) : imag(a) < imag(b);
    }
}

double cross(P a, P b) { return imag(conj(a)*b); }
double dot(P a, P b) { return real(conj(a)*b); }


int ccw(P a, P b, P c) {
    b -= a; c -= a;
    double cr = cross(b-a, c-a);
    if (cr > EPS) return 1;
    if (cr < -EPS) return -1;
    if (dot(b-a, c-a) < -EPS) return 2;
    if (dot(a-b, c-b) < -EPS) return -2;
    return 0;
}
