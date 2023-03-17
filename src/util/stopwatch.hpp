struct StopWatch {
    bool f = false;
    clock_t st;
    void start() {
        f = true;
        st = clock();
    }
    int msecs() {
        assert(f);
        return int(1LL * (clock()-st)*1000 / CLOCKS_PER_SEC);
    }
};
