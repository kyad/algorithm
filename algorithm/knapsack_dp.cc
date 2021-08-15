// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_B&lang=ja
// https://qiita.com/drken/items/a5e6fe22863b7992efdb

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int N, W;
  cin >> N >> W;
  vector<int> v(N + 1);
  vector<int> w(N + 1);
  for (int n = 1; n <= N; n++) {
    cin >> v[n] >> w[n];
  }
  // Knapsack DP
  vector<vector<int> > dp(N + 1, vector<int>(W + 1));
  dp[0].assign(W + 1, 0);
  for (int n = 1; n <= N; n++) {
    for (int i = 0; i <= W; i++) {
      if (i - w[n] >= 0) {
        dp[n][i] = max(dp[n - 1][i], dp[n - 1][i - w[n]] + v[n]);
      } else {
        dp[n][i] = dp[n - 1][i];
      }
    }
  }
  cout << dp[N][W] << endl;  
  return 0;
}
