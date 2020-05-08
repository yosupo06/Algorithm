#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "base.hpp"
#include "math/modint.hpp"
#include "math/dynamicmodint.hpp"
#include "math/comb.hpp"

#include "aplusb.hpp"

using Mint = ModInt<TEN(9) + 7>;
using DMint = DynamicModInt;
int main() {
    {
        Comb<Mint> c(100);
        assert(c.fact[33] * c.ifact[33] == Mint(1));
        assert(c.fact[100] * c.ifact[100] == Mint(1));
    }
    {
        DMint::set_mod(103);
        Comb<DMint> c(100);
        assert(c.fact[33] * c.ifact[33] == DMint(1));
        assert(c.fact[100] * c.ifact[100] == DMint(1));
    }

    solve_aplusb();
    return 0;
}
