T gcd(T)(T a, T b) {
    if (b==0) return a;
    return gcd(b, a%b);
}

long powMod(long x, long n, long md) {
    x %= md; n %= md-1;
    long r = 1;
    while (n) {
        if (n & 1) r *= x; r %= md;
        x *= x; x %= md;
        n >>= 1;
    }
    return r;
}

long invMod(long r, long md) {
    return powMod(r, md-2, md);
}

void powModTable(long[] d, long b, long md) {
    d[0] = 1;
    foreach (i; 1..d.length) {
        d[i] = (d[i-1]*b)%md;
    }
}
void powTable(double[] d, double b) {
    d[0] = 1;
    foreach (i; 1..d.length) {
        d[i] = (d[i-1]*b);
    }
}

void combTable(double[] d, long n) {
    d[0] = 1;
    foreach (i; 1..d.length) {
        d[i] = d[i-1]*(n-i+1)/i;
    }
}
long combMod(long n, long k, long md) {
    assert(k < md);
    n %= md;
    if (n < k || k < 0) return 0;
    long r = 1;
    foreach (i; 1..k+1) {
        r *= i;
        r %= md;
    }
    r = invMod(r, md);
    foreach (i; n-k+1..n+1) {
        r *= i;
        r %= md;
    }
    return r;
}

long lucas(long n, long k, long md) {
    if (n < k) return 0;
    long res = 1;
    while (n) {
        auto a = n % md;
        auto b = k % md;
        n /= md; k /= md;
        res *= combMod(a, b, md);
    }
    return res;
}

class CombinationGen(MD) {
    long[][] d;
    this(int n, int k) {
        d = new long[][](n+1, k+1);
        foreach (j; 0..k+1) {
            d[0][j] = 0;
        }
        foreach (i; 0..n+1) {
            d[i][0] = 1;
        }
        foreach (i; 1..n+1) {
            foreach (j; 1..k+1) {
                d[i][j] = (d[i-1][j] + d[i-1][j-1]) % MD;
            }
        }
    }
}

