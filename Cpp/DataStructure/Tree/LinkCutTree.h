/**
 * Link-Cut Tree
 *
 * 機能としては、link、cut、evert、parent, rootを実装済み
 * 辺に値を持たせたい場合は頂点倍加
 */
struct LCNode {
	using NP = LCNode*;

	LCNode() : p(nullptr), l(nullptr), r(nullptr), sz(1), rev(false) {
	}

	NP update() {
		sz = 1;
		if (l) sz += l->sz;
		if (r) sz += r->sz;
		return this;
	}
	void push() {
		int lsz = (l) ? l->sz : 0, rsz = (r) ? r->sz : 0;
		if (rev) {
			if (lsz) {
				l->revdata();
			}
			if (rsz) {
				r->revdata();
			}
			rev = false;
		}
	}
	void revdata() {
		swap(l, r);
		rev ^= true;
	}

	//ここから
	NP p, l, r;
	int sz;
	bool rev;
	inline int pos() {
		if (p) {
			if (p->l == this) return -1;
			if (p->r == this) return 1;
		}
		return 0;
	}
	void rot() {
		NP q = p->p;
		int pps = p->pos();
		if (pps == -1) {
			q->l = this;
		}
		if (pps == 1) {
			q->r = this;
		}
		if (p->l == this) {
			p->l = r;
			if (r) r->p = p;
			r = p;
		} else {
			p->r = l;
			if (l) l->p = p;
			l = p;
		}
		p->p = this;
		p->update();
		update();
		p = q;
		if (q) q->update();
	}
	void splay() {
		supush();
		int ps;
		while ((ps = pos())) {
			int pps = p->pos();
			if (!pps) {
				rot();
			} else if (ps == pps) {
				p->rot(); rot();
			} else {
				rot(); rot();
			}
		}
	}
	void expose() {
		NP u = this, ur = nullptr;
		do {
			u->splay();
			u->r = ur;
			u->update();
			ur = u;
		} while ((u = u->p));
		splay();
	}
	/**
	 * splayする前に一括でその頂点のパス木の根までをpushする
	 * 唯一stack overflowしうる関数なので注意すること
	 */
	void supush() {
		if (pos()) {
			p->supush();
		}
		push();
	}
	//ここまでは絶対必要

	void link(NP r) {
		expose();
		r->expose();
		p = r;
	}

	void cut() {
		expose();
		assert(l);
		l->p = nullptr;
		l = nullptr;
		update();
	}

	NP root() {
		expose();
		NP u = this;
		while (u->l) {
			u = u->l;
			u->push();
		}
		u->expose();
		return u;
	}

	NP parent() {
		expose();
		NP u = this->l;
		if (!u) return u;
		u->push();
		while (u->r) {
			u = u->r;
			u->push();
		}
		u->expose();
		return u;
	}

	void evert() {
		expose();
		revdata();
	}

	NP lca(NP n) {
		n->expose();
		expose();
		NP t = n;
		while (n->p != nullptr) {
			if (!n->pos()) t = n->p;
			n = n->p;
		}
		return (this == n) ? t : nullptr;
	}
};


/**
 * Link-Cut Tree
 *
 * 機能としては、link、cut、evert、parent, rootを実装済み
 * 辺に値を持たせたい場合は頂点倍加
 */
struct LCNode {
	using NP = LCNode*;

	int tsz, tsm;
	LCNode() : p(nullptr), l(nullptr), r(nullptr), sz(1), rev(false) {
		tsz = 0;
		tsm = 0;
	}

