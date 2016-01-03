namespace StopWatch {
    clock_t st;
    bool f = false;
    void start() {
        f = true;
        st = clock();
    }
    int msecs() {
        assert(f);
        return (clock()-st)*1000 / CLOCKS_PER_SEC;
    }
}
