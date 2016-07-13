using R = double;
const R PI = 4*atan(R(1));
using Pc = complex<R>;

void fft(int s, bool type, Pc c[]) {
    const int N = 1<<s;
    vector<Pc> a(N), b(N);
    copy_n(c, N, a.begin());
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
    copy_n(a.begin(), N, c);
}

void multiply(int s, int x[], int y[], ll z[]) {
    // x*y -> z. x_i, y_i must positive and lower than 2^30
    //!!!this code may be overflow!!!
    const int N = 1<<s;
    Pc *a[3]; Pc *b[3];
    for (int fe = 0; fe < 3; fe++) {
        a[fe] = new Pc[N]; b[fe] = new Pc[N];
        for (int i = 0; i < N; i++) {
            a[fe][i] = Pc((x[i] >> (fe*10)) & ((1<<10)-1), 0);
            b[fe][i] = Pc((y[i] >> (fe*10)) & ((1<<10)-1), 0);
        }
        fft(s, false, a[fe]);
        fft(s, false, b[fe]);
    }
    Pc *c = new Pc[N];
    fill_n(z, N, 0);
    for (int fe = 0; fe < 5; fe++) {
        fill_n(c, N, Pc(0, 0));
        for (int xf = max(fe-2, 0); xf <= min(2, fe); xf++) {
            int yf = fe-xf;
            for (int i = 0; i < N; i++) {
                c[i] += a[xf][i]*b[yf][i];
            }
        }
        fft(s, true, c);
        for (int i = 0; i < N; i++) {
            c[i] *= 1.0/N;
            z[i] += ll(round(c[i].real())) << (fe*10);
        }
    }
    for (int i = 0; i < 3; i++) {
        delete[] a[i];
        delete[] b[i];
    }
    delete[] c;
}
