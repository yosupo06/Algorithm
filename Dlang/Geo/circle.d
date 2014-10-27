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
    P[10000] pb;
    P[3] q;
    const eps = 1e-9;
    int pbc = 1;
    int cnt = 0;
    Cir dfs(int pc, int qc) {
        Cir get() {
            final switch (qc) {
            case 3:
                return curcumCircle(q[0], q[1], q[2]);
            case 2:
                return Cir((q[0]+q[1])/2, abs(q[0]-q[1])/2);
            case 1:
                return Cir(q[0], 0);
            case 0:
                return Cir(P(0, 0), -1);
            }
        }
        Cir c = get();
        foreach_reverse (i; max(-pc+1, 1)..pbc) {
            if ( abs(pb[i]-c[0]) <= c[1] + eps) {
                continue;
            }
            q[qc++] = pb[i];
            c = dfs(-i, qc);
            qc--;
        }
        foreach (int i; 0..pc) {
            if (p[i].re == p[i].re.infinity || abs(p[i]-c[0]) <= c[1] + eps) {
                continue;
            }
            q[qc++] = p[i];
            c = dfs(i, qc);
            qc--;
            pb[pbc++] = p[i];
            p[i].re = double.infinity;
        }
        return c;
    }
    return dfs(cast(int)p.length, 0);
}
