struct ACTrie {
    using NP = ACTrie*;
    V<int> acc;
    map<int, NP> next;
    NP fail = nullptr, dnx = nullptr;

  private:
    void add(const string& s, int id, int p = 0) {
        if (p == int(s.size())) {
            acc.push_back(id);
            return;
        }
        if (next[s[p]] == nullptr) {
            next[s[p]] = new ACTrie();
        }
        next[s[p]]->add(s, id, p + 1);
    }
    template <class OP> NP count(OP op, int p) {
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

  public:
    // パターンにマッチするたびにop(string ID, 発見位置の終端)を呼び出す
    // 終端が同じで複数マッチする文字列が存在する場合，長い順に呼び出される
    // s = "abaaba", pattern = {"ab", "ba"} なら
    // op(0, 2), op(1, 3), op(0, 5), op(1, 6)
    template <class OP> void match(const string& s, OP op, int p = 0) {
        if (p == int(s.size())) return;
        if (next[s[p]]) {
            next[s[p]]->count(op, p + 1);
            next[s[p]]->match(s, op, p + 1);
        } else {
            if (!fail)
                match(s, op, p + 1);  // root
            else
                fail->match(s, op, p);  // other
        }
    }
    static NP make(V<string> v) {
        NP tr = new ACTrie();
        for (int i = 0; i < int(v.size()); i++) {
            tr->add(v[i], i);
        }
        queue<NP> q;
        q.push(tr);
        tr->fail = nullptr;
        while (!q.empty()) {
            NP ntr = q.front();
            q.pop();
            for (auto p : ntr->next) {
                int i = p.first;
                NP fail = ntr->fail;
                while (fail && !fail->next.count(i)) {
                    fail = fail->fail;
                }
                ntr->next[i]->fail = (fail == nullptr) ? tr : fail->next[i];
                q.push(ntr->next[i]);
            }
        }
        return tr;
    }
};
