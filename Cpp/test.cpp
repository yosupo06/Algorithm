#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

template<int N, int K, ll MOD>
struct CombinationsM {
    ll data[N][K];
    CombinationsM() {
        data[0][0] = 1;
        fill_n(&(data[0][1]), N-1, 0);
        for (int i = 1; i < N; i++) {
            data[i][0] = 1;
            for (int j = 1; j < K; j++) {
                data[i][j] = (data[i-1][j]+data[i-1][j-1]) % MOD;
            }
        }
    }
    ll* operator[](int n) {
        return data[n];
    }
    const ll* operator[](int n) const {
        return data[n];
    }
};

CombinationsM<20, 20, 100> c;

int main() {
    cout << c[19][2] << endl;
}