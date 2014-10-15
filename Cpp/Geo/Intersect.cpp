#include "Base.h"
#include "Intersect.h"

#include <iostream>
int main() {
    L a = L(P(0, 0), P(1, 1));
    L b = L(P(1.5, 1.5), P(0.6, 0.6));
    cout << insSS(a, b) << endl;
    cout << crossP(a, b) << endl;
    cout << distLP(a, P(0,1)) << endl;
    return 0;
}