#include "gtest/gtest.h"
#include "base.h"
#include "random.h"
#include "math/modint.h"
#include "fft.h"

TEST(FFTYosupo, FFTRandom) {
    auto naive_fft = [&](V<int> a, V<int> b) {
        int A = int(a.size()), B = int(b.size());
        V<int> c(A+B-1);
        for (int i = 0; i < A; i++) {
            for (int j = 0; j < B; j++) {
                c[i+j] += a[i] * b[j];
            }
        }
        return c;
    };

    auto fast_fft = [&](V<int> a, V<int> b) {
        int A = int(a.size()), B = int(b.size());
        V<D> na(A), nb(B);
        for (int i = 0; i < A; i++) na[i] = a[i];
        for (int i = 0; i < B; i++) nb[i] = b[i];
        auto nc = multiply(na, nb);
        V<int> c(A+B-1);
        for (int i = 0; i < A+B-1; i++) c[i] = int(round(nc[i]));
        return c;
    };

    auto fast2_fft = [&](V<int> a, V<int> b) {
        int A = int(a.size()), B = int(b.size());
        V<Pc> na(A), nb(B);
        for (int i = 0; i < A; i++) na[i] = Pc(a[i], 0);
        for (int i = 0; i < B; i++) nb[i] = Pc(b[i], 0);
        auto nc = multiply(na, nb);
        V<int> c(A+B-1);
        for (int i = 0; i < A+B-1; i++) c[i] = int(round(nc[i].real()));
        return c;
    };

    auto check_fft = [&](int A, int B) {
        V<int> a(A), b(B);
        for (int i = 0; i < A; i++) {
            a[i] = rand_int(0, 100);
        }
        for (int i = 0; i < B; i++) {
            b[i] = rand_int(0, 100);
        }
        V<int> c1 = naive_fft(a, b);
        V<int> c2 = fast_fft(a, b);
        V<int> c3 = fast2_fft(a, b);
        ASSERT_EQ(c1.size(), A+B-1);
        ASSERT_EQ(c2.size(), A+B-1);
        ASSERT_EQ(c3.size(), A+B-1);
        for (int i = 0; i < A+B-1; i++) {
            assert(c1[i] == c2[i]);
            assert(c1[i] == c3[i]);
        }
    };

    int N = 50;
    for (int l = 1; l < N; l++) {
        for (int r = 1; r < N; r++) {
            check_fft(l, r);
        }
    }
}
