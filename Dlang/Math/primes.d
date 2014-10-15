class Primes {
    immutable bool[] isPrime;
    immutable int[] primes;
    this(int n) {
        auto used = new bool[n];
        int[] p;
        used[0] = used[1] = true;
        for (int i = 2; i < n; i++) {
            if (used[i]) continue;
            p ~= i;
            for (int j = i*2; j < n; j+= i) {
                used[j] = true;
            }
        }
        isPrime = used.idup.map!(i => !i).array;
        primes = p.idup;
    }
};

template <int N>
struct Moebius {
    using ll = long long;
    int v[N];
    Moebius(Primes<N> &p) {
        fill_n(v, N, -1);
        for (ll d: p.primes) {
            for (ll i = d; i < N; i += d) {
                v[i] *= -1;
            }
            for (ll i = d*d; i < N; i += d*d) {
                v[i] = 0;
            }
        }       
    }
};