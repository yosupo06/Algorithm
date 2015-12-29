struct Node {
    using NP = Node*;

    const int INF = 1<<28;
    int mi, lz;

    /*
     init_leaf, update, push
    */
    void init_leaf() {
        mi = lz = 0;
    }
    void update() {
        mi = min(l->mi, r->mi);
    }
    void push() {
        if (lz) {
            l->lzdata(lz);
            r->lzdata(lz);
            lz = 0;
        }
    }
    void lzdata(int x) {
        mi += x;
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
        if (b <= 0 or sz <= a) return INF;
        if (a <= 0 and sz <= b) {
            return mi;
        }
        push();
        return min(l->get(a, b), r->get(a-sz/2, b-sz/2));
    }

    NP l, r;
    int sz;
    Node(int sz) : sz(sz) {
        if (sz == 1) {
            init_leaf();
            return;
        }
        l = new Node(sz/2);
        r = new Node(sz - sz/2);
        update();
    }
};
