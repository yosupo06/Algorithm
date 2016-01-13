using R = double;
const R PI = 4.0*atan(1.0);
using Pc = complex<R>;

void fft(int s, bool type, Pc c[]) {
    const int N = 1<<s;
    Pc *a = new Pc[N]
    Pc *b = new Pc[N];
    copy_n(c, N, a);
    for (int i = 1; i <= s; i++) {
        int H = 1<<(i-1), W = 1<<(s-i); //高さ2H, 幅W
        Pc base = polar<R>(1, (type ? -PI : PI) / H);
        Pc now = Pc(1, 0);
        for (int y = 0; y < (N>>1); y += W) {
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
    copy_n(a, N, c);
    delete[] a;
    delete[] b;
}
