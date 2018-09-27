#include "gtest/gtest.h"
#include "base.h"
#include "random.h"
#include "datastructure/wavelet.h"

struct WaveletNaive {
    V<int> v;
    WaveletNaive(V<int> _v = V<int>()) : v(_v) {}

    int rank(int a, int b, int u) {
        int ans = 0;
        for (int i = a; i < b; i++) {
            if (v[i] < u) ans++;
        }
        return ans;
    }

    int select(int a, int b, int k) {
        V<int> buf(v.begin() + a, v.begin() + b);
        sort(buf.begin(), buf.end());
        return buf[k];
    }
};


TEST(Wavelet, RankTest) {
    for (int te = 0; te < 100; te++) {
        int n = rand_int(1, 100);
        int q = rand_int(1, 100);
        V<int> v(n);
        for (int i = 0; i < n; i++) v[i] = rand_int(0, 100);
        Wavelet wt(v);
        WaveletNaive wtn(v);
        for (int ph = 0; ph < q; ph++) {
            int a = rand_int(0, n-1);
            int b = rand_int(0, n-1);
            if (a > b) swap(a, b);
            b++;
            int u = rand_int(0, 100);
            EXPECT_EQ(wt.rank(a, b, u), wtn.rank(a, b, u));
        }
    }
}

TEST(Wavelet, SelectTest) {
    for (int te = 0; te < 100; te++) {
        int n = rand_int(1, 100);
        int q = rand_int(1, 100);
        V<int> v(n);
        for (int i = 0; i < n; i++) v[i] = rand_int(0, 100);
        Wavelet wt(v);
        WaveletNaive wtn(v);
        for (int ph = 0; ph < q; ph++) {
            int a = rand_int(0, n-1);
            int b = rand_int(0, n-1);
            if (a > b) swap(a, b);
            b++;
            int k = rand_int(0, b-a-1);
            EXPECT_EQ(wt.select(a, b, k), wtn.select(a, b, k));
        }
    }
}

TEST(Wavelet, CompressRankTest) {
    for (int te = 0; te < 100; te++) {
        int n = rand_int(1, 100);
        int q = rand_int(1, 100);
        V<int> v(n);
        for (int i = 0; i < n; i++) v[i] = rand_int(0, 100);
        CompressWavelet wt(v);
        WaveletNaive wtn(v);
        for (int ph = 0; ph < q; ph++) {
            int a = rand_int(0, n-1);
            int b = rand_int(0, n-1);
            if (a > b) swap(a, b);
            b++;
            int u = rand_int(0, 100);
            assert(wt.rank(a, b, u) == wtn.rank(a, b, u));
        }
    }
}

TEST(Wavelet, CompressSelectTest) {
    for (int te = 0; te < 100; te++) {
        int n = rand_int(1, 100);
        int q = rand_int(1, 100);
        V<int> v(n);
        for (int i = 0; i < n; i++) v[i] = rand_int(0, 100);
        CompressWavelet wt(v);
        WaveletNaive wtn(v);
        for (int ph = 0; ph < q; ph++) {
            int a = rand_int(0, n-1);
            int b = rand_int(0, n-1);
            if (a > b) swap(a, b);
            b++;
            int k = rand_int(0, b-a-1);
            EXPECT_EQ(wt.select(a, b, k), wtn.select(a, b, k));
        }
    }
}

