int bsr(uint x) {
    if (x == 0) return -1;
    return 31-__builtin_clz(x);
}

template<class C>
struct RadixHeap {
    typedef pair<uint, C> P;
    vector<P> v[33];
    uint last, sz;
    RadixHeap() {
        last = sz = 0;
    }
    void push(uint x, C p) {
        assert(last <= x);
        sz++;
        v[bsr(x^last)+1].push_back(P(x, p));
    }
    void push(P p) {
        push(p.first, p.second);
    }
    P top() {
        return pop(false);
    }
    P pop(bool f = true) {
        assert(sz);
        if (!v[0].size()) {
            int i = 1;
            while (!v[i].size()) i++;
            last = min_element(v[i].begin(), v[i].end())->first;
            for (P p: v[i]) {
                v[bsr(p.first^last)+1].push_back(p);
            }
            v[i].clear();
        }
        P r = v[0].back();
        if (f) {
            sz--;
            v[0].pop_back();
        }
        return r;
    }
    int size() {
        return sz;
    }
    bool empty() {
        return sz == 0;
    }
    void clear() {
        last = sz = 0;
        for (int i = 0; i < 33; i++) {
            v[i].clear();
        }
    }
};

struct RadixHeapInt {
    vector<uint> v[33];
    uint last, sz;
    RadixHeapInt() {
        last = sz = 0;
    }
    void push(uint x) {
        assert(last <= x);
        sz++;
        v[bsr(x^last)+1].push_back(x);
    }
    uint pop() {
        assert(sz);
        if (!v[0].size()) {
            int i = 1;
            while (!v[i].size()) i++;
            last = *min_element(v[i].begin(), v[i].end());
            for (uint x: v[i]) {
                v[bsr(x^last)+1].push_back(x);
            }
            v[i].clear();
        }
        sz--;
        v[0].pop_back();
        return last;
    }
};
