using D = double;
const D PI = acos(D(-1));
using Pc = complex<D>;

void fft(bool type, V<Pc>& c) {
    int N = int(c.size());
    int s = 0;
    while ((1 << s) < N) s++;
    assert(1 << s == N);

    static V<Pc> ep[30];
    if (!ep[s].size()) {
        for (int i = 0; i < N; i++) {
            ep[s].push_back(polar<D>(1, i * 2 * PI / N));
        }
    }
    V<Pc> a = c, b(N);
    for (int i = 1; i <= s; i++) {
        int W = 1 << (s - i);
        for (int y = 0; y < N / 2; y += W) {
            Pc now = ep[s][y];
            if (type) now = conj(now);
            for (int x = 0; x < W; x++) {
                auto l = a[y << 1 | x];
                auto u = now, v = a[y << 1 | x | W];
                auto r = Pc(u.real() * v.real() - u.imag() * v.imag(),
                            u.real() * v.imag() + u.imag() * v.real());
                b[y | x] = l + r;
                b[y | x | N >> 1] = l - r;
            }
        }
        swap(a, b);
    }
    c = a;
}

template<int G, class Mint>
void nft(bool type, V<Mint>& c) {
    int N = int(c.size());
    int s = 0;
    while ((1 << s) < N) s++;
    assert(1 << s == N);

    V<Mint> a = c, b(N);
    for (int i = 1; i <= s; i++) {
        int W = 1 << (s - i);
        Mint base = Mint(G).pow(Mint(-1).v / (1 << i));
        if (type) base = base.inv();
        Mint now = 1;
        for (int y = 0; y < N / 2; y += W) {
            for (int x = 0; x < W; x++) {
                auto l = a[y << 1 | x];
                auto r = now * a[y << 1 | x | W];
                b[y | x] = l + r;
                b[y | x | N >> 1] = l - r;
            }
            now *= base;
        }
        swap(a, b);
    }
    c = a;
}

V<Pc> multiply(const V<Pc>& a, const V<Pc>& b) {
    int A = int(a.size()), B = int(b.size());
    if (!A || !B) return {};
    int lg = 0;
    while ((1 << lg) < A + B - 1) lg++;
    int N = 1 << lg;
    V<Pc> ac(N), bc(N);
    for (int i = 0; i < A; i++) ac[i] = a[i];
    for (int i = 0; i < B; i++) bc[i] = b[i];
    fft(false, ac);
    fft(false, bc);
    for (int i = 0; i < N; i++) {
        ac[i] *= bc[i];
    }
    fft(true, ac);
    V<Pc> c(A + B - 1);
    for (int i = 0; i < A + B - 1; i++) {
        c[i] = ac[i] / D(N);
    }
    return c;
}

V<D> multiply(const V<D>& a, const V<D>& b) {
    int A = int(a.size()), B = int(b.size());
    if (!A || !B) return {};
    int lg = 0;
    while ((1 << lg) < A + B - 1) lg++;
    int N = 1 << lg;
    V<Pc> d(N);
    for (int i = 0; i < N; i++) d[i] = Pc(i < A ? a[i] : 0, i < B ? b[i] : 0);
    fft(false, d);
    for (int i = 0; i < N / 2 + 1; i++) {
        auto j = i ? (N - i) : 0;
        Pc x = Pc(d[i].real() + d[j].real(), d[i].imag() - d[j].imag());
        Pc y = Pc(d[i].imag() + d[j].imag(), -d[i].real() + d[j].real());
        d[i] = x * y / D(4);
        if (i != j) d[j] = conj(d[i]);
    }
    fft(true, d);
    V<D> c(A + B - 1);
    for (int i = 0; i < A + B - 1; i++) {
        c[i] = d[i].real() / N;
    }
    return c;
}

template<uint G, class Mint>
V<Mint> multiply(const V<Mint>& a, const V<Mint>& b) {
    int A = int(a.size()), B = int(b.size());
    if (!A || !B) return {};
    int lg = 0;
    while ((1 << lg) < A + B - 1) lg++;
    int N = 1 << lg;
    V<Mint> ac(N, Mint(0)), bc(N, Mint(0));
    for (int i = 0; i < A; i++) ac[i] = a[i];
    for (int i = 0; i < B; i++) bc[i] = b[i];
    nft<G>(false, ac);
    nft<G>(false, bc);
    for (int i = 0; i < N; i++) {
        ac[i] *= bc[i];
    }
    nft<G>(true, ac);
    V<Mint> c(A + B - 1);
    for (int i = 0; i < A + B - 1; i++) {
        c[i] = ac[i] / Mint(N);
    }
    return c;
}

template<uint MD>
V<ModInt<MD>> multiply(const V<ModInt<MD>>& a, const V<ModInt<MD>>& b) {
    using Mint = ModInt<MD>;
    constexpr int K = 3, SHIFT = 11;
    int A = int(a.size()), B = int(b.size());
    if (!A || !B) return {};
    int lg = 0;
    while ((1 << lg) < A + B - 1) lg++;
    int N = 1 << lg;

    VV<Pc> x(K, V<Pc>(N)), y(K, V<Pc>(N));
    for (int ph = 0; ph < K; ph++) {
        V<Pc> z(N);
        for (int i = 0; i < N; i++) {
            D nx = 0, ny = 0;
            if (i < A) nx = (a[i].v >> (ph * SHIFT)) & ((1 << SHIFT) - 1);
            if (i < B) ny = (b[i].v >> (ph * SHIFT)) & ((1 << SHIFT) - 1);
            z[i] = Pc(nx, ny);
        }
        fft(false, z);
        for (int i = 0; i < N; i++) {
            z[i] *= 0.5;
        }
        for (int i = 0; i < N; i++) {
            int j = (i) ? N - i : 0;
            x[ph][i] = Pc(z[i].real()+z[j].real(), z[i].imag()-z[j].imag());
            y[ph][i] = Pc(z[i].imag()+z[j].imag(), -z[i].real()+z[j].real());
        }
    }
    VV<Pc> z(K, V<Pc>(N));
    for (int xp = 0; xp < K; xp++) {
        for (int yp = 0; yp < K; yp++) {
            int zp = (xp + yp) % K;
            for (int i = 0; i < N; i++) {
                if (xp + yp < K) {
                    z[zp][i] += x[xp][i] * y[yp][i];
                } else {
                    z[zp][i] += x[xp][i] * y[yp][i] * Pc(0, 1);
                }
            }
        }
    }
    for (int ph = 0; ph < K; ph++) {
        fft(true, z[ph]);
    }
    V<Mint> c(A + B - 1);
    Mint base = 1;
    for (int ph = 0; ph < 2 * K - 1; ph++) {
        for (int i = 0; i < A + B - 1; i++) {
            if (ph < K) {
                c[i] += Mint(ll(round(z[ph][i].real() / N))) * base;
            } else {
                c[i] += Mint(ll(round(z[ph - K][i].imag() / N))) * base;
            }
        }
        base *= 1 << SHIFT;
    }
    return c;
}
