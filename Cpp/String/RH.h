namespace Hull {
    ull B = TEN(9)+7, iB = 13499267949257065399ULL;
    vector<ull> powB{1}, powiB{1};
    struct H {
        static void expand(int N) {
            while (powB.size() <= N) {
                powB.push_back(powB.back()*B);
                powiB.push_back(powiB.back()*iB);
            }
        }
        ull d;
        static H make(int x) {return H{ull(x)};}
        H operator+(const H &r) const {return H{d+r.d};}
        H operator-(const H &r) const {return H{d-r.d};}
        H operator<<(int s) const {return H{d*powB[s]};}
        H operator>>(int s) const {return H{d*powiB[s]};}
        bool operator==(const H &r) const {return d==r.d;}
    };
}
namespace H2mod {
    using M0 = ModInt<TEN(9)+7>;
    using M1 = ModInt<TEN(9)+9>;
    vector<M0> powB0{1}, powiB0{1};
    vector<M1> powB1{1}, powiB1{1};
    M0 B0 = rand() % TEN(9) + 1, iB0 = M0::inv(B0);
    M1 B1 = rand() % TEN(9) + 1, iB1 = M1::inv(B1);
    struct H {
        static void expand(int N) {
            while (powB0.size() <= N) {
                powB0.push_back(powB0.back()*B0);
                powiB0.push_back(powiB0.back()*iB0);
                powB1.push_back(powB1.back()*B1);
                powiB1.push_back(powiB1.back()*iB1);
            }
        }
        M0 d0; M1 d1;
        static H make(int x) {return H{x, x};}
        H operator+(const H &r) const {return H{d0+r.d0, d1+r.d1};}
        H operator-(const H &r) const {return H{d0-r.d0, d1-r.d1};}
        H operator<<(int s) const {return H{d0*powB0[s], d1*powB1[s]};}
        H operator>>(int s) const {return H{d0*powiB0[s], d1*powiB1[s]};}
        bool operator==(const H &r) const {return (d0.v==r.d0.v && d1.v==r.d1.v);}
    };
}
template<class H>
struct HashStr {
    vector<H> v;
    string s;
    HashStr(string s) : s(s) {
        int N = (int)s.size();
        H::expand(N);
        v.resize(N+1);
        v[0] = H::make(0);
        for (int i = 1; i <= N; i++) {
            v[i] = v[i-1] + (H::make(s[i-1])<<(i-1));
        }
    }
    H get(int l, int r) {
        return (v[r]-v[l])>>l;
    }
};
