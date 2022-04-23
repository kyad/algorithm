// https://atcoder.jp/contests/dp/tasks/dp_x

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int N;
  cin >> N;
  vector<tuple<int, int, int> > wsv(N);
  for (int n = 0; n < N; n++) {
    cin >> get<0>(wsv.at(n))
        >> get<1>(wsv.at(n))
        >> get<2>(wsv.at(n));
  }
  // min(sa, sb - wa) > min(sb, sa - wb) ならばa < bとして小さい順にソート
  sort(wsv.begin(), wsv.end(), [](tuple<int, int, int> a, tuple<int, int, int> b) {
    int wa = get<0>(a);
    int wb = get<0>(b);
    int sa = get<1>(a);
    int sb = get<1>(b);
    return min(sa, sb - wa) > min(sb, sa - wb);
  });
  // dp[i][j]: i個目まで満た時の重さの合計jのときの価値の最大値
  vector<vector<long long> > dp(N + 1, vector<long long>(20001, -1));
  dp[0][0] = 0;
  for (int i = 0; i < N; i++) {
    int w = get<0>(wsv[i]);
    int s = get<1>(wsv[i]);
    int v = get<2>(wsv[i]);
    for (int j = 0; j <= 20000; j++) {
      if (dp[i][j] < 0) {
        continue;
      }
      // i個目を取らない
      dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
      // i個目を取る
      if (j > s) {
        continue;
      }
      int nj = j + w;
      if (nj > 20000) {
        continue;
      }
      dp[i + 1][nj] = max(dp[i + 1][nj], dp[i][j] + v);
    }
  }
  long long ans = -1;
  for (int j = 0; j <= 20000; j++) {
    ans = max(ans, dp[N][j]);
  }
  cout << ans << endl;
  return 0;
}
