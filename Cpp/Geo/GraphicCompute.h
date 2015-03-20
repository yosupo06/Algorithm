C circumCircle(T t) {
    P a = t.d[0], b = t.d[1], c = t.d[2];
    b -= a; c -= a;
    R s = 2*cross(b, c);
    R x = norm(b-c), y = norm(c), z = norm(b);
    R S = x+y+z;
    P r = (y*(S-2*y)*b+z*(S-2*z)*c)/(s*s);
    return C(r + a, abs(r));
}

C smallestEnclosingCircle(Pol &p, int ps, T q = T(), int qs = 0) {
    if (!ps) {
        switch (qs) {
            case 0:
                return C(P(0, 0), -1);
            case 1:
                return C(q.d[0], 0);
            case 2:
                return C((q.d[0]+q.d[1])/R(2.0), abs(q.d[0]-q.d[1])/R(2.0));
            case 3:
                return circumCircle(q);
        }
        assert(false);
    }
    C c = smallestEnclosingCircle(p, ps-1, q, qs);
    if (sgn(c.r, abs(p[ps-1]-c.p)) == 1) {
        q.d[qs] = p[ps-1];
        return smallestEnclosingCircle(p, ps-1, q, qs+1);
    }
    return c;
}