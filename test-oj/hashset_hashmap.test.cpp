#define PROBLEM "https://judge.yosupo.jp/problem/associative_array"

#include "base.hpp"
#include "util/fast_io.hpp"
#include "datastructure/hashset.hpp"
#include "datastructure/hashmap.hpp"

int main() {
    Scanner sc(stdin);
    Printer pr(stdout);

    int q;
    sc.read(q);
    HashSet<ll> st;
    HashMap<ll, ll> mp;

    for (int ph = 0; ph < q; ph++) {
        int ty;
        sc.read(ty);
        if (ty == 0) {
            ll k, v;
            sc.read(k, v);
            if (v == 0) {
                st.reset(k);
                mp.remove(k);
            } else {
                st.set(k);
                mp.set(k, v);
            }
        } else {
            ll k;
            sc.read(k);
            ll u = mp.get(k);
            assert(st.get(k) == (u != 0));
            pr.writeln(u);
        }
    }
    return 0;
}
