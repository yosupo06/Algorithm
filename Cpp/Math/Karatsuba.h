/**
 * 多項式の乗算を高速で行う
 * N=2^nかつ64以上が必要
 * N=3000ぐらいがよいと思われ
 **/

namespace Karatsuba {
    template<class T>
    vector<T> naive_mul_64(const vector<T> &a, const vector<T> &b) {
        constexpr int n = 64;
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
        if (n <= (1<<6)) {
            return naive_mul_64(a, b);
        }
        int m = n/2;
        auto A = vector<T>(a.begin()+m, a.end());
        auto B = vector<T>(a.begin(), a.begin()+m);
        auto C = vector<T>(b.begin()+m, b.end());
        auto D = vector<T>(b.begin(), b.begin()+m);
        auto z2 = mul(B, D);
        auto z0 = mul(A, C);
        for (int i = 0; i < m; i++) {
            B[i] += A[i];
            D[i] += C[i];
        }
        auto z1 = mul(B, D);
        for (int i = 0; i < n-1; i++) {
            z1[i] -= (z0[i] + z2[i]);
        }
        auto res = vector<T>(2*n-1, 0);
        for (int i = 0; i < n-1; i++) {
            res[i] += z2[i];
            res[i+m] += z1[i];
            res[i+n] += z0[i];
        }
        return res;
    }
}