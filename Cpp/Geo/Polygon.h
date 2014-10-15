typedef vector<P> Pol;

P cu(Pol p, int i) { 
    int s = p.size();
    return p[(i%s+s)%s];
};

//to [-Pi, Pi)
double nptop(double arg) {
    arg = fmod(fmod(arg,M2PI)+M2PI,M2PI);
    if (arg >= MPI) arg -= M2PI;
    return arg;
}

//true:Polygon is counter_cycle false:cycle
bool iscclock(Pol pol) {
    double th = 0;
    for (int i = 0; i < pol.size(); i++) {
        P a = cu(pol,i), b=cu(pol, i+1), c=cu(pol, i+2);
        th += nptop(arg(c-b)-arg(b-a));
    }
    return (th > 0);
}

//0:P is out 1:P is on line 2:P is in
int contains(const Pol &pol, P p) {
    int in = -1;
    for (int i = 0; i < pol.size(); i++) {
        P a=cu(pol,i)-p, b=cu(pol,i+1)-p;
        if (imag(a) > imag(b)) swap(a, b);
        if (imag(a) <= 0 && 0 < imag(b)) {
            if (cross(a, b) < 0) in *= -1;
        }
        if (abs(cross(a, b)) < EPS && dot(a, b) < EPS) return 1;
    }
    return in+1;
}

