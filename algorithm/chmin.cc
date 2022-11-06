// https://atcoder.jp/contests/abc275/tasks/abc275_f

#include <iostream>
#include <vector>
using namespace std;

template<class T> void chmin(T& a, const T b) { a = min(a, b); }

int main() {
  int N, M;
  cin >> N >> M;
  vector<int> A(N + 1, 0);
  for (int n = 1; n <= N; n++) {
    cin >> A.at(n);
  }
  const int INF = 1e9+1;
  // iまで見て、iを取らない(j=0)/取る(j=1)時に、総和がkになる操作回数の最小値
  // 1<=i<=N, 1<=k<=M
  vector<vector<vector<int> > > dp(N + 1, vector<vector<int> > (2, vector<int>(M + 1, INF)));
  dp[0][1][0] = 0;
  //dp[1][0][0] = 1;
  //dp[1][1][A[1]] = 0;
  for (int i = 1; i <= N; i++) {
    for (int k = 0; k <= M; k++) {
      for (int pj = 0; pj < 2; pj++) {  // i-1のj
        // A[i]を取らない
        chmin(dp[i][0][k], dp[i - 1][pj][k] + pj);
        // A[i]を取る
        int pk = k - A[i];
        if (pk >= 0) {
          chmin(dp[i][1][k], dp[i - 1][pj][pk]);
        }
      }
    }
  }
  for (int x = 1; x <= M; x++) {
    int ans = min(dp[N][0][x], dp[N][1][x]);
    if (ans == INF) {
      ans = -1;
    }
    cout << ans << '\n';
  }
  return 0;
}
