// https://atcoder.jp/contests/abc180/tasks/abc180_e
// https://drken1215.hatenablog.com/entry/2020/10/21/172509
// https://qiita.com/drken/items/7c6ff2aa4d8fce1c9361#11-bit-dp

#include <iostream>
#include <vector>
using namespace std;

const int INF = 17 * 1000000 + 1;

int main() {
  int N;
  cin >> N;
  vector<int> X(N), Y(N), Z(N);
  for (int n = 0; n < N; n++) {
    cin >> X.at(n) >> Y.at(n) >> Z.at(n);
  }
  vector<vector<int> > dist(N, vector<int>(N));
  for (int u = 0; u < N; u++) {
    for (int v = 0; v < N; v++) {
      dist[u][v] = abs(X.at(u) - X.at(v)) + abs(Y.at(u) - Y.at(v)) + max(0, Z.at(v) - Z.at(u));
    }
  }
  // Bit DP, TSP from node 0
  vector<vector<int> > dp(1 << N, vector<int>(N, INF));
  dp[1][0] = 0;
  for (int bit = 0; bit < (1 << N); bit++) {
    // u: nodes included in bit
    for (int u = 0; u < N; u++) {
      if (bit & (1 << u) == 0) {
        continue;
      }
      // nu: nodes not included in bit
      for (int nu = 0; nu < N; nu++) {
        if (bit & (1 << nu) == 1) {
          continue;
        }
        int nbit = bit | (1 << nu);
        dp[nbit][nu] = min(dp[nbit][nu], dp[bit][u] + dist[u][nu]);
      }
    }
  }
  int ans = INF;
  for (int v = 1; v < N; v++) {
    ans = min(ans, dp[(1 << N) - 1][v] + dist[v][0]);
  }
  cout << ans << endl;
  return 0;
}
