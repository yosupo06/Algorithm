#include <vector>

//prims.size -> N=100k:near10k
template <int N>
struct Primes {
    bool used[N] = {};
    std::vector<int> primes;
    Primes() {
        for (int i = 2; i < N; i++) {
            if (!used[i]) {
                primes.push_back(i);
            }
            for (int j = i; j < N; j += i) {
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