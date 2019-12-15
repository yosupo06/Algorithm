#include "base.h"
#include "util/fast_io.h"

int main() {
    Printer pr(stdout);
    pr.writeln("Hello");
    pr.writeln(string("World"));
}
