#include "Base.h"
#include "Polygon.h"

#include <iostream>
int main() {
    Pol p1;
    cout << nptop(M2PI*100+1.2) << endl;
    cout << nptop(M2PI*-100-1.0) << endl;
    p1.push_back(P(0,0));
    p1.push_back(P(0,1));
    p1.push_back(P(1,1));
    p1.push_back(P(1,0));
    Pol p2 = p1; reverse(p2.begin(), p2.end());
    cout << iscclock(p1) << endl;
    cout << iscclock(p2) << endl;
    P p = P(0.5, 0.5);
    cout << contains(p1, p) << endl;
    return 0;
}