import std.stdio, std.conv;
import core.bitop;
import std.bitmanip;
import std.datetime;
import std.math;

int main() {
    float[] d = new float[](50000000);
    float[] dd = new float[](50000000);
    StopWatch sw;
    sw.start();
    foreach (i, _; d) {
        d[i] = cast(float)i;
        dd[i] = cast(float)(123.8-i);
        dd[i] *= 2.34;
        dd[i] = 15.4;
    }
    writeln(sw.peek().msecs);
    double sum = 0;
    foreach (i, _; d) {
        sum += d[i] / cast(float)15.4;//dd[i];
    }
    writeln(sum);
    writeln(sw.peek().msecs);
    foreach (i, _; d) {
//        sum += sqrt(d[i]) + sqrt(dd[i]);
    }
    writeln(sum);
    writeln(sw.peek().msecs);
    return 0;
}