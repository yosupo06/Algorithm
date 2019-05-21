ostream &operator<<(ostream &o, __int128_t x) {
    if (x == 0) return o << 0;
    if (x < 0) o << '-', x = -x;
    deque<int> ds;
    while (x) ds.push_front(x % 10), x /= 10;
    for (int d: ds) o << d;
    return o;
}
