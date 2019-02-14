template <class Mint> void nft(bool type, V<Mint>& a) {
    int n = int(a.size()), s = 0;
    while ((1 << s) < n) s++;
    assert(1 << s == n);

    V<Mint> b(n);
    for (int i = 1; i <= s; i++) {
        int w = 1 << (s - i);
        Mint base = Mint::G.pow(Mint(-1).v / (1 << i));
        if (type) base = base.inv();
        Mint now = 1;
        for (int y = 0; y < n / 2; y += w) {
            for (int x = 0; x < w; x++) {
                auto l = a[y << 1 | x];
                auto r = now * a[y << 1 | x | w];
                b[y | x] = l + r;
                b[y | x | n >> 1] = l - r;
            }
            now *= base;
        }
        swap(a, b);
    }
}

template <class Mint> V<Mint> multiply(const V<Mint>& a, const V<Mint>& b) {
    int A = int(a.size()), B = int(b.size());
    if (!A || !B) return {};
    int lg = 0;
    while ((1 << lg) < A + B - 1) lg++;
    int N = 1 << lg;
    V<Mint> ac(N, Mint(0)), bc(N, Mint(0));
    for (int i = 0; i < A; i++) ac[i] = a[i];
    for (int i = 0; i < B; i++) bc[i] = b[i];
    nft(false, ac);
    nft(false, bc);
    for (int i = 0; i < N; i++) {
        ac[i] *= bc[i];
    }
    nft(true, ac);
    V<Mint> c(A + B - 1);
    for (int i = 0; i < A + B - 1; i++) {
        c[i] = ac[i] / Mint(N);
    }
    return c;
}
