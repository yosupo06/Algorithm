struct RadixHeap {
    typedef pair<int, int> P;
    vector<P> v[32];
    int mi, sz;
    RadixHeap(int x, int p): sz(1) {
        mi = x;
        v[0].push_back(P(x, p));
    }
    void push(int x, int p) {
        sz++;
        v[nlz(x^mi)+1].push_back(P(x, p));
    }
    P pop() {
        sz--;
        if (!v[0].size()) {
            int i = 1;
            while (!v[i].size()) i++;
            mi = v[i][0].first;
            for (P &d: v[i]) {
                mi = min(mi, d.first);
            }
            for (P &p: v[i]) {
                v[nlz(mi^p.first)+1].push_back(p);
            }
            v[i].clear();
        }
        P r = v[0].back();
        v[0].pop_back();
        return r;
    }
    int size() {
        return sz;
    }
    bool empty() {
        return sz == 0;
    }
};
