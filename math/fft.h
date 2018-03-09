using R = double;
const R PI = 4*atan(R(1));

using Pc = complex<R>;
Pc* ep_list(bool type, int s) {
    static V<Pc> buf[2][30];
    int N = 1<<s;
    if (!buf[type][s].size()) {
        buf[type][s] = V<Pc>(N);
        for (int i = 0; i < N; i++) {
            buf[type][s][i] = polar<R>(1, i*2*PI/N);
            if (type) buf[type][s][i] = conj(buf[type][s][i]);
        }
    }
    return buf[type][s].data();
}

void fft(bool type, V<Pc> &c) {
    int N = int(c.size());
    int s = 0;
    while ((1<<s) < N) s++;
    assert(1<<s == N);
    auto list = ep_list(type, s);
    V<Pc> a = c, b(N);
    for (int i = 1; i <= s; i++) {
        int W = 1<<(s-i);
        for (int y = 0; y < N/2; y += W) {
            Pc now = list[y];
            for (int x = 0; x < W; x++) {
                auto l =       a[y<<1 | x];
                auto u = now, v = a[y<<1 | x | W];
                auto r = Pc(u.real() * v.real() - u.imag() * v.imag(),
                    u.real() * v.imag() + u.imag() * v.real());
                b[y | x]        = l+r;
                b[y | x | N>>1] = l-r;
            }
        }
        swap(a, b);
    }
    c = a;
}

V<Pc> fft_from_double(bool type, const V<double> &c) {
    int N = int(c.size());
    int s = 0;
    while ((1<<s) < N) s++;
    assert(1<<s == N);
    int M = int(c.size());
    if (s == 0) return {Pc(c[0], 0)};
    V<Pc> d(N/2);
    for (int i = 0; i < N/2; i++) {
        d[i] = Pc(c[2*i], c[2*i+1]);
    }
    fft(type, d);
    V<Pc> le(N/2), ri(N/2);
    for (int i = 0; i < N/2; i++) {
        auto j = i ? (N/2-i) : 0;
        le[i] = Pc(d[i].real()+d[j].real(), d[i].imag()-d[j].imag()) / R(2);
        ri[i] = Pc(d[i].imag()+d[j].imag(), -d[i].real()+d[j].real()) / R(2);
    }
    d.resize(N);
    auto list = ep_list(type, s);
    for (int i = 0; i < N/2; i++) {
        d[i] = le[i] + list[i] * ri[i];
        d[i+N/2] = le[i] - list[i] * ri[i];
    }
    return d;
}

V<R> fft_to_double(bool type, const V<Pc> &c) {
    int N = int(c.size());
    int s = 0;
    while ((1<<s) < N) s++;
    assert(1<<s == N);
    if (s == 0) return {c[0].real()};
    auto list = ep_list(type, s);
    V<Pc> le(N/2), ri(N/2);
    for (int i = 0; i < N/2; i++) {
        le[i] = (c[i] + c[i+N/2]);
        ri[i] = list[i] * (c[i] - c[i+N/2]);
    }
    V<Pc> d(N/2);
    for (int i = 0; i < N/2; i++) {
        d[i] = Pc(le[i].real()-ri[i].imag(), le[i].imag()+ri[i].real());
    }
    fft(type, d);
    V<R> e(N);
    for (int i = 0; i < N/2; i++) {
        e[2*i] = d[i].real();
        e[2*i+1] = d[i].imag();
    }
    return e;
}

V<Pc> multiply(const V<Pc> &a, const V<Pc> &b) {
    int A = int(a.size()), B = int(b.size());
    if (!A || !B) return {};
    int lg = 1;
    while ((1<<lg) < A+B-1) lg++;
    int N = 1<<lg;
    V<Pc> ac(N, Pc(0, 0)), bc(N, Pc(0, 0));
    for (int i = 0; i < A; i++) ac[i] = a[i];
    for (int i = 0; i < B; i++) bc[i] = b[i];
    fft(false, ac);
    fft(false, bc);
    for (int i = 0; i < N; i++) {
        ac[i] *= bc[i];
    }
    fft(true, ac);
    V<Pc> c(A+B-1);
    for (int i = 0; i < A+B-1; i++) {
        c[i] = ac[i] / R(N);
    }
    return c;
}

V<R> multiply(const V<R> &a, const V<R> &b) {
    int A = int(a.size()), B = int(b.size());
    if (!A || !B) return {};
    int lg = 1;
    while ((1<<lg) < A+B-1) lg++;
    int N = 1<<lg;
    V<Pc> ac(N, Pc(0, 0)), bc(N, Pc(0, 0));
    for (int i = 0; i < A; i++) ac[i] = Pc(a[i], 0);
    for (int i = 0; i < B; i++) bc[i] = Pc(b[i], 0);
    fft(false, ac);
    fft(false, bc);
    for (int i = 0; i < N; i++) {
        ac[i] *= bc[i];
    }
    fft(true, ac);
    V<R> c(A+B-1);
    for (int i = 0; i < A+B-1; i++) {
        c[i] = ac[i].real() / N;
    }
    return c;
}

V<R> multiply_opt(const V<R> &a, const V<R> &b) {
    int A = int(a.size()), B = int(b.size());
    if (!A || !B) return {};
    int lg = 1;
    while ((1<<lg) < A+B-1) lg++;
    int N = 1<<lg;
    V<Pc> d(N, Pc(0, 0));
    for (int i = 0; i < A; i++) d[i] = Pc(a[i], d[i].imag());
    for (int i = 0; i < B; i++) d[i] = Pc(d[i].real(), b[i]);
    fft(false, d);
    for (int i = 0; i < N/2+1; i++) {
        auto j = i ? (N-i) : 0;
        Pc x = Pc(d[i].real()+d[j].real(), d[i].imag()-d[j].imag());
        Pc y = Pc(d[i].imag()+d[j].imag(), -d[i].real()+d[j].real());
        d[i] = x * y / R(4);
        if (i != j) d[j] = conj(d[i]);
    }
    fft(true, d);
    V<R> c(A+B-1);
    for (int i = 0; i < A+B-1; i++) {
        c[i] = d[i].real() / N;
    }
    return c;
}

V<R> multiply_opt2(const V<R> &a, const V<R> &b) {
    int A = int(a.size()), B = int(b.size());
    if (!A || !B) return {};
    int lg = 1;
    while ((1<<lg) < A+B-1) lg++;
    int N = 1<<lg;
    V<R> _a = a, _b = b;
    _a.resize(N), _b.resize(N);
    V<Pc> le = fft_from_double(false, _a);
    V<Pc> ri = fft_from_double(false, _b);
    V<Pc> d(N);
    for (int i = 0; i < N; i++) {
        d[i] = le[i] * ri[i];
    }
    V<R> e = fft_to_double(true, d);
    V<R> c(A+B-1);
    for (int i = 0; i < A+B-1; i++) {
        c[i] = e[i] / N;
    }
    return c;
}
