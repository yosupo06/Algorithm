//fast random number generator
unsigned long xor128(){ 
    static unsigned long x=123456789,y=362436069,z=521288629,w=88675123; 
    unsigned long t; 
    t=(x^(x<<11));x=y;y=z;z=w; return( w=(w^(w>>19))^(t^(t>>8)) ); 
}

//d[0]~d[k-1] are 1st~kth smallest elements
template <class T>
void nth_e(T d[], int s, int e, int k) {
    if (e - s <= 1) return;
    T p = d[xor128() % (e-s) + s];
    int l = s, r = e-1;
    while (true) {
        while (d[l] < p) l++;
        while (l < r && p <= d[r]) r--;
        if (l >= r) break;
        swap(d[l], d[r]);
    }
    if (k < (l - s)) {
        nth_e(d, s, l, k);
    } else {
        while (l < e && d[l] == p) l++;
        if ((l - s) < k) {
            nth_e(d, l, e, k - (l - s));
        }
    }
}