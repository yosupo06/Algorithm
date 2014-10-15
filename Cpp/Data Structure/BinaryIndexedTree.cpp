#include <algorithm>

//0-indexed overflow-> max:Height*MOD sum's comment out:2*MOD
template <class T, int SIZE>
struct BinaryIndexedTree {
    T seg[SIZE];
    
    inline void init() {
        fill_n(seg, SIZE, 0);
    }

    inline void add(int i, T x) {
        while (i < SIZE) {
            seg[i] += x;
            i += (i+1) & ~i;
        }
    }
    //[0, i)
    inline T sum(int i) {
        T s = 0;
        uint d = 1;
        while (i >= d) {
            i -= d;
            s += seg[i];
            d = (i+1) & ~i;
        }
        return s;
    }
    //[a, b)
    inline T sum(int a, int b) {
        T d = sum(b) - sum(a);
        if (MOD) {
            d = (d + MOD) % MOD;
        }
        return d;
    }
};
