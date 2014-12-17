//prims.size -> N=100k:near10k
template <int N>
struct Primes {
    bool used[N];
    vector<int> p;
    Primes() {
        used[0] = used[1] = true;
        for (int i = 2; i < N; i++) {
            if (!used[i]) {
                p.push_back(i);
            }
            for (int j = 2*i; j < N; j += i) {
                used[j] = true;
            }
        }
    }
};

template <int N>
struct Moebius {
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