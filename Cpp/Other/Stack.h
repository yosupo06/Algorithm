// stack sizeを拡張する 64bit用
int main() {
    static ll eord, enew;
    const int sz = 256*1024*1024;
    static unsigned char *p = (unsigned char*)malloc(sz);
    enew = ((ll)(p+sz-1) & ~0xff);
    __asm__ volatile("mov %%rsp, %0" : "=r"(eord));
    __asm__ volatile("mov %0, %%rsp" : : "r"(enew));
    main2();
    __asm__ volatile("mov %0, %%rsp" : : "r"(eord));
    return 0;
}
