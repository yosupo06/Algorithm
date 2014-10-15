#include <vector>
#include <iostream>
#include <set>
#include <cstdio>
#include <queue>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <cmath>
#include <complex>
#include <algorithm>
#include <tuple>
#include <algorithm>
#include <limits>
#include <map>

using namespace std;

typedef long long ll;
struct Pi {
    int x, y;
    Pi() {}
    Pi(int xx, int yy) {
        x = xx; y = yy;
    }
    bool operator<(Pi &r) {
        if (x != r.x) return x < r.x;
        return y < r.y;
    }
};
struct Ti {
    int x, y, z;
    Ti() {}
    Ti(int xx, int yy, int zz) {
        x = xx; y = yy; z = zz;
    }
    bool operator<(Ti &r) {
        if (x != r.x) return x < r.x;
        if (y != r.y) return y < r.y;
        return z < r.z;
    }
};
int main() {
    return 0;
}
