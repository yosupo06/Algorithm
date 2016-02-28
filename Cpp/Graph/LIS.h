// LISを求める
int lis(int n, int d[], int res[]) {
    int dp[n];
    int ans = -1;
    fill_n(dp, n, 1<<28);
    for (int i = 0; i < n; i++) {
        res[i] = lower_bound(dp, dp+n, d[i]) - dp;
        ans = max(ans, res[i]);
        dp[res[i]] = d[i];
    }
    return ans;
}
