// https://atcoder.jp/contests/arc141/tasks/arc141_b

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// xをbase進数で見た時の桁数を返す
int digits(long long x, int base) { int d = 0; while (x > 0) { x /= base; d++; } return d; }

int main() {
  const int MOD = 998244353;
  long long N, M;
  cin >> N >> M;
  int d = digits(M, 2);
  if (N > d) {
    cout << 0 << endl;
    return 0;
  }
  // count[k]: 2進数で見た時に桁数kの個数 (1<=k<=d)
  vector<long long> count(d + 1, 0);
  for (int k = 1; k < d; k++) {
    count.at(k) = 1LL<<(k - 1);
    count.at(k) %= MOD;
  }
  count.at(d) = M - (1LL<<(d - 1)) + 1LL;
  count.at(d) %= MOD;
  // dp[i][j]: i(1<=i<=d)まで見てj(1<=j<=d)個取る時の組み合わせの数
  vector<vector<long long> > dp(d + 1, vector<long long>(d + 1, 0));
  dp[0][0] = 1LL;
  for (int i = 1; i <= d; i++) {
    for (int j = 0; j <= d; j++) {
      dp[i][j] = dp[i - 1][j];  // iを取らない
      if (j > 0) {
        dp[i][j] += dp[i - 1][j - 1] * count[i];  // iを取る
        dp[i][j] %= MOD;
      }
    }
  }
  cout << dp[d][N] << endl;
  return 0;
}
