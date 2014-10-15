//fast random number generator
unsigned long xor128(){ 
    static unsigned long x=123456789,y=362436069,z=521288629,w=88675123; 
    unsigned long t; 
    t=(x^(x<<11));x=y;y=z;z=w; return( w=(w^(w>>19))^(t^(t>>8)) ); 
}

//quick sort
template <class T>
void q_sort(T d[], int s, int e) {
    if (e - s <= 1) return;
    T p = d[xor128() % (e-s) + s];
    int l = s, r = e-1;
    while (true) {
        while (d[l] < p) l++;
        while (l < r && p <= d[r]) r--;
        if (l >= r) break;
        swap(&d[l], &d[r]);
    }
    q_sort(d, s, l);
    while (l < e && d[l] == p) l++;
    q_sort(d, l, e);
}