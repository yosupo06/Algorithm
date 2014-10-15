#include <vector>

template <int SIZE>
struct UnionFind {
    using uint = unsigned int;
    int i2g[SIZE];
    std::vector<int> g2i[SIZE];
    inline void init() {
        for (int i = 0; i < SIZE; ++i) {
            i2g[i] = i;
            g2i[i].assign(1, i);
        }
    }
 
    inline void merge(uint ia, uint ib) {
        if (g2i[i2g[ia]].size() < g2i[i2g[ib]].size()) swap(ia, ib);
        int ga = i2g[ia], gb = i2g[ib];
        for (int j : g2i[gb]) i2g[j] = ga;
        g2i[ga].insert(g2i[ga].end(), g2i[gb].begin(), g2i[gb].end());
        g2i[gb].clear();
    }
 
    inline bool is_same_group(uint ia, uint ib) {
        return i2g[ia] == i2g[ib];
    }
};