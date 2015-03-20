struct T {
    P d[3];
    T() {}
    T(P x, P y, P z) {
        d[0] = x; d[1] = y; d[2] = z;
    }
};

typedef vector<P> Pol;

P cu(const Pol &p, int i) { 
    int s = p.size();
    return p[(i%s+s)%s];
};

//0:P is out 1:P is on line 2:P is in
int contains(const Pol &pol, P p) {
    int in = -1;
    for (int i = 0; i < (int)pol.size(); i++) {
        P a=cu(pol,i)-p, b=cu(pol,i+1)-p;
        if (ccw(a, b, P(0, 0)) == 0) return 1;
        if (imag(a) > imag(b)) swap(a, b);
        if (imag(a) <= 0 && 0 < imag(b)) {
            if (cross(a, b) < 0) in *= -1;
        }
    }
    return in+1;
}

R area(const Pol &p) {
    R u = 0;
    for (int i = 0; i < (int)pol.size(); i++) {
        u += cross(cu(pol,i), cu(pol,i+1));
    }
    return abs(u)/2;
}

/*
スパゲッティソースをパクった、直線の左側の多角形を返却する   
*/
Pol convex_cut(const Pol &p, const L &l) {
    Pol q;
    for (int i = 0; i < (int)p.size(); i++) {
        P a = cu(p, i), b = cu(p, i+1);
        if (ccw(l.x, l.y, a) != -1) q.push_back(a);
        if (insLS(l, L(a, b))) {
            //TODO
        }
    }
}

//true:Polygon is counter_cycle false:cycle
bool iscclock(const Pol &pol) {
    double th = 0;
    for (int i = 0; i < pol.size(); i++) {
        P a = cu(pol,i), b=cu(pol, i+1), c=cu(pol, i+2);
        th += deg2NorN(arg(c-b)-arg(b-a));
    }
    return (th > 0);
}


Pol convex(Pol p) {
    sort(p.begin(), p.end());
    if (p.size() <= 2) return p;
    Pol up;
    for (P d: p) {
        //if (up.size() > 1) printf("ccw%d\n",  ccw(up[up.size()-2], up[up.size()-1], d) );
        while (up.size() > 1 && ccw(up[up.size()-2], up[up.size()-1], d) > 0) {
        //    printf("pop\n");
            up.pop_back();
        }
        //printf("push\n");
        up.push_back(d);
    }
    reverse(up.begin(), up.end());
    Pol down;
    for (P d: p) {
        while (down.size() > 1 && ccw(down[down.size()-2], down[down.size()-1], d) < 0) down.pop_back();
        down.push_back(d);
    }
    //printf("%ld %ld\n", up.size(), down.size());
    down.insert(down.begin(), up.begin()+1, up.end()-1);
    return down;
}



