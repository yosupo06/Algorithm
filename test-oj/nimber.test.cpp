#define PROBLEM "https://judge.yosupo.jp/problem/nim_product_64"

#include "base.hpp"
#include "util/fast_io.hpp"
#include "math/nimber.hpp"

int main() {
    Scanner sc(stdin);
    Printer pr(stdout);
    int t;
    sc.read(t);
    for (int i = 0; i < t; i++) {
        ull a, b;
        sc.read(a, b);
        pr.writeln((Nimber64(a) * Nimber64(b)).v);
    }
    return 0;
}
