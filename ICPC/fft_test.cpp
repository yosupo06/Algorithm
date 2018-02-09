#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <numeric>
#include <random>
#include <vector>
#include <array>
#include <bitset>
#include <queue>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <complex>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n==0) ? 1 : 10*TEN(n-1); }
template<class T> using V = vector<T>;
template<class T> using VV = V<V<T>>;

#include "fft.h"

ll rand_int(ll l, ll r) { //[l, r]
    using D = uniform_int_distribution<ll>;
    static random_device rd;
    static mt19937 gen(rd());
    return D(l, r)(gen);
}

V<int> naive(V<int> a, V<int> b) {
    int A = int(a.size()), B = int(b.size());
    V<int> c(A+B-1);
    for (int i = 0; i < A; i++) {
        for (int j = 0; j < B; j++) {
            c[i+j] += a[i] * b[j];
        }
    }
    return c;
}

V<int> fast(V<int> a, V<int> b) {
    int A = int(a.size()), B = int(b.size());
    V<R> na(A), nb(B);
    for (int i = 0; i < A; i++) na[i] = a[i];
    for (int i = 0; i < B; i++) nb[i] = b[i];
    auto nc = multiply_fast(na, nb);
    V<int> c(A+B-1);
    for (int i = 0; i < A+B-1; i++) c[i] = int(round(nc[i]));
    return c;
}

void check(int A, int B) {
    V<int> a(A), b(B);
    for (int i = 0; i < A; i++) {
        a[i] = rand_int(0, 100);
    }
    for (int i = 0; i < B; i++) {
        b[i] = rand_int(0, 100);
    }
    V<int> c1 = naive(a, b);
    V<int> c2 = fast(a, b);
    assert(c1.size() == A+B-1);
    assert(c2.size() == A+B-1);
    for (int i = 0; i < A+B-1; i++) {
        assert(c1[i] == c2[i]);
    }
}

int main() {
    int N = 100;
    for (int l = 1; l < N; l++) {
        for (int r = 1; r < N; r++) {
            check(l, r);
        }
    }
    return 0;
}
