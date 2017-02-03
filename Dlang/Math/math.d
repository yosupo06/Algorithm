T[2] extgcd(T)(T a, T b) {
    T d = a;
    if (b) {
        auto x = extgcd(b, a%b);
        swap(x[0], x[1]);
        x[1] -= (a / b) * x[0];
        return x;
    } else {
        return [T(1), T(0)];
    }
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
long[] powModTable(long base, size_t length, int md) {
    import std.range : recurrence, take;
    import std.array : array;
    return 1L.recurrence!((a, i) => (a[i-1]*base) % md).take(length).array;
}

real[] powTable(real base, size_t length) {
    import std.range : recurrence, take;
    import std.array : array;
    return 1.0L.recurrence!((a, i) => a[i-1]*base).take(length).array;
}

//i=0,1,...,num-1についてi! % mdのテーブルを構築する
long[] factModTable(size_t length, int md) {
    import std.range : recurrence, take;
    import std.array : array;
    return 1L.recurrence!((a, i) => (a[i-1]*i) % md).take(length).array;
}

//i=0,1,...,num-1についてi!の逆元のテーブルを構築する
long[] invFactModTable(size_t length, int md) {
    import std.algorithm : map;
    import std.array : array;
    return factModTable(length, md).map!(a => invMod(a, md)).array;
}

unittest {
    import std.algorithm : map, equal;
    import std.range : zip, repeat, take;
    //1009 is prime
    auto x = factModTable(10, 1009);
    auto y = invFactModTable(10, 1009);
    assert(equal(zip(x, y).map!(a => a[0]*a[1] % 1009), repeat(1).take(10)));
}

/// Calculate binomial coefficients C[n, r] for 0 <= r < length.
real[] combTable(long n, size_t length) {
    import std.range : recurrence, take;
    import std.array : array;
    return 1.0L.recurrence!((a, i) => a[i-1] * (n-i+1) / i).take(length).array;
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

//nCk % mdを計算する mdが小さい時に有効
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

//res[n][k] = nCk % mdとなるテーブルを構築
long[][] comb2DTable(long n, long k, int md) {
    long[][] d = new long[][](n, k);
    d[0][0] = 1;
    foreach (i; 1..n) {
        d[i][0] = 1;
        foreach (j; 1..k) {
            d[i][j] = (d[i-1][j] + d[i-1][j-1]) % md;
        }
    }
    return d;
}


