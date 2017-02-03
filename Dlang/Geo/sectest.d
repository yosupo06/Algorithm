import std.stdio, std.complex;

//smallest enclosing circle
class SmallestEnclosingCircle {
	alias P = Complex!(double);
	double r;
	P x;
	this(P[] p, int time) {
		x = (0);
		double dif = 1;
		foreach (i; 0..time+1) {
			P li;
			r = 0;
			foreach (y; p) {
				double l = abs(y-x);
				if (l > r) {
					li = y;
					r = l;
				}
			}
			x += (li-x)*dif;
			dif /= 2;
		}
	}
}

int main() {
	Complex!(double)[] c = [complex(1,1), complex(2,2)];
	auto sec = new SmallestEnclosingCircle(c, 30);
	sec.init(c, 20);
	writeln(sec.x);
	return 0;
}