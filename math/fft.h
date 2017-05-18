using R = double;
const R PI = 4*atan(R(1));

void fft(bool type, V<Pc> &c) {
    static V<Pc> buf[30];
    int N = int(c.size());
    int s = bsr(N);
    assert(1<<s == N);
    if (!buf[s].size()) {
        buf[s] = V<Pc>(N);
        for (int i = 0; i < N; i++) {
            buf[s][i] = Pc::polar(1, i*2*PI/N);
        }
    }
    V<Pc> a = c, b(N);
    for (int i = 1; i <= s; i++) {
        int W = 1<<(s-i); //変更後の幅W
        for (int y = 0; y < N/2; y += W) {
            Pc now = buf[s][y]; if (type) now.y *= -1;
            for (int x = 0; x < W; x++) {
                auto l =       a[y<<1 | x];
                auto r = now * a[y<<1 | x | W];
                b[y | x]        = l+r;
                b[y | x | N>>1] = l-r;
            }
        }
        swap(a, b);            
    }
    c = a;
}

template<class Mint>
V<Mint> multiply(V<Mint> x, V<Mint> y) {
    constexpr int B = 3, SHIFT = 10;
    int S = x.size()+y.size()-1;
    int N = 2<<bsr(S-1);
    V<Pc> a[B], b[B];
    for (int fe = 0; fe < B; fe++) {
        a[fe] = V<Pc>(N);
        b[fe] = V<Pc>(N);
        V<Pc> c(N);
        for (int i = 0; i < int(x.size()); i++) {
            c[i].x = (x[i].v >> (fe*SHIFT)) & ((1<<SHIFT)-1);
        }
        for (int i = 0; i < int(y.size()); i++) {
            c[i].y = (y[i].v >> (fe*SHIFT)) & ((1<<SHIFT)-1);
        }
        fft(false, c);
        for (int i = 0; i < N; i++) {
            c[i] *= 0.5;
        }
        for (int i = 0; i < N; i++) {
            int j = (N-i)%N;
            a[fe][i] = Pc(c[i].x+c[j].x, c[i].y-c[j].y);
            b[fe][i] = Pc(c[i].y+c[j].y, -c[i].x+c[j].x);
        }
    }
    V<Mint> z(S);
    V<Pc> c[B];
    for (int fe = 0; fe < B; fe++) {
        c[fe] = V<Pc>(N);
    }
    for (int af = 0; af < B; af++) {
        for (int bf = 0; bf < B; bf++) {
            int cf = (af+bf)%B;
            for (int i = 0; i < N; i++) {
                if (af+bf<B) {
                    c[cf][i] += a[af][i]*b[bf][i];
                } else {
                    c[cf][i] += a[af][i]*b[bf][i]*Pc(0, 1);
                }
            }
        }
    }
    for (int fe = 0; fe < B; fe++) {
        fft(true, c[fe]);
    }
    Mint base = 1;
    for (int fe = 0; fe < 2*B-1; fe++) {
        for (int i = 0; i < S; i++) {
            if (fe < B) {
                c[fe][i].x *= 1.0/N;
                z[i] += Mint(ll(round(c[fe][i].x)))*base;
            } else {       
                c[fe-B][i].y *= 1.0/N;
                z[i] += Mint(ll(round(c[fe-B][i].y)))*base;
            }
        }
        base *= 1<<SHIFT;
    }
    return z;
}

template<int B, uint MD>
void nft(bool type, V<ModInt<MD>> &c) {
    using Mint = ModInt<MD>;
    int N = int(c.size());
    int s = bsr(N);
    assert(1<<s == N);
    V<Mint> a = c, b(N);
    for (int i = 1; i <= s; i++) {
        int W = 1<<(s-i); //変更後の幅W
        Mint base = pow(Mint(B), (MD-1)/(1<<i));
        if (type) base = Mint::inv(base);
        Mint now = 1;
        for (int y = 0; y < N/2; y += W) {
            for (int x = 0; x < W; x++) {
                auto l =       a[y<<1 | x];
                auto r = now * a[y<<1 | x | W];
                b[y | x]        = l+r;
                b[y | x | N>>1] = l-r;
            }
            now *= base;
        }
        swap(a, b);
    }
    c = a;
}
