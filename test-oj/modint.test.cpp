#define LOCAL
#include "base.h"
#include "math/dynamicmodint.h"

using DMint = DynamicModInt;

int main() {
    DMint::set_mod(103);
    for (int i = 1; i < 103; i++) {
        ll a = DMint(i).inv().v;
        assert(1 <= a && a < 103);
        assert((a * i) % 103 == 1);
    }
    return 0;
}
