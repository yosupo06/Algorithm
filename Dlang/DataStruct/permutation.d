import std.range, std.stdio;

struct Permutation {
	int N;
	int[] d;
	alias d this;

	this(int _N) {
		N = _N;
		d = iota(N).array;
	}

	Permutation opBinary(string op) (Permutation r)
		if (op == "*")
	{
		assert(N == r.N);
		auto tmp = Permutation(N);
		foreach (i; 0..N) {
			tmp[i] = r[d[i]];
		}
		return tmp;
	}
}

int main() {
	Permutation p = Permutation(10);
	Permutation q = Permutation(10);
	writeln(p);
	foreach (i; 0..10) {
		p[i] = (i+1)%10;
	}
	writeln(p);
	writeln(p*p*q);
	return 0;
}