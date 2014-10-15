#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

#include "FenwickTreeMod.h"
#include "FenwickRAddMod.h"

#include <iostream>
FenwickRAddMod<5, 1000> b;
int main () {
    ll d[] = {1,2,4,8,16};
    b.init(d);
    b.add(1,2);
    b.add(2,4);
    cout << b.sum(0) << endl;
    cout << b.sum(1) << endl;
    cout << b.sum(2) << endl;
    cout << b.sum(3) << endl;
    cout << b.sum(4) << endl;
    cout << b.sum(5) << endl;
    b.add(1, 3, 1);
    cout << b.sum(0) << endl;
    cout << b.sum(1) << endl;
    cout << b.sum(2) << endl;
    cout << b.sum(3) << endl;
    cout << b.sum(4) << endl;
    cout << b.sum(5) << endl;
    return 0;
}