using R = double;
const R PI = 4*atan(R(1));
using Pc = complex<R>;

void fft(bool type, vector<Pc> &c) {
    static vector<Pc> buf[30];
    int N = int(c.size());
    int s = bsr(N);
    assert(1<<s == N);
    if (!buf[s].size()) {
        buf[s] = vector<Pc>(N);
        for (int i = 0; i < N; i++) {
            buf[s][i] = polar<R>(1, i*2*PI/N);
        }
    }
    vector<Pc> a(N), b(N);
    copy(begin(c), end(c), begin(a));
    for (int i = 1; i <= s; i++) {
        int W = 1<<(s-i); //変更後の幅W
        for (int y = 0; y < N/2; y += W) {
            Pc now = buf[s][y]; if (type) now = conj(now);
            for (int x = 0; x < W; x++) {
                auto l =       a[y<<1 | x];
                auto r = now * a[y<<1 | x | W];
                b[y | x]        = l+r;
                b[y | x | N>>1] = l-r;
            }
        }
        swap(a, b);            
    }
    copy(begin(a), end(a), begin(c));
}

template<int B, uint MD>
void nft(bool type, vector<ModInt<MD>> &c) {
    using Mint = ModInt<MD>;
    int N = int(c.size());
    int s = bsr(N);
    assert(1<<s == N);
    vector<Mint> a(N), b(N);
    copy(begin(c), end(c), begin(a));
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
    copy(begin(a), end(a), begin(c));
}

template<class Mint>
vector<Mint> multiply(vector<Mint> x, vector<Mint> y) {
    int S = x.size()+y.size()-1;
    int N = 2<<bsr(S-1);
    vector<Pc> a[3], b[3];
    for (int fe = 0; fe < 3; fe++) {
        a[fe] = vector<Pc>(N);
        b[fe] = vector<Pc>(N);
        for (int i = 0; i < int(x.size()); i++) {
            a[fe][i] = Pc((x[i].v >> (fe*10)) & ((1<<10)-1), 0);
        }
        for (int i = 0; i < int(y.size()); i++) {
            b[fe][i] = Pc((y[i].v >> (fe*10)) & ((1<<10)-1), 0);
        }
        fft(false, a[fe]);
        fft(false, b[fe]);
    }
 
    vector<Mint> z(S);
    vector<Pc> c(N);
    Mint base = 1;
    for (int fe = 0; fe < 5; fe++) {
        fill_n(begin(c), N, Pc(0, 0));
        for (int xf = max(fe-2, 0); xf <= min(2, fe); xf++) {
            int yf = fe-xf;
            for (int i = 0; i < N; i++) {
                c[i] += a[xf][i]*b[yf][i];
            }
        }
        fft(true, c);
        for (int i = 0; i < S; i++) {
            c[i] *= 1.0/N;
            z[i] += Mint(ll(round(c[i].real()))) * base;
        }
        base *= 1<<10;
    }
    return z;
}
