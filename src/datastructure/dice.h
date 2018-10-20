/**
 * +x=0 +y=1 +z=2
 * d = [+x, +y, +z]
 * dir[4] = [+x, +y, -x, -y]
 * Dice(a, b): +x=a +y=bとなるサイコロ生成
 * get(dir): dir方向の値を取得
 * rot(dir): dir方向に転がす
 */
struct Dice {
    int d[3];
    Dice(int a, int b) {
        for (int i = 0; i < 3; i++) {
            d[i] = (a + i) % 3 + a / 3 * 3;
        }
        while (d[1] != b) rot(1);
    }
    int get(int dir) {
        if (dir < 2) {
            return d[dir];
        } else {
            dir -= 2;
            return 5 - d[dir];
        }
    }
    void rot(int dir) {
        int t = d[2];
        if (dir < 2) {
            d[2] = 5 - d[dir];
            d[dir] = t;
        } else {
            dir -= 2;
            d[2] = d[dir];
            d[dir] = 5 - t;
        }
    }
};
