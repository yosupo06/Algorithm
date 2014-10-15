#include <algorithm>
#include <limits>

//size:2**N N=17:131072 N=12:4096
template <class T, int N>
struct StarrySkyTree {
    using P = std::pair<T, T>;
    using uint = unsigned int;
    static constexpr int size = 1<<N;
    P seg[size*2];
    
    void init(T x) {
        for (int i = 0; i < size*2; i++) {
            seg[i] = P(x, 0);
        }
    }

    void add(uint i, T x) {
        //if (i >= size) return;
        i += size - 1;
        seg[i].first += x;
        while (i) {
            i = (i - 1) / 2;
            int s1 = seg[i*2+1].first, s2 = seg[i*2+2].first;
            seg[i].first = seg[i].second + std::max(s1, s2);
        }
    }

    inline void add(uint a, uint b, T x, uint k = 0, uint l = 0, uint r = size) {
        if (a >= b || b > size) return;
        if (r <= a || b <= l) return;
        if (a <= l && r <= b) {
            seg[k].first += x;
            seg[k].second += x;
            return;
        }
        add(a, b, x, k*2+1, l, (l+r)/2);
        add(a, b, x, k*2+2, (l+r)/2, r);
        seg[k].first = seg[k].second + std::max(seg[k*2+1].first, seg[k*2+2].first);
    }

    inline T get(uint a = 0, uint b = size, uint k = 0, uint l = 0, uint r = size) {
        if (a >= b || b > size) return std::numeric_limits<T>::min();
        if (a <= l && r <= b) return seg[k].first;
        if (r <= a || b <= l) return std::numeric_limits<T>::min();
        T vl = get(a, b, k*2+1, l, (l+r)/2);
        T vr = get(a, b, k*2+2, (l+r)/2, r);
        return seg[k].second + std::max(vl, vr);
    }
};