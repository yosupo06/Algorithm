#include "Base.h"
#include "Intersect.h"
#include "Circle.h"
#include <iostream>
int main() {
    C c1 = C(P(0,0),1);
    C c2 = C(P(2,0),3.1);
    L l = L(P(-10,-sqrt(2)/2),P(10,-sqrt(2)/2));
    L r;
    cout << crossP(c1,l,r) << endl;
    cout << r.x << r.y << endl;
    cout << crossP(c1, c2, l) << endl;
    cout << l.x << l.y << endl; 
    return 0;
}