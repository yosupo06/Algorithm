struct Node {
    using NP = const Node*;

    int ma, lz;

    /*
     init_node, update, push
    */
    void init_node() {
        ma = lz = 0;
    }
    void update() {
        ma = max(l->ma, r->ma);
    }
    void push() {
        if (!lz) continue;
        auto nl = make(l);
        auto nr = make(r);
        if (lz) {
            nl->lzdata(lz);
            nr->lzdata(lz);
            lz = 0;
        }
        l = nl;
        r = nr;
    }
    /// pushはconstに関わらず呼んで良い
    void push() const {
        const_cast<Node*>(this)->push();
    }
    void lzdata(int x) {
        ma += x;
        lz += x;
    }

    NP add(int a, int b, int x) const {
        if (b <= 0 or sz <= a) return this;
        if (a <= 0 and sz <= b) {
            auto n = make(this);
            n->lzdata(x);
            return n;
        }
        push();
        auto n = make(this);
        auto n->l = l->add(a, b, x);
        auto n->r = r->add(a - sz/2, b - sz/2, x);
        n->update();
        return n;
    }
    int get(int a, int b) const {
        if (b <= 0 or sz <= a) return -1;
        if (a <= 0 and sz <= b) {
            return ma;
        }
        push();
        return max(l->get(a, b), r->get(a-sz/2, b-sz/2));
    }

    NP l, r;
    int sz;
    Node() {}
    Node(int sz) : sz(sz) {
        init_node();
        if (sz == 1) return;
        l = new Node(sz/2);
        r = new Node(sz - sz/2);
        update();
    }
    static Node* make(NP x) {
        auto n = new Node();
        *n = *x;
        return n;
    }
};