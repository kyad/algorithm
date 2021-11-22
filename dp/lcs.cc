// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_10_C&lang=ja
// Longest Common Subsequence (最長共通部分列)

#include <iostream>
#include <vector>
using namespace std;

int main() {
  int q;
  cin >> q;
  while (q--) {
    string X, Y;
    cin >> X >> Y;
    vector<vector<int> > dp(X.size() + 1, vector<int>(Y.size() + 1, 0));
    for (int x = 1; x <= X.size(); x++) {
      for (int y = 1; y <= Y.size(); y++) {
        dp[x][y] = max(dp[x - 1][y], dp[x][y - 1]);
        if (X[x - 1] == Y[y - 1]) {
          dp[x][y] = max(dp[x][y], dp[x - 1][y - 1] + 1);
        }
      }
    }
    cout << dp[X.size()][Y.size()] << endl;
  }
  return 0;
}
