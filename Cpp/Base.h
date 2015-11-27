/**
 * Ubuntuコマンド
 * gsettings set org.gnome.desktop.interface gtk-key-theme Emacs
 * setxkbmap -option ctrl:nocaps
 **/

ll gcd(ll a, ll b) {
    if (b==0) return a;
    return gcd(b, a%b);
}

ll lcm(ll a, ll b) {
    return a/gcd(a, b)*b;
}

/// 高速累乗, x^nをO(logn)で求める
ll pow(ll x, ll n) {
    ll r = 1;
    while (n) {
        if (n & 1) r *= x;
        x *= x;
        n >>= 1;
    }
    return r;
}

/// x^n % md
ll pow_mod(ll x, ll n, ll md) {
	ll r = 1;
	while (n) {
		if (n & 1) r = (r * x) % md;
		x = (x * x) % md;
		n >>= 1;
	}
	return r;
}

/// xの逆元, mdは素数かつxはmdの倍数ではない必要がある
ll invp(ll x, ll md) {
	return pow_mod(x, md-2, md);
}

int bsr(uint n, int p = 31) {
    return (p == -1 || n & (1<<p)) ? p : static_bsr(n, p-1);
}

int static_ceil_log2(uint n) {
    return n == 0 ? -1 : 1+static_bsr(n-1);
}

//時間計測は闇が多いことに注意
//codeforcesで動作確認
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

/*AOJ用 stack sizeを拡張する*/
int main() {
#ifndef __APPLE__
    static ll eord, enew;
    const int sz = 32*1024*1024;
    static void *p = malloc(sz);
    enew = (long long)p + sz - 1;
    __asm__ volatile("mov %%rsp, %0" : "=r"(eord));
    __asm__ volatile("mov %0, %%rsp" : : "r"(enew));
#endif
    main2();
#ifndef __APPLE__
    __asm__ volatile("mov %0, %%rsp" : : "r"(eord));
#endif
    return 0;
}

