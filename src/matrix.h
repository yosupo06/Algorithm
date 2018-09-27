// Matrix type = VV<T>, Vector type = V<T>

template<class T>
V<T> operator+(const V<T> &l, const V<T> &r) {
    assert(l.size() == r.size());
    int N = int(l.size());
    V<T> res(N);
    for (int i = 0; i < N; i++) res[i] = l[i] + r[i];
    return res;
}

template<class T>
VV<T> operator+(const VV<T> &l, const VV<T> &r) {
    assert(l.size() == r.size());
    int N = int(l.size());
    VV<T> res(N);
    for (int i = 0; i < N; i++) res[i] = l[i] + r[i];
    return res;
}
