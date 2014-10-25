Cir curcumCircle(P a, P b, P c) {
    b -= a; c -= a;
    double s = 2*cross(b, c);
    assert(s.abs() > 1e-9);
    double A = (b-c).norm(), B = c.norm(), C = b.norm();
    double S = A+B+C;
    P r = (B*(S-2*B)*b+C*(S-2*C)*c)/(s*s);
    return Cir(r + a, r.abs);
}

Cir smallestEnclosingCircle(P[] p) {
    const eps = 1e-9;
    Cir dfs(P[] p, int pc, P[] q, int qc) {
        Cir get3(in P[3] q) {
            Cir c;
            foreach (int i; 0..3) {
                c[0] = (q[i]+q[(i+1)%3])/2;
                c[1] = abs(q[i]-q[(i+1)%3])/2;
                if (abs(q[(i+2)%3]-c[0]) <= c[1] + eps) {
                    return c;
                }
            }
            return curcumCircle(q[0], q[1], q[2]);            
        }
        Cir get(P[] q, int qc) {
            if (qc == 0) {
                return Cir(P(0, 0), -1);
            }
            if (qc == 1) {
                return Cir(q[0], 0);
            }
            if (qc == 2) {
                return Cir((q[0]+q[1])/2, abs(q[0]-q[1])/2);
            }
            Cir c, r;
            c[1] = -1;
            foreach (i; 0..qc-1) {
                foreach (j; i+1..qc-1) {
                    r = get3([q[i], q[j], q[qc-1]]);
                    if (c[1] < r[1]) {
                        c = r;
                    }
                }
            }
            return c;
        }
        Cir c = get(q, qc);
        foreach (int i; 0..pc) {
            if (abs(p[i]-c[0]) <= c[1] + eps) {
                continue;
            }
            q[qc++] = p[i];
            c = dfs(p, i, q, qc);
            qc--;
        }
        return c;
    }
    static Xorshift rnd = Xorshift(252521);
    randomShuffle(p, rnd);
    static P[100] q;
    return dfs(p, cast(int)p.length, q, 0);
}
