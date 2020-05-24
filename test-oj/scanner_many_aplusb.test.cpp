#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb"

#include "base.hpp"
#include "util/fast_io.hpp"

int main() {
    Scanner sc(stdin);
    Printer pr(stdout);

    int q;
    sc.read(q);

    for (int i = 0; i < q; i++) {
        ll a, b;
        sc.read(a, b);
        pr.writeln(a + b);
    }
}