	void update() {
		int lsz = (l) ? l->sz : 0, rsz = (r) ? r->sz : 0;
		sz = 1;
		tsm = 1 + tsz;
		if (lsz) {
			sz += lsz;
			tsm += l->tsm;
		}
		if (rsz) {
			sz += rsz;
			tsm += r->tsm;
		}
	}
	void addch(NP b) {
		assert(!b || b->p == this);
		if (b) {
			tsz += b->tsm;
			tsm += b->tsm;
		}
	}
	void delch(NP b) {
		assert(!b || b->p == this);
		if (b) {
			tsz -= b->tsm;
			tsm -= b->tsm;
		}
	}
	void push() {
		int lsz = (l) ? l->sz : 0, rsz = (r) ? r->sz : 0;
		if (rev) {
			if (lsz) {
				l->revdata();
			}
			if (rsz) {
				r->revdata();
			}
			rev = false;
		}
	}
	void revdata() {
		swap(l, r);
		rev ^= true;
	}

	//ここから
	NP p, l, r;
	int sz;
	bool rev;
	inline int pos() {
		if (p) {
			if (p->l == this) return -1;
			if (p->r == this) return 1;
		}
		return 0;
	}
	void rot() {
		NP q = p->p;
		int pps = p->pos();
		if (pps == -1) {
			q->l = this;
		}
		if (pps == 1) {
			q->r = this;
		}
		if (p->l == this) {
			p->l = r;
			if (r) r->p = p;
			r = p;
		} else {
			p->r = l;
			if (l) l->p = p;
			l = p;
		}
		p->p = this;
		p->update();
		update();
		p = q;
		if (q) q->update();
	}
	void splay() {
		supush();
		int ps;
		while ((ps = pos())) {
			int pps = p->pos();
			if (!pps) {
				rot();
			} else if (ps == pps) {
				p->rot(); rot();
			} else {
				rot(); rot();
			}
		}
	}
	void expose() {
		for (NP u = this; u; u = u->p) {
			u->splay();
		}
		for (NP u = this, ur = nullptr; u; u = u->p) {
			NP tmp = u->r;
			u->r = nullptr;
			u->update();
			u->addch(tmp);
			u->delch(ur);
			u->r = ur;
			u->update();
			ur = u;
		}
		splay();
	}
	void supush() {
		if (pos()) {
			p->supush();
		}
		push();
	}
	//ここまでは絶対必要

	void link(NP r) {
		expose();
		r->expose();
		p = r;
		r->addch(this);
	}

	NP parent() {
		expose();
		NP u = this->l;
		if (!u) return nullptr;
		u->push();
		while (u->r) {
			u = u->r;
			u->push();
		}
		u->expose();
		return u;
	}

	void cut() {
		NP u = parent();
		assert(u);
		assert(!u->r);
		u->delch(this);
		this->p = nullptr;
	}


	NP root() {
		expose();
		NP u = this;
		while (u->l) {
			u = u->l;
			u->push();
		}
		u->expose();
		return u;
	}

	void evert() {
		expose();
		revdata();
	}

	NP lca(NP n) {
		n->expose();
		expose();
		NP t = n;
		while (n->p != nullptr) {
			if (!n->pos()) t = n->p;
			n = n->p;
		}
		return (this == n) ? t : nullptr;
	}
};


/**
 * Link-Cut Tree
 *
 * 機能としては、link、cut、evert、parent, rootを実装済み
 * 辺に値を持たせたい場合は頂点倍加
 */
struct LCNode {
	using NP = LCNode*;

	ll tsz, tszsm;
	ll tsm;
	ll d;
	ll dsm;
	ll lsm, rsm;
	LCNode() {}
	LCNode(int d) : p(nullptr), l(nullptr), r(nullptr), sz(1), rev(false) {
		tsz = 0;
		tszsm = 0;
		tsm = 0;
		this->d = d;
		dsm = d;
		lsm = rsm = 0;
	}

