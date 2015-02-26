T gcd(T)(T a, T b) {
    if (b==0) return a;
    return gcd(b, a%b);
}

//(md-1)*(md-1)がlongに収まらないとオーバーフローを起こすためmdをintにしている
//mdは必ず素数
long powMod(long x, long n, int md) {
    x %= md; n %= md-1;
    long r = 1;
    while (n) {
        if (n & 1) r *= x; r %= md;
        x *= x; x %= md;
        n >>= 1;
    }
    return r;
}

//rのmdでの逆元
//mdは必ず素数
long invMod(long r, int md) {
    return powMod(r, md-2, md);
}

//O(sqrt(x)) xの素因数を列挙する
T[] factor(T)(T x) {
    T[] res;
    T y = x;
    for (T i = 2; i*i <= x; i++) {
        while (y % i == 0) {
            res ~= i;
            y /= i;
        }
    }
    if (y > 1) res ~= y;
    return res;
}

//res[i]にnをbase進数で表したi桁目が入る
T[] convDigit(T)(T n, T base) {
    T[] res;
    while (n) {
        res ~= n % base;
        n /= base;
    }
    return res;
}

//i=0,1,...,num-1についてbase^i % mdのテーブルを構築する
long[] powModTable(int num, long base, int md) {
    auto res = new long[](num);
    res[0] = 1;
    foreach (i; 1..num) {
        res[i] = (res[i-1]*num) % md;
    }
    return res;
}

double[] powTable(int num, double base) {
    auto res = new double[](num);
    res[0] = 1.0;
    foreach (i; 1..num) {
        res[0] = res[i-1]*num;
    }
    return res;
}


/*
 ここからはまずい
 */


void combTable(double[] d, long n) {
    d[0] = 1;
    foreach (i; 1..d.length) {
        d[i] = d[i-1]*(n-i+1)/i;
    }
}
long combMod(long n, long k, int md) {
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

long lucas(long n, long k, int md) {
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

