template <class T, class U>
ostream& operator<<(ostream& os, const pair<T, U>& p) {
    return os << "P(" << p.first << ", " << p.second << ")";
}

template <class T> ostream& operator<<(ostream& os, const V<T>& v) {
    os << "[";
    for (auto d : v) os << d << ", ";
    return os << "]";
}

ostream &operator<<(ostream &o, __int128_t x) {
    if (x == 0) return o << 0;
    if (x < 0) o << '-', x = -x;
    deque<int> ds;
    while (x) ds.push_front(x % 10), x /= 10;
    for (int d: ds) o << d;
    return o;
}