	void update() {
		int lsz = (l) ? l->sz : 0, rsz = (r) ? r->sz : 0;
		sz = 1;
		tszsm = tsz;
		dsm = d;
		if (lsz) {
			dsm += l->dsm;
			sz += lsz;
			tszsm += l->tszsm;
		}
		if (rsz) {
			dsm += r->dsm;
			sz += rsz;
			tszsm += r->tszsm;
		}
		ll ldsm = (l) ? l->dsm : 0;
		ll llsm = (l) ? l->lsm : 0;
		ll lrsm = (l) ? l->rsm : 0;
		ll ltszsm = (l) ? l->tszsm : 0;
		ll rdsm = (r) ? r->dsm : 0;
		ll rlsm = (r) ? r->lsm : 0;
		ll rrsm = (r) ? r->rsm : 0;
		ll rtszsm = (r) ? r->tszsm : 0;
		lsm = llsm + ldsm * tsz + tsm + (ldsm + d) * rtszsm + rlsm;
		rsm = rrsm + rdsm * tsz + tsm + (rdsm + d) * ltszsm + lrsm;
	}
	void cngchsz(int x) {
		tsz += x;
		tszsm += x;
	}
	void addch(NP b) {
		assert(!b || b->p == this);
		if (b) {
			cngchsz(b->tszsm);
			tsm += b->lsm + (d) * b->tszsm;
		}
	}
	void delch(NP b) {
		assert(!b || b->p == this);
		if (b) {
			cngchsz(-b->tszsm);
			tsm -= b->lsm + (d) * b->tszsm;
		}
	}
	void push() {
		int lsz = (l) ? l->sz : 0, rsz = (r) ? r->sz : 0;
		if (rev) {
			if (lsz) {
				l->revdata();
			}
			if (rsz) {
				r->revdata();
			}
			rev = false;
		}
	}
	void revdata() {
		swap(l, r);
		swap(lsm, rsm);
		rev ^= true;
	}

	//ここから
	NP p, l, r;
	int sz;
	bool rev;
	inline int pos() {
		if (p) {
			if (p->l == this) return -1;
			if (p->r == this) return 1;
		}
		return 0;
	}
	void rot() {
		NP q = p->p;
		int pps = p->pos();
		if (pps == -1) {
			q->l = this;
		}
		if (pps == 1) {
			q->r = this;
		}
		if (p->l == this) {
			p->l = r;
			if (r) r->p = p;
			r = p;
		} else {
			p->r = l;
			if (l) l->p = p;
			l = p;
		}
		p->p = this;
		p->update();
		update();
		p = q;
		if (q) q->update();
	}
	void splay() {
		supush();
		int ps;
		while ((ps = pos())) {
			int pps = p->pos();
			if (!pps) {
				rot();
			} else if (ps == pps) {
				p->rot(); rot();
			} else {
				rot(); rot();
			}
		}
	}
	void expose() {
		for (NP u = this; u; u = u->p) {
			u->splay();
		}
		for (NP u = this, ur = nullptr; u; u = u->p) {
			NP tmp = u->r;
			u->r = nullptr;
			u->update();
			u->addch(tmp);
			u->delch(ur);
			u->r = ur;
			u->update();
			ur = u;
		}
		splay();
	}
	void supush() {
		if (pos()) {
			p->supush();
		}
		push();
	}
	//ここまでは絶対必要

	void link(NP r) {
		expose();
		r->expose();
		p = r;
		r->addch(this);
	}

	NP parent() {
		expose();
		NP u = this->l;
		if (!u) return nullptr;
		u->push();
		while (u->r) {
			u = u->r;
			u->push();
		}
		u->expose();
		return u;
	}

	void cut() {
		NP u = parent();
		assert(u);
		assert(!u->r);
		u->delch(this);
		this->p = nullptr;
	}

	NP root() {
		expose();
		NP u = this;
		while (u->l) {
			u = u->l;
			u->push();
		}
		u->expose();
		return u;
	}

	void evert() {
		expose();
		revdata();
	}

	NP lca(NP n) {
		n->expose();
		expose();
		NP t = n;
		while (n->p != nullptr) {
			if (!n->pos()) t = n->p;
			n = n->p;
		}
		return (this == n) ? t : nullptr;
	}

	NP get(int x) {
		push();
		int rszsm = (r) ? r->tszsm : 0;
		if (r && x <= rszsm) return r->get(x);
		if (x <= tsz + rszsm) {
			splay();
			return this;
		}
		if (l) return l->get(x - (tsz + rszsm));
		return nullptr;
	}
};
