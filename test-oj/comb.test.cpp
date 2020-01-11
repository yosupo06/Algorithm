#define LOCAL
#include "base.h"
#include "math/modint.h"
#include "math/comb.h"

using Mint = ModInt<TEN(9) + 7>;

int main() {
    Comb<Mint> c(100);
    assert(c.fact[33] * c.ifact[33] == Mint(1));
    assert(c.fact[100] * c.ifact[100] == Mint(1));
    return 0;
}
