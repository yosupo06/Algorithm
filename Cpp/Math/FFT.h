using R = double;
const R PI = 4*atan(R(1));
using Pc = complex<R>;

void fft(int s, bool type, Pc c[]) {
    const int N = 1<<s;
    Pc *a = new Pc[N];
    Pc *b = new Pc[N];
    copy_n(c, N, a);
    for (int i = 1; i <= s; i++) {
        int W = 1<<(s-i); //変更後の幅W
        for (int y = 0; y < N/2; y += W) {
            Pc now = polar<R>(1, y*(type ? -2*PI : 2*PI)/N);
            for (int x = 0; x < W; x++) {
                auto l =       a[y<<1 | x];
                auto r = now * a[y<<1 | x | W];
                b[y | x]        = l+r;
                b[y | x | N>>1] = l-r;
            }
        }
        swap(a, b);            
    }
    copy_n(a, N, c);
    delete[] a;
    delete[] b;
}
