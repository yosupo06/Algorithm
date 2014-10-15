#include <algorithm>
#include <limits>
#include <cstring>
#include <array>
//size:2**N N=19:524288 N=17:131072 N=12:4096
template <class T, int N, int K>
struct RangeKthSmallest {
    using PA = std::pair<T, int>;
    using P = std::pair<std::array<PA, K>, T>;
    using uint = unsigned int;
    static const int size = 1<<N;
    P seg[size*2];
    
    void init(T x) {
        int l = size-1, r = size*2-2;
        for (int i = 0; i <= N; i++) {
            for (int j = l; j <= r; j++) {
                seg[j].first[0] = PA(x, 1<<i);
                for (int i = 1; i < K; i++) {
                    seg[j].first[i] = PA(0, -1);
                }
                if (i) {
                    seg[j].second = 0;
                } else {
                    seg[j].second = x;
                }
            }
            l = (l-1)/2; r = (r-1)/2;
        }
        for (int i = 0; i < K; i++) {
            seg[size*2-1].first[i] = PA(0, -1);
        }
    }

    //a=b+c
    inline void merge(P *A, P &a1, P &a2) {
        int c1 = 0, c2 = 0;
        P &a = *A;
        for (int c = 0; c < K; c++) {
            PA &p1 = a1.first[c1], &p2 = a2.first[c2];
            bool f1 = (c1 == K || p1.second == -1), f2 = (c2 == K || p2.second == -1);
            if (f1 && f2) {
                a.first[c] = PA(0, -1);
                continue;
            }
            if (f1) {
                a.first[c] = p2;
                c2++;
            } else if (f2) {
                a.first[c] = p1;
                c1++;
            } else if (p1.first == p2.first) {
                a.first[c] = PA(p1.first, p1.second + p2.second);
                c1++; c2++;
            } else if (p1.first < p2.first) {
                a.first[c] = p1;
                c1++;
            } else {
                a.first[c] = p2;
                c2++;
            }
            a.first[c].first += a.second;
        }
    }

    inline void merge2(P *a, P &a1) {
        P a2;
        memcpy(&a2, a, sizeof(a2));
        merge(a, a1, a2);
    }

    inline void add(uint i, T x) {
        if (i >= size) return;
        i += size - 1;
        seg[i].first[0].first += x;
        seg[i].second += x;
        while (i) {
            i = (i - 1) / 2;
            merge(&seg[i], seg[i*2+1], seg[i*2+2]);
        }
    }

    inline void add(uint a, uint b, T x, uint k = 0, uint l = 0, uint r = size) {
        if (a >= b || b > size) return;
        if (r <= a || b <= l) return;
        if (a <= l && r <= b) {
            for (int i = 0; i < K && seg[k].first[i].second != -1; i++) {
                seg[k].first[i].first += x;
            }
            seg[k].second += x;
            return;
        }
        add(a, b, x, k*2+1, l, (l+r)/2);
        add(a, b, x, k*2+2, (l+r)/2, r);
        merge(&seg[k], seg[k*2+1], seg[k*2+2]);
    }

    inline PA get(uint k) {
        return seg[0].first[k];
    }
    P buff_p;
    int buff_a = size, buff_b = size;
    inline PA get(uint a, uint b, uint k) {
        if (a != buff_a || b != buff_b) {
            buff_p = get2(a, b);
            buff_a = a;
            buff_b = b;
        }
        return buff_p.first[k];
    }

private:
    inline P get2(uint a, uint b, uint k = 0, uint l = 0, uint r = size) {
        if (a >= b || b > size || r <= a || b <= l) return seg[size*2-1];
        if (a <= l && r <= b) {
            return seg[k];
        }
        P p1 = get2(a, b, k*2+1, l, (l+r)/2);
        P p2 = get2(a, b, k*2+2, (l+r)/2, r);
        P p;
        p.second = seg[k].second;
        merge(&p, p1, p2);
        return p;
    }
};
