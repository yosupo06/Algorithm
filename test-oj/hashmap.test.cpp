#define PROBLEM "https://judge.yosupo.jp/problem/associative_array"

#include "base.hpp"
#include "util/fast_io.hpp"
#include "datastructure/hashmap.hpp"

int main() {
    Scanner sc(stdin);
    Printer pr(stdout);

    int q;
    sc.read(q);
    HashMap<ll, ll> mp;

    for (int ph = 0; ph < q; ph++) {
        int ty;
        sc.read(ty);
        if (ty == 0) {
            ll k, v;
            sc.read(k, v);
            mp.set(k, v);
        } else {
            ll k;
            sc.read(k);
            pr.writeln(mp.get(k));
        }
    }
    return 0;
}
