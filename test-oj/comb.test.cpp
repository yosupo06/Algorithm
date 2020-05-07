#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "base.h"
#include "math/modint.h"
#include "math/dynamicmodint.h"
#include "math/comb.h"

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
    int a, b;
    cin >> a >> b;
    cout << a + b << endl;
    return 0;
}
