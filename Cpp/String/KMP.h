//sのkmpテーブルを構築する resは長さs.size()以上の配列へのポインタ
void kmp(string s, int res[]) {
    res[0] = -1;
    int j = -1;
    for (int i = 0; i < s.size() ; i++) {
        while (j >= 0 && s[i] != s[j]) j = res[j];
        j++;
        res[i+1] = j;
    }
}
