#include "src/base.h"
#include "src/util/fast_io.h"

int main() {
    Printer pr(stdout);
    pr.writeln("Hello");
    pr.writeln(string("World"));
}
