#include "Base.h"

#include <iostream>
int main() {
    cout << MPI << endl;
    cout << ccw(P(0,0), P(1,0), P(0,1)) << endl;
    cout << ccw(P(0,0), P(1,0), P(0,-1)) << endl;
    cout << ccw(P(0,0), P(1,0), P(-1,0)) << endl;
    cout << ccw(P(0,0), P(1,0), P(2,0)) << endl;
    cout << ccw(P(0,0), P(1,0), P(0.5,0)) << endl;

    cout << ccw(P(0,0), P(1,0), P(0,0)) << endl;
    cout << ccw(P(0,0), P(1,0), P(1,0)) << endl;
}