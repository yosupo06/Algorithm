class Scanner {
	import std.stdio : File, readln;
	import std.conv : to;
	import std.range : front, popFront, array, ElementType;
	import std.array : split;
	import std.traits : isSomeString, isDynamicArray;
	import std.algorithm : map;
private:
	File f;
	this(File f) {
		this.f = f;
	}
	string[] buf;
	bool succ() {
		while (!buf.length) {
			if (f.eof) return false;
			buf = readln.split;
		}
		return true;
	}
public:
	int read(Args...)(auto ref Args args) {
		foreach (i, ref v; args) {
			if (!succ()) return i;
			alias VT = typeof(v);
			static if (!isSomeString!VT && isDynamicArray!VT) {
				v = buf.map!(to!(ElementType!VT)).array;
				buf.length = 0;
			} else {
				v = buf.front.to!VT;
				buf.popFront();
			}
		}
		return args.length;
	}
}
