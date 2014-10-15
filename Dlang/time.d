import std.stdio, std.range;
import std.datetime;

int main() {
	StopWatch sw;
	sw.start();
	int[] d = iota(100).array;
	int i = 30;
	foreach (u; d[i..$]) {
		writeln(u);
		i = 60;
	}
	writeln(sw.peek().msecs);
	return 0;
}
