/**
 動的SegTree(RMQ)
 */
struct Node {
    typedef Node* NP;
    int sz, d;
    NP l, r;
    Node() {
        l = r = nullptr; d = INF;
    }
    Node(int sz) : sz(sz) {
        assert(sz);
        l = r = nullptr; d = INF;
    }

    void set(int a, int b, int x) {
        if (a <= 0 && sz <= b) {
            d = min(d, x);
            return;
        }
        if (b <= 0 || sz <= a) {
            return;
        }
        if (l == nullptr) {
            l = new Node(sz/2);
        }
        l->set(a, b, x);
        if (r == nullptr) {
            r = new Node(sz - sz/2);
        }
        r->set(a-sz/2, b-sz/2, x);
    }
    int get(int x) {
        if (sz == 1) {
            return d;
        }
        if (x < sz/2) {
            if (l == nullptr) {
                return d;
            }
            return min(d, l->get(x));
        } else {
            if (r == nullptr) {
                return d;
            }
            return min(d, r->get(x - sz/2));
        }
    }
};
