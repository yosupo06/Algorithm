struct Node {
    using NP = Node*;

    int ma, lz;

    /*
     init_node, update, push
    */
    void init_node() {
        ma = lz = 0;
    }
    void update() {
        assert(!lz);
        ma = max(l->ma, r->ma);
    }
    void push() {
        if (lz) {
            l->lzdata(lz);
            r->lzdata(lz);
            lz = 0;
        }
    }
    void lzdata(int x) {
        ma += x;
        lz += x;
    }

    void add(int a, int b, int x) {
        if (b <= 0 or sz <= a) return;
        if (a <= 0 and sz <= b) {
            lzdata(x);
            return;
        }
        push();
        l->add(a, b, x);
        r->add(a - sz/2, b - sz/2, x);
        update();
    }
    int get(int a, int b) {
        if (b <= 0 or sz <= a) return -1;
        if (a <= 0 and sz <= b) {
            return ma;
        }
        push();
        return max(l->get(a, b), r->get(a-sz/2, b-sz/2));
    }

    NP l, r;
    int sz;
    Node(int sz) : sz(sz) {
        init_node();
        if (sz == 1) return;
        l = new Node(sz/2);
        r = new Node(sz - sz/2);
        update();
    }
};
