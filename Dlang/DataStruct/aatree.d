alias AA = AATree;
alias CP = const(AA)*;
 
immutable int mSZ = 200_000_000 / AA.sizeof;
__gshared int mC = 0;
__gshared AA[] mL;
 
static this() {
	mL = new AA[](mSZ);
}
 
AA* make(A...)(A a) {
	mL[mC++] = AA(a);
	return &(mL[mC-1]);
}
 
struct AATree {
	long sm, lz;
 
	CP l, r;
	int sz, lv; // size, level
	this(in CP n) {
		this = *n;
	}
	this(long v) {
		sm = v; lz = 0;
		sz = 1;
	}
	this(in CP L, in CP R) {
		l = L; r = R; lv = L.lv + 1;
		update;
	}
	void push() {
		if (lz) {
			auto L = make(l);
			auto R = make(r);
			L.lzdata(lz);
			R.lzdata(lz);
			l = L; r = R;
			lz = 0;
		}
	}
	void lzdata(long x) {
		sm += x*sz;
		lz += x;
	}
	void update() {
		sz = l.sz + r.sz;
		sm = l.sm + r.sm;
	}
}
 
AA* skew(AA* n) {
	if (n.l is null) return n;
	if (n.lv == n.l.lv) {
		return make(n.l, make(n.l.r, n.r));
	}
	return n;
}
 
AA* pull(AA* n) {
	if (n.r is null || n.r.r is null) return n;
	if (n.lv == n.r.lv && n.r.lv == n.r.r.lv) {		
		return make(make(n.l, n.r.l), n.r.r);
	}
	return n;
}
 
CP merge(CP a, CP b) {
	if (a is null) return b;
	if (b is null) return a;
	if (a.lv == b.lv) {
		return make(a, b);
	}
	if (a.lv < b.lv) {
		auto B = make(b); B.push;
		return pull(skew(make(merge(a, B.l), B.r)));//.skew.pull;
	} else {
		auto A = make(a); A.push;
		return pull(make(A.l, merge(A.r, b)));//.pull;
	}
}
 
CP[2] split(CP n, int k) { //[0..k), [k..$)
	if (n is null) return [null, null];
	if (n.sz == 1) {
		if (k == 0) return [null, n];
		return [n, null];
	}
	auto n2 = make(n); n2.push;
	if (k <= n2.l.sz) {
		auto l = split(n2.l, k);
		return [l[0], l[1].merge(n2.r)];
	} else {
		auto l = split(n2.r, k - n2.l.sz);
		return [n2.l.merge(l[0]), l[1]];
	}
}
 