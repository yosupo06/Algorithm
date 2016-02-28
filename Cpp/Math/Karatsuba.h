/**
 * 多項式の乗算を高速で行う
 * N=2^nかつ64以上が必要
 * N=3000ぐらいがよいと思われ
 **/

namespace Karatsuba {
    template<class T>
    vector<T> naive_mul(const vector<T> &a, const vector<T> &b) {
        int n = (int)a.size();
        vector<T> res(2*n-1, 0);
        for (int i = 0; i < n; i++) {
            T aa = a[i];
            for (int j = 0; j < n; j++) {
                res[i+j] += aa*b[j];
            }
        }
        return res;
    }

    template<class T>
    vector<T> mul(const vector<T> &a, const vector<T> &b) {
        assert(a.size() == b.size());
        int n = (int)a.size();
        if (n <= 64) {
            return naive_mul(a, b);
        }
        int m = n/2, k = n-m;
        auto A = vector<T>(a.begin()+m, a.end());
        auto B = vector<T>(a.begin(), a.begin()+m);
        auto C = vector<T>(b.begin()+m, b.end());
        auto D = vector<T>(b.begin(), b.begin()+m);
        auto z2 = mul(B, D);
        auto z0 = mul(A, C);
        for (int i = 0; i < m; i++) {
            A[i] += B[i];
            C[i] += D[i];
        }
        auto z1 = mul(A, C);
        for (int i = 0; i < 2*m-1; i++) z1[i] -= z2[i];
        for (int i = 0; i < 2*k-1; i++) z1[i] -= z0[i];
        auto res = vector<T>(2*n-1, 0);
        for (int i = 0; i < 2*m-1; i++) res[i] += z2[i];
        for (int i = 0; i < 2*k-1; i++) res[i+m] += z1[i];
        for (int i = 0; i < 2*k-1; i++) res[i+2*m] += z0[i];
        return res;
    }
}

