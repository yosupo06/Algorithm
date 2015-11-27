struct AA {
	using NP = AA*;
	int ma;
	NP l, r;
	int sz, lv;
	AA(int ma) : l(nullptr), r(nullptr), sz(1), lv(0), ma(ma) {}
	AA(NP l, NP r, int lv) : l(l), r(r), lv(lv) {
		update();
	}
	void update() {
		sz = l->sz + r->sz;
		ma = max(l->ma, r->ma);
	}
	static NP skew(NP n) {
		if (n->l == nullptr || n->lv != n->l->lv) return n;
		NP L = n->l;
		n->l = L->r;
		n->update();
		L->r = n;
		L->update();
		return L;
	}
	static NP pull(NP n) {
		if (n->r == nullptr || n->lv != n->r->lv) return n;
		if (n->r->r == nullptr || n->lv != n->r->r->lv) return n;
		NP R = n->r;
		n->r = R->l;
		n->update();
		R->l = n;
		R->lv++;
		R->update();
		return R;
	}
	static NP merge(NP l, NP r) {
		if (l == nullptr) return r;
		if (r == nullptr) return l;
		if (l->lv == r->lv) {
			return new AA(l, r, l->lv+1);
		}
		if (l->lv < r->lv) {
			r->l = merge(l, r->l);
			r->update();
			return pull(skew(r));
		} else {
			l->r = merge(l->r, r);
			l->update();
			return pull(skew(l));
		}
	}
	static pair<NP, NP> split(NP n, int k) {
		if (n == nullptr) return pair<NP, NP>(nullptr, nullptr);
		if (n->sz == 1) {
			if (k == 0) return pair<NP, NP>(nullptr, n);
			else return pair<NP, NP>(n, nullptr);
		}
		pair<NP, NP> m;
		if (k <= n->l->sz) {
			m = split(n->l, k);
			m.second = merge(m.second, n->r);
		} else {
			m = split(n->r, k - n->l->sz);
			m.first = merge(n->l, m.first);
		}
		delete n;
		return m;
	}
	static NP insert(NP n, int k, NP m) {
		if (n == nullptr) return m;
		if (n->sz == 1) {
			if (k == 0) return new AA(m, n, 1);
			else return new AA(n, m, 1);
		}
		if (k <= n->l->sz) {
			n->l = insert(n->l, k, m);
			n->update();
			return pull(skew(n));
		} else {
			n->r = insert(n->r, k - n->l->sz, m);
			n->update();
			return pull(skew(n));
		}
	}
	static NP remove(NP n, int k) {
		if (n->sz == 1) {
			delete n;
			return nullptr;
		}
		NP m;
		if (k < n->l->sz) {
			m = merge(remove(n->l, k), n->r);
		} else {
			m = merge(n->l, remove(n->r, k - n->l->sz));
		}
		delete n;
		return m;
	}
};
