// D.key must be unsigned integer
template <class D> struct RadixHeap {
    using C = typename make_unsigned<decltype(D().key)>::type;
    static int bsr1(C x) { return (x == 0) ? 0 : bsr(x) + 1; }
    int sz = 0;
    C last = 0;
    VV<D> v = VV<D>(sizeof(C) * 8 + 1);
    RadixHeap() {}
    void push(D x) {
        assert(decltype(x.key)(last) <= x.key);
        sz++;
        v[bsr1(x.key ^ last)].push_back(x);
    }
    void pull() {
        if (v[0].size()) return;
        int i = 1;
        while (!v[i].size()) i++;
        last = min_element(v[i].begin(), v[i].end(),
                           [&](D l, D r) { return l.key < r.key; })
                   ->key;
        for (D p : v[i]) {
            v[bsr1(p.key ^ last)].push_back(p);
        }
        v[i].clear();
    }
    D top() {
        pull();
        return v[0].back();
    }
    void pop() {
        pull();
        sz--;
        v[0].pop_back();
    }
    int size() const { return sz; }
    bool empty() const { return sz == 0; }
};
