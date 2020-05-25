#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "base.hpp"
#include "aplusb.hpp"
#include "datastructure/hashset.hpp"

int main() {
    HashSet<ll> st;

    for (int i = 0; i < 100; i++) {
        st.insert(i);
        assert(st.size() == i);
    }
    
    solve_aplusb();
    return 0;
}
