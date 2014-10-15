struct union_find{
    int rnk[MAX], par[MAX];
    
    union_find(int n){ for(int i = 0; i < n; i++) rnk[i] = 1, par[i] = i;}
    
    int find(int x){
        if(x == par[x]) return x;
        else return par[x] = find(par[x]);
    }
    void unite(int x, int y){
        x = find(x); y = find(y);
        if(x == y) return;
        if(rnk[x] > rnk[y]) par[y] = x;
        else{
            par[x] = y;
            if(rnk[x] == rnk[y]) rnk[y]++;
        }
    }
    bool same(int x, int y){
        x = find(x); y = find(y);
        return x == y;
    }
};
