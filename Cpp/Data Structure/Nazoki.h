template<ll N>
struct Nazoki {
    const ll bnum = 1LL<<(N/2);
    ll min = -1, max = -1;
    Nazoki<N-1> sum;
    Nazoki<N-1> data[bnum];
    ll high(ll u) {
        return u/bnum;
    }
    ll low(ll u) {
        return u%bnum;
    }
    void ins(ll u) {
        if (min == -1) {
            min = max = u;
            return;
        }
        if (min == max) {
            if (u < min) {
                min = u;
            } else {
                max = u;
            }
            return;
        }
        if (u < min) {
            swap(min, u);
        }
        if (max < u) {
            swap(u, max);
        }
        if (data[high(min)].min == -1) {
            sum.ins(high(u));
        }
        data[high(u)].ins(low(u));
    }

    void del(ll u) {
        if (min == max && min == u) {
            min = max = -1;
            return;
        }
        if (u == min) {
            ll h = sum.min;
            min = h*bnum+data[h].min;
            data[h].del(data[h].min);
            if (data[h].min == -1) {
                sum.del(h);
            }
            return;
        }
        if (u == max) {
            ll h = sum.max;
            max = h*bnum+data[h].max;
            data[h].del(data[h].max);
            if (data[h].max == -1) {
                sum.del(h);
            }
            return;
        }
    }
    bool exist(ll u) {
        if (u == min || u == max) return true;
        return data[high(u)].exist(low(u));
    }
}