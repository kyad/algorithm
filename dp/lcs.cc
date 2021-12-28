// https://atcoder.jp/contests/dp/tasks/dp_f
// Longest Common Subsequence (最長共通部分列)

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// LCS
int main() {
  string s, t;
  cin >> s >> t;
  s.insert(s.begin(), ' ');
  t.insert(t.begin(), ' ');
  vector<vector<int> > dp(s.size(), vector<int>(t.size(), 0));
  for (size_t i = 1; i < s.size(); i++) {
    for (size_t j = 1; j < t.size(); j++) {
      dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
      if (s[i] == t[j]) {
        dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
      }
    }
  }
  int N = dp[s.size() - 1][t.size() - 1];
  int i = s.size() - 1;
  int j = t.size() - 1;
  string ans;
  for (int n = N; n >= 1; n--) {
    while (true) {
      if (i > 1 && dp[i - 1][j] == n) {
        i--;
      } else if (j > 1 && dp[i][j - 1] == n) {
        j--;
      } else {
        break;
      }
    }
    ans.push_back(s[i]);
    if (i > 1) {
      i--;
    }
    if (j > 1) {
      j--;
    }
  }
  reverse(ans.begin(), ans.end());
  cout << ans << endl;
  return 0;
}
