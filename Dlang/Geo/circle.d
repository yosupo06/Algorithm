Cir curcumCircle(in P a,in P b,in P c) pure {
    double s = 2*cross(b-a, b-c);
    assert(s.abs() > 1e-9);
    double A = (b-c).norm(), B = (c-a).norm(), C = (a-b).norm();
    double S = A+B+C;
    return Cir((A*(S-2*A)*a+B*(S-2*B)*b+C*(S-2*C)*c)/(s*s), (A*B*C/(s*s)).sqrt());
}

class SmallestEnclosingCircle {
    /*
    epsだけ(中心,半径)は本来よりズレる
    eps * max(d)が15桁を
    */
    static double eps = 1e-6;
    static Xorshift rnd;
    static this() {
        rnd = Xorshift(unpredictableSeed);
    }

    static Cir get(P[] q) {
        int qc = cast(int)q.length;
        if (qc == 0) {
            return Cir2(P(0, 0), -1);
        }
        if (qc == 1) {
            return Cir2(q[0], 0);
        }
        if (qc == 2) {
            return Cir2((q[0]+q[1])/2, abs(q[0]-q[1])/4);
        }

        if (qc == 3) {
            Cir c;
            foreach (i; 0..3) {
                c[0] = (q[i]+q[(i+1)%3])/2;
                c[1] = abs(q[i]-q[(i+1)%3])/2;
                if (abs(q[(i+2)%3]-c[0]) <= c[1] + eps) {
                    return c;
                }
            }
            return curcumCircle(q[0], q[1], q[2]);
        }
        randomShuffle(q[0..$-1], rnd);
        return dfs(q[0..$-1], [q[$-1]]);
    }
    static Cir dfs(P[] p, P[] q) {
        Cir c = get(q);
        foreach (int i; 0..cast(int)p.length) {
            if (abs(p[i]-c[0]) <= c[1] + eps) {
                continue;
            }
            c = dfs(p[0..i], q ~ p[i]);
        }
        return c;
    }
    static Cir exec(P[] d) {
        randomShuffle(d, rnd);
        return dfs(d, []);
    }
}
