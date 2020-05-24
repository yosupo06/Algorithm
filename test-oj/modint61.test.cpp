#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "aplusb.hpp"

#include "base.hpp"
#include "math/modint61.hpp"
#include "util/random.hpp"

using Mint = ModInt61;

int main() {
    Random gen = Random();
    for (int ph = 0; ph < 100; ph++) {
        ull a = gen.uniform(0ULL, Mint::get_mod() - 1);
        ull b = gen.uniform(0ULL, Mint::get_mod() - 1);
        ull expect = (__uint128_t(a) + b) % Mint::get_mod();
        ull actual = (Mint(a) + Mint(b)).v;
        assert(expect == actual);
    }
    for (int ph = 0; ph < 100; ph++) {
        ull a = gen.uniform(0ULL, Mint::get_mod() - 1);
        ull b = gen.uniform(0ULL, Mint::get_mod() - 1);
        ull expect = (__uint128_t(a) - b + Mint::get_mod()) % Mint::get_mod();
        ull actual = (Mint(a) - Mint(b)).v;
        assert(expect == actual);
    }
    for (int ph = 0; ph < 100; ph++) {
        ull a = gen.uniform(0ULL, Mint::get_mod() - 1);
        ull b = gen.uniform(0ULL, Mint::get_mod() - 1);
        ull expect = __uint128_t(a) * b % Mint::get_mod();
        ull actual = (Mint(a) * Mint(b)).v;
        assert(expect == actual);
    }
    for (int ph = 0; ph < 100; ph++) {
        Mint a = Mint(gen.uniform(0ULL, Mint::get_mod() - 1));
        Mint ia = a.inv();
        assert((a * ia).v == 1);
    }
    solve_aplusb();
    return 0;
}
