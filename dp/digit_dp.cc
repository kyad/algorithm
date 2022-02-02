// https://atcoder.jp/contests/dp/tasks/dp_s

#include <iostream>
#include <vector>
using namespace std;

int main() {
  const int MOD = 1000000007;
  string K;
  cin >> K;
  int N = (int)K.size();
  int D;
  cin >> D;
  // Digit DP
  // dp[i][smaller][j]: 上からi桁目までの和をDで割った余りがjの倍数の個数
  // smaller=1はKのi桁目より小さい、smaller=0はKのi桁目と一致
  vector<vector<vector<long long> > > dp(N + 1, vector<vector<long long> >(2, vector<long long>(D, 0)));
  dp[0][0][0] = 1;
  for (int i = 0; i < N; i++) {
    int k = (int)(K[i]) - '0';
    for (int j = 0; j < D; j++) {
      for (int d = 0; d < 10; d++) {
        dp[i + 1][1][(j + d) % D] += dp[i][1][j];
        dp[i + 1][1][(j + d) % D] %= MOD;
      }
      for (int d = 0; d < k; d++) {
        dp[i + 1][1][(j + d) % D] += dp[i][0][j];
        dp[i + 1][1][(j + d) % D] %= MOD;
      }
      dp[i + 1][0][(j + k) % D] += dp[i][0][j];
      dp[i + 1][0][(j + k) % D] %= MOD;
    }
  }
  long long ans = (dp[N][0][0] + dp[N][1][0] - 1 + MOD) % MOD;
  cout << ans << endl;
  return 0;
}
