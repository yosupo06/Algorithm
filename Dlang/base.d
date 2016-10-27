T read(T)() {
    import std.stdio : readln;
    import std.string : split;
    import std.conv : to;
    string readToken() {
        static size_t pos;
        static string[] tokens;
        while (!(pos < tokens.length)) {
            pos = 0;
            tokens = readln.split;
        }
        return tokens[pos++];
    }
    return readToken.to!T;
}


T lcm(T)(T a, T b) {
    import std.numeric : gcd;
    return a/gcd(a,b)*b;
}

uint powMod(long x, ulong n, uint md) {
    if (md == 1) return 0;
    x = (x%md+md)%md;
    long r = 1;
    while (n) {
        if (n & 1) r = r*x % md;
        x = x*x % md;
        n >>= 1;
    }
    return cast(uint)r;
}

T pow(T)(T x, ulong n) {
    T r = 1;
    while (n) {
        if (n & 1) r *= x;
        x *= x;
        n >>= 1;
    }
    return r;
}

int invMod(int r, uint md) {
    return powMod(r, md-2, md);
}

struct ModInt(uint MD) {
    import std.conv : to;
    uint v;
    this(int v) {this.v = (v%MD+MD)%MD;}
    this(long v) {this.v = (v%MD+MD)%MD;}
    auto normS(uint x) {return (x<MD)?x:x-MD;}
    auto make(uint x) {ModInt m; m.v = x; return m;}
    auto opBinary(string op:"+")(ModInt r) {return make(normS(v+r.v));}
    auto opBinary(string op:"-")(ModInt r) {return make(normS(v+MD-r.v));}
    auto opBinary(string op:"*")(ModInt r) {return make(cast(ulong)v*r.v%MD);}
    auto opOpAssign(string op)(ModInt r) {return mixin ("this=this"~op~"r");}
    static ModInt inv(ModInt x) {return pow(x, MD-2);}
    string toString() {return v.to!string;}
}
//alias Mint = ModInt!(10^^9+7);

unittest {
    import std.random;
    auto gen = Random(unpredictableSeed);
    // powMod
    foreach (_; 0..1000) {
        int x = uniform(0, 1000, gen);
        int y = uniform(0, 1000, gen);
        int md = uniform(2, 1000, gen);
        int ans1 = cast(int)(powMod(x, y, md));
        int ans2 = 1;
        foreach (i; 0..y) {
            ans2 *= x; ans2 %= md;
        }
        assert(ans1 == ans2);
    }
}

unittest {
    import std.random;
    auto gen = Random(unpredictableSeed);
    // Mint
    immutable MD = 10^9+7;
    alias Mint = ModInt!(MD);
    foreach (_; 0..1000) {
        int x = uniform(0, MD, gen);
        int y = uniform(0, MD, gen);
        Mint mx = x, my = y;
        assert((mx+my).v == (x+y) % MD);
        assert((mx-my).v == (x-y+MD) % MD);
        assert((mx*my).v == (cast(ulong)x*y) % MD);
    }
}