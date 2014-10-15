#include <iostream>
#include <vector>
#include <valarray>
using namespace std;
typedef long long ll;
struct SMatrix {
    typedef ll D;
    D d[10][10] = {};

    D* operator[](int p) {
        return d[p];
    }
    
    const D* operator[](int p) const {
        return d[p];
    }
    
    SMatrix& operator=(const SMatrix &other) {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                d[i][j] = other[i][j];
            }
        }
        return *this;
    }
    
    SMatrix operator*(const SMatrix &right) {
        SMatrix res;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                for (int k = 0; k < 10; k++) {
                    res[i][j] += d[i][k]*right[k][j];
                }
            }
        }
        return res;
    }
};

int main() {
    SMatrix r;
    double d[3][3] = {
        {1,2,5},
        {1,-1,1},
        {0,1,2}
    };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            r[i][j] = d[i][j];
        }
    }
    cout << r.inverse() << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%.3f  ", r[i][j]);
        }
        printf("\n");
    }
    return 0;
}