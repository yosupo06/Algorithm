class Primes {
    import std.algorithm : map;
    import std.array : array;
    immutable bool[] isPrime;
    immutable int[] primes;
    this(int n) {
        auto used = new bool[n];
        int[] p;
        used[0] = used[1] = true;
        for (int i = 2; i < n; i++) {
            if (used[i]) continue;
            p ~= i;
            for (int j = i*i; j < n; j+= i) {
                used[j] = true;
            }
        }
        isPrime = used.idup.map!(i => !i).array;
        primes = p.idup;
    }
}

/** The Moebius function.

Params:
    <var>N</var> = an integer

Returns:
    An array mu(<var>n</var>) for 0 <= <var>n</var> < <var>N</var>.
    <dl><dt><var>n</var> is square-free</dt><dd>mu(<var>n</var>) = (-1)<sup>(number of prime factors)</sup></dd>
    <dt><var>n</var> is not square-free</dt><dd>mu(<var>n</var>) = 0</dd></dl>
*/
struct Moebius {
    immutable int[] v;
    this (int N)
    {
        this (new Primes(N));
    }
    this (Primes p) {
        import std.math : sqrt, ceil;
        import std.conv : to;
        import std.range : iota;
        immutable N = p.isPrime.length;
        immutable nsc = N.to!real.sqrt.ceil.to!ulong;
        auto v = new int[N];
        v[] = 1;
        foreach (d; p.primes)
            foreach (i; iota(0, N, d))
                v[i] *= -1;
        foreach (d; p.primes)
        {
            if (nsc <= d)
                break;
            foreach (i; iota(0, N, d*d))
                v[i] = 0;
        }
        this.v = v.dup;
    }
}

unittest
{
    assert (Moebius(100).v[0..30] == [
        0,  1, -1, -1,  0, -1,  1, -1,  0,  0,
        1, -1,  0, -1,  1,  1,  0, -1,  0, -1,
        0,  1,  1, -1,  0,  0,  1,  0,  0, -1]);
}
