#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "src/base.h"
#include "src/bitop.h"
#include "src/math/modint.h"
#include "src/math/nft.h"

using Mint = ModInt<998244353>;
template <> const Mint Mint::G = Mint(3);

int main() {
    Scanner sc(stdin);
    Printer pr(stdout);

    int n, m;
    sc.read(n, m);

    V<Mint> a(n);
    for (int i = 0; i < n; i++) {
        sc.read(a[i].v);
    }
    V<Mint> b(m);
    for (int i = 0; i < m; i++) {
        sc.read(b[i].v);
    }
    auto c = multiply(a, b);
    for (auto x : c) {
        pr.write(x.v);
        pr.write(' ');
    }
    pr.writeln();
    return 0;
}
