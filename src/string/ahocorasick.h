struct AhoTrie {
    using NP = AhoTrie*;
    V<int> acc;
    map<int, NP> next;
    NP fail = nullptr, dnx = nullptr;
    void add(const string &s, int p, int id) {
        if (p == int(s.size())) {
            acc.push_back(id);
            return;
        }
        if (next[s[p]] == nullptr) {
            next[s[p]] = new AhoTrie();
        }
        next[s[p]]->add(s, p+1, id);
    }
    template<class OP>
    NP count(OP op, int p) {
        if (fail == nullptr) return this;
        for (int id : acc) {
            op(id, p);
        }
        if (dnx) {
            dnx->count(op, p);
        } else {
            dnx = fail->count(op, p);
        }
        return acc.size() ? this : dnx;
    }
    template<class OP>
    void match(const string &s, OP op, int p = 0) {
        if (p == int(s.size())) return;
        if (next[s[p]]) {
            next[s[p]]->count(op, p+1);
            next[s[p]]->match(s, op, p+1);
        } else {
            if (!fail) match(s, op, p+1); // root
            else fail->match(s, op, p); // other
        }
    }
    static NP make(V<string> v) {
        int n = int(v.size());
        NP tr = new AhoTrie();
        for (int i = 0; i < n; i++) {
            tr->add(v[i], 0, i);
        }
        queue<NP> q;
        q.push(tr);
        tr->fail = nullptr;
        while (!q.empty()) {
            NP ntr = q.front(); q.pop();
            for (auto p: ntr->next) {
                int i = p.first;
                NP fail = ntr->fail;
                while (fail and !fail->next.count(i)) {
                    fail = fail->fail;
                }
                ntr->next[i]->fail = (fail == nullptr) ? tr : fail->next[i];
                q.push(ntr->next[i]);
            }
        }
        return tr;
    }
};
