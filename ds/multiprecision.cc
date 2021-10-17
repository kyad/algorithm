// https://atcoder.jp/contests/arc128/tasks/arc128_a
// TLE

#include <algorithm>
#include <iostream>
#include <vector>
#include <boost/rational.hpp>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std;
using namespace boost;

int main() {
  int N;
  cin >> N;
  vector<int> A(N + 1);
  for (int n = 1; n <= N; n++) {
    cin >> A.at(n);
  }
  // dp[0][]: gold
  // dp[1][]: silver
  vector<vector<rational<multiprecision::cpp_int> > > dp(2, vector<rational<multiprecision::cpp_int> >(N + 1));
  vector<vector<int> > memo(2, vector<int>(N + 1));
  dp[0][0] = 1;
  dp[1][0] = 0;
  for (int n = 1; n <= N; n++) {
    // gold
    rational<multiprecision::cpp_int> a, b;
    a = dp[0][n - 1];
    b = dp[1][n - 1] / A.at(n);
    memo[0][n] = b > a ? 1 : 0;
    dp[0][n] = max(a, b);
    // silver
    a = dp[1][n - 1];
    b = dp[0][n - 1] * A.at(n);
    memo[1][n] = b > a ? 1 : 0;
    dp[1][n] = max(a, b);
  }
  vector<int> ans;
  int k = 0;
  for (int n = N; n >= 1; n--) {
    ans.push_back(memo[k][n]);
    if (memo[k][n]) {
      k = 1 - k;
    }
  }
  reverse(ans.begin(), ans.end());
  for (int i = 0; i < ans.size(); i++) {
    cout << ans[i] << (i == ans.size() - 1 ? '\n' : ' ');
  }
  return 0;
}
