// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1611&lang=jp
// https://drken1215.hatenablog.com/entry/2020/03/10/160500

#include <iostream>
#include <vector>
using namespace std;

int solve() {
  int n;
  cin >> n;
  if (n == 0) {
    return -1;
  }
  vector<int> w(n);
  for (int i = 0; i < n; i++) {
    cin >> w.at(i);
  }
  vector<vector<int> >dp(n, vector<int>(n + 1, -1));
  for (int i = 0; i < n; i++) {
    dp[i][i] = 0;
    if (i < n) {
      dp[i][i + 1] = 0;
    }
  }
  for (int width = 2; width <= n; width++) {
    for (int i = 0; i < n; i++) {
      int j = i + width;
      if (j <= n) {
        if (dp[i + 1][j - 1] == j - i - 2) {
          if (abs(w[i] - w[j - 1]) <= 1) {
            dp[i][j] = max(dp[i][j], j - i);
          } else {
            dp[i][j] = max(dp[i][j], j - i - 2);
          }
        }
        for (int k = i + 1; k < j; k++) {
          dp[i][j] = max(dp[i][j], dp[i][k] + dp[k][j]);
        }
      }
    }
  }
  cout << dp[0][n] << endl;
  return 0;
}

int main() {
  int ret;
  do {
    ret = solve();
  } while (ret >= 0);
  return 0;
}
