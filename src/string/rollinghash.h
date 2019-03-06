using Mint0 = ModInt<TEN(9) + 7>;
using Mint1 = ModInt<TEN(9) + 9>;

V<Mint0> powB0{1}, powiB0{1};
V<Mint1> powB1{1}, powiB1{1};
Mint0 B0 = rand_int(1, TEN(9)), iB0 = B0.inv();
Mint1 B1 = rand_int(1, TEN(9)), iB1 = B1.inv();
void first() {
    for (int i = 0; i < TEN(6); i++) {
        powB0.push_back(powB0.back() * B0);
        powiB0.push_back(powiB0.back() * iB0);
        powB1.push_back(powB1.back() * B1);
        powiB1.push_back(powiB1.back() * iB1);
    }
}

struct H {
    int le = 0;
    Mint0 h0;
    Mint1 h1;
    H() : le(0), h0(0), h1(0) {}
    H(int _le, Mint0 _h0, Mint1 _h1) : le(_le), h0(_h0), h1(_h1) {}
    H(int c) {
        le = 1;
        h0 = Mint0(c);
        h1 = Mint1(c);
    }
    H operator+(const H& r) const {
        return H{le + r.le, h0 + r.h0 * powB0[le], h1 + r.h1 * powB1[le]};
    }
    H& operator+=(const H& r) { return *this = *this + r; }

    bool operator==(const H& r) const {
        return le == r.le && h0 == r.h0 && h1 == r.h1;
    }
    bool operator!=(const H& r) const {
        return !(*this == r);
    }
    H strip_left(const H& r) const {
        return H{le - r.le, (h0 - r.h0) * powiB0[r.le], (h1 - r.h1) * powiB1[r.le]};
    }
    H strip_right(const H& r) const {
        return H{le - r.le, h0 - r.h0 * powB0[le - r.le], h1 - r.h1 * powB1[le - r.le]};
    }
};
