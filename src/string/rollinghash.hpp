#pragma once

#include "math/comb.hpp"
#include "math/modint61.hpp"
#include "util/random.hpp"

struct H {
  private:
    static ModInt61 B;
    static ModInt61 iB;
    static V<ModInt61> powB, powiB;

  public:
    static void init(int n) {
        powB = powTable(n, B);
        powiB = powTable(n, iB);
    }
    int le = 0;
    ModInt61 h;
    H() : le(0), h(0) {}
    H(int _le, ModInt61 _h) : le(_le), h(_h) {}
    H(int c) : le(1), h(c) {}
    // H(l) + H(r) = H(lr)
    H operator+(const H& r) const { return H{le + r.le, h + r.h * powB[le]}; }
    H& operator+=(const H& r) { return *this = *this + r; }

    bool operator==(const H& r) const { return le == r.le && h == r.h; }
    bool operator!=(const H& r) const { return !(*this == r); }
    // H(lr).strip_left(H(l)) = H(r)
    H strip_left(const H& l) const {
        return H{le - l.le, (h - l.h) * powiB[l.le]};
    }
    // H(lr).strip_right(H(r)) = H(l)
    H strip_right(const H& r) const {
        return H{le - r.le, h - r.h * powB[le - r.le]};
    }
};
ModInt61 H::B =
    ModInt61(global_runtime_gen().uniform(0ULL, ModInt61::get_mod() - 1));
ModInt61 H::iB = H::B.inv();
V<ModInt61> H::powB, H::powiB;
