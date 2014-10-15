#include <algorithm>

//0-indexed overflow-> max:NMAX*MOD*K
template <class T, int SIZE, T MOD>
struct RangeBinaryIndexedTree {
    using uint = unsigned int;
    T seg[2][SIZE];
    
    inline void init() {
        fill_n((T *)seg, SIZE*2, 0);
    }

private:
    inline void add1(uint f, uint i, T x) {
        while (i < SIZE) {
            seg[f][i] += x;
            if (MOD) seg[f][i] %= MOD;
            i += (i+1) & ~i;
        }
    }

public:
    inline void add(uint a, uint b, T x) {
            add1(0, a, -x*a);
            add1(0, b, x*b);
            add1(1, a, x);
            add1(1, b, -x);
    }

private:
    //[0, i)
    inline T sum1(uint f, uint i) {
        T s = 0;
        uint d = 1;
        while (i >= d) {
            i -= d;
            s += seg[f][i];
            d = (i+1) & ~i;
        }
        if (MOD) s %= MOD;
        return s;
    }

public:
    //[a, b)
    inline T sum(uint a, uint b) {
        T d = sum1(0, b) - sum1(0, a) + sum1(1, b) * b - sum1(1, a) * a;
        if (MOD) {
            d = (d + MOD) % MOD;
        }
        return d;
    }
};
